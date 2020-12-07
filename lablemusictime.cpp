#include "lablemusictime.h"

LableMusicTime::LableMusicTime(QWidget *parent) : QLabel(parent)
{

}

void LableMusicTime::onDurationChanged(qint64 duration){
    int secs = duration/1000; //全部秒数
    int mins = secs/60;//分
    secs = secs % 60;//秒
    durationTime = QString::asprintf("%.2d:%.2d",mins,secs);
    setText(positionTime+"/"+durationTime);
}

void LableMusicTime::onPositionChanged(qint64 position){
    int secs = position/1000;
    int mins = secs/60;
    secs = secs % 60;
    positionTime = QString::asprintf("%.2d:%.2d",mins,secs);
    setText(positionTime+"/"+durationTime);
}
