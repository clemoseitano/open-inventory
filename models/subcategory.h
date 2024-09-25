#ifndef SUBCATEGORY_H
#define SUBCATEGORY_H

#include "basemodel.h"
#include <QString>

class SubCategory : public BaseModel {
public:
    QString name;
    qint64 categoryId;  // Foreign key to Category

    QString toString() const;
};

#endif // SUBCATEGORY_H
