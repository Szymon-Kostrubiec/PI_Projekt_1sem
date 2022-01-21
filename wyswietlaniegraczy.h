#ifndef WYSWIETLANIEGRACZY_H
#define WYSWIETLANIEGRACZY_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class WyswietlanieGraczy : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit WyswietlanieGraczy(int domyslna, QObject *parent = nullptr);
    void zmianaGracza(int oIle);
    QGraphicsPixmapItem * jakaTekstura();
    int jakiPionek();
signals:

private:
    static constexpr float skalaGraczy{0.13};
    int ktoWyswietlany;
    QList<QGraphicsPixmapItem *> tekstury;
};

#endif // WYSWIETLANIEGRACZY_H
