#ifndef PRODUCTIMAGE_H
#define PRODUCTIMAGE_H

#include "basemodel.h"
#include <QString>

class ProductImage : public BaseModel {
public:
    QString imageFile;
    qint64 productId;  // Foreign key to Product

    QString toString() const;
};

#endif // PRODUCTIMAGE_H
