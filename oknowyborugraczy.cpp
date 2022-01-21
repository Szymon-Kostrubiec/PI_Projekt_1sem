#include "oknowyborugraczy.h"
#include "ui_oknowyborugraczy.h"

oknoWyboruGraczy::oknoWyboruGraczy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oknoWyboruGraczy)
{
    //kwestie graficzne
    ui->setupUi(this);
    this->setWindowTitle("Wybierz graczy");
    this->setFixedSize(1000, 700);
    QPixmap background(":/img/Assets/backgroundOknoStartowe.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
    //animacje
    aniBtnGraj = new QPropertyAnimation(ui->btnGraj, "geometry");
    aniBtnGraj->setKeyValueAt(0, QRectF(600, 570, 340, 90));
    aniBtnGraj->setKeyValueAt(0.5f, QRectF(620, 590, 300, 50));
    aniBtnGraj->setKeyValueAt(1, QRectF(600, 570, 340, 90));

    aniBtnStworz = new QPropertyAnimation(ui->btnNowaPlansza, "geometry");
    aniBtnStworz->setKeyValueAt(0, QRectF(600, 520, 340, 50));
    aniBtnStworz->setKeyValueAt(0.5f, QRectF(620, 540, 300, 10));
    aniBtnStworz->setKeyValueAt(1, QRectF(600, 520, 340, 50));
    //zmienne programowe
    ostatnieZiarno = 0l;
    liczbaGraczy = 0;
    for (int i = 0; i < 4; i++) {
        oknaZGraczami.append(new WyswietlanieGraczy(i));
    }
    ui->viewGracz1->setScene(oknaZGraczami.at(0));
    ui->viewGracz2->setScene(oknaZGraczami.at(1));
    ui->viewGracz3->setScene(oknaZGraczami.at(2));
    ui->viewGracz4->setScene(oknaZGraczami.at(3));

    plansza = new Plansza(false, this);
    {
        int ziarno = QRandomGenerator::global()->generate();
        plansza->generujPlansze(ziarno);
        ui->ziarnoGeneratora->setText(QString::number(ziarno));
    }
    ui->viewPlansza->setScene(plansza);
}

oknoWyboruGraczy::~oknoWyboruGraczy()
{
    delete ui;
    delete plansza;
}

void oknoWyboruGraczy::on_btnGraj_clicked()
{
    aniBtnGraj->start();

    QStringList nazwy;
    QList<QPixmap> grafiki;
    QList<int> grafikiInt;
    this->liczbaGraczy = 0;

    if (ui->nazwaGracz1->text() != "") {
        nazwy.append(ui->nazwaGracz1->text());
        grafiki.append(oknaZGraczami.at(0)->jakaTekstura()->pixmap());
        grafikiInt.append(oknaZGraczami.at(0)->jakiPionek());
        liczbaGraczy++;
    }
    if (ui->nazwaGracz2->text() != "") {
        nazwy.append(ui->nazwaGracz2->text());
        grafiki.append(oknaZGraczami.at(1)->jakaTekstura()->pixmap());
        grafikiInt.append(oknaZGraczami.at(1)->jakiPionek());
        liczbaGraczy++;
    }
    if (ui->nazwaGracz3->text() != "") {
        nazwy.append(ui->nazwaGracz3->text());
        grafiki.append(oknaZGraczami.at(2)->jakaTekstura()->pixmap());
        grafikiInt.append(oknaZGraczami.at(2)->jakiPionek());
        liczbaGraczy++;
    }
    if (ui->nazwaGracz4->text() != "") {
        nazwy.append(ui->nazwaGracz4->text());
        grafiki.append(oknaZGraczami.at(3)->jakaTekstura()->pixmap());
        grafikiInt.append(oknaZGraczami.at(3)->jakiPionek());
        liczbaGraczy++;
    }

    qDebug() << "Liczba graczy " << liczbaGraczy;
    if (liczbaGraczy  > 1) {
        QString komunikat{};
        if(czyInne(nazwy, grafikiInt, komunikat))
        {
        emit przygotuj(liczbaGraczy, nazwy, ui->ziarnoGeneratora->text().toLong(), grafiki);
        this->done(Accepted);
        }
        else
        {
            ui->labelOstrzezenie->setText(komunikat);
        }
    }
    else {
        ui->labelOstrzezenie->setText("Potrzeba przynajmniej dwóch graczy.");
    }
}

void oknoWyboruGraczy::on_btnNowaPlansza_clicked()
{

    aniBtnStworz->start();
    if (ui->ziarnoGeneratora->text() == "" or ostatnieZiarno == ui->ziarnoGeneratora->text().toLong()) {
        ui->ziarnoGeneratora->setText(QString::number(QRandomGenerator::global()->generate()));
    }
    ostatnieZiarno = ui->ziarnoGeneratora->text().toLong();
    plansza->generujPlansze(ui->ziarnoGeneratora->text().toLong());
}

bool oknoWyboruGraczy::czyInne(QStringList nazwy, QList<int> grafiki, QString &komunikat)
{
    for(int i=0;i<nazwy.length();i++)
    {
       if(nazwy.at(i).contains(' ')) {
           komunikat = "Nazwa nie moze zawierać spacji";
           return false;
        }
    }
    for(int i=0;i<nazwy.length();i++)
    {

       if(nazwy.count(nazwy.at(i))>1)
       {
           komunikat = "Nazwy graczy sie powtórzyły.";
           return false;
       }
    }
    for(int i = 0; i < grafiki.length(); i++) {
        if (grafiki.count(grafiki.at(i)) > 1) {
            komunikat = "Wybrano te same grafiki";
            return false;
        }
    }
    return true;
}

void oknoWyboruGraczy::on_btnPrawo1_clicked()
{
    oknaZGraczami.at(0)->zmianaGracza(1);
}


void oknoWyboruGraczy::on_btnLewo1_clicked()
{
    oknaZGraczami.at(0)->zmianaGracza(-1);
}


void oknoWyboruGraczy::on_btnLewo2_clicked()
{
    oknaZGraczami.at(1)->zmianaGracza(-1);
}


void oknoWyboruGraczy::on_btnPrawo2_clicked()
{
    oknaZGraczami.at(1)->zmianaGracza(1);
}


void oknoWyboruGraczy::on_btnLewo3_clicked()
{
    oknaZGraczami.at(2)->zmianaGracza(-1);
}


void oknoWyboruGraczy::on_btnPrawo3_clicked()
{
    oknaZGraczami.at(2)->zmianaGracza(1);
}


void oknoWyboruGraczy::on_btnLewo4_clicked()
{
    oknaZGraczami.at(3)->zmianaGracza(-1);
}


void oknoWyboruGraczy::on_btnPrawo4_clicked()
{
    oknaZGraczami.at(3)->zmianaGracza(1);
}

