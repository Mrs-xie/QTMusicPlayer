#ifndef MUSICDATABASE_H
#define MUSICDATABASE_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>

class musicDatabase
{
public:
    musicDatabase();

    //建立数据库连接
    bool openDatabase(const QString &dbName);
    //建立表
    bool createTable(const QString &tableName);
    //删除表
    bool deleteTable(const QString &tableName);
    //在指定表中插入音乐数据
    bool insertData(const QString &tableName, int id, const QString name, const QString path);
    //移除音乐
    bool deleteMusic(int index);


    //显示所有音乐数据
    bool showData();

private:


};

#endif // MUSICDATABASE_H
