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
signals:
private:
    static constexpr float skalaGraczy{7.5f};
    static constexpr int czasAnimacji{500};
    int aktualnePole;
    int poleKoncowe;
    QString nazwaGracza;
    QTimer * czasPrzesuwania;
private slots:
    void animacjaPrzesuwania();


};

#endif // PIONEK_H
