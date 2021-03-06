#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //kwestie graficzne
    this->setWindowTitle("Weże i Drabiny");
    QPixmap background(":/img/Assets/backgroundOknoStartowe.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
    this->setFixedSize(800, 600);

    //przygotowanie wszystkich okien
    oknoW = new CreditsWindow;
    oknoWyboru = new oknoWyboruGraczy;
    oknoG = new OknoGry;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnGraj_clicked()
{

    QObject::connect(oknoWyboru, &oknoWyboruGraczy::przygotuj, oknoG, &OknoGry::przygotuj);

    this->hide();

    int wybor = oknoWyboru->exec();
    if (wybor == QDialog::Accepted) {
        oknoG->exec();
    }
    this->show();
}

void MainWindow::on_btnWykorzystane_clicked()
{
    this->hide();
    oknoW->exec();
    this->show();
}


void MainWindow::on_btnWyjdz_clicked()
{
    QCoreApplication::quit();
}




