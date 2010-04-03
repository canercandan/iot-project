#include "includes/AbstractBox.h"

AbstractBox::AbstractBox()
{
}

WindowGeometry const & AbstractBox::getGeometry() const
{
    return (this->_geometry);
}
