#ifndef PIONEK_H
#define PIONEK_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#include "plansza.h"

class Pionek : public QObject
{
    Q_OBJECT
public:
    explicit Pionek(QPixmap tekstura, QString nazwa);
    ~Pionek();
    QGraphicsPixmapItem * grafika;
    void przesun(int oIle);
    void wymusPrzesuniecie(int nrPola); //uzywane do nieanimowanego przesuniecia gracza przez weza/drabine
    int jakiePole();
    QString nazwaGracza;
signals:
    void ustawScoreBoard(int wartosc);
    void informujOSpadnieciu(QString informacja);
    void zakonczylemRuch();
private:
    static constexpr float skalaGraczy{0.05};
    static constexpr int czasAnimacji{500};

    static int iloscGraczy;
    int aktualnePole;
    int poleKoncowe;
    int przesuniecieWymuszone;
    QTimer * czasPrzesuwania;
private slots:
    void animacjaPrzesuwania();

};
#endif // PIONEK_H
