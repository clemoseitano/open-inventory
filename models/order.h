#ifndef ORDER_H
#define ORDER_H

#include "basemodel.h"
#include <QString>

class Order : public BaseModel {
public:
    QString displayName;
    double cost;
    int status;
    qint64 deliveryLocationId;  // Foreign key to UserLocation
    qint64 userId;  // Foreign key to User
};

#endif // ORDER_H
