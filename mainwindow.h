#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QSoundEffect>

#include "creditswindow.h"
#include "oknowyborugraczy.h"
#include "oknogry.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnWykorzystane_clicked();

    void on_btnWyjdz_clicked();

    void on_btnGraj_clicked();

private:
    Ui::MainWindow * ui;
    CreditsWindow * oknoW;
    oknoWyboruGraczy * oknoWyboru;
    OknoGry * oknoG;
//    QSoundEffect sfxPrzycisk;
};
#endif // MAINWINDOW_H
