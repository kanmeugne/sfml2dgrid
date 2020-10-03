#ifndef IGRID_H
#define IGRID_H

#include <tuple>

class IGrid
{
public:
	typedef unsigned int CELL;
	
	// Functor definition to apply on cell
	// We can inherit from this to function
	// to apply on cells
	class ICellFunctor {
	public:
		virtual void operator()(
			const CELL // cell_id
		) = 0;
	};
	virtual ~IGrid() = default ;
	virtual unsigned int iGetSizeX() const = 0;
	virtual unsigned int iGetSizeY() const = 0;
	virtual unsigned int iGetNumberOfCells() const = 0;
	virtual unsigned int iGetResolutionX() const = 0;
	virtual unsigned int iGetResolutionY() const = 0;
	//-- functors
	virtual void iApplyOnCells(ICellFunctor&) const = 0;
	//-- Test
	virtual bool iGetCellPosition(
		CELL, // cell_id
		unsigned int&, // posx
		unsigned int& // posy
	) const = 0;
	virtual bool iGetCellCoordinates(
		CELL, // cell_id
		unsigned int&, // row_number
		unsigned int& // column_number
	) const = 0;
	virtual bool iGetCellNumber(
		unsigned int, // row_number
		unsigned int, // column_number
		CELL&
	) const = 0;
	virtual bool iGetContainingCell(
		const unsigned int, // posx
		const unsigned int, // posy
		CELL& // cell_id
	) const = 0;
	virtual bool iIsWithinCell(
		const unsigned int, // posx
		const unsigned int, // posy
		CELL // cell_id
	) const = 0;
	// initialize : the vector of cells, obstacle mask, etc.
	virtual void iInitialize() = 0;
	// set a cell as obstacle
	virtual bool iAddObstacle(const CELL /*cell_id*/) = 0;
	// return the obstacle status : true if obstacle, false otherwise
	virtual bool iIsObstacle(const CELL /*cell_id*/) const = 0;
};
#endif // !IGRID_H
