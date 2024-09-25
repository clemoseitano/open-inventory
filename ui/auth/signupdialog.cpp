#include "signupdialog.h"
#include "logindialog.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include "user.h"
#include "ui_signupdialog.h"

SignupDialog::SignupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignupDialog)
{
    ui->setupUi(this);
    connect(ui->signupButton, &QPushButton::clicked, this, &SignupDialog::onSignupClicked);
}

SignupDialog::~SignupDialog()
{
    delete ui;
}

void SignupDialog::onSignupClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if (username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Input Error", "Passwords do not match.");
        return;
    }

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(),
                                                         QCryptographicHash::Sha256);

    QSqlQuery query;
    query.prepare(
        "INSERT INTO user (id, username, email, password, is_superuser, is_staff, is_active, date_joined, created_at, updated_at, first_name, last_name) "
        "VALUES (:id, :username, :email, :password, :is_superuser, :is_staff, :is_active, :date_joined, :created_at, :updated_at, :first_name, :last_name)");

    query.bindValue(":id", User().generateId());
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", hashedPassword.toHex());
    query.bindValue(":is_superuser", false);
    query.bindValue(":is_staff", false);
    query.bindValue(":is_active", true);
    query.bindValue(":date_joined", QDateTime::currentDateTime());
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":updated_at", QDateTime::currentDateTime());
    query.bindValue(":first_name", "");
    query.bindValue(":last_name", "");

    if (!query.exec()) {
        if (query.lastError().text().contains("UNIQUE constraint failed")) {
            QMessageBox::warning(this, "Registration Error", "Username or email already exists.");
        } else {
            QMessageBox::warning(this,
                                 "Database Error",
                                 "Failed to register: " + query.lastError().text());
        }
        return;
    }


    QMessageBox::information(this, "Registration Success", "You have successfully signed up.");
    this->close();
}


void SignupDialog::openLoginDialog() {
    this->close();
    LoginDialog loginDialog(this);
    loginDialog.exec();
}
