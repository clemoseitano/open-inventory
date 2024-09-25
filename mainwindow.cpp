#include "mainwindow.h"
#include "ui/shop/createshopwizard.h"
#include "ui/shop/shopselectiondialog.h"
#include "./ui_mainwindow.h"
#include "shop.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QList>
#include <QShowEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_shops(QList<Shop>())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    m_shops.clear();
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    // Call fetchAllShops after the window is shown
    fetchAllShops();

    if (m_shops.length() == 0) {
        CreateShopWizard wizard(this);  // Create the wizard instance
        if (wizard.exec() == QDialog::Accepted) {
            // Handle the case where the wizard completes successfully
            fetchAllShops();  // Optionally refresh the shop list
        }
    } else {
        // Show the ShopSelectionDialog when shops are available
        ShopSelectionDialog shopDialog(m_shops, this);
        // Connect the signal from ShopSelectionDialog to the slot in MainWindow
        connect(&shopDialog, &ShopSelectionDialog::shopSelected,
                this, &MainWindow::onShopSelected);
        shopDialog.exec();  // Show the dialog modally
    }
}

void MainWindow::fetchAllShops()
{
    QSqlQuery query;

    // Prepare the SQL query to fetch all items from the shop table
    query.prepare("SELECT * FROM shop");

    // Clear the existing shops list
    m_shops.clear();

    // Execute the query
    if (query.exec()) {
        while (query.next()) {
            // Fetch each column from the current row
            int id = query.value("id").toInt();
            QString image = query.value("image").toString();
            QString link = query.value("link").toString();
            QString name = query.value("name").toString();
            qint64 ownerId = query.value("owner_id").toLongLong();
            qint64 locationId = query.value("location_id").toLongLong();

            // Create the Shop object and append it to the list
            Shop shop = Shop(id, name, link, image, ownerId, locationId);
            m_shops.append(shop);

            // Output or use the fetched data
            qDebug() << "Shop ID:" << id
                     << "Image:" << image
                     << "Link:" << link
                     << "Name:" << name
                     << "Owner ID:" << ownerId
                     << "Location ID:" << locationId;
        }
    } else {
        // Handle query execution error
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}


void MainWindow::onShopSelected(Shop *shop)
{
    // Handle the selected shop here
    qDebug() << "Selected shop:" << shop->name << "with ID:" << shop->id;

    // You can now take any further actions, like updating the UI or storing the selected shop
}
