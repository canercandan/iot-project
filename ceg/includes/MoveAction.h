#ifndef MOVEACTION_H
#define MOVEACTION_H

#include "IAction.h"

class MoveAction : public IAction
{
public:
  MoveAction();

  virtual bool	exec(LayerManager&);
};

#endif // !MOVEACTION_H
