#ifndef CREDITSWINDOW_H
#define CREDITSWINDOW_H

#include <QDialog>

namespace Ui {
class CreditsWindow;
}

class CreditsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreditsWindow(QWidget *parent = nullptr);
    ~CreditsWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreditsWindow *ui;
};

#endif // CREDITSWINDOW_H
