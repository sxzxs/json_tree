#ifndef EDITDELEGATE_H
#define EDITDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QStandardItemModel>

class EditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    EditDelegate(QStandardItemModel *model, QObject *parent = nullptr);
    ~EditDelegate();

    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
    QStandardItemModel *m_model;
};

#endif // EDITDELEGATE_H
