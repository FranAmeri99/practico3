#include <QApplication>
#include "formulario.h"
#include "login.h"
#include <QDir>
#include <QDebug>

int main( int argc, char ** argv )  {
    QApplication a( argc, argv );

    qDebug() << QDir::currentPath();

    Login login;
    login.show();

    return a.exec();
}
