#include "dbmanager.h"
#include <QDebug>

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

QList<DomaineLoi> DbManager::GetAllDomaineLoi()
{
    QList<DomaineLoi> lois;

    QSqlQuery query("SELECT * FROM DomaineLoi");
    while (query.next())
    {
       QString intitule = query.value("intitule").toString();
       QString description = query.value("description").toString();
       int id = query.value("id").toInt();
       DomaineLoi dl;
       dl.m_Intitule = intitule;
       dl.m_Description = description;
       dl.m_Id = id;
       lois.push_back(dl);
    }

    return lois;
}


QList<CaracCoutume> DbManager::GetAllCaracCoutume()
{
    QList<CaracCoutume> caracs;

    QSqlQuery query("SELECT * FROM CaracCoutume");
    while (query.next())
    {
       QString intitule = query.value("intitule").toString();
       qDebug()<<intitule;
       QString description = query.value("description").toString();
       int id = query.value("id").toInt();
       CaracCoutume car;
       car.m_Intitule = intitule;
       car.m_Description = description;
       car.m_Id = id;
       caracs.push_back(car);
    }

    return caracs;
}
