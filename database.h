#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void initializeDatabase(QSqlDatabase &db) {
    // Ensure the migrations table exists
    QSqlQuery query(db);
    if (!query.exec("CREATE TABLE IF NOT EXISTS migrations ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT UNIQUE NOT NULL, "
                    "applied_at DATETIME DEFAULT CURRENT_TIMESTAMP)")) {
        qDebug() << "Failed to create migrations table:" << query.lastError();
        return;
    }

    // Check if the migration has already been applied
    QString migrationName = "0001_initial.sql";
    query.prepare("SELECT COUNT(*) FROM migrations WHERE name = :name");
    query.bindValue(":name", migrationName);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to check migration status:" << query.lastError();
        return;
    }

    if (query.value(0).toInt() > 0) {
        qDebug() << "Migration" << migrationName << "has already been applied.";
        return;  // Migration already applied, skip execution
    }

    // Apply the migration
    QFile file(":/sql/" + migrationName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open SQL file." << file.fileName();
        return;
    }

    QTextStream in(&file);
    QString sql = in.readAll();
    file.close();

    // Split the SQL script into individual statements
    QStringList sqlStatements = sql.split(';', Qt::SkipEmptyParts);

    foreach(
    const QString &statement, sqlStatements) {
        if (!statement.trimmed().isEmpty()) {  // Ignore empty statements
            if (!query.exec(statement.trimmed())) {
                qDebug() << "Failed to execute SQL statement:" << statement << query.lastError();
                return;
            }
        }
    }

    // Record the migration as applied
    query.prepare("INSERT INTO migrations (name) VALUES (:name)");
    query.bindValue(":name", migrationName);
    if (!query.exec()) {
        qDebug() << "Failed to record migration:" << query.lastError();
    }
}

#endif // DATABASE_H
