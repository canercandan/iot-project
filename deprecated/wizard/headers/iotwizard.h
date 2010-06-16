#ifndef IOT_WIZARD_H_
#define IOT_WIZARD_H_

#include <QWizard>

// More information:
// http://doc.qt.nokia.com/4.6/qwizard.html

class	IotWizard : public QWizard
{
  Q_OBJECT

  public:
  IotWizard(const QString& title);
  virtual ~IotWizard(void);

protected:
  virtual void	createPages(void) = 0;
  virtual void	createIntroPage(void) = 0;
  virtual void	createLicenseAgreementPage(void) = 0;
  virtual void	createConclusionPage(void) = 0;
};

#endif
