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
	virtual unsigned int iGetSizeX() const;
	virtual unsigned int iGetSizeY() const;
	virtual unsigned int iGetNumberOfCells() const;
	virtual unsigned int iGetResolutionX() const;
	virtual unsigned int iGetResolutionY() const;
	// Test
	virtual bool iGetCellPosition(CELL, unsigned int&, unsigned int&) const;
	virtual bool iGetCellCoordinates(CELL, unsigned int&, unsigned int&) const;
	virtual bool iGetCellNumber(unsigned int, unsigned int, CELL&) const;
	virtual bool iGetContainingCell(
		const unsigned int, // posx
		const unsigned int, // posy
		CELL& // output cellid
	) const;
	virtual bool iIsWithinCell(
		const unsigned int, // posx
		const unsigned int, // posy
		CELL // cellid
	) const;
	virtual void iInitialize() ;
	virtual bool iIsObstacle(const CELL) const;
	virtual bool iAddObstacle(const CELL);
	virtual bool iRemoveObstacle(const CELL);
	//-- functors
	virtual void iApplyOnCells(ICellFunctor&) const;
	//-- Setters
	void setSizeX(unsigned int);
	void setSizeY(unsigned int);
	void setResolutionX(unsigned int);
	void setResolutionY(unsigned int);
private:
	unsigned int _sizex = 10;
	unsigned int _sizey = 10;
	unsigned int _resolutionx = 1;
	unsigned int _resolutiony = 1;
	std::vector<CELL> _cells;
};
#endif // !GRID_H
