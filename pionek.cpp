#include "pionek.h"

Pionek::Pionek(QPixmap tekstura, QString nazwa, QObject *parent)
{
    this->aktualnePole = 1;
    this->nazwaGracza = nazwa;
    this->grafika = new QGraphicsPixmapItem(tekstura);
    grafika->setScale(skalaGraczy);
    grafika->setPos(Plansza::wspolrzednePolaGry(aktualnePole));

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

void Pionek::animacjaPrzesuwania()
{
    this->aktualnePole++;
    grafika->setPos(Plansza::wspolrzednePolaGry(this->aktualnePole));
    if (aktualnePole != poleKoncowe) czasPrzesuwania->start(czasAnimacji);
}
