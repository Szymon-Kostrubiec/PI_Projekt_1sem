#include "oknogry.h"
#include "ui_oknogry.h"

OknoGry::OknoGry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OknoGry)
{
    //kwestie graficzne
    ui->setupUi(this);
    this->setWindowTitle("Węże i drabiny. Tura 1.");
    this->setFixedSize(1280, 1050);
    QPixmap background(":/img/Assets/backgroundOknoStartowe.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    grafikaZwyciestwa = new QGraphicsPixmapItem(QPixmap(":/img/Assets/WINNER.png"));

    // animacje
    aniBtnRzut = new QPropertyAnimation(ui->btnRzut, "geometry");
    aniBtnRzut->setKeyValueAt(0, QRectF(1040, 300, 230, 120));
    aniBtnRzut->setKeyValueAt(0.5, QRectF(1060, 320, 190, 80));
    aniBtnRzut->setKeyValueAt(1, QRectF(1040, 300, 230, 120));

    this->plansza = new Plansza(true, this);
    ui->viewPlansza->setScene(plansza);

    aktualnyPionek = 0;
    this->czyGraZakonczona = false;

}

OknoGry::~OknoGry()
{
    delete ui;
    delete grafikaZwyciestwa;
}

void OknoGry::przygotuj(int liczba, QStringList nazwy, long ziarno, QList<QPixmap> tekstury)
{
    //sprzatanie po poprzedniej generacji
    for(auto gracz: gracze) {
        plansza->removeItem(gracz->grafika);
        delete gracz;
    }
    gracze.clear();
    //generacja na nowo
    this->liczbaGraczy = liczba;
    this->nazwyGraczy = nazwy;
    this->ziarnoGeneratora = ziarno;
    plansza->generujPlansze(ziarnoGeneratora);
    switch (liczbaGraczy) {
        case 4:
            ui->player4Label->setText(nazwyGraczy.at(3));   //w tej instrukcji switch-case swiadomie pominieto break;
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
            qDebug() << "Wystapil blad w instrukcji switch case przygotowywania planszy";
    }
    for (int i = 0; i < liczbaGraczy; i++) {
        gracze.append(new Pionek(tekstury.at(i), nazwyGraczy.at(i)));
        QObject::connect(gracze.at(i), &Pionek::ustawScoreBoard, this, &OknoGry::ustawScoreBoard);
        QObject::connect(gracze.at(i), &Pionek::informujOSpadnieciu, this, &OknoGry::informujOSpadnieciu);
        QObject::connect(gracze.at(i), &Pionek::zakonczylemRuch, this, &OknoGry::zakonczylemRuch);
        plansza->addItem(gracze.at(i)->grafika);
    }
    ui->labelZiarno->setText("Obecne ziarno generatora: " + QString::number(ziarnoGeneratora));
}

void OknoGry::ustawScoreBoard(int wartosc)
{
    switch (aktualnyPionek) {
    case 0:
        ui->player1Score->setText(QString::number(wartosc));
        break;
    case 1:
        ui->player2Score->setText(QString::number(wartosc));
        break;
    case 2:
        ui->player3Score->setText(QString::number(wartosc));
        break;
    case 3:
        ui->player4Score->setText(QString::number(wartosc));
        break;
    }
}

void OknoGry::informujOSpadnieciu(QString informacja)
{
    ui->labelInfo->setText(informacja);
}

void OknoGry::zakonczylemRuch()
{
    if (gracze.at(aktualnyPionek)->jakiePole() == 100) {
        zwyciestwo(gracze.at(aktualnyPionek)->nazwaGracza);
    }
    if (not(czyGraZakonczona))
        ui->btnRzut->setEnabled(true);
    aktualnyPionek++;
    if (aktualnyPionek >= liczbaGraczy) aktualnyPionek = 0;
}

void OknoGry::on_btnZakoncz_clicked()
{
    if (czyGraZakonczona) {
        this->done(Accepted);
    }
    else {
        this->done(Rejected);
    }
}


void OknoGry::on_btnRzut_clicked()
{
    aniBtnRzut->start();
    int losowa = QRandomGenerator::global()->generate() % 6 + 1;
    gracze.at(aktualnyPionek)->przesun(losowa);
    int przesuniecie{};
    if ((przesuniecie = plansza->czyToPoleJestAkcyjne(gracze.at(aktualnyPionek)->jakiePole()))) {
        gracze.at(aktualnyPionek)->wymusPrzesuniecie(przesuniecie);
        qDebug() << "Gracz nr " << aktualnyPionek + 1 << "doswiadcza dzialania drabiny/weza";
    }
    ui->labelJestTura->setText("Jest tura gracza " + QString::number(aktualnyPionek + 1));
    this->setWindowTitle("Węże i drabiny. Tura gracza " + QString::number(aktualnyPionek + 1));
    ui->btnRzut->setEnabled(false);
}

void OknoGry::zwyciestwo(QString nazwaZwyciezcy)
{
    ui->btnRzut->setEnabled(false);
    czyGraZakonczona = true;
    ui->labelZwyciestwo->setText("Zwyciężył " + nazwaZwyciezcy);
    plansza->addItem(grafikaZwyciestwa);
    grafikaZwyciestwa->setScale(1.6);
    grafikaZwyciestwa->setPos(220, 170);
}

