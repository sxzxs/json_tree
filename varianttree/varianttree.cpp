#include "varianttree.h"

#include <QStandardItemModel>
#include <QJsonDocument>
#include <QFile>

QVariant loadJson(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    return QJsonDocument::fromJson(file.readAll()).toVariant();
}

void saveJson(const QVariant variant, const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument::fromVariant(variant).toJson());
}

void convertStandItemToVariant(const QStandardItem *item, QVariant &variant)
{
    if (item == nullptr)
    {
        return;
    }

    if (item->hasChildren())
    {
        if(item->rowCount() > 0)
        {
            QString keyStr = item->child(0)->text();
            if (keyStr.startsWith("[") && keyStr.endsWith("]"))
            {
                QVariantList childList = QVariantList();
                for (int i = 0; i < item->rowCount(); ++i)
                {
                    QVariant childVariant;
                    convertStandItemToVariant(item->child(i), childVariant);
                    childList.append(childVariant);
                }
                variant = childList;
            }
            else
            {
                QVariantMap childMap = QVariantMap();
                for(int i = 0; i < item->rowCount(); i++)
                {
                    QVariant childVariant;
                    convertStandItemToVariant(item->child(i), childVariant);
                    childMap[item->child(i)->text()] = childVariant;
                }
                variant = childMap;
            }
        }
    }
    else
    {
        QStandardItem *parentItem = item->parent();
        int currentRow = item->row();
        //variant = parentItem->child(currentRow, 1)->text();
        variant = parentItem->child(currentRow, 1)->data();
    }
}

void convertVariantToStandardItem(const QVariant& variant, QString key, QStandardItem *item)
{
    if (variant.type() == QVariant::Map)
    {
        QStandardItem* mapItem = new QStandardItem(key);
        item->appendRow(mapItem);
        QVariantMap map = variant.toMap();
        QMapIterator<QString, QVariant> it(map);
        while (it.hasNext())
        {
            it.next();
            convertVariantToStandardItem(it.value(), it.key(), mapItem);
        }
    }
    else if (variant.type() == QVariant::List)
    {
        QVariantList list = variant.toList();
        QStandardItem* listItem = new QStandardItem(key);
        item->appendRow(listItem);
        for (int i = 0; i < list.size(); ++i)
        {
            QString indexKey = QString("[%1]").arg(i);
            convertVariantToStandardItem(list[i], indexKey, listItem);
        }
    }
    else
    {
        QList<QStandardItem*> items;
        QStandardItem* colum_key = new QStandardItem(key);
        QStandardItem* colum_value = new QStandardItem(variant.toString());
        colum_value->setData(variant);
        if(variant.type() == QVariant::String)
        {
            colum_value->setIcon(QIcon(":/varianttree/resources/text.png"));
        }
        else if(variant.type() == QVariant::Bool)
        {
            colum_value->setIcon(QIcon(":/varianttree/resources/check.png"));
        }
        else
        {
            colum_value->setIcon(QIcon(":/varianttree/resources/number.png"));
        }
        items.append(colum_key);
        items.append(colum_value);
        item->appendRow(items);
    }
    return;
}

void standarditem_add_item(QStandardItem *parent, const QString key, const QVariant &value)
{
    QList<QStandardItem*> items;
    QStandardItem* colum_key = new QStandardItem(key);
    QStandardItem* colum_value = new QStandardItem(value.toString());
    colum_value->setData(value);
    if(value.type() == QVariant::String)
    {
        colum_value->setIcon(QIcon(":/varianttree/resources/text.png"));
    }
    else if(value.type() == QVariant::Bool)
    {
        colum_value->setIcon(QIcon(":/varianttree/resources/check.png"));
    }
    else
    {
        colum_value->setIcon(QIcon(":/varianttree/resources/number.png"));
    }
    items.append(colum_key);
    items.append(colum_value);
    parent->appendRow(items);
}
