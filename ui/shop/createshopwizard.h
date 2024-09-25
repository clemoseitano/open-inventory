#ifndef CREATESHOPWIZARD_H
#define CREATESHOPWIZARD_H

#include <QWizard>

namespace Ui {
class CreateShopWizard;
}

class CreateShopWizard : public QWizard
{
    Q_OBJECT

public:
    explicit CreateShopWizard(QWidget *parent = nullptr);
    ~CreateShopWizard();

private slots:
    void onCreateShopWizardAccepted();

    void onSelectImagePushButtonClicked();

private:
    Ui::CreateShopWizard *ui;
};

#endif // CREATESHOPWIZARD_H
