#ifndef SALE_H
#define SALE_H

#include "basemodel.h"
#include <QString>

class Sale : public BaseModel {
public:
    QString customerName;
    QString customerContact;
    int price;
    int quantity;
    qint64 productId;  // Foreign key to Product
    qint64 shopId;  // Foreign key to Shop
    qint64 userId;  // Foreign key to User

    QString toString() const;
};

#endif // SALE_H
