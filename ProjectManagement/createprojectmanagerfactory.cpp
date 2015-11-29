#include "createprojectmanagerfactory.h"

#include "createprojectcontroller.h"
#include "createprojectwidget.h"

CreateProjectManagerFactory::CreateProjectManagerFactory()
{
}

AbstractProjectView* CreateProjectManagerFactory::makeProjectView()
{
    CreateProjectWidget* pCreateView = new CreateProjectWidget();
    return pCreateView;
}

AbstractProjectController* CreateProjectManagerFactory::makeProjectController()
{
    CreateProjectController *pCreateController = new CreateProjectController();
    return pCreateController;
}
