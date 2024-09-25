#ifndef USERLOCATION_H
#define USERLOCATION_H

#include "basemodel.h"
#include <QString>

class UserLocation : public BaseModel {
public:
    QString address;
    double latitude;
    double longitude;
    QString name;
    QString mobilePhone;
    qint64 userId;  // Foreign key to User

    QString toString() const;
};

#endif // USERLOCATION_H
