#include "createproductdialog.h"
#include "ui_createproductdialog.h"

CreateProductDialog::CreateProductDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateProductDialog)
{
    ui->setupUi(this);
}

CreateProductDialog::~CreateProductDialog()
{
    delete ui;
}

void CreateProductDialog::onSaveCategoryButtonClicked()
{

}
