#include "pionek.h"

Pionek::Pionek(QPixmap tekstura, QString nazwa, QObject *parent)
{
    this->iloscGraczy++;
    this->aktualnePole = 1;
    this->przesuniecieWymuszone = 0;
    this->nazwaGracza = nazwa;
    this->grafika = new QGraphicsPixmapItem(tekstura);
    grafika->setScale(skalaGraczy);
    grafika->setPos(Plansza::wspolrzednePolaGry(aktualnePole));
    // do naprawienia wyswietlanie graczy
    switch (this->iloscGraczy) {
    case 1:
        this->grafika->setOffset(QPointF(300, -200));
        break;
    case 2:
        this->grafika->setOffset(QPointF(-900, -200));
        break;
    case 3:
        this->grafika->setOffset(QPointF(300, -1000));
        break;
    case 4:
        this->grafika->setOffset(QPointF(-900, -1000));
        break;
    default:
        qDebug() << "Konstruktor pionka dostal niepoprawna wartosc! Offset nieustalony!!!";
    }

    czasPrzesuwania = new QTimer(this);
    czasPrzesuwania->setSingleShot(true);
    QObject::connect(czasPrzesuwania, &QTimer::timeout, this, &Pionek::animacjaPrzesuwania);
}

Pionek::~Pionek()
{
    this->iloscGraczy--;
}

void Pionek::przesun(int oIle)
{
    this->poleKoncowe = aktualnePole + oIle;
    if (poleKoncowe > 100) poleKoncowe = 100;
    czasPrzesuwania->start(czasAnimacji);
}

void Pionek::wymusPrzesuniecie(int nrPola)
{
    this->przesuniecieWymuszone = nrPola;
}

int Pionek::jakiePole()
{
    return this->poleKoncowe;
}

void Pionek::animacjaPrzesuwania()
{
    this->aktualnePole++;
    grafika->setPos(Plansza::wspolrzednePolaGry(this->aktualnePole));
    emit ustawScoreBoard(aktualnePole);
    qDebug() << przesuniecieWymuszone;
    if (aktualnePole != poleKoncowe) czasPrzesuwania->start(czasAnimacji);
//    else if (przesuniecieWymuszone != 0) {
//        poleKoncowe -= przesuniecieWymuszone;
//        aktualnePole = poleKoncowe;
//        this->grafika->setPos(Plansza::wspolrzednePolaGry(poleKoncowe));
//        przesuniecieWymuszone = 0;
//    }
}
