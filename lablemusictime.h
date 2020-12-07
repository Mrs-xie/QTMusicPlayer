#ifndef LABLEMUSICTIME_H
#define LABLEMUSICTIME_H

#include <QLabel>

class LableMusicTime : public QLabel
{
    Q_OBJECT
public:
    explicit LableMusicTime(QWidget *parent = nullptr);
    //文件时长变化，更新当前播放文件名显示
    void onDurationChanged(qint64 duration);
    //当前文件播放位置变化，更新进度显示
    void onPositionChanged(qint64 position);

private:
    QString durationTime = "00:00";
    QString positionTime = "00:00";

signals:

};

#endif // LABLEMUSICTIME_H
