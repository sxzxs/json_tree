#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QVariant>
#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QFile>
#include <QHeaderView>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "varianttree/editdelegate.h"
#include "varianttree/varianttree.h"
#include "varianttree/treeviewinputdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 创建一个示例QVariantMap
    QVariantMap variantMap;
    variantMap["Name"] = "John";
    variantMap["Age"] = 30;

    QVariantMap address;
    address["Street"] = "123 Main St";
    address["City"] = "Anytown";
    address["State"] = "CA";
    variantMap["Address"] = address;

    QVariantList hobbies;
    hobbies.append("Reading");
    hobbies.append("Swimming");
    variantMap["Hobbies"] = hobbies;

    model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList() << "Path" << "Value"); // 设置表头

    QStandardItem* rootItem = model->invisibleRootItem();
    qDebug() << QCoreApplication::applicationDirPath();

    // 选在文件

    QString file_name = QFileDialog::getOpenFileName(this, "选择JSON文件", "", "JSON Files (*.json)");
    if (!file_name.isEmpty())
    {
        qDebug() << "选择的文件路径: " << file_name;
    }
    else
    {
          int ret = QMessageBox::warning(this, tr("My Application"),
                                 tr("The document has been modified.\n"
                                    "Do you want to save your changes?"),
                                 QMessageBox::Save | QMessageBox::Discard
                                 | QMessageBox::Cancel,
                                 QMessageBox::Save);
          QCoreApplication::exit();
          return;
    }
    qDebug() << file_name;
    auto dir =QDir(file_name);
    m_json_dir = dir;

    QVariant mp = loadJson(dir.path());
    convertVariantToStandardItem(mp, "root", rootItem);
    QModelIndex index = model->index(0, 0);
    qDebug() << model->rowCount();
    qDebug() << model->columnCount();
    qDebug() << model->item(0, 0)->text();
    qDebug() << model->item(0, 0)->child(0, 0)->child(0, 0)->child(0, 0)->text();
    QList<QStandardItem *> list;
    QStandardItem *a = new QStandardItem("abcd");
    list.append(a);
    model->item(0, 0)->child(0, 0)->child(0, 0)->child(0, 1)->appendRow(list);

    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->setModel(model);
    m_edit_dele = new EditDelegate(model, this);
    ui->treeView->setItemDelegate(m_edit_dele);
    QVariant vr;
    qDebug() << vr;

    QObject::connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(on_loadjson_clicked()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(on_savejson_clicked()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_addchild_clicked()));
    QObject::connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(on_delete_clicked()));

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &MainWindow::show_treeview_context_menue);
    QObject::connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::on_item_clicked);

    statusBar()->showMessage("Ready", 10000);
}
void MainWindow::on_item_clicked(const QModelIndex &index)
{
    qDebug() << index;
    qDebug() << model->itemFromIndex(index)->data();
    qDebug() << index.row() << " " << index.column();
    auto my_index = index;
    QString path("");

    while(my_index.isValid())
    {
        qDebug() << my_index.row() << " " << my_index.data();
        path = my_index.data().toString() + tr("/") + path;
        my_index = my_index.parent();
    }
    statusBar()->showMessage("path: " + path);
}

void MainWindow::show_treeview_context_menue(const QPoint &pos)
{
    QPoint globalPos = mapToGlobal(pos);

    // 创建菜单
    QMenu contextMenu;
    QAction *action1 = contextMenu.addAction("Action 1");
    QAction *action2 = contextMenu.addAction("Action 2");
    contextMenu.addSeparator();
    QAction *action3 = contextMenu.addAction("Action 3");

    QFile style_file(":/qdarkstyle/style.qss");
    if(style_file.open(QFile::ReadOnly))
    {
        QString style = style_file.readAll();
        contextMenu.setStyleSheet(style);
        qDebug() << "set style ok";
    }

    // 显示菜单并获取用户选择
    QAction *selectedAction = contextMenu.exec(globalPos);
    if (selectedAction == action1) {
        qDebug() << "Action 1 triggered";
    } else if (selectedAction == action2) {
        qDebug() << "Action 2 triggered";
    } else if (selectedAction == action3) {
        qDebug() << "Action 3 triggered";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadjson_clicked()
{
    QVariant mp = loadJson(m_json_dir.path());
    auto root = model->invisibleRootItem();
    root->removeRow(0);
    convertVariantToStandardItem(mp, "root", root);
    qDebug() << mp;
}

void MainWindow::on_savejson_clicked()
{
    qDebug() << "save json clicked";

    QStandardItem* rootItem = model->invisibleRootItem();
    auto item = rootItem->child(0);

    QVariant vr;
    convertStandItemToVariant(item, vr);
    saveJson(vr, m_json_dir.path());
}

void MainWindow::on_addchild_clicked()
{
    qDebug() << "ok";
    auto indexs = ui->treeView->selectionModel()->selectedIndexes();
    if(!indexs.isEmpty())
    {
        qDebug() << indexs.first();
        qDebug() << model->itemFromIndex(indexs.first())->text();

        TreeviewInputDialog *input_dialog = new TreeviewInputDialog(this);
        if(input_dialog->exec() == QDialog::Rejected)
        {
            return;
        }

        standarditem_add_item(model->itemFromIndex(indexs.first()), input_dialog->get_key(), input_dialog->get_value());
    }
}

void MainWindow::on_delete_clicked()
{
    qDebug() << "delete";
    auto indexs = ui->treeView->selectionModel()->selectedIndexes();
    if(!indexs.isEmpty())
    {
        qDebug() << indexs.first();
        qDebug() << model->itemFromIndex(indexs.first())->text();

        model->itemFromIndex(indexs.first())->parent()->removeRow(indexs.first().row());
    }
}
