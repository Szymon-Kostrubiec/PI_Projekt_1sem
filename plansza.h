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
    int czyToPoleJestAkcyjne(int nrPola); //argumentem jest numer pola, zwraca o ile pionek powinien sie przesunac, albo 0 jesli nie trafil na akcyjne pole
signals:

private:
    //zmienne do szybkiej edycji
    static constexpr int liczbaDrabin{5};
    static constexpr int liczbaWezy{5};
    static constexpr float skalaMalejPlanszy{0.38};

    QString drabinaDluga{":/img/Assets/DrabinaDluga.png"};
    QString drabinaBDluga{":/img/Assets/DrabinaBDluga.png"};
    QString drabinaKrotka{":/img/Assets/DrabinaKrotka.png"};
    QString drabinaBKrotka{":/img/Assets/DrabniaBKrotka.png"};

    QString wazRozowy{":/img/Assets/wazRozowy.png"};
    QString wazZielony{":/img/Assets/wazZielony.png"};
    //zmienne programowe
    long ziarnoGeneratora;
    bool czyDuzaSkala;
    QGraphicsPixmapItem * planszaBackground;
    QList<QGraphicsPixmapItem *> listaDrabiny;
    QList<QGraphicsPixmapItem *> listaWeze;

    QList<int> polaDrabiny, polaWeze, celeDrabiny, celeWeze;

    void generujZestawPol();
    void rysujDrabine(int ktora);
    void rysujWeza(int ktora);
    void rysujObiekt(bool czyDrabina, int numer);
    QPointF wspolrzednePunktu(int nrPola);
};

#endif // PLANSZA_H
