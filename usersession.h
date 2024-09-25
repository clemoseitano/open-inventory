#ifndef USERSESSION_H
#define USERSESSION_H

#include <QObject>
#include "user.h"

class UserSession : public QObject
{
    Q_OBJECT

public:
    // Singleton instance accessor
    static UserSession& instance() {
        static UserSession instance;
        return instance;
    }

    // Delete copy constructor and assignment operator
    UserSession(UserSession const&) = delete;
    void operator=(UserSession const&) = delete;

    void setUser(User user) { this->user = user; }
    User getUser() { return user; }

signals:
    void userChanged(User newUser);

private:
    // Private constructor to enforce singleton pattern
    UserSession() : user() {} // Initialize with a default invalid userId

    User user;
};

#endif // USERSESSION_H
