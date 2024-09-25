#include "logindialog.h"
#include "signupdialog.h"
#include "../usersession.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLoginClicked()
{
    QString usernameOrEmail = ui->usernameEmailLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (usernameOrEmail.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(),
                                                         QCryptographicHash::Sha256);

    QSqlQuery query;
    query.prepare("SELECT password, id FROM user WHERE (username = :username OR email = :email)");
    query.bindValue(":username", usernameOrEmail);
    query.bindValue(":email", usernameOrEmail);

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        qDebug() << "Executed Query: " << query.lastQuery();
        qDebug() << "Bound Values: " << query.boundValues();
        QMessageBox::warning(this, "Login Error", "Invalid username/email or password. 1");
        return;
    } else {
        qDebug() << "Query succeeded.";
    }

    if (query.next()) {
        QString password = query.value(0).toString();
        qDebug() << "Password:" << password;
    } else {
        qDebug() << "No matching records found.";
    }


    QString storedHashedPassword = query.value(0).toString();

    if (storedHashedPassword != hashedPassword.toHex()) {
        QMessageBox::warning(this, "Login Error", "Invalid username/email or password.");
        return;
    }
    qint64 userId = query.value(1).toLongLong();
    query.prepare("SELECT * FROM user WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec() && query.next()) {
        // Initialize a User object from the query result
        User user(query);

        // Set the userId in the singleton
        UserSession::instance().setUser(user);

        // Optionally emit a signal if you want to notify other parts of the application
        emit UserSession::instance().userChanged(user);

        // Proceed with closing the login window or navigating to the main window
        this->close();
        QMessageBox::information(this, "Login Success", "Welcome back, " + user.firstName + "!");
        this->accept();
    } else {
        qDebug() << "Failed to retrieve user: " << query.lastError().text();
        QMessageBox::warning(this, "Login Error", "Failed to retrieve user details.");
    }
}

void LoginDialog::openSignupDialog() {
    this->close();
    SignupDialog signupDialog(this);
    signupDialog.exec();  // Open the dialog modal
}
