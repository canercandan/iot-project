#include "ClickAction.h"

ClickAction::ClickAction(int nbClick): _nbClick()
{
}

bool	ClickAction::exec(LayerManager&)
{
  return true;
}
