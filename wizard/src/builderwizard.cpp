#include <QLabel>
#include <QLayout>
#include <iostream>
#include "licensepage.h"
#include "builderwizard.h"

BuilderWizard::BuilderWizard(const QString& title)
  : IotWizard(title)
{
  createPages();
}

BuilderWizard::~BuilderWizard(void)
{
}

void	BuilderWizard::createPages(void)
{
  createIntroPage();
  createLicenseAgreementPage();
  createConclusionPage();
}

void	BuilderWizard::createIntroPage(void)
{
  QWizardPage *page = new QWizardPage;
  page->setTitle(tr("Setup - Iot Builder"));

  QLabel *label = new QLabel(tr("Welcome to the Iot Builder Setup Wizard."));
  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);
  addPage(page);
}

void	BuilderWizard::createLicenseAgreementPage(void)
{
  QWizardPage*	page = new LicensePage;
  addPage(page);
}

void	BuilderWizard::createConclusionPage(void)
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("Conclusion");

  QLabel *label = new QLabel(tr("Thank you for installing our product."));
  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);
  addPage(page);
}
