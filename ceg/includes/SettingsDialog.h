// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* IOT Copyright (C) 2010 CEG development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: CEG <ceg@ionlythink.com>, http://www.ionlythink.com
 */

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <vector>

#include <QDialog>
#include <QPaintEvent>

#include "ui_settingsDialog.h"

/*
  Classe de Configuration
  Permet de parametrer l'application via une interface graphique.
  */
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

private:
    Languages _languages;
};

#endif // SETTINGSDIALOG_H
