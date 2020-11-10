#include "AbstractViewer.h"
#include <algorithm>
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

void ViewerMgr::iAddViewer(AbstractViewer* v)
{
	auto it = std::find(_viewers.begin(), _viewers.end(), v);
	if (it == _viewers.end())
		_viewers.push_back(v);
}

void ViewerMgr::iDraw()
{
	for (auto it = _viewers.begin(); it!=_viewers.end(); it++)
		(*it)->iDisplay();
}

void ViewerMgr::iSetApp(App *app)
{
	for (auto it = _viewers.begin(); it!=_viewers.end(); it++)
		(*it)->iSetApp(app);
}
