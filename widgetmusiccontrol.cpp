#include "widgetmusiccontrol.h"
#include "ui_widgetmusiccontrol.h"

WidgetMusicControl::WidgetMusicControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMusicControl)
{
    ui->setupUi(this);




}

WidgetMusicControl::~WidgetMusicControl()
{
    delete ui;
}
