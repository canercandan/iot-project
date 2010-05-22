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

  void setVisible(bool visible);

 protected:
  void closeEvent(QCloseEvent *event);

  private slots:
  void setIcon();
  void iconActivated(QSystemTrayIcon::ActivationReason reason);
  void showMessage();

 private:
  void createIconGroupBox();
  void createMessageGroupBox();
  void createActions();
  void createTrayIcon();

  QIcon     *icon;
  QGroupBox *iconGroupBox;
  QComboBox *iconSystray;

  QGroupBox *messageGroupBox;
  QComboBox *typeComboBox;

  QAction *minimizeAction;
  QAction *maximizeAction;
  QAction *restoreAction;
  QAction *networkAction;
  QAction *svnAction;
  QAction *configAction;
  QAction *quitAction;

  QSystemTrayIcon *trayIcon;
  QMenu *trayIconMenu;
};

class test_window : public QWidget
{

};

#endif
