#include "admindb.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QCryptographicHash>

AdminDB::AdminDB( QObject * parent ) : QObject( parent )  {
    db = QSqlDatabase::addDatabase( "QSQLITE" );
}

AdminDB::~AdminDB()  {
    db.close();
}

bool AdminDB::conectar( QString archivoSqlite )  {

    db.setDatabaseName( archivoSqlite );

    if( db.open() )
        return true;

    return false;
}

QSqlDatabase AdminDB::getDB()  {
    return db;
}

QStringList AdminDB::validarUsuario( QString usuario, QString clave, QString tabla )  {

    QStringList nombre_apellido_usuario_valido;

    QByteArray hashClave = QCryptographicHash::hash( clave.toUtf8(), QCryptographicHash::Md5 ).toHex();

    QSqlQuery query( db );
    query.exec( "SELECT nombre, apellido FROM " + tabla + " WHERE usuario = '" + usuario
                + "' AND clave = '" + hashClave + "'" );
//    query.exec( "SELECT nombre, apellido FROM " + tabla );


    int contador_de_registros = 0;

    while( query.next() )  {
        contador_de_registros++;
        nombre_apellido_usuario_valido.append( query.value( 0 ).toString() );
        nombre_apellido_usuario_valido << query.value( 1 ).toString();
    }

    if( contador_de_registros == 1 )  {
        return nombre_apellido_usuario_valido;
    }

    return nombre_apellido_usuario_valido;
}



/**
 * @brief Método que ejecuta una consulta SQL a la base de datos que ya se encuentra conectado.
          Utiliza QSqlQuery para ejecutar la consulta, con el método next() se van extrayendo
          los registros que pueden ser analizados con QSqlRecord para conocer la cantidad de
          campos por registro.
 * @param comando es una consulta como la siguiente: SELECT nombre, apellido, id FROM usuarios
 * @return Devuelve un QVector donde cada elemento es un registro, donde cada uno de estos registros
           están almacenados en un QStringList que contiene cada campo de cada registro.
 */
QVector< QStringList > AdminDB::select( QString comando )  {

    QVector< QStringList > vRegistros;

    if ( db.isOpen() && comando.startsWith( "select", Qt::CaseInsensitive ) )  {
        QSqlQuery query( db );

        bool exito = query.exec( comando );

        if ( exito )  {

            while( query.next() )  {

                QSqlRecord registro = query.record();
                int cantidad_registros = registro.count();

                QStringList valores_campos;

                for ( int i = 0 ; i < cantidad_registros ; i++ )  {

                    QString valor = registro.value( i ).toString();
                    valores_campos.append( valor );  // igual a   valores_campos << valor;
                }

                vRegistros.append( valores_campos );
            }
        }
    }

    return vRegistros;
}

/**
 * @brief AdminDB::campos Devuelve los nombres de los campos de la tabla
 */
QStringList AdminDB::campos( QString tabla )  {
    Q_UNUSED( tabla )

    QStringList lista_nombres;



    return lista_nombres;
}

bool AdminDB::registrar( QString evento )  {

    bool exito = false;

    QSqlQuery query( db );

    if ( db.isOpen() )  {
        exito = query.exec( "INSERT INTO registros ( evento ) VALUES ('" + evento + "')" );

    }

    return exito;
}

void AdminDB::creats()
{
    QString createUser = "CREATE TABLE IF NOT EXISTS usuarios  "
                         "(id INTEGER PRIMARY KEY, "
                         "usuario TEXT NOT NULL, "
                         "clave TEXT NOT NULL, "
                         "nombre TEXT NOT NULL, "
                         "apellido TEXT NOT NULL)";

    QSqlQuery query2( db );
    query2.exec(createUser);
        qDebug() << query2.lastError();  // Devuelve un objeto de QSqlError


    QString createR = "CREATE TABLE IF NOT EXISTS registros "
                      "(id INTEGER PRIMARY KEY, "
                      "evento TEXT NOT NULL)";

    query2.exec(createR);
        qDebug() << query2.lastError();  // Devuelve un objeto de QSqlError

}

void AdminDB::admin(QString ad, QString ps){
    QSqlQuery query;
    QByteArray hashClave = QCryptographicHash::hash( ps.toUtf8(), QCryptographicHash::Md5 ).toHex();

    query.exec( "INSERT INTO usuarios (usuario, clave, nombre, apellido) VALUES ('" + ad + "', '" + hashClave + "', '" + ad + "', '" + ad + "')" );

    qDebug() << query.lastError();  // Devuelve un objeto de QSqlError

}






