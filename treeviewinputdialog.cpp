#include "treeviewinputdialog.h"
#include "ui_treeviewinputdialog.h"

TreeviewInputDialog::TreeviewInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TreeviewInputDialog)
{
    ui->setupUi(this);
}

TreeviewInputDialog::~TreeviewInputDialog()
{
    delete ui;
}

QString TreeviewInputDialog::get_key()
{
    return ui->lineEdit->text();
}
QString TreeviewInputDialog::get_value()
{
    return ui->lineEdit_2->text();
}
