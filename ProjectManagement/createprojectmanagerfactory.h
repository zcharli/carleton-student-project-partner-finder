#ifndef CREATEPROJECTMANAGERFACTORY_H
#define CREATEPROJECTMANAGERFACTORY_H

#include "abstractprojectmanagerfactory.h"

class CreateProjectManagerFactory : public AbstractProjectManagerFactory
{
public:
    CreateProjectManagerFactory();

    virtual AbstractProjectView* makeProjectView();
    virtual AbstractProjectController* makeProjectController();
};

#endif // CREATEPROJECTMANAGERFACTORY_H
