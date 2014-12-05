#ifndef SQLCONNECTION_H
#define SQLCONNECTION_H
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QFile>
#include <QVariant>
#include <QSqlError>
#include <QTextStream>
#include <iostream>
using namespace std;

class SQLConnection
{
  private:
    static SQLConnection* _instance;

  protected:
    SQLConnection();

    QSqlDatabase db;

  public:
    static SQLConnection* getInstance();
    ~SQLConnection();
    bool connected();
    bool drop();
    bool disconnect();
    QSqlQuery* getQuery();
  private:
    bool connect();
    bool exists();
    bool setup();
};

#endif // SQLCONNECTION_H
