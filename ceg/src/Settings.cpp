#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

#include "Settings.h"

Settings::Settings(QWidget *parent) :
        QDialog(parent), _dir()
{
    this->setupUi(this);
}

void Settings::on_confList_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    if (!current)
        current = previous;

    this->confStack->setCurrentIndex(this->confList->row(current));
}

void Settings::on_buttonBox_accepted()
{
    if (!this->customCheck->isChecked() && this->_dir.isEmpty())
    {
        QMessageBox::information(0, "Error", "Please define the custom xml path !");
        return;
    }
    if (this->proxyCheck->isChecked() &&
        (this->proxyHost->text().isEmpty() ||
         this->proxyName->text().isEmpty() ||
         this->proxyPassword->text().isEmpty()))
    {
        QMessageBox::information(0, "Error", "Please fill all proxy fields !");
        return;
    }

    QSettings settings("ionlythink-ceg.ini", QSettings::IniFormat);
    settings.setValue("firstStart", false);
    settings.beginGroup("general");
    settings.setValue("squareNumber", this->squareNumberBox->text());
    settings.setValue("customCheck", this->customCheck->isChecked());
    settings.setValue("customXMLPath", this->_dir);
    settings.endGroup();
    settings.beginGroup("color");
    settings.setValue("outside", this->colorOutsideCombo->currentText());
    settings.setValue("selected", this->colorSelectedCombo->currentText());
    settings.setValue("unselected", this->colorUnselectedCombo->currentText());
    settings.setValue("opacity", this->colorOpacitySlider->value());
    settings.endGroup();
    settings.beginGroup("network");
    settings.setValue("proxyCheck", this->proxyCheck->text());
    settings.setValue("host", this->proxyHost->text());
    settings.setValue("port", this->proxyPort->text());
    settings.setValue("name", this->proxyName->text());
    settings.setValue("password", this->proxyPassword->text());
    settings.endGroup();
    this->close();
}

void Settings::on_buttonBox_rejected()
{
    this->close();
}

void Settings::on_customXMLPathButton_clicked()
{
    this->_dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if (!this->_dir.isEmpty())
    {
        this->customXMLPathLabel->setText("Path (" + this->_dir + "):");
    }
}
