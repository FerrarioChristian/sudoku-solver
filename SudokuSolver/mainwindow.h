#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QItemDelegate>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void solveSudoku();
    void resetGrid();
    void nextStep();
    void previousStep();

    void startAutoSolve();
    void stopAutoSolve();
    void showNextStep();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    QTableView *table;

    QVector<QVector<int>> solutionSteps;
    int currentStep;
    QTimer *solveTimer;

    bool isValid(int row, int col, int num);
    bool findEmptyCell(int &row, int &col);
    bool solveSudokuAlgorithm(int &row, int &col);

    void saveCurrentStep();
    void displayStep(int step);
};


#endif // MAINWINDOW_H
