#ifndef ORDERITEM_H
#define ORDERITEM_H

#include "basemodel.h"

class OrderItem : public BaseModel {
public:
    qint64 productId;  // Foreign key to Product
    qint64 orderId;  // Foreign key to Order
};

#endif // ORDERITEM_H
