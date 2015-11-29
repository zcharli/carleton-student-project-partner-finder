#include "abstractprojectcontroller.h"

AbstractProjectController::AbstractProjectController()
{
}

void AbstractProjectController::setViewForController(AbstractProjectView *viewForController)
{
    this->view = viewForController;
}
