#include "treeviewinputdialog.h"
#include "ui_treeviewinputdialog.h"
#include <QDebug>

TreeviewInputDialog::TreeviewInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeviewInputDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_current_index_changed(int)));
}


void TreeviewInputDialog::on_current_index_changed(int index)
{
    qDebug() << "index change " << index;
    ui->stackedWidget->setCurrentIndex(index);
}

TreeviewInputDialog::~TreeviewInputDialog()
{
    delete ui;
}

QString TreeviewInputDialog::get_key()
{
    return ui->lineEdit->text();
}

QVariant TreeviewInputDialog::get_value()
{
    if(ui->comboBox->currentIndex() == 0)
    {
        return ui->lineEdit_2->text();
    }
    else if(ui->comboBox->currentIndex() == 1)
    {
        return ui->doubleSpinBox->value();
    }
    else if(ui->comboBox->currentData() == 2)
    {
        return ui->checkBox->isChecked();
    }
    else
    {
        return "";
    }
}
