#ifndef CREATEPRODUCTDIALOG_H
#define CREATEPRODUCTDIALOG_H

#include <QDialog>

namespace Ui {
class CreateProductDialog;
}

class CreateProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProductDialog(QWidget *parent = nullptr);
    ~CreateProductDialog();

private slots:
    void onSaveCategoryButtonClicked();

private:
    Ui::CreateProductDialog *ui;
};

#endif // CREATEPRODUCTDIALOG_H
