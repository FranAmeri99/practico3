#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include <QGridLayout>

#include "admindb.h"

class Login : public QWidget  {
    Q_OBJECT

public:
    Login( QWidget * parent = nullptr );

private:
    QGridLayout * layout;

    QLabel * lUsuario;
    QLabel * lClave;
    QLineEdit * leUsuario;
    QLineEdit * leClave;
    QPushButton * pb;

    AdminDB * adminDB;

private slots:
    void slot_validar();
};


#endif // LOGIN_H
