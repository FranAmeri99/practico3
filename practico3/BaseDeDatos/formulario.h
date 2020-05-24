#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>
#include "login.h"
#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVector>

class Formulario : public QWidget
{
    Q_OBJECT
public:
    explicit Formulario(QWidget *parent = nullptr);

private:

private:
    QGridLayout * layout;

    QLabel * lUsuario;
    QLabel * lClave;
    QLabel * lNombre;
    QLabel * lApellido;

    QLineEdit * leUsuario;
    QLineEdit * leClave;
    QLineEdit * leNombre;
    QLineEdit * leApellido;

    QPushButton * pbInsertar;
    QPushButton * pbBorrar;
    QPushButton * pbBuscar;

    AdminDB * adminDB;

    bool NoRepetido(QString user);

private slots:
    void slot_insertar();
};

#endif // FORMULARIO_H
