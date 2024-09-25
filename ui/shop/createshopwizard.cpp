#include "createshopwizard.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QFileDialog>
#include "basemodel.h"
#include "../usersession.h"
#include "user.h"
#include "ui_createshopwizard.h"

CreateShopWizard::CreateShopWizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::CreateShopWizard)
{
    ui->setupUi(this);
}

CreateShopWizard::~CreateShopWizard()
{
    delete ui;
}

void CreateShopWizard::onCreateShopWizardAccepted()
{
    User user = UserSession::instance().getUser();

    if (!user.fromDb) {
        QMessageBox::warning(this, "User Error", "Failed to retrieve user details. Log in again.");
        this->close();
    }
    qint64 userId = user.id;
    QString locationName = ui->locationNameLineEdit->text();
    QString locationAddress = ui->addressLineEdit->text();
    QString locationLatitude = ui->latitudeLineEdit->text();
    QString locationLongitude = ui->longitudeLineEdit->text();
    QString locationContact = ui->contactLineEdit->text();

    QString image = ui->imageLineEdit->text();
    QString shopName = ui->shopNameLineEdit->text();
    QString website = ui->websiteLineEdit->text();

    if (locationName.isEmpty() || locationContact.isEmpty() || locationAddress.isEmpty() || shopName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Location name, address, contact and shop name fields are required.");
        return;
    }

    QSqlQuery query;
    query.prepare(
        "INSERT INTO userlocation (id, created_at, updated_at, address, latitude, longitude, name, mobile_phone, user_id) "
        "VALUES (:id, :created_at, :updated_at, :address, :latitude, :longitude, :name, :mobile_phone, :user_id)");
    qint64 locationId = BaseModel().generateId();

    query.bindValue(":id", locationId);
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":updated_at", QDateTime::currentDateTime());
    query.bindValue(":address", locationAddress);
    query.bindValue(":latitude", locationLatitude);
    query.bindValue(":longitude", locationLongitude);
    query.bindValue(":name", locationName);
    query.bindValue(":mobile_phone", locationContact);
    query.bindValue(":user_id", userId);

    // Execute the query and handle any potential errors
    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to insert location: " + query.lastError().text());
        return;
    }

    query.prepare("INSERT INTO shop (id, created_at, updated_at, image, link, name, location_id, owner_id) "
                  "VALUES (:id, :created_at, :updated_at, :image, :link, :name, :location_id, :owner_id)");

    query.bindValue(":id", BaseModel().generateId());
    query.bindValue(":created_at", QDateTime::currentDateTime());
    query.bindValue(":updated_at", QDateTime::currentDateTime());
    query.bindValue(":image", image);
    query.bindValue(":link", website);
    query.bindValue(":name", shopName);
    query.bindValue(":location_id", locationId);
    query.bindValue(":owner_id", userId);

    if (!query.exec()) {
        qDebug() << "Error inserting into shop table:" << query.lastError().text();
        return;
    }
    // If the insertion is successful
    QMessageBox::information(this, "Creation Success", "The shop has been successfully added.");
    this->close();
}

void CreateShopWizard::onSelectImagePushButtonClicked()
{
    // Open a file dialog to select an image file
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("Select Image"), // Dialog title
        "",                 // Initial directory (empty means default)
        tr("Image Files (*.png *.jpg *.jpeg);;All Files (*)") // File types filter
        );

    if (!fileName.isEmpty()) {
        // If the user selected a file, set it to the relevant UI element or process it
        ui->imageLineEdit->setText(fileName); // Assuming you have a QLineEdit to display the file path

        // Optionally, output the selected file name for debugging purposes
        qDebug() << "Selected image file:" << fileName;
    } else {
        // Optionally handle the case where no file was selected
        qDebug() << "No image file selected.";
    }
}

