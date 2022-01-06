#ifndef OKNOWYBORUGRACZY_H
#define OKNOWYBORUGRACZY_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QRandomGenerator>

#include "plansza.h"
#include "wyswietlaniegraczy.h"

namespace Ui {
class oknoWyboruGraczy;
}

class oknoWyboruGraczy : public QDialog
{
    Q_OBJECT

public:
    explicit oknoWyboruGraczy(QWidget *parent = nullptr);
    ~oknoWyboruGraczy();

private slots:
    void on_btnGraj_clicked();

    void on_btnPrawo1_clicked();

    void on_btnLewo1_clicked();

    void on_btnLewo2_clicked();

    void on_btnPrawo2_clicked();

    void on_btnLewo3_clicked();

    void on_btnPrawo3_clicked();

    void on_btnLewo4_clicked();

    void on_btnPrawo4_clicked();

    void on_btnNowaPlansza_clicked();

private:

    Ui::oknoWyboruGraczy *ui;
    QList<WyswietlanieGraczy *> oknaZGraczami;
    Plansza * plansza;
    QPropertyAnimation * aniBtnGraj;
    QPropertyAnimation * aniBtnStworz;
    long ostatnieZiarno;
    int liczbaGraczy;
    bool czyInne(QStringList nazwy, QList<int> grafiki, QString &komunikat);
signals:
    void przygotuj(int liczbaGraczy, QStringList nazwy, long ziarno, QList<QPixmap> tekstury);
};

#endif // OKNOWYBORUGRACZY_H
