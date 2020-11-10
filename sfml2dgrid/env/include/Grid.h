#ifndef GRID_H
#define GRID_H

#include "IGrid.h"
#include <vector>

namespace env
{
	const int DEFAULT_GRID_SIZEX = 10;
	const int DEFAULT_GRID_SIZEY = 10;
	const int DEFAULT_RESOLUTIONX = 1;
	const int DEFAULT_RESOLUTIONY = 1;

	class Grid : public IGrid
	{
	public:
		virtual ~Grid() = default;
		Grid() = default;
		// functor
		virtual void iApplyOnCells(ICellFunctor&) const;
		//-- Getters
		virtual int iGetSizeX() const;
		virtual int iGetSizeY() const;
		virtual int iGetNumberOfCells() const;
		virtual int iGetResolutionX() const;
		virtual int iGetResolutionY() const;
		// Test
		virtual bool iGetCellPosition(const CELL &, int &, int &) const;
		virtual bool iGetCellCoordinates(const CELL &, int &, int &) const;
		virtual bool iGetCellNumber(int, int, CELL &) const;
		virtual bool iGetContainingCell(int, int, CELL &) const;
		virtual bool iIsWithinCell(int, int, const CELL &) const;
		virtual void iInitialize();
		//-- Setters
		void setSizeX(int);
		void setSizeY(int);
		void setResolutionX(int);
		void setResolutionY(int);
		//-- Obstacle
		virtual bool iAddObstacle(const CELL&);
		virtual bool iRemoveObstacle(const CELL&);
		virtual bool iIsObstacle(const CELL& ) const;
		// Pheromons
		virtual bool iAddPheromon(const CELL&, const float);
		virtual void iUpdatePheromon(const int&);

	private:
		int _sizex = DEFAULT_GRID_SIZEX;
		int _sizey = DEFAULT_GRID_SIZEY;
		int _resolutionx = DEFAULT_RESOLUTIONX;
		int _resolutiony = DEFAULT_RESOLUTIONY;
		std::vector<CELL> _cells;
	};
} // namespace env
#endif // !GRID_H

