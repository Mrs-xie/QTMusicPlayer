#ifndef MUSICITEM_H
#define MUSICITEM_H
#include <QObject>
#include <QString>

class MusicItem : public QObject
{
    Q_OBJECT
public:
    explicit MusicItem(QObject *parent = nullptr);
    explicit MusicItem(int id, const QString &name, const QString &path, QObject *parent = nullptr);

private:
    //音乐id，唯一标识
    int id;
    //名称
    QString name;
    //路径
    QString path;

    void SetId(int id) { this->id = id; }
    void SetName(const QString name) { this->name = name; }
    void SetPath(const QString path) { this->path = path; }

    int GetId(){ return id; }
    QString GetName(){ return name; }
    QString GetPath(){ return path; }


signals:

};

#endif // MUSICITEM_H
