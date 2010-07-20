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

#include <algorithm>

#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <QColorDialog>
#include <QPainter>
#include <QDebug>

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent), _languages(2)
{
    this->setupUi(this);
    this->on_colorOpacitySlider_valueChanged(this->colorOpacitySlider->value());

    _languages[0] = "en_US";
    _languages[1] = "fr_FR";

    // LOAD

    QSettings settings;

    settings.beginGroup("general");

    Languages::iterator it = std::find(_languages.begin(), _languages.end(), settings.value("language").toString());

    if (it != _languages.end())
	{
	    this->languageComboBox->setCurrentIndex(it - _languages.begin());
	}

    this->squareNumberBox->setValue(settings.value("squareNumber").toInt());
    this->customCheck->setChecked(settings.value("customCheck").toBool());
    this->customXMLPathLine->setText(settings.value("customXMLPath").toString());
    this->customGroupBox->setEnabled( ! this->customCheck->isChecked() );
    settings.endGroup();

    settings.beginGroup("color");
    QString color = settings.value("focus").toString();
    this->colorFocusLabel->setPalette(QPalette(color));
    this->colorFocusLabel->setAutoFillBackground(true);
    color = settings.value("blur").toString();
    this->colorBlurLabel->setPalette(QPalette(color));
    this->colorBlurLabel->setAutoFillBackground(true);
    this->colorOpacitySlider->setValue((settings.value("opacity").toDouble() * 100.));
    color = settings.value("text").toString();
    this->colorTextLabel->setPalette(QPalette(color));
    this->colorTextLabel->setAutoFillBackground(true);
    settings.endGroup();

    settings.beginGroup("server");
    this->serverPort->setValue(settings.value("port").toInt());
    this->serverPasswordCheckBox->setChecked(settings.value("passwordCheckBox").toBool());
    this->serverPassword->setText(settings.value("password").toString());
    this->serverPassword->setEnabled(this->serverPasswordCheckBox->isChecked());
    settings.endGroup();
}

void SettingsDialog::on_confList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (!current)
        current = previous;

    this->confStack->setCurrentIndex(this->confList->row(current));
}

void SettingsDialog::on_buttonBox_accepted()
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

    settings.beginGroup("general");

    if ( (unsigned int)this->languageComboBox->currentIndex() < _languages.size() )
	{
	    QString language = _languages[ this->languageComboBox->currentIndex() ];

	    if (settings.value("language").toString() != language)
		{
		    QMessageBox::information
			(0,
			 tr("Language changed"),
			 tr("The language has been changed. To apply this modification you have to restart the program.")
			 );

		    settings.setValue("language", language);
		}
	}

    settings.setValue("squareNumber", this->squareNumberBox->text());
    settings.setValue("customCheck", this->customCheck->isChecked());
    settings.setValue("customXMLPath", this->customXMLPathLine->text());
    settings.endGroup();

    settings.beginGroup("color");

    QString focusColor = this->colorFocusLabel->palette().color(QPalette::Background).name();
    QString blurColor = this->colorBlurLabel->palette().color(QPalette::Background).name();
    double opacityValue = this->colorOpacitySlider->value() / 100.;
    QString textColor = this->colorTextLabel->palette().color(QPalette::Background).name();

    if (settings.value("focus").toString() != focusColor ||
	settings.value("blur").toString() != blurColor ||
	settings.value("opacity").toDouble() != opacityValue ||
	settings.value("text").toString() != textColor)
	{
	    QMessageBox::information
		(0,
		 tr("Color changed"),
		 tr("To apply correctly colors updates, we recommand you to restart the program.")
		 );

	    settings.setValue("focus", focusColor);
	    settings.setValue("blur", blurColor);
	    settings.setValue("opacity", opacityValue);
	    settings.setValue("text", textColor);
	}

    settings.endGroup();

    settings.beginGroup("server");
    settings.setValue("port", this->serverPort->text());
    settings.setValue("passwordCheckBox", this->serverPasswordCheckBox->isChecked());
    settings.setValue("password", this->serverPassword->text());
    settings.endGroup();

    this->accept();
}

void SettingsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void SettingsDialog::on_customXMLPathButton_clicked()
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

void SettingsDialog::on_colorFocusButton_clicked()
{
	QColor color = QColorDialog::getColor(this->colorFocusLabel->palette().color(QPalette::Background), this);
    if (color.isValid()) {
        this->colorFocusLabel->setPalette(QPalette(color));
    }
}

void SettingsDialog::on_colorBlurButton_clicked()
{
	QColor color = QColorDialog::getColor(this->colorBlurLabel->palette().color(QPalette::Background), this);
    if (color.isValid()) {
        this->colorBlurLabel->setPalette(QPalette(color));
    }
}

void SettingsDialog::on_colorOpacitySlider_valueChanged(int value)
{
    qreal realValue = value;
    realValue /= 100;
    QColor color(Qt::blue);
    color.setAlphaF(realValue);
    this->colorOpacityLabel->setPalette(QPalette(color));
    this->colorOpacityLabel->setAutoFillBackground(true);
}

void SettingsDialog::on_colorTextButton_clicked()
{
	QColor color = QColorDialog::getColor(this->colorTextLabel->palette().color(QPalette::Background), this);
    if (color.isValid()) {
        this->colorTextLabel->setPalette(QPalette(color));
    }
}
