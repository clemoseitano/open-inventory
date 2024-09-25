#include "shopitem.h"

ShopItem::ShopItem(const std::vector<Shop>& shops, QObject *parent)
    : QAbstractItemModel(parent), m_shops(shops)
{
}

QVariant ShopItem::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Image");
        case 1:
            return QString("Link");
        case 2:
            return QString("Name");
        case 3:
            return QString("Owner ID");
        case 4:
            return QString("Location ID");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

QModelIndex ShopItem::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid() && row >= 0 && row < m_shops.size() && column >= 0 && column < 5) {
        return createIndex(row, column);
    }
    return QModelIndex();
}

QModelIndex ShopItem::parent(const QModelIndex &index) const
{
    return QModelIndex();  // This is a flat list, so no parent-child relationship
}

int ShopItem::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return m_shops.size();
    }
    return 0;
}

int ShopItem::columnCount(const QModelIndex &parent) const
{
    return 5; // Image, Link, Name, Owner ID, Location ID
}

QVariant ShopItem::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        const Shop &shop = m_shops.at(index.row());
        switch (index.column()) {
        case 0:
            return shop.image;
        case 1:
            return shop.link;
        case 2:
            return shop.name;
        case 3:
            return shop.ownerId;
        case 4:
            return shop.locationId;
        default:
            return QVariant();
        }
    }
    return QVariant();
}
