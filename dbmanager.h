#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "cmdt.h"

class DbManager
{
public:
    DbManager(const QString& path);

    QList<DomaineLoi> GetAllDomaineLoi();
    QList<CaracCoutume> GetAllCaracCoutume();

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
