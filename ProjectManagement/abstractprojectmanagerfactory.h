#ifndef ABSTRACTPROJECTMANAGERFACTORY_H
#define ABSTRACTPROJECTMANAGERFACTORY_H

class AbstractProjectController;
class AbstractProjectView;

class AbstractProjectManagerFactory
{
public:
    AbstractProjectManagerFactory();

    virtual AbstractProjectView* makeProjectView() = 0;
    virtual AbstractProjectController* makeProjectController() = 0;
};

#endif // ABSTRACTPROJECTMANAGERFACTORY_H
