#ifndef MUSICPROGRESSBAR_H
#define MUSICPROGRESSBAR_H

#include <QSlider>

class MusicProgressBar : public QSlider
{
    Q_OBJECT
public:
    explicit MusicProgressBar(QWidget *parent = nullptr);

    //文件时长变化，更新当前播放文件名显示
    void onDurationChanged(qint64 duration);
    //当前文件播放位置变化，更新进度显示
    void onPositionChanged(qint64 position);

private:

signals:

};

#endif // MUSICPROGRESSBAR_H
