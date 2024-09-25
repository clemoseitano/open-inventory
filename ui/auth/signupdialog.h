#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>

namespace Ui {
class SignupDialog;
}

class SignupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDialog(QWidget *parent = nullptr);
    ~SignupDialog();

private slots:
    void onSignupClicked();
    void openLoginDialog();

private:
    Ui::SignupDialog *ui;
};

#endif // SIGNUPDIALOG_H
