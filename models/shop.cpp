#include "shop.h"
#include "basemodel.h"
#include <QString>

QString Shop::toString() const {
    return name;
}

Shop::Shop(qint64 id, QString name, QString link, QString image, qint64 ownerId, qint64 locationId ):BaseModel(id),
    name(name),link(link),image(image),ownerId(ownerId),locationId(locationId){}

Shop::~Shop(){}
