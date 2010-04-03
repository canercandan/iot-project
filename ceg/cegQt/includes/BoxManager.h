#ifndef BOXMANAGER_H
#define BOXMANAGER_H

#include <map>
#include <list>
#include <string>

#include "AbstractBox.h"

class BoxManager
{
public:
    BoxManager();

private:
    std::map<std::string, std::list<AbstractBox *>> _patterns;
};

#endif // BOXMANAGER_H
