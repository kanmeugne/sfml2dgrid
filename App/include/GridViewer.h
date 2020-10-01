#ifndef GRIDVIEWER_H
#define GRIDVIEWER_H

#include "AbstractViewer.h"

class App;
class GridViewer : public AbstractViewer
{
public:
	GridViewer() = default;
	virtual ~GridViewer() = default;
protected:
	virtual void iDraw();
};
#endif // !GRIDVIEWER_H
