#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QWidget>

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QDir>
#include <QIcon>
#include <QPushButton>
#include <QFileDialog>
#include <QMovie>

#include "musicDatabase.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //音乐播放列表和播放器
    QMediaPlaylist * playerList;
    QMediaPlayer * player;
    //是否正在播放
    bool isPlaying = false;
    //播放动图
    QMovie * movie = new QMovie(":/res/musicPlaying.gif");
    //数据库控制类
    musicDatabase database;
    //音乐id好
    int id = 0;


    //初始化
    void init();
    //获取路径下所有音乐文件
    QStringList getFileNames(const QString&);


    //槽函数
    //点击暂停/播放 -> 播放，暂停音乐
    void slotButtonStart();
    //点击上一首 -> 上一首
    void slotButtonLast();
    //点击下一首 -> 下一首
    void slotButtonNext();
    //音乐改变时 -> 获取当前音乐名称
    void slotCurrentMusic();
    //双击listWidget中的一首音乐 -> 播放该音乐
    void slotDoubleClickMusic();
    //添加音乐
    void slotAddMusic();
    //移除音乐
    void slotRemoveMusic();
    //静音
    void slotMute();
    //改变音量
    void slotVolumeChanged(int volume);
    //改变播放模式
    void slotPlayMod();


};
#endif // MAINWINDOW_H
