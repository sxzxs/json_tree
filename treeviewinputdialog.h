#ifndef TREEVIEWINPUTDIALOG_H
#define TREEVIEWINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class TreeviewInputDialog;
}

class TreeviewInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TreeviewInputDialog(QWidget *parent = nullptr);
    ~TreeviewInputDialog();

    QString get_key();
    QString get_value();

private:
    QString m_key;
    QString m_value;
    Ui::TreeviewInputDialog *ui;
};

#endif // TREEVIEWINPUTDIALOG_H
