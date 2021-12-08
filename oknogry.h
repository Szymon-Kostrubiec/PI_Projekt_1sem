#ifndef OKNOGRY_H
#define OKNOGRY_H

#include <QDialog>
#include "plansza.h"

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
    void przygotuj(int liczba, QStringList nazwy, long ziarno, QList<QGraphicsPixmapItem *> tekstury);
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::OknoGry *ui;
    int liczbaGraczy;
    long ziarnoGeneratora;
    QStringList nazwyGraczy;
    Plansza * plansza;
};

#endif // OKNOGRY_H