#include "plansza.h"

Plansza::Plansza(bool czyFullScale, QObject *parent) : QGraphicsScene(parent)
{
    this->czyDuzaSkala = czyFullScale;
    planszaBackground = new QGraphicsPixmapItem(QPixmap(":/img/Assets/PlanszaNowa.png"));
    this->addItem(planszaBackground);
    if (not(czyDuzaSkala)) planszaBackground->setScale(skalaMalejPlanszy);
}

Plansza::~Plansza()
{
    delete planszaBackground;
}
void Plansza::generujPlansze(long ziarno)
{
    this->ziarnoGeneratora = ziarno;
    //sprzatanie po poprzedniej iteracji
    for (int i = 0; i< listaDrabiny.length(); i++) {
        this->removeItem(listaDrabiny.at(i));
        //czy tu jest memory leak?
    }
    for (int i = 0; i < listaWeze.length(); i++) {
        this->removeItem(listaWeze.at(i));
    }
    listaDrabiny.clear();
    listaWeze.clear();
    polaDrabiny.clear();
    polaWeze.clear();
    celeDrabiny.clear();
    celeWeze.clear();
    this->generujZestawPol();
    qDebug() << "Wygenerowano: " << polaDrabiny << " " << celeDrabiny << " " << polaWeze << " " << celeWeze;
    for (int i = 0; i < liczbaDrabin; i++) {
        listaDrabiny.append(new QGraphicsPixmapItem(QPixmap(sciezkaDoDrabiny)));
        this->rysujObiekt(true, i);
    }
    for (int i = 0; i < liczbaWezy; i++) {
        listaWeze.append(new QGraphicsPixmapItem(QPixmap(sciezkaDoWeze)));
        this->rysujObiekt(false, i);
    }
}

QPointF Plansza::wspolrzednePolaGry(int nrPola)
{
    int x{};
    if (nrPola / 10 % 2 == 0) {
        x = nrPola % 10;
        x *= 100;
        x -= 50;
    }
    else {
        x = 10 - nrPola % 10;
        x *= 100;
        x += 50;
    }
    int y{};
    y = 10 - nrPola / 10;
    y *= 100;
    y -= 50;
//    qDebug() << "Wspolrzedne pola " << nrPola << " " << x << " " << y;
    return QPointF(x, y);
}

void Plansza::generujZestawPol()
{
    qDebug() << "Rozpoczeto generacje drabin";
    QList<int> losowe;
    int obecnePole{};
    int koncowePole{};
    int rozproszenie = 75/liczbaDrabin;
    //przerobienie ziarna na poszczegolne wartosci losowe
    if (this->ziarnoGeneratora < 1) ziarnoGeneratora *= -1;
    for (int i = 0; i < 9; i++) {
        if (i == 0) {       //zle praktyki
            losowe.append(this->ziarnoGeneratora % 10);
            continue;
        }
        losowe.append(this->ziarnoGeneratora / (10 * i) % 10);
    }
    for (int i = 0; i < liczbaDrabin; i++) {
        do {
            obecnePole = 12 + rozproszenie * (i) + (7 + losowe.at(i)) % 4;
            losowe[i] += 3;
        } while(obecnePole % 10 == 0 or obecnePole % 10 == 1 or polaDrabiny.count(obecnePole) or celeDrabiny.count(obecnePole) or obecnePole > 95);
        polaDrabiny.append(obecnePole);
        do {
            koncowePole = obecnePole + (10 * (losowe.at(i) % 3 + 1)) + (5 + losowe.at(i)) % 4;    //ta 8 tam jest dla zwiekszenia losowosci
            losowe[i] += 7;
        } while(koncowePole % 10 == 0 or koncowePole % 10 == 1 or polaDrabiny.count(koncowePole) or polaDrabiny.count(koncowePole) or koncowePole > 98);
        celeDrabiny.append(koncowePole);
    }
    qDebug() << "Rozpoczeto generacje wezy";
    for (int i = 0; i < liczbaWezy; i++) {
        do {
            obecnePole = 12 + rozproszenie * (i) + (6 + losowe.at(i)) % 4;
            losowe[i] += 5;
        } while(obecnePole % 10 == 0 or obecnePole % 10 == 1 or polaDrabiny.count(obecnePole) or celeDrabiny.count(obecnePole) or obecnePole > 95);
        do {
            koncowePole = obecnePole + (10 * (losowe.at(i) % 3 + 1)) + (6 + losowe.at(i)) % 4;
            losowe[i] += 1;
        } while(koncowePole % 10 == 0 or koncowePole % 10 == 1 or polaDrabiny.count(koncowePole) or polaDrabiny.count(koncowePole) or koncowePole > 98);
        polaWeze.append(koncowePole);
        celeWeze.append(obecnePole);
    }
}

void Plansza::rysujObiekt(bool czyDrabina, int numer)
{
    if (czyDrabina) {   //rysowanie drabiny
        QPointF poczatek = this->wspolrzednePunktu(polaDrabiny.at(numer));
        QPointF koniec = this->wspolrzednePunktu(celeDrabiny.at(numer));

        this->addItem(listaDrabiny.at(numer));
        listaDrabiny.at(numer)->setPos(wspolrzednePunktu(polaDrabiny.at(numer)));
        float angle{};
        angle = qAtan2(koniec.y() - poczatek.y(), koniec.x() - poczatek.x());     //w takiej kolejnosci bo tak chce ta funkcja
        angle = qRadiansToDegrees(angle) + 270;
        listaDrabiny.at(numer)->setRotation(angle);
        float skala{};
        skala = sqrtf(pow(poczatek.x() - koniec.x(), 2) + pow(poczatek.y() - koniec.x(), 2));
        skala /= 100.0f;
        listaDrabiny.at(numer)->setScale(skala);
    }
    else {  //rysowanie weza
        QPointF poczatek = this->wspolrzednePunktu(polaWeze.at(numer));
        QPointF koniec = this->wspolrzednePunktu(celeWeze.at(numer));

        this->addItem(listaWeze.at(numer));
        listaWeze.at(numer)->setPos(wspolrzednePunktu(polaWeze.at(numer)));
        float angle{};
        angle = qAtan2(koniec.y() - poczatek.y(), koniec.x() - poczatek.x());
        angle = qRadiansToDegrees(angle) + 270;
        listaWeze.at(numer)->setRotation(angle);
        float skala{};
        skala = sqrtf(pow(koniec.x() - poczatek.x(), 2) + pow(koniec.y() - poczatek.y(), 2));
        skala /= 100.0f;
        listaWeze.at(numer)->setScale(skala);
    }
}

QPointF Plansza::wspolrzednePunktu(int nrPola)
{
    int x{};
    if (nrPola / 10 % 2 == 0) {
        x = nrPola % 10;
        x *= 100;
        x -= 50;
    }
    else {
        x = 10 - nrPola % 10;
        x *= 100;
        x += 50;
    }
    int y{};
    y = 10 - nrPola / 10;
    y *= 100;
    y -= 50;
    if (not(czyDuzaSkala)) {
        x *= skalaMalejPlanszy;
        y *= skalaMalejPlanszy;
    }
//    qDebug() << "Wspolrzedne pola " << nrPola << " " << x << " " << y;
    return QPointF(x, y);
}
