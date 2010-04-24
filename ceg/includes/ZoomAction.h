#ifndef ZOOMACTION_H
#define ZOOMACTION_H

#include "IAction.h"

class ZoomAction : public IAction
{
public:
	ZoomAction(bool zoom);

	virtual bool	exec(LayerManager&);

private:
	bool	_zoom;
};

#endif // !ZOOMACTION_H
