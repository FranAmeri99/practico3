#ifndef ADMINDB_H
#define ADMINDB_H

#include <QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QObject>

class AdminDB : public QObject  {
    Q_OBJECT

public:
    explicit AdminDB( QObject * parent = nullptr );
    ~AdminDB();

    bool conectar( QString archivoSqlite );
    QSqlDatabase getDB();

    QStringList validarUsuario( QString usuario, QString clave, QString tabla = "usuarios" );

    QVector< QStringList > select( QString comando );

    QStringList campos( QString tabla );

    bool registrar( QString evento );

    void creats();

    void admin( QString ad, QString ps );


private:
    QSqlDatabase db;
};

#endif // ADMINDB_H
