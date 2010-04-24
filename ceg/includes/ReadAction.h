#ifndef READACTION_H
#define READACTION_H

#include "IAction.h"

class ReadAction : public IAction
{
public:
  ReadAction();

  virtual bool	exec(LayerManager&);
};

#endif // !READACTION_H
