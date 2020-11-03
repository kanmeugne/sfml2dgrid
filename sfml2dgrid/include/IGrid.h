#ifndef IGRID_H
#define IGRID_H

#include <tuple>

namespace env
{
	struct CELL
	{
		int _id; // id of the cell
		CELL() = default;
		CELL(const CELL &) = default;
	};

	class IGrid
	{
	public:
		virtual ~IGrid() = default;
		// returns the width
		virtual int iGetSizeX() const = 0;
		// return the height
		virtual int iGetSizeY() const = 0;
		// return the number of cells in the grid
		virtual int iGetNumberOfCells() const = 0;
		// get the width of a cell (in terms of pixels)
		virtual int iGetResolutionX() const = 0;
		// get the height of a cell (in terms of pixels)
		virtual int iGetResolutionY() const = 0;
		//-- Test
		// relative position of a cell according to its id
		virtual bool iGetCellPosition(
			const CELL &, // cell
			int &,		  // posx
			int &		  // posy
		) const = 0;
		// coordinates of a cell accoring to its id
		virtual bool iGetCellCoordinates(
			const CELL &, // cell
			int &,		  // row_number
			int &		  // column_number
		) const = 0;
		// cell rank of the the cell according to its relative position in the grid
		virtual bool iGetCellNumber(
			int, // row_number
			int, // column_number
			CELL &) const = 0;
		// the containing cell given the coordinates in the 2D space
		virtual bool iGetContainingCell(
			int,   // posx
			int,   // posy
			CELL & // cell
		) const = 0;
		// check if a given point is within a given cell
		virtual bool iIsWithinCell(
			int,		 // posx
			int,		 // posy
			const CELL & // cell
		) const = 0;
		// initialize the vector of cells, obstacle mask, etc.
		virtual void iInitialize() = 0;
	};
} // namespace env
#endif // !IGRID_H
