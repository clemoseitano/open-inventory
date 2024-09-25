#ifndef PRODUCT_H
#define PRODUCT_H

#include "basemodel.h"
#include <QString>

class Product : public BaseModel {
public:
    QString name;
    QString description;
    QString code;
    int price;
    int quantity;
    QString size;
    bool archived;
    qint64 shopId;  // Foreign key to Shop
    qint64 categoryId;  // Foreign key to Category
    qint64 subcategoryId;  // Foreign key to SubCategory

    QString toString() const;
};

#endif // PRODUCT_H
