#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include "basemodel.h"

class ShopManager : public BaseModel {
public:
    qint64 shopId;  // Foreign key to Shop
    qint64 userId;  // Foreign key to User

    QString toString() const;
};

#endif // SHOPMANAGER_H
