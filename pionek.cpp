#include "pionek.h"

Pionek::Pionek(QPixmap tekstura, QString nazwa)
{
    this->aktualnePole = 1;
    this->nazwaGracza = nazwa;
    this->grafika = new QGraphicsPixmapItem(tekstura);
    grafika->setScale(skalaPionkow);
    grafika->setPos(Plansza::wspolrzednePolaGry(aktualnePole));
}

void Pionek::przesun(int oIle)
{
    for (int i = 0; i < oIle; i++) {
        this->aktualnePole++;
        this->grafika->setPos(Plansza::wspolrzednePolaGry(aktualnePole));
        QThread::sleep(1);
    }
}
