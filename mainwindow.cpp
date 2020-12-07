#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    //点击开始/暂停 -> 开始/暂停播放
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::slotButtonStart);
    //点击上一首 -> 上一首
    connect(ui->btnLastMusic, &QPushButton::clicked, this, &MainWindow::slotButtonLast);
    //点击下一首 -> 下一首
    connect(ui->btnNextMusic, &QPushButton::clicked, this, &MainWindow::slotButtonNext);


    //音乐改变时 -> 改变当前音乐名
    connect(playerList, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::slotCurrentMusic);

    //音乐改变时 -> 设置进度条为当前音乐长度
    connect(player, &QMediaPlayer::durationChanged, ui->musicProgressBar, &MusicProgressBar::onDurationChanged);
    connect(player, &QMediaPlayer::durationChanged, ui->labelMusicTime, &LableMusicTime::onDurationChanged);
    //音乐播放位置改变时 -> 设置进度条与音乐当前位置，与音乐同步
    connect(player, &QMediaPlayer::positionChanged, ui->musicProgressBar, &MusicProgressBar::onPositionChanged);
    connect(player, &QMediaPlayer::positionChanged, ui->labelMusicTime, &LableMusicTime::onPositionChanged);
    //手动拖动进度条是 -> 设置音乐与进度条同步
    connect(ui->musicProgressBar, &MusicProgressBar::valueChanged, [=](int position){
        //避免进度条与musicplayer互相刷新而造成卡顿
        if(qAbs (player->position() -position ) > 99){
            player->setPosition(position);
        }
    });

    //双击listWidget中的一首音乐 -> 播放该音乐
    connect(ui->listWidget, &QListWidget::doubleClicked, this, &MainWindow::slotDoubleClickMusic);

    //点击添加按钮 -> 添加音乐
    connect(ui->btnAddMusic, &QPushButton::clicked, this, &MainWindow::slotAddMusic);

    //点击移除按钮 -> 移除音乐
    connect(ui->btnDeleteMusic, &QPushButton::clicked, this, &MainWindow::slotRemoveMusic);

    //拖动音量进度条 -> 改变音量并解除静音
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::slotVolumeChanged);

    //点击音量键 -> 静音/解除静音
    connect(ui->btnVolume, &QPushButton::clicked, this, &MainWindow::slotMute);

    //点击播放模式键 -> 改变播放模式
    connect(ui->btnPlayMod, &QPushButton::clicked, this, &MainWindow::slotPlayMod);

    //静音状态改变时 -> 改变静音键图标
    connect(player, &QMediaPlayer::mutedChanged, ui->btnVolume, [=](bool muted){

        if(muted){
            ui->btnVolume->setStyleSheet("QPushButton{border-image:url(:/res/slience.png)}");
        } else {
            ui->btnVolume->setStyleSheet("QPushButton{border-image:url(:/res/volume.png)}");
        }

    });


}

//初始化
void MainWindow::init(){

    setWindowIcon(QIcon(":/res/icon.png"));

    playerList = new QMediaPlaylist;
    player = new QMediaPlayer;

    //设置列表播放模式为循环模式。
    playerList->setPlaybackMode(QMediaPlaylist::Loop);

    player->setPlaylist(playerList);

    //设置播放图片
    QPixmap pix(":/res/musicPlaying.png");
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(pix);

    //建立数据库连接，建立音乐表
    database.openDatabase("musicDatabase");
    database.createTable("music");

    //将数据库中已存在的音乐添加到playerList中, 并在WidgetList上显示
    QSqlQuery query;
    query.exec("SELECT name, path FROM music");
    while (query.next()) {
        QString name = query.value(0).toString();
        QString path = query.value(1).toString();
        ui->listWidget->addItem(name);
        playerList->addMedia(QUrl::fromLocalFile(path));
        id++;
    }

}

//获取路径下所有音乐文件
QStringList MainWindow::getFileNames(const QString &path){
    QDir dir(path);
    QStringList nameFilters;
    nameFilters << "*.mp3";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    return files;

}

//播放，暂停音乐
void MainWindow::slotButtonStart(){
    if(!isPlaying){
        ui->btnPause->setStyleSheet("QPushButton{border-image:url(:/res/pause.png)}");
        isPlaying = true;
        player->play();
        //音乐播放动图
        ui->label->setMovie(movie);
        movie->start();

    }else{
        ui->btnPause->setStyleSheet("QPushButton{border-image:url(:/res/start.png)}");        isPlaying = false;
        player->pause();
        //停止动图
        movie->stop();
    }
}

//上一首
void MainWindow::slotButtonLast(){
    playerList->previous();
}

//下一首
void MainWindow::slotButtonNext(){
    playerList->next();
}

//音乐改变时 -> 获取当前音乐名称
void MainWindow::slotCurrentMusic(){
    int index = playerList->currentIndex();
    ui->listWidget->setCurrentRow(index);
    ui->labelMusicName->setText(ui->listWidget->currentItem()->text());
}

//双击listWidget中的一首音乐 -> 播放该音乐
void MainWindow::slotDoubleClickMusic(){
    ui->labelMusicName->setText( ui->listWidget->currentItem()->text() );
    playerList->setCurrentIndex( ui->listWidget->currentRow() );
    //开始播放，设置播放按钮位为暂停
    ui->btnPause->setStyleSheet("QPushButton{border-image:url(:/res/pause.png)}");
    isPlaying = true;
    player->play();
    //设置动图播放
    ui->label->setMovie(movie);
    movie->start();
}

//添加音乐
void MainWindow::slotAddMusic(){

    QString initialName=QDir::homePath();
    QStringList pathList=QFileDialog::getOpenFileNames(this, "选择文件", initialName, "*.mp3");

    for(int i=0; i<pathList.size(); ++i)
    {
        QString path=QDir::toNativeSeparators(pathList.at(i));
        if(!path.isEmpty())
        {
            QString fileName=path.split("\\").last().split(".").first();

            //添加到数据库
            database.insertData("music", id++, fileName, path);
            //在QMediaPlayList中添加音乐
            playerList->addMedia(QUrl::fromLocalFile(path));
            //添加到WidgetList中
            ui->listWidget->addItem(fileName);

        }
    }

}

//移除音乐
void MainWindow::slotRemoveMusic(){
    int index = ui->listWidget->currentRow();
    //从QMediaPlayList中移除
    playerList->removeMedia(index);
    //从WidgetList中移除
    ui->listWidget->takeItem(index);
    //从数据库中移除
    database.deleteMusic(index);

    ui->labelMusicName->setText(ui->listWidget->currentItem()->text());
}

//静音
void MainWindow::slotMute(){

    if(player->isMuted()){
        player->setMuted(false);
    }else{
        player->setMuted(true);
    }

}

//改变音量
void MainWindow::slotVolumeChanged(int volume){
    player->setVolume(volume);
    if(player->isMuted()){
        player->setMuted(false);
    }
}

//改变播放模式
void MainWindow::slotPlayMod(){

    if(playerList->playbackMode() == QMediaPlaylist::Loop){
        //随机模式
        playerList->setPlaybackMode(QMediaPlaylist::Random);
        ui->btnPlayMod->setStyleSheet("QPushButton{border-image:url(:/res/random.png)}");
    }else if(playerList->playbackMode() == QMediaPlaylist::Random){
        //顺序模式
        playerList->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->btnPlayMod->setStyleSheet("QPushButton{border-image:url(:/res/Sequential.png)}");
    }else{
        //循环模式
        playerList->setPlaybackMode(QMediaPlaylist::Loop);
        ui->btnPlayMod->setStyleSheet("QPushButton{border-image:url(:/res/loop.png)}");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

