#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>
#include "login.h"
#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QTableWidget>
#include <QComboBox>

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

    QPushButton * pb;

    AdminDB * adminDB;

    QComboBox * tipo;
    QTableWidget *teSelect;
    
    
    void mostrar();
    void insertar();
    void borrar();
    
    bool NoRepetido(QString user);
    
    private slots:
    void slot_pb();
};

#endif // FORMULARIO_H
