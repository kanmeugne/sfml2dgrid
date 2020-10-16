#ifndef IGRID_H
#define IGRID_H

class IGrid
{
public:
	typedef int CELL;
	
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
	virtual int iGetSizeX() const = 0;
	virtual int iGetSizeY() const = 0;
	virtual int iGetNumberOfCells() const = 0;
	virtual int iGetResolutionX() const = 0;
	virtual int iGetResolutionY() const = 0;
	//-- functors
	virtual void iApplyOnCells(ICellFunctor&) const = 0;
	//-- Test
	virtual bool iGetCellPosition(
		CELL, // cell_id
		int&, // posx
		int& // posy
	) const = 0;
	virtual bool iGetCellCoordinates(
		CELL, // cell_id
		int&, // row_number
		int& // column_number
	) const = 0;
	virtual bool iGetCellNumber(
		int, // row_number
		int, // column_number
		CELL&
	) const = 0;
	virtual bool iGetContainingCell(
		int, // posx
		int, // posy
		CELL& // cell_id
	) const = 0;
	virtual bool iIsWithinCell(
		int, // posx
		int, // posy
		CELL // cell_id
	) const = 0;
	// initialize : the vector of cells, obstacle mask, etc.
	virtual void iInitialize() = 0;
	// set a cell as obstacle
	virtual bool iAddObstacle(const CELL /*cell_id*/) = 0;
	// remove obstacle on a cell
	virtual bool iRemoveObstacle(const CELL /*cell_id*/) = 0;
	// return the obstacle status : true if obstacle, false otherwise
	virtual bool iIsObstacle(const CELL /*cell_id*/) const = 0;
	// pheromons
	virtual bool iAddPheromon(
		const CELL, // cell no
		const float // pheromon deposit
	) = 0;
	virtual bool iGetPheromon( const CELL /*cell*/, float& /*value*/) const = 0;
	virtual void iUpdatePheromon(const int&) = 0;
};
#endif // !IGRID_H
