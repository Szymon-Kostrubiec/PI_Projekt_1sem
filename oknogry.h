#ifndef OKNOGRY_H
#define OKNOGRY_H

#include <QDialog>
#include <QRandomGenerator>
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
private slots:

    void on_btnZakoncz_clicked();

    void on_btnRzut_clicked();

private:
    int aktualnyPionek;
    Ui::OknoGry *ui;
    int liczbaGraczy;
    long ziarnoGeneratora;
    QStringList nazwyGraczy;
    Plansza * plansza;
    QList<Pionek *> gracze;
};

#endif // OKNOGRY_H
