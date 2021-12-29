#include "wyswietlaniegraczy.h"

WyswietlanieGraczy::WyswietlanieGraczy(int domyslna, QObject *parent) : QGraphicsScene(parent)
{
    this->ktoWyswietlany = domyslna;
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-1.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-2.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-3.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-4.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-5.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-6.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-7.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-8.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-9.png")));
    tekstury.append(new QGraphicsPixmapItem(QPixmap(":/img/Assets/PIONEK-10.png")));

    this->addItem(tekstury.at(domyslna));
    tekstury.at(domyslna)->setScale(skalaGraczy);
}

void WyswietlanieGraczy::zmianaGracza(int oIle)
{
    this->removeItem(tekstury.at(ktoWyswietlany));
    this->ktoWyswietlany += oIle;
    if (ktoWyswietlany > 9) ktoWyswietlany = 0;
    else if (ktoWyswietlany < 0) ktoWyswietlany = 9;
    this->addItem(tekstury.at(ktoWyswietlany));
    tekstury.at(ktoWyswietlany)->setScale(skalaGraczy);
}

QGraphicsPixmapItem *WyswietlanieGraczy::jakaTekstura()
{
    return this->tekstury.at(ktoWyswietlany);
}
