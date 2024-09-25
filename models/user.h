#ifndef USER_H
#define USER_H

#include "basemodel.h"
#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRecord>

class User : public BaseModel {
public:
    QString email;
    QString firstName;
    QString lastName;
    QString profilePhoto;
    bool isActive;

    User();
    // Constructor to initialize User from a QSqlQuery
    User(const QSqlQuery &query);
    QString fullName() const;
};

#endif // USER_H
