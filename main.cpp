#include <QApplication>
#include <QSqlDatabase>
#include "ui/auth/logindialog.h"
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set up and initialize the database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("app_data.sqlite3");
    if (!db.open()) {
        qDebug() << "Failed to open database!";
        return -1;
    }

    initializeDatabase(db);
    if (!db.open()) {
        qCritical() << "Failed to connect to the database.";
        return -1;
    }

    // Create and display the login dialog
    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        // If login is successful, show the main window
        MainWindow mainWindow;
        mainWindow.show();
        return app.exec();
    } else {
        // If login fails, exit the application
        return 0;
    }
}
