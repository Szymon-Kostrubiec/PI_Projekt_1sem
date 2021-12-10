#ifndef PIONEK_H
#define PIONEK_H

#include <QGraphicsPixmapItem>
#include "plansza.h"
#include <QThread>
class Pionek
{
public:
    Pionek(QPixmap tekstura, QString nazwa);
    void ustawNaPole(int jakiePole);
    QGraphicsPixmapItem * grafika;
private:
    static constexpr float skalaPionkow{7.5f};
    int aktualnePole;
    QString nazwaGracza;
    void przesun(int oIle);
};

#endif // PIONEK_H
