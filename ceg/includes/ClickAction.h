#ifndef CLICKACTION_H
#define CLICKACTION_H

#include "IAction.h"

class ClickAction : public IAction
{
public:
  ClickAction(int nbClick);

  virtual bool	exec(LayerManager&);
private:
  int	_nbClick;
};

#endif // !CLICKACTION_H
