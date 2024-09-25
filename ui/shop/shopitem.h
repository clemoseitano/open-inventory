#ifndef SHOPITEM_H
#define SHOPITEM_H

#include <QAbstractItemModel>
#include "shop.h"
#include <vector>

class ShopItem : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ShopItem(const std::vector<Shop>& shops, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<Shop> m_shops;
};

#endif // SHOPITEM_H
