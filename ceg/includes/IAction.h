#ifndef IACTION_H
#define IACTION_H

class LayerManager;

class IAction
{
public:
    ~IAction(){}
    virtual bool	exec(LayerManager&) = 0;
};

#endif // IACTION_H
