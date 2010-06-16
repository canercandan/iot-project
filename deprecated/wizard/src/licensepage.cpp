#include "licensepage.h"

LicensePage::LicensePage(void)
{
  setupUi(this);
  connect(acceptButton, SIGNAL(clicked()), SIGNAL(completeChanged()));
  connect(rejectButton, SIGNAL(clicked()), SIGNAL(completeChanged()));
}

LicensePage::~LicensePage(void)
{
}

bool	LicensePage::isComplete(void) const
{
  return acceptButton->isChecked();
}
