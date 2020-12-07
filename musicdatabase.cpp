#include "musicdatabase.h"
#include <QMessageBox>

musicDatabase::musicDatabase()
{

}

//建立数据库连接
bool musicDatabase::openDatabase(const QString &dbName){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if(!db.open()){
        qDebug() << "open database failed!";
        return false;
    }

    return true;

}

//建立表
bool musicDatabase::createTable(const QString &tableName){

    QSqlQuery query;

    QString str = "CREATE TABLE " + tableName + "("
            + "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            + "name VARCHAR,"
            + "path VARCHAR)";

    if(!query.exec(str)) {
        qDebug() << "craete table failed:";
        qDebug() << query.lastError().text();

        return false;
    }

    return true;

}

//删除表
bool musicDatabase::deleteTable(const QString &tableName){

    QSqlQuery query;

    QString str = "DROP TABLE " + tableName ;

    if(!query.exec(str)) {
        qDebug() << "delete table failed:";
        qDebug() << query.lastError().text();

        return false;
    }

    return true;
}


//在指定表中插入音乐数据
bool musicDatabase::insertData(const QString &tableName, int id, const QString name, const QString path){

    QSqlQuery query;

    QString str = QString("INSERT INTO %1 (id, name, path)"
                  "VALUES ( %2, '%3', '%4')").arg(tableName).arg(id).arg(name).arg(path);

    if(!query.exec(str)) {
        qDebug() << "insert data failed:";
        qDebug() << query.lastError().text();

        return false;
    }

    return true;

}

//移除音乐
bool musicDatabase::deleteMusic(int index){

    QSqlQuery query;

    QString str = QString("DELETE FROM music "
                          "WHERE "
                          "id=(SELECT MAX(id) "
                          "FROM "
                          "(SELECT id FROM music LIMIT %1))").arg(index+1);

    qDebug() << str;
    if(!query.exec(str)) {
        qDebug() << "delete music failed:";
        qDebug() << query.lastError().text();

        return false;
    }

    return true;

}


//显示所有音乐数据
bool musicDatabase::showData(){

    QSqlQuery query;

    query.exec("SELECT id, name, path FROM music");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString path = query.value(2).toString();
        qDebug() << id << ":" << name << ": " << path;
    }


    return true;

}

