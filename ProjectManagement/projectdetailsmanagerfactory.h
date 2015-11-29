#ifndef PROJECTDETAILSMANAGERFACTORY_H
#define PROJECTDETAILSMANAGERFACTORY_H

#include "abstractprojectmanagerfactory.h"

class ProjectDetailsManagerFactory : public AbstractProjectManagerFactory
{
public:
    ProjectDetailsManagerFactory();

    virtual AbstractProjectController* makeProjectController();
    virtual AbstractProjectView* makeProjectView();

};

#endif // PROJECTDETAILSMANAGERFACTORY_H
