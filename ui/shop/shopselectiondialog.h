#ifndef SHOPSELECTIONDIALOG_H
#define SHOPSELECTIONDIALOG_H

#include <QDialog>
#include <QList>
#include "shop.h"

namespace Ui {
class ShopSelectionDialog;
}

class ShopSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopSelectionDialog(QList<Shop>& shops, QWidget *parent = nullptr);
    ~ShopSelectionDialog();

signals:
    void shopSelected(Shop *shop);  // Signal to emit when a shop is selected


private slots:
    void onCreateShopPushButtonClicked();

    void onShopsTableViewDoubleClicked(const QModelIndex &index);

private:
    Ui::ShopSelectionDialog *ui;
    void populateShopTable(const QList<Shop>& shops);
    QList<Shop>& m_shops;
};

#endif // SHOPSELECTIONDIALOG_H
