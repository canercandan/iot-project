#ifndef CLICKACTION_H
#define CLICKACTION_H

#include "IAction.h"

class ClickAction : public IAction
{
public:
  ClickAction();

  virtual bool	exec(LayerManager&);
};

#endif // !CLICKACTION_H
