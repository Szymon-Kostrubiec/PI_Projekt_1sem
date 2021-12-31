#include "mainwindow.h"
#include "pionek.h"

#include <QApplication>
#include <QFile>

int Pionek::iloscGraczy = 0;    //inicjalizacja zmiennej statycznej

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile plikArkusz (":/styles/Assets/QWidget.qss");
    plikArkusz.open(QFile::ReadOnly);
    QString arkuszStylu {QLatin1String(plikArkusz.readAll())};
    a.setStyleSheet(arkuszStylu);

    MainWindow w;
    w.show();
    return a.exec();
}
