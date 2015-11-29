#include "projectdetailsmanagerfactory.h"

#include "projectdetailsview.h"
#include "projectdetailscontroller.h"

ProjectDetailsManagerFactory::ProjectDetailsManagerFactory()
{
}

AbstractProjectView* ProjectDetailsManagerFactory::makeProjectView()
{
    ProjectDetailsView* pDetailsView = new ProjectDetailsView();
    return pDetailsView;
}

AbstractProjectController* ProjectDetailsManagerFactory::makeProjectController()
{
    ProjectDetailsController *pDetailsController = new ProjectDetailsController();
    return pDetailsController;
}
