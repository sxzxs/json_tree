#include "mainwindow.h"

#include <QApplication>
#include <QTreeView>
#include <QJsonDocument>
#include <QFile>
#include <QHeaderView>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFile style_file(":/qdarkstyle/style.qss");
    if(style_file.open(QFile::ReadOnly))
    {
        QString style = style_file.readAll();
        w.setStyleSheet(style);
        qDebug() << "set style ok";
    }
    return a.exec();
}
