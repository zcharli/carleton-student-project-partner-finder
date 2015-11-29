#ifndef PROJECTLISTMANAGERFACTORY_H
#define PROJECTLISTMANAGERFACTORY_H

#include "abstractprojectmanagerfactory.h"

class ProjectListManagerFactory : public AbstractProjectManagerFactory
{
public:
    ProjectListManagerFactory();

    virtual AbstractProjectView* makeProjectView();
    virtual AbstractProjectController* makeProjectController();

};

#endif // PROJECTLISTMANAGERFACTORY_H
