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

#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QColorDialog>
#include <QPainter>

#include "Settings.h"

Settings::Settings(QWidget *parent) :
        QDialog(parent)
{
    this->setupUi(this);
    this->on_colorOpacitySlider_valueChanged(this->colorOpacitySlider->value());
}

void Settings::on_confList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (!current)
        current = previous;

    this->confStack->setCurrentIndex(this->confList->row(current));
}

void Settings::on_buttonBox_accepted()
{
    if (!this->customCheck->isChecked() && this->customXMLPathLine->text().isEmpty())
    {
      QMessageBox::information(0, tr("Error"), tr("Please define the custom xml path !"));
      return;
    }
    if (this->serverPasswordCheckBox->isChecked() &&
        this->serverPassword->text().isEmpty())
    {
      QMessageBox::information(0, tr("Error"), tr("Please fill all proxy fields !"));
      return;
    }

    QSettings settings;
    settings.setValue("firstStart", false);
    settings.beginGroup("general");
    settings.setValue("squareNumber", this->squareNumberBox->text());
    settings.setValue("customCheck", this->customCheck->isChecked());
    settings.setValue("customXMLPath", this->customXMLPathLine->text());
    settings.endGroup();
    settings.beginGroup("color");
    settings.setValue("focus", this->colorFocusLabel->text());
    settings.setValue("blur", this->colorBlurLabel->text());
    settings.setValue("opacity", this->colorOpacitySlider->value());
    settings.endGroup();
    settings.beginGroup("server");
    settings.setValue("port", this->serverPort->text());
    settings.setValue("password", this->serverPassword->text());
    settings.endGroup();
    this->close();
}

void Settings::on_buttonBox_rejected()
{
    this->close();
}

void Settings::on_customXMLPathButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
    {
        this->customXMLPathLine->setText(dir);
    }
}

void Settings::on_colorFocusButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid()) {
        this->colorFocusLabel->setText(color.name());
        this->colorFocusLabel->setPalette(QPalette(color));
        this->colorFocusLabel->setAutoFillBackground(true);
    }
}

void Settings::on_colorBlurButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid()) {
        this->colorBlurLabel->setText(color.name());
        this->colorBlurLabel->setPalette(QPalette(color));
        this->colorBlurLabel->setAutoFillBackground(true);
    }
}

void Settings::on_colorOpacitySlider_valueChanged(int value)
{
    qreal realValue = value;
    realValue /= 100;
    QColor color(Qt::blue);
    color.setAlphaF(realValue);
    this->colorOpacityLabel->setPalette(QPalette(color));
    this->colorOpacityLabel->setAutoFillBackground(true);
}
