#ifndef BUILDER_WIZARD_H_
#define BUILDER_WIZARD_H_

#include "iotwizard.h"

class	BuilderWizard : public IotWizard
{
  Q_OBJECT

  public:
  BuilderWizard(const QString& title);
  virtual ~BuilderWizard(void);

private:
  virtual void  createPages(void);
  virtual void  createIntroPage(void);
  virtual void	createLicenseAgreementPage(void);
  virtual void  createConclusionPage(void);
};

#endif
