#include "login.h"
#include "formulario.h"
#include <QDebug>
#include <QMessageBox>

Login::Login( QWidget * parent ) : QWidget( parent ),
                                   layout( new QGridLayout( this ) ),
                                   lUsuario( new QLabel( "Usuario", this ) ),
                                   lClave( new QLabel( "Clave", this ) ),
                                   leUsuario( new QLineEdit( this ) ),
                                   leClave( new QLineEdit ),
                                   pb( new QPushButton( "Validar", this ) ),
                                   adminDB( new AdminDB( this ) )
{

    adminDB->conectar( "../db/usuarios.sqlite" );
    adminDB->registrar( "Aplicación abierta" );

    leClave->setEchoMode( QLineEdit::Password );  // enum

    //        0          1         2
    //  --- Usuario ---                 --- 0
    //  --- Clave -----                 --- 1
    //  ---------------Validar------------- 2

    layout->addWidget( lUsuario,  0, 0, 1, 1 );
    layout->addWidget( lClave,    1, 0, 1, 1 );
    layout->addWidget( leUsuario, 0, 1, 1, 2 );
    layout->addWidget( leClave,   1, 1, 1, 2 );
    layout->addWidget( pb,        2, 1, 1, 1 );

    this->setLayout( layout );

    connect( pb, SIGNAL( pressed() ), this, SLOT( slot_validar() ) );
    connect( leClave, SIGNAL( returnPressed() ), this, SLOT( slot_validar() ) );
    adminDB->creats();
    adminDB->admin("admin","123456");

}

void Login::slot_validar()  {

    QVector< QStringList > vRegistros = adminDB->select( "SeLEct id, clave, apellido from usuarios" );

  //  qDebug() << vRegistros;


    QStringList nombre_apellido = adminDB->validarUsuario( leUsuario->text(), leClave->text(), "usuarios" );

    if ( ! nombre_apellido.isEmpty() )  {
        qDebug() << nombre_apellido.first();
        qDebug() << nombre_apellido.last();
        QMessageBox::information( this, "Usuario valido", "Hola " + nombre_apellido.first()
                                  + nombre_apellido.last() + ". Bienvenido!!!" );
      //  Formulario formulario;

    }
    else  {
        leUsuario->setText( "" );
        leClave->clear();
        QMessageBox::warning( this, "Intente de nuevo", "No me ...." );
    }

}


