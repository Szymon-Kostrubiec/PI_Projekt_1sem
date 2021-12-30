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
    //sprzatanie po poprzedniej generacji
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
    //generacja na nowo:
    this->generujZestawPol();
    qDebug() << "Wygenerowano: " << polaDrabiny << " " << celeDrabiny << " " << polaWeze << " " << celeWeze;
    for (int i = 0; i < liczbaDrabin; i++) {
        this->rysujDrabine(i);
    }
    for (int i = 0; i < liczbaWezy; i++) {
        this->rysujWeza(i);
    }
}

QPointF Plansza::wspolrzednePolaGry(int nrPola)
{
    if (nrPola % 10 == 0) nrPola--;
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
    if (nrPola % 10 == 0) {
        if (nrPola % 10 % 2 == 0) x -= 100;
        else x += 100;
    }
//    qDebug() << "Wspolrzedne pola " << nrPola << " " << x << " " << y;
    return QPointF(x, y);
}

int Plansza::czyToPoleJestAkcyjne(int nrPola)
{
    if (polaDrabiny.count(nrPola)) return celeDrabiny.at(polaDrabiny.indexOf(nrPola));
    if (polaWeze.count(nrPola)) return celeWeze.at(celeWeze.indexOf(nrPola));
    return 0;
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

void Plansza::rysujDrabine(int ktora)
{
    QPointF poczatek = this->wspolrzednePolaGry(polaDrabiny.at(ktora));
    QPointF koniec  = this->wspolrzednePolaGry(celeDrabiny.at(ktora));
    QPointF roznica = koniec - poczatek;
    int dlugosc = sqrt(pow(roznica.x(), 2) + pow(roznica.y(), 2));

    float wspolczynnikSkali{0};

    if (dlugosc < 400) {
        listaDrabiny.append(new QGraphicsPixmapItem(QPixmap(drabinaBKrotka)));
        wspolczynnikSkali = 1;      //do uzupelnienia
    }
    else if (dlugosc < 600) {
        listaDrabiny.append(new QGraphicsPixmapItem(QPixmap(drabinaKrotka)));
        wspolczynnikSkali = 1;
    }
    else if (dlugosc < 700) {
        listaDrabiny.append(new QGraphicsPixmapItem(QPixmap(drabinaDluga)));
        wspolczynnikSkali = 1;
    }
    else if (dlugosc < 900) {
        listaDrabiny.append(new QGraphicsPixmapItem(QPixmap(drabinaBDluga)));
        wspolczynnikSkali = 1;
    }
    else qDebug() << "Funkcja rysuj drabine dostala zawalu bo skala = " << dlugosc;

    this->addItem(listaDrabiny.at(ktora));
    if (czyDuzaSkala) listaDrabiny.at(ktora)->setScale(wspolczynnikSkali * dlugosc/2000.0f);
    else listaDrabiny.at(ktora)->setScale(wspolczynnikSkali * dlugosc/4000.0);
    listaDrabiny.at(ktora)->setPos(poczatek);

    listaDrabiny.at(ktora)->setOffset(-(listaDrabiny.at(ktora)->boundingRect().width()/2), 0);

    float angle{};
    angle = qAtan2(koniec.y() - poczatek.y(), koniec.x() - poczatek.x());     //w takiej kolejnosci bo tak chce ta funkcja
    angle = qRadiansToDegrees(angle) + 270;
    listaDrabiny.at(ktora)->setRotation(angle);
}

void Plansza::rysujWeza(int ktora)
{
    //czy tu nie ma pomylenia poczatku z koncem weza???
    QPointF poczatek = this->wspolrzednePolaGry(polaWeze.at(ktora));
    QPointF koniec = this->wspolrzednePolaGry(celeWeze.at(ktora));
    QPointF roznica = koniec - poczatek;
    int dlugosc = sqrt(pow(roznica.x(), 2) + pow(roznica.y(), 2));

    float wspolczynnikSkali{0};

    if (ktora % 2) { //co drugi waz inny
        listaWeze.append(new QGraphicsPixmapItem(QPixmap(wazRozowy)));
        wspolczynnikSkali = 1;      //do uzupelnienia
    }
    else {
        listaWeze.append(new QGraphicsPixmapItem(QPixmap(wazZielony)));
        wspolczynnikSkali = 1;
    }
    this->addItem(listaWeze.at(ktora));
    if (czyDuzaSkala) listaWeze.at(ktora)->setScale(wspolczynnikSkali * dlugosc/2000.0f);   //te dwie wartosci tez do dobrania
    else listaWeze.at(ktora)->setScale(wspolczynnikSkali * dlugosc/4000.0f);
    listaWeze.at(ktora)->setPos(poczatek);

    listaWeze.at(ktora)->setOffset(-(listaWeze.at(ktora)->boundingRect().width()/2), 0);

    float angle{};
    angle = qAtan2(koniec.y() - poczatek.y(), koniec.x() - poczatek.x());     //w takiej kolejnosci bo tak chce ta funkcja
    angle = qRadiansToDegrees(angle) + 270;
    listaWeze.at(ktora)->setRotation(angle);
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
