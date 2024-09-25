#include "emptystatewidget.h"
#include "ui_emptystatewidget.h"

EmptyStateWidget::EmptyStateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmptyStateWidget)
{
    ui->setupUi(this);
}

EmptyStateWidget::~EmptyStateWidget()
{
    delete ui;
}
