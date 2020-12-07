#include "musicitem.h"

MusicItem::MusicItem(QObject *parent) : QObject(parent)
{

}

MusicItem::MusicItem(int id, const QString &name, const QString &path, QObject *parent) : QObject(parent)
{
    this->id = id;
    this->name = name;
    this->path = path;
}
