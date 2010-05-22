#ifndef WINDOW_H
#define WINDOW_H

#include <QSystemTrayIcon>
#include <QWidget>

class QAction;
class QComboBox;
class QGroupBox;
class QMenu;

class Systray : public QWidget
{
    Q_OBJECT

public:
    Systray();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void createActions();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;

    QMenu *trayIconMenu;
    QAction *restoreAction;
    QAction *networkAction;
    QAction *svnAction;
    QAction *configAction;
    QAction *quitAction;
};
#endif
