#ifndef CATEGORY_H
#define CATEGORY_H

#include "basemodel.h"
#include <QString>

class Category : public BaseModel {
public:
    QString image;
    QString name;
    qint64 shopId;  // Foreign key to Shop

    QString toString() const;
};

#endif // CATEGORY_H
