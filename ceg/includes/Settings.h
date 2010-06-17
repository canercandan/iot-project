#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "ui_settings.h"

class Settings : public QDialog, private Ui_Settings
{
    Q_OBJECT
public:
    Settings(QWidget *parent = 0);

public slots:
    void on_confList_currentItemChanged(QListWidgetItem*, QListWidgetItem*);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_customXMLPathButton_clicked();

private:
    QString _dir;
};

#endif // SETTINGS_H
