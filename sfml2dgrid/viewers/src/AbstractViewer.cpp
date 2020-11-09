#include "AbstractViewer.h"
using namespace viewers;

void AbstractViewer::iSetApp(App *app)
{
	_app = app;
}

void AbstractViewer::iActivate()
{
	_active = true;
}

void AbstractViewer::iDeactivate()
{
	_active = false;
}

bool AbstractViewer::iIsActive() const
{
	return _active;
}

void AbstractViewer::iDisplay()
{
    if (iIsActive())
        iDraw();
}