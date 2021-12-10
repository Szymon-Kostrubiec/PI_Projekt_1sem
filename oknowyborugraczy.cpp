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
    //animacje
    aniBtnGraj = new QPropertyAnimation(ui->btnGraj, "geometry");
    aniBtnGraj->setKeyValueAt(0, QRectF(560, 560, 340, 90));    //potrzebny fix, zmienily sie koordynaty
    aniBtnGraj->setKeyValueAt(0.5f, QRectF(580, 580, 330, 80));
    aniBtnGraj->setKeyValueAt(1, QRectF(560, 560, 340, 90));

    aniBtnStworz = new QPropertyAnimation(ui->btnNowaPlansza, "geometry");
    aniBtnStworz->setKeyValueAt(0, QRectF(570, 410, 340, 50));
    aniBtnStworz->setKeyValueAt(0.5f, QRectF(590, 430, 330, 40));
    aniBtnStworz->setKeyValueAt(1, QRectF(570, 410, 340, 50));
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
}

void oknoWyboruGraczy::on_btnGraj_clicked()
{
/*    aniBtnGraj->start();   */       //potrzebny fix
    qDebug() << "Liczba graczy " << liczbaGraczy;
    QStringList nazwy;
    //potrzebne walidacje: niewybrania tych samych pionkow, niewybrania tych samych nazw
    this->liczbaGraczy = 0;
    if (ui->nazwaGracz1->text() != "") {
        nazwy.append(ui->nazwaGracz1->text());
        liczbaGraczy++;
    }
    if (ui->nazwaGracz2->text() != "") {
        nazwy.append(ui->nazwaGracz2->text());
        liczbaGraczy++;
    }
    if (ui->nazwaGracz3->text() != "") {
        nazwy.append(ui->nazwaGracz3->text());
        liczbaGraczy++;
    }
    if (ui->nazwaGracz4->text() != "") {
        nazwy.append(ui->nazwaGracz4->text());
        liczbaGraczy++;
    }
    QList<QPixmap> tekstury;
    for(int i = 0; i < liczbaGraczy; i++) {
        tekstury.append(oknaZGraczami.at(i)->jakaTekstura()->pixmap());
    }
    if (liczbaGraczy  > 1) {
        emit przygotuj(liczbaGraczy, nazwy, ui->ziarnoGeneratora->text().toLong(), tekstury);
        this->done(Accepted);
    }
    else {
        ui->labelOstrzezenie->setText("Potrzeba przynajmniej dwóch graczy.");
    }
}

void oknoWyboruGraczy::on_btnNowaPlansza_clicked()
{
    //potrzebna walidacja wprowadzonej zmiennej (czy jest cyfra)
//    aniBtnStworz->start();  //potrzebny fix
    if (ui->ziarnoGeneratora->text() == "" or ostatnieZiarno == ui->ziarnoGeneratora->text().toLong()) {
        ui->ziarnoGeneratora->setText(QString::number(QRandomGenerator::global()->generate()));
    }
    ostatnieZiarno = ui->ziarnoGeneratora->text().toLong();
    plansza->generujPlansze(ui->ziarnoGeneratora->text().toLong());
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

