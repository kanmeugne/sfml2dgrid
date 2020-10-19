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
	virtual int iGetSizeX() const;
	virtual int iGetSizeY() const;
	virtual int iGetNumberOfCells() const;
	virtual int iGetResolutionX() const;
	virtual int iGetResolutionY() const;
	// Test
	virtual bool iGetCellPosition(CELL, int&, int&) const;
	virtual bool iGetCellLocation(CELL, int&, int&) const;
	virtual bool iGetCellNumberFromPosition(int, int, CELL&) const;
	virtual bool iGetContainingCell(
		int, // posx
		int, // posy
		CELL& // output cellid
	) const;
	virtual bool iIsWithinCell(
		int, // posx
		int, // posy
		CELL // cellid
	) const;
	virtual void iInitialize() ;
	virtual bool iIsObstacle(const CELL) const;
	virtual bool iAddObstacle(const CELL);
	virtual bool iRemoveObstacle(const CELL);
	virtual bool iAddPheromon(const CELL, const float);
	virtual void iUpdatePheromon(const int&);
	virtual bool iGetPheromon(const CELL /*cell*/, float& /*value*/) const;
	//-- functors
	virtual void iApplyOnCells(ICellFunctor&) const;
	//-- Setters
	void setSizeX(int);
	void setSizeY(int);
	void setResolutionX(int);
	void setResolutionY(int);
private:
	int _sizex = 10;
	int _sizey = 10;
	int _resolutionx = 1;
	int _resolutiony = 1;
	std::vector<bool> _cells;
	std::vector<float> _pheromons;
};
#endif // !GRID_H
