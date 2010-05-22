#include <QtGui>
#include "systray.h"

Systray::Systray()
{
    createIconGroupBox();
    createMessageGroupBox();
    
    createActions();
    createTrayIcon();
    
    connect(iconSystray, SIGNAL(currentIndexChanged(int)), this, SLOT(setIcon()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    
    iconSystray->setCurrentIndex(1);
    trayIcon->show();
    
    setWindowTitle(tr("IOT (I Only Think)"));
    resize(400, 300);
}

void Systray::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    networkAction->setEnabled(visible);
    svnAction->setEnabled(visible);
    configAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QWidget::setVisible(visible);
}

void Systray::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        showMessage();
        hide();
        event->ignore();
    }
}

void Systray::setIcon()
{
    QIcon icon = iconSystray->itemIcon(0);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);
    
    trayIcon->setToolTip(iconSystray->itemText(0));
}

void Systray::iconActivated(QSystemTrayIcon::ActivationReason reason) // Click on the systray
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        showMessage();
        break;
    case QSystemTrayIcon::DoubleClick:
        iconSystray->setCurrentIndex((iconSystray->currentIndex() + 1) % iconSystray->count());
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void Systray::showMessage()
{
    QString text_title_popup = "IOT";
    QString text_popup = "The program will keep running in the system tray.";
    
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(typeComboBox->itemData(typeComboBox->currentIndex()).toInt());
    trayIcon->showMessage(text_title_popup, text_popup, icon, 1000);
}

void Systray::createIconGroupBox()
{ 
    iconGroupBox = new QGroupBox();
    iconSystray = new QComboBox;
    iconSystray->addItem(QIcon(":/images/img.png"), tr("IOT"));
}

void Systray::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox();
    
    typeComboBox = new QComboBox;
    typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
    typeComboBox->addItem(style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("Information"), QSystemTrayIcon::Information);
    
    typeComboBox->setCurrentIndex(1);
}

void Systray::createActions() // Right click on the systray
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    
    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));
    
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    
    networkAction = new QAction(tr("&Network"), this);
    connect(networkAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    svnAction = new QAction(tr("&SVN"), this);
    connect(svnAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    configAction = new QAction(tr("&Config"), this);
    connect(configAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Systray::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(networkAction);
    trayIconMenu->addAction(svnAction);
    trayIconMenu->addAction(configAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
