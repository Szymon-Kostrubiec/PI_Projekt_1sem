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
    czasPrzesuwania->start(czasAnimacji);
}

void Pionek::animacjaPrzesuwania()
{
    this->aktualnePole++;
    grafika->setPos(Plansza::wspolrzednePolaGry(this->aktualnePole));
    if (aktualnePole != poleKoncowe) czasPrzesuwania->start(czasAnimacji);
}
