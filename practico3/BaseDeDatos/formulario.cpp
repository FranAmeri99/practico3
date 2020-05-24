#include "formulario.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QMessageBox>
Formulario::Formulario(QWidget *parent) : QWidget(parent),adminDB( new AdminDB( this ))
{
    layout = new QGridLayout ;
    lUsuario = new QLabel;
    lClave = new QLabel;
    lNombre = new QLabel;
    lApellido = new QLabel;
    leUsuario = new QLineEdit("Usuario");
    leClave = new QLineEdit("Clave") ;
    leNombre = new QLineEdit("Nombre") ;
    leApellido = new QLineEdit("Apellido") ;

    tipo = new QComboBox();
    tipo->addItem("Insertar");
    tipo->addItem("Buscar");
    tipo->addItem("Borrar");

    pb = new QPushButton(pb->text());
    teSelect = new QTableWidget();

    adminDB->conectar( "../db/usuarios.sqlite" );
    adminDB->registrar( "Aplicación abierta" );

    leClave->setEchoMode( QLineEdit::Password );  // enum

    layout->addWidget( tipo,      0, 0, 1, 1 );
    layout->addWidget( leUsuario, 0, 1, 1, 1 );
    layout->addWidget( leClave,   0, 2, 1, 1 );

    layout->addWidget( leNombre,   1, 0, 1, 1 );
    layout->addWidget( leApellido, 1, 1, 1, 1 );
    layout->addWidget( pb, 1, 2, 1, 1 );

    this->setLayout( layout );

    QStringList headers2 = { "USUARIO", "NOMBRE", "APELLIDO" };
    teSelect->setHorizontalHeaderLabels(headers2);

    qDebug()<<"formulario;";
}

void Formulario::mostrar()
{
    QSqlQuery mostrar;
    QString consulta = "SELECT usuario, nombre, apellido FROM usuarios ";
    mostrar.exec(consulta);


    int fila =0;
    teSelect->setRowCount(0);
    while(mostrar.next()){ //muestro en la tabla lo que devuelve la consulta
        teSelect->insertRow(fila);
        teSelect->setItem(fila, 0,new QTableWidgetItem(mostrar.value(0).toByteArray().constData()));
        teSelect->setItem(fila, 1,new QTableWidgetItem(mostrar.value(1).toByteArray().constData()));
        teSelect->setItem(fila, 2,new QTableWidgetItem(mostrar.value(2).toByteArray().constData()));
        fila ++;
    }

}

bool Formulario::NoRepetido(QString user)
{
    QSqlQuery query;
    QString check = "SELECT COUNT(usuario) FROM usuarios WHERE usuario = '" + user + "'";
    if(query.exec(check)){
        int cantidad = query.value( 0 ).toInt();
        if(cantidad > 0){
            return false;
        }
        return true;
    }
    qDebug()<<"Hubo algun problema";
    return false;

}

void Formulario::insertar()
{
    QString ps = leClave->text();
    QString us = leUsuario->text();
    QString no = leNombre->text();
    QString ap = leApellido->text();
    QSqlQuery query;
    QByteArray hashClave = QCryptographicHash::hash( ps.toUtf8(), QCryptographicHash::Md5 ).toHex();

    QString insertion=  "INSERT INTO usuarios (usuario,"
                        " clave, nombre, apellido) VALUES "
                        "('" + us + "', '" + hashClave +
                        "', '" + no + "', '" + ap + "')" ;
    if(NoRepetido(us)){
        if(query.exec(insertion)){

            QMessageBox::information( this, "Se inserto", "Bienvenido "+ no + " " + ap );
        }
        else{
            QMessageBox::information( this, "Problemas", " Consulte con el desarollador");

        }
    }
    else{

        QMessageBox::warning( this, "Intente de nuevo", "Usuario repetido" );

    }
}

void Formulario::borrar()
{
    QString ps = leClave->text();
    QString us = leUsuario->text();
    QSqlQuery query;
    QByteArray hashClave = QCryptographicHash::hash( ps.toUtf8(), QCryptographicHash::Md5 ).toHex();

    QString borrar = "DELETE FROM usuarios WHERE usuarios ='"+ us +"' AND clave = "+ ps +"'" ;

    if (!query.exec(borrar)) {
        QMessageBox::warning( this, "no borro", "Hubo algun problema" );
        qDebug()<<query.lastError();
    }
}

void Formulario::slot_pb()
{
    QString operacion = tipo->currentText();
    if (operacion == "Insertar") {
        insertar();
    }
    if (operacion == "Borrar"){
        leNombre->setDisabled(true);
        leApellido->setDisabled(true);
        borrar();
    }
    mostrar();
}



