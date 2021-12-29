#include "pionek.h"

Pionek::Pionek(QPixmap tekstura, QString nazwa, int ktory, int ile, QObject *parent)
{
    this->aktualnePole = 1;
    this->nazwaGracza = nazwa;
    this->grafika = new QGraphicsPixmapItem(tekstura);
    grafika->setScale(skalaGraczy);
    grafika->setPos(Plansza::wspolrzednePolaGry(aktualnePole));
    qDebug() << "Pionek: " << Plansza::wspolrzednePolaGry(56);
    // do naprawienia wyswietlanie graczy
    switch (ktory) {
    case 1:
        this->grafika->setOffset(QPointF(300, -200));
        break;
    case 2:
        this->grafika->setOffset(QPointF(-700, -200));
        break;
    case 3:
        this->grafika->setOffset(QPointF(300, -1000));
        break;
    case 4:
        this->grafika->setOffset(QPointF(-700, -1000));
        break;
    default:
        qDebug() << "Konstruktor pionka dostal niepoprawna wartosc!";
    }

    czasPrzesuwania = new QTimer(this);
    czasPrzesuwania->setSingleShot(true);
    QObject::connect(czasPrzesuwania, &QTimer::timeout, this, &Pionek::animacjaPrzesuwania);
}

void Pionek::przesun(int oIle)
{
    this->poleKoncowe = aktualnePole + oIle;
    if (poleKoncowe > 100) poleKoncowe = 100;
    czasPrzesuwania->start(czasAnimacji);
}

void Pionek::wymusPrzesuniecie(int nrPola)
{
    this->aktualnePole = nrPola;
    this->grafika->setPos(Plansza::wspolrzednePolaGry(this->aktualnePole));
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
    if (aktualnePole != poleKoncowe) czasPrzesuwania->start(czasAnimacji);
}
