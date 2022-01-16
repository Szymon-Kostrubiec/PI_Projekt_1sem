#ifndef OKNOGRY_H
#define OKNOGRY_H

#include <QDialog>
#include <QRandomGenerator>
#include <QPropertyAnimation>

#include "plansza.h"
#include "pionek.h"

namespace Ui {
class OknoGry;
}

class OknoGry : public QDialog
{
    Q_OBJECT

public:
    explicit OknoGry(QWidget *parent = nullptr);
    ~OknoGry();
public slots:
    void przygotuj(int liczba, QStringList nazwy, long ziarno, QList<QPixmap> tekstury);

    void ustawScoreBoard(int wartosc);

    void informujOSpadnieciu(QString informacja);

    void zakonczylemRuch();
private slots:

    void on_btnZakoncz_clicked();

    void on_btnRzut_clicked();

private:
    void zwyciestwo(QString nazwaZwyciezcy);

    int aktualnyPionek;
    int liczbaGraczy;
    long ziarnoGeneratora;
    bool czyGraZakonczona;
    QStringList nazwyGraczy;

    Ui::OknoGry *ui;
    Plansza * plansza;
    QList<Pionek *> gracze;

    QPropertyAnimation * aniBtnRzut;
    QGraphicsPixmapItem  * grafikaZwyciestwa;
};

#endif // OKNOGRY_H

