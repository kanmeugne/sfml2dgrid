#ifndef GRIDVIEWER_H
#define GRIDVIEWER_H

#include "AbstractViewer.h"
#include "geometry.h"
#include <vector>


class GridViewer : public AbstractViewer
{
public:
	GridViewer() = default;
	virtual void initialize();
	virtual ~GridViewer() = default;
protected:
	virtual void iDraw();
private:
	void drawLines(geometry::ISegmentFunctor&) const;
	std::vector<geometry::Segment> _lines;
};
#endif // !GRIDVIEWER_H
