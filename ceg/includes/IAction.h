#ifndef IACTION_H
#define IACTION_H

class LayerManager;

class IAction
{
public:
  virtual bool	exec(LayerManager&) = 0;
};

#endf // IACTION_H
