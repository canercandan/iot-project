#include "ZoomAction.h"

ZoomAction::ZoomAction(bool zoom) : _zoom(zoom)
{

}

bool	ZoomAction::exec(LayerManager&)
{
    return (true);
}
