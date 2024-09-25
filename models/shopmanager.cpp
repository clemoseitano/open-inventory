#include "shopmanager.h"

QString ShopManager::toString() const {
    return QString("User %1 manages Shop %2").arg(userId).arg(shopId);
}
