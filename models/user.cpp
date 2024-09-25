#include "user.h"
#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlRecord>

User::User() : isActive(true) {}

QString User::fullName() const {
    return firstName + " " + lastName;
}

// Constructor to initialize a User instance from a QSqlQuery result
User::User(const QSqlQuery &query)
    : BaseModel(query.value("id").toLongLong()),
    email(query.value("email").toString()),
    isActive(query.value("is_active").toBool()),
    firstName(query.value("first_name").toString()),
    lastName(query.value("last_name").toString())
{
    this->fromDb=true;
}
