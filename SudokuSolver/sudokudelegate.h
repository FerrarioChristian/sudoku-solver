#ifndef SUDOKUDELEGATE_H
#define SUDOKUDELEGATE_H

#include <QItemDelegate>

class SudokuDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit SudokuDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;


private:
    bool isValidMove(const QAbstractItemModel *model, const QModelIndex &index, int value) const;
};

#endif // SUDOKUDELEGATE_H
