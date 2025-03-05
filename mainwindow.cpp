#include "mainwindow.h"
#include "ui/shop/createshopwizard.h"
#include "ui/shop/shopselectiondialog.h"
#include "./ui_mainwindow.h"
#include "shop.h"
#include "product.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QList>
#include <QShowEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_shops(QList<Shop>()), m_products(QList<Product>()), selectedShop(nullptr)
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
        CreateShopWizard wizard(this);
        if (wizard.exec() == QDialog::Accepted) {
            fetchAllShops();
        }
    } else {
        // Show the ShopSelectionDialog when shops are available
        ShopSelectionDialog shopDialog(m_shops, this);
        // Connect the signal from ShopSelectionDialog to the slot in MainWindow
        connect(&shopDialog, &ShopSelectionDialog::shopSelected,
                this, &MainWindow::onShopSelected);
        shopDialog.exec();
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
        }
    } else {
        // Handle query execution error
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

void MainWindow::fetchAllProductsForShop()
{
    if (selectedShop == nullptr) {
        qDebug() << "No shop selected.";
        return;
    }

    QSqlQuery query;

    // Prepare the SQL query to fetch all products from the selected shop
    query.prepare("SELECT * FROM product WHERE shop_id = :shop_id");
    query.bindValue(":shop_id", selectedShop->id);

    // Clear the existing products list
    m_products.clear();

    // Execute the query
    if (query.exec()) {
        while (query.next()) {
            Product product;

            product.id = query.value("id").toLongLong();
            product.name = query.value("name").toString();
            product.description = query.value("description").toString();
            product.code = query.value("code").toString();
            product.price = query.value("price").toInt();
            product.quantity = query.value("quantity").toInt();
            product.size = query.value("size").toString();
            product.archived = query.value("archived").toBool();
            product.shopId = query.value("shop_id").toLongLong();
            product.categoryId = query.value("category_id").toLongLong();
            product.subcategoryId = query.value("subcategory_id").toLongLong();
            product.createdAt = query.value("created_at").toDateTime();
            product.updatedAt = query.value("updated_at").toDateTime();

            m_products.append(product);
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}


void MainWindow::onShopSelected(Shop *shop)
{
    selectedShop = shop;
    qDebug() << "Selected shop:" << shop->name << "with ID:" << shop->id;
    fetchAllProductsForShop();
    // TODO: if products are not available show empty state widget
    if (m_products.isEmpty()) {
        // No products available; show the empty state page
        ui->stackedWidget->setCurrentIndex(0); // or ui->stackedWidget->setCurrentWidget(ui->emptyState);
    } else {
        // Products are available; show the product page
        ui->stackedWidget->setCurrentIndex(1); // or ui->stackedWidget->setCurrentWidget(ui->productPage);

        // Update the product page with the list of products
        // ui->productPage->setProducts(m_products);
    }
}
