#include "shopselectiondialog.h"
#include "ui_shopselectiondialog.h"
#include <QStandardItemModel>

ShopSelectionDialog::ShopSelectionDialog(QList<Shop>& shops, QWidget *parent) :
    QDialog(parent), m_shops(shops),
    ui(new Ui::ShopSelectionDialog)
{
    ui->setupUi(this);

    // Populate the table view with the shops
    populateShopTable(m_shops);
}

ShopSelectionDialog::~ShopSelectionDialog()
{
    delete ui;
}

void ShopSelectionDialog::onCreateShopPushButtonClicked()
{
    this->close();
    // Logic to create a new shop
}

void ShopSelectionDialog::onShopsTableViewDoubleClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        int row = index.row();
        if (row >= 0 && row < m_shops.size()) {
            // Emit the selected shop using the shopSelected signal
            Shop *selectedShop = &m_shops[row];  // Obtain a pointer to the Shop object

            emit shopSelected(selectedShop);  // Emit the signal with a pointer
        }
    }

    this->close();  // Close the dialog after selecting a shop
}

void ShopSelectionDialog::populateShopTable(const QList<Shop>& shops)
{
    // Example of populating a QTableView or QListView with the shops
    // Assuming you are using a QTableView and want to display shops in it

    QStandardItemModel *model = new QStandardItemModel(shops.size(), 3, this);  // Assuming 3 columns for shop data
    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Name");
    model->setHeaderData(2, Qt::Horizontal, "Link");

    for (int row = 0; row < shops.size(); ++row) {
        const Shop& shop = shops[row];
        model->setData(model->index(row, 0), shop.id);
        model->setData(model->index(row, 1), shop.name);
        model->setData(model->index(row, 2), shop.link);
    }

    ui->shopsTableView->setModel(model);  // Set the model for the table view
}
