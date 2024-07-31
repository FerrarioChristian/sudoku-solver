#include "sudokudelegate.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

SudokuDelegate::SudokuDelegate(QObject *parent)
    : QItemDelegate(parent)
{
}

QWidget *SudokuDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setAlignment(Qt::AlignCenter);
    QIntValidator *validator = new QIntValidator(1, 9, editor);
    editor->setValidator(validator);
    return editor;
}

void SudokuDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(value);


}

void SudokuDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = lineEdit->text();
    if(isValidMove(model,index, value.toInt()))
        model->setData(index, value, Qt::EditRole);
    else
        QMessageBox::warning(editor, "Errore", "Questo input non rispetta le regole");


}


bool SudokuDelegate::isValidMove(const QAbstractItemModel *model, const QModelIndex &index, int value) const
{
    int row = index.row();
    int col = index.column();

    // Controlla se il valore è già presente nella riga
    for (int c = 0; c < 9; ++c)
    {
        if (model->data(model->index(row, c)).toInt() == value)
        {
            return false;
        }
    }

    // Controlla se il valore è già presente nella colonna
    for (int r = 0; r < 9; ++r)
    {
        if (model->data(model->index(r, col)).toInt() == value)
        {
            return false;
        }
    }

    // Controlla se il valore è già presente nella sottogriglia 3x3
    int startRow = row - (row % 3);
    int startCol = col - (col % 3);
    for (int r = startRow; r < startRow + 3; ++r)
    {
        for (int c = startCol; c < startCol + 3; ++c)
        {
            if (model->data(model->index(r, c)).toInt() == value)
            {
                return false;
            }
        }
    }

    qInfo("true");
    return true;
}
