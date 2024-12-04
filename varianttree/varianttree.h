#ifndef __VARIANTTREE_H__
#define __VARIANTTREE_H__

#include <QVariant>
#include <QStandardItem>

QVariant loadJson(const QString &fileName);

void saveJson(const QVariant variant, const QString &fileName);

void convertStandItemToVariant(const QStandardItem *item, QVariant &variant);

void convertVariantToStandardItem(const QVariant& variant, QString key, QStandardItem *item);

void standarditem_add_item(QStandardItem *parent, const QString key, const QVariant &value);

#endif
