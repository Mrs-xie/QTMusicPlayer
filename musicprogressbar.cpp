#include "musicprogressbar.h"
#include <QDebug>

MusicProgressBar::MusicProgressBar(QWidget *parent) : QSlider(parent)
{

}

void MusicProgressBar::onDurationChanged(qint64 duration){
    //设置进度条最大值
    this->setMaximum(duration);
}

void MusicProgressBar::onPositionChanged(qint64 position){
    //设置进度条进度
    this->setSliderPosition(position);
}

