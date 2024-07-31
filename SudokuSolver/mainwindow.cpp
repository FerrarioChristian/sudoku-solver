#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudokudelegate.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentStep(-1)
    , solveTimer(new QTimer(this))
{
    ui->setupUi(this);
    setWindowTitle("Sudoku Solver");

    table = ui->table;
    model = new QStandardItemModel(9, 9, this);


    connect(ui->solveButton, &QPushButton::clicked, this, &MainWindow::solveSudoku);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetGrid);
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::previousStep);
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::nextStep);
    connect(ui->autoSolveButton, &QPushButton::clicked, this, &MainWindow::startAutoSolve);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::stopAutoSolve);
    connect(solveTimer, &QTimer::timeout, this, &MainWindow::showNextStep);

    ui->backButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->autoSolveButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);


    for (int row = 0; row < 9; ++row) {
        for (int column = 0; column < 9; ++column) {
            QStandardItem *item = new QStandardItem();
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, column, item);
        }
    }

    table->setModel(model);
    SudokuDelegate *delegate = new SudokuDelegate(this);
    table->setItemDelegate(delegate);

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::isValid(int row, int col, int num)
{
    // Verifica nella riga
    for (int x = 0; x < 9; ++x) {
        if (model->data(model->index(row, x)).toInt() == num)
            return false;
    }

    // Verifica nella colonna
    for (int x = 0; x < 9; ++x) {
        if (model->data(model->index(x, col)).toInt() == num)
            return false;
    }

    // Verifica nel blocco 3x3
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (model->data(model->index(i, j)).toInt() == num)
                return false;
        }
    }

    return true;
}

bool MainWindow::findEmptyCell(int &row, int &col)
{
    for (row = 0; row < 9; ++row) {
        for (col = 0; col < 9; ++col) {
            if (model->data(model->index(row, col)).toInt() == 0) {
                return true;
            }
        }
    }
    return false;
}

bool MainWindow::solveSudokuAlgorithm(int &row, int &col) {
    if (!findEmptyCell(row, col)) {
        return true;
    }
    for (int num = 1; num <= 9; ++num) {
        if (isValid(row, col, num)) {
            model->setData(model->index(row, col), num, Qt::EditRole);
            saveCurrentStep();

            int nextRow = row;
            int nextCol = col;
            if (solveSudokuAlgorithm(nextRow, nextCol)) {
                return true;
            }

            model->setData(model->index(row, col), 0, Qt::EditRole); // Backtrack
            saveCurrentStep();
        }
    }

    return false;
}


void MainWindow::solveSudoku() {
    ui->solveButton->setDisabled(true);
    solutionSteps.clear();
    currentStep = -1;

    int row = 0, col = 0;
    if (solveSudokuAlgorithm(row, col)) {
        QMessageBox::information(this, "Successo", "Il Sudoku è stato risolto!");
        ui->backButton->setDisabled(false);
        ui->nextButton->setDisabled(false);
        ui->autoSolveButton->setDisabled(false);
        ui->pauseButton->setDisabled(false);
        ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    } else {
        QMessageBox::warning(this, "Errore", "Non esiste una soluzione per questo Sudoku!");
    }
}

void MainWindow::saveCurrentStep()
{
    QVector<int> step;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            step.append(model->data(model->index(row, col)).toInt());
        }
    }
    solutionSteps.append(step);
}

void MainWindow::displayStep(int step)
{
    if (step < 0 || step >= solutionSteps.size())
        return;

    int index = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if(solutionSteps[step][index] != 0) {
                model->setData(model->index(row, col), solutionSteps[step][index], Qt::EditRole);
                index++;
            } else {
                QStandardItem *item = new QStandardItem();
                item->setTextAlignment(Qt::AlignCenter);
                model->setItem(row, col, item);
            }
        }
    }
}

void MainWindow::nextStep()
{
    stopAutoSolve();
    if (currentStep < solutionSteps.size() - 1) {
        currentStep++;
        displayStep(currentStep);
    }
}

void MainWindow::previousStep()
{
    stopAutoSolve();
    if (currentStep > 0) {
        currentStep--;
        displayStep(currentStep);
    }
}

void MainWindow::startAutoSolve()
{
    if(ui->autoSolveButton->isChecked()) {
        solveTimer->start(250);
    } else {
        stopAutoSolve();
    }

}

void MainWindow::stopAutoSolve()
{
    solveTimer->stop();
    ui->autoSolveButton->setChecked(false);
}

void MainWindow::showNextStep()
{
    if (currentStep < solutionSteps.size() - 1) {
        currentStep++;
        displayStep(currentStep);
    } else {
        stopAutoSolve();
    }
}

void MainWindow::resetGrid() {
    model->clear();
    solutionSteps.clear();
    currentStep = -1;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            QStandardItem *item = new QStandardItem();
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(row, col, item);
        }
    }
    ui->backButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->autoSolveButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->solveButton->setDisabled(false);
    ui->table->setEditTriggers(QAbstractItemView::AnyKeyPressed);
}


