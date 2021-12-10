#ifndef PLANSZA_H
#define PLANSZA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QtMath>

class Plansza : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Plansza(bool czyFullScale, QObject *parent = nullptr);
    ~Plansza();
    void generujPlansze(long ziarno);
    static QPointF wspolrzednePolaGry(int nrPola);
signals:

private:
    QGraphicsPixmapItem * planszaBackground;
    long ziarnoGeneratora;
    bool czyDuzaSkala;
    static constexpr int liczbaDrabin{5};
    static constexpr int liczbaWezy{5};
    static constexpr float skalaMalejPlanszy{0.38f};
    QString sciezkaDoDrabiny{":/img/Assets/drabina.png"};
    QString sciezkaDoWeze{":/img/Assets/waz.png"};

    QList<QGraphicsPixmapItem *> listaDrabiny;
    QList<QGraphicsPixmapItem *> listaWeze;

    QList<int> polaDrabiny, polaWeze, celeDrabiny, celeWeze;

    void generujZestawPol();
    void rysujObiekt(bool czyDrabina, int numer);
    QPointF wspolrzednePunktu(int nrPola);
};

#endif // PLANSZA_H
