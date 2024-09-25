#ifndef SHOP_H
#define SHOP_H

#include "basemodel.h"
#include <QString>

class Shop : public BaseModel {
public:
    Shop(qint64 id, QString name, QString link, QString image, qint64 ownerId, qint64 locationId);
    ~Shop();
    QString image;
    QString link;
    QString name;
    qint64 ownerId;  // Foreign key to User
    qint64 locationId;  // Foreign key to UserLocation

    QString toString() const;
};

#endif // SHOP_H
