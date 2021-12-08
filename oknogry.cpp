#include "oknogry.h"
#include "ui_oknogry.h"

OknoGry::OknoGry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OknoGry)
{
    ui->setupUi(this);
    this->setWindowTitle("Węże i drabiny. Tura 1.");

    this->plansza = new Plansza(true, this);
    ui->viewPlansza->setScene(plansza);

}

OknoGry::~OknoGry()
{
    delete ui;
}

void OknoGry::przygotuj(int liczba, QStringList nazwy, long ziarno, QList<QGraphicsPixmapItem *> tekstury) //dodac jakis cel tym teksturom
{
    this->liczbaGraczy = liczba;
    this->nazwyGraczy = nazwy;
    this->ziarnoGeneratora = ziarno;
    plansza->generujPlansze(ziarnoGeneratora);
    switch (liczbaGraczy) {
        case 4:
            ui->player4Label->setText(nazwyGraczy.at(3));
            ui->player4Score->setText("1");
        case 3:
            ui->player3Label->setText(nazwyGraczy.at(2));
            ui->player3Score->setText("1");
        case 2:
            ui->player2Label->setText(nazwyGraczy.at(1));
            ui->player2Score->setText("1");
        case 1:
            ui->player1Label->setText(nazwyGraczy.at(0));
            ui->player1Score->setText("1");
            break;
        default:
            qDebug() << "Wystapil blad w instrukcji switch case.";
    }
    ui->labelZiarno->setText("Obecne ziarno generatora: " + QString::number(ziarnoGeneratora));
}

void OknoGry::on_pushButton_2_clicked()
{
    this->done(Rejected);
}

