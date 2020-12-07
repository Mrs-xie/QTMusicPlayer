#ifndef WIDGETMUSICCONTROL_H
#define WIDGETMUSICCONTROL_H

#include <QWidget>

namespace Ui {
class WidgetMusicControl;
}

class WidgetMusicControl : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMusicControl(QWidget *parent = nullptr);
    ~WidgetMusicControl();

private:
    Ui::WidgetMusicControl *ui;
};

#endif // WIDGETMUSICCONTROL_H
