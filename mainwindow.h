#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDir>
#include "varianttree/editdelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

public slots:
    void on_savejson_clicked();
    void on_loadjson_clicked();
    void on_addchild_clicked();
    void on_delete_clicked();
    void show_treeview_context_menue(const QPoint &pos);
    void on_item_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel* model;
    QDir m_json_dir;

    EditDelegate *m_edit_dele;
};
#endif // MAINWINDOW_H
