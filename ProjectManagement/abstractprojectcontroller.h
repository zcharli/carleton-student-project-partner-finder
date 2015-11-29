#ifndef ABSTRACTPROJECTCONTROLLER_H
#define ABSTRACTPROJECTCONTROLLER_H

#include "abstractprojectview.h"

class AbstractProjectController
{
protected:
    AbstractProjectView* view;

public:
    AbstractProjectController();

    void setViewForController(AbstractProjectView*);
};

#endif // ABSTRACTPROJECTCONTROLLER_H
