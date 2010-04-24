#ifndef WRITEACTION_H
#define WRITEACTION_H

#include "IAction.h"

class WriteAction : public IAction
{
public:
  WriteAction();

  virtual bool	exec(LayerManager&);
};

#endif // !WRITEACTION_H
