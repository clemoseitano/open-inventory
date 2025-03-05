#ifndef EMPTYSTATEWIDGET_H
#define EMPTYSTATEWIDGET_H

#include <QWidget>

namespace Ui {
class EmptyStateWidget;
}

class EmptyStateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmptyStateWidget(QWidget *parent = nullptr);
    ~EmptyStateWidget();

private slots:
    void onAddProductPushButtonClicked();

private:
    Ui::EmptyStateWidget *ui;
};

#endif // EMPTYSTATEWIDGET_H
