#ifndef TREEVIEWINPUTDIALOG_H
#define TREEVIEWINPUTDIALOG_H

#include <QDialog>
#include <QVariant>

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
    QVariant get_value();

public slots:
    void on_current_index_changed(int index);

private:
    QString m_key;
    QString m_value;
    Ui::TreeviewInputDialog *ui;
};

#endif // TREEVIEWINPUTDIALOG_H
