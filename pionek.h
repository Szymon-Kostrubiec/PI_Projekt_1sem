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
    explicit Pionek(QPixmap tekstura, QString nazwa, QObject *parent = nullptr);
    QGraphicsPixmapItem * grafika;
    void przesun(int oIle);
    void wymusPrzesuniecie(int nrPola);
    int jakiePole() {qDebug() << aktualnePole; return this->aktualnePole;}        //ta funkcja jest celowo inline
    QString nazwaGracza;
signals:
    void ustawScoreBoard(int wartosc);
private:
    static constexpr float skalaGraczy{7.5f};
    static constexpr int czasAnimacji{500};
    int aktualnePole;
    int poleKoncowe;
    QTimer * czasPrzesuwania;
private slots:
    void animacjaPrzesuwania();


};

#endif // PIONEK_H
