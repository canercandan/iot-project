#ifndef LICENSE_PAGE_H_
#define LICENSE_PAGE_H_

#include <QWizardPage>
#include "ui_licensepage.h"

class	LicensePage : public QWizardPage, public Ui_LicensePage
{
  Q_OBJECT

  public:
  LicensePage(void);
  ~LicensePage(void);

  virtual bool	isComplete(void) const;
};

#endif
