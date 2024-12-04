#include "editdelegate.h"
#include <QLineEdit>
#include <QTreeView>
#include <QStandardItemModel>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QCheckBox>

EditDelegate::EditDelegate(QStandardItemModel *model, QObject *parent)
    :m_model(model), QItemDelegate(parent)
{

}

EditDelegate::~EditDelegate()
{

}

QWidget * EditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    qDebug() << qobject_cast<QTreeView *>(parent);

    qDebug() << m_model->itemFromIndex(index)->data();

    auto data = m_model->itemFromIndex(index)->data();

    QWidget *edit = nullptr;
    if(data.type() == QVariant::Double)
    {
        auto edit_tmp = new QDoubleSpinBox(parent);
        edit_tmp->setValue(data.toDouble());
        edit = edit_tmp;
    }
    else if(data.type() == QVariant::Bool)
    {
        auto edit_tmp = new QCheckBox(parent);
        if(data.toBool())
        {
            edit_tmp->setCheckState(Qt::CheckState::Checked);
        }
        else
        {
            edit_tmp->setCheckState(Qt::CheckState::Unchecked);
        }
        edit = edit_tmp;
    }
    else
    {
        auto edit_tmp = new QLineEdit(parent);
        edit_tmp->setText(data.toString());
        edit = edit_tmp;
    }

    //auto item = qobject_cast<QStandardItemModel *>(qobject_cast<QTreeView *>(parent)->model())->itemFromIndex(index);
    //qDebug() << item;
    return edit;
}

void EditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    return;
}

void EditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

    auto data = m_model->itemFromIndex(index)->data();
    if(data.type() == QVariant::Double)
    {
        QDoubleSpinBox *spin_edit = qobject_cast<QDoubleSpinBox *>(editor);
        model->setData(index, spin_edit->value(), Qt::UserRole + 1);
        model->setData(index, spin_edit->value(), Qt::DisplayRole);
    }
    else if(data.type() == QVariant::Bool)
    {
        QCheckBox *check_edit = qobject_cast<QCheckBox *>(editor);
        model->setData(index, check_edit->isChecked(), Qt::UserRole + 1);
        model->setData(index, check_edit->isChecked(), Qt::DisplayRole);
    }
    else
    {
        QLineEdit *lin_edit = qobject_cast<QLineEdit *>(editor);
        model->setData(index, lin_edit->text(), Qt::UserRole + 1);
        model->setData(index, lin_edit->text(), Qt::DisplayRole);
    }
}

void EditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
