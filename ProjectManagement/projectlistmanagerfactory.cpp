#include "projectlistmanagerfactory.h"

#include "projectlistview.h"
#include "projectlistcontroller.h"

ProjectListManagerFactory::ProjectListManagerFactory()
{
}

AbstractProjectView* ProjectListManagerFactory::makeProjectView()
{
    ProjectListView* pListView = new ProjectListView();
    return pListView;
}

AbstractProjectController* ProjectListManagerFactory::makeProjectController()
{
    ProjectListController *pListController = new ProjectListController();
    return pListController;
}
