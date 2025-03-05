#include "emptystatewidget.h"
#include "ui_emptystatewidget.h"

EmptyStateWidget::EmptyStateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmptyStateWidget)
{
    ui->setupUi(this);
}

void EmptyStateWidget::onAddProductPushButtonClicked()
{

}

EmptyStateWidget::~EmptyStateWidget()
{
    delete ui;
}
