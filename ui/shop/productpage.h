#ifndef PRODUCTPAGE_H
#define PRODUCTPAGE_H

#include <QWidget>

namespace Ui {
class ProductPage;
}

class ProductPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProductPage(QWidget *parent = nullptr);
    ~ProductPage();

private:
    Ui::ProductPage *ui;
};

#endif // PRODUCTPAGE_H
