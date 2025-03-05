#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shop.h"
#include "product.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onShopSelected(Shop *shop);

private:
    Ui::MainWindow *ui;
    Shop *selectedShop;
    QList<Shop> m_shops;
    QList<Product> m_products;
    void fetchAllShops();
    void fetchAllProductsForShop();

protected:
    void showEvent(QShowEvent *event);
};
#endif // MAINWINDOW_H
