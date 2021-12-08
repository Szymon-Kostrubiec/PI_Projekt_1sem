#include "wyswietlaniegraczy.h"

WyswietlanieGraczy::WyswietlanieGraczy(int domyslna, QObject *parent) : QGraphicsScene(parent)
{
    this->ktoWyswietlany = domyslna;
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/player1.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/player2.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/player3.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/player4.png")));
    this->addItem(tekstury.at(domyslna));
    tekstury.at(domyslna)->setScale(skalaGraczy);
}

void WyswietlanieGraczy::zmianaGracza(int oIle)
{
    this->removeItem(tekstury.at(ktoWyswietlany));
    this->ktoWyswietlany += oIle;
    if (ktoWyswietlany > 3) ktoWyswietlany = 0;
    else if (ktoWyswietlany < 0) ktoWyswietlany = 3;
    this->addItem(tekstury.at(ktoWyswietlany));
    tekstury.at(ktoWyswietlany)->setScale(skalaGraczy);
}

QGraphicsPixmapItem *WyswietlanieGraczy::jakaTekstura()
{
    return this->tekstury.at(ktoWyswietlany);
}
