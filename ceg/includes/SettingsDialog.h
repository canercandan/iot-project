#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <vector>

#include <QDialog>
#include <QPaintEvent>

#include "ui_settingsDialog.h"

class SettingsDialog : public QDialog, private Ui_SettingsDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent = 0);

public slots:
    void on_confList_currentItemChanged(QListWidgetItem*, QListWidgetItem*);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_customXMLPathButton_clicked();
    void on_colorBlurButton_clicked();
    void on_colorFocusButton_clicked();
    void on_colorOpacitySlider_valueChanged(int value);

private:
    typedef std::vector< QString > Languages;
    Languages _languages;
};

#endif // SETTINGSDIALOG_H
