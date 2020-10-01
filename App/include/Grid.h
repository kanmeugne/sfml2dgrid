#ifndef GRID_H
#define GRID_H

#include "IGrid.h"
#include <vector>

class Grid : public IGrid
{
public:
	virtual ~Grid() = default;
	Grid() = default;
	//-- Getters
	virtual size_t iGetSizeX() const;
	virtual size_t iGetSizeY() const;
	virtual size_t iGetNumberOfCells() const;
	virtual double iGetResolutionX() const;
	virtual double iGetResolutionY() const;
	// Test
	virtual bool iGetCellPosition(CELL, double&, double&) const;
	virtual bool iGetCellCoordinates(CELL, size_t&, size_t&) const;
	virtual bool iGetCellNumber(size_t, size_t, CELL&) const;
	virtual bool iGetContainingCell(
		const float, // posx
		const float, // posy
		CELL& // output cellid
	) const;
	virtual bool iIsWithinCell(
		const float, // posx
		const float, // posy
		CELL // cellid
	) const;
	virtual void iInitialize() ;
	virtual bool iIsObstacle(const CELL) const;
	virtual bool iAddObstacle(const CELL);
	virtual bool iRemoveObstacle(const CELL);
	//-- functors
	virtual void iApplyOnCells(ICellFunctor&) const;
	virtual void iApplyOnSegments(ISegmentFunctor&) const;
	//-- Setters
	void setSizeX(size_t);
	void setSizeY(size_t);
	void setResolutionX(double);
	void setResolutionY(double);
private:
	size_t _sizex = 10;
	size_t _sizey = 10;
	double _resolutionx = 1.;
	double _resolutiony = 1.;
	std::vector<CELL> _cells;
	std::vector<Segment> _lines;
};
#endif // !GRID_H
