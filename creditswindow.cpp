#include "creditswindow.h"
#include "ui_creditswindow.h"

CreditsWindow::CreditsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Wykorzystane materiały");
    QPixmap background(":/img/Assets/backgroundOknoStartowe.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    this->setFixedSize(500, 440);
}

CreditsWindow::~CreditsWindow()
{
    delete ui;
}

void CreditsWindow::on_pushButton_clicked()
{
    this->done(Accepted);
}

