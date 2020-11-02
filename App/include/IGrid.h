#ifndef IGRID_H
#define IGRID_H

#include <tuple>

namespace env
{
	struct CELL
	{
		int _id;
		CELL() = default;
		CELL(const CELL &) = default;
	};

	class IGrid
	{
	public:
		virtual ~IGrid() = default;
		virtual int iGetSizeX() const = 0;
		virtual int iGetSizeY() const = 0;
		virtual int iGetNumberOfCells() const = 0;
		virtual int iGetResolutionX() const = 0;
		virtual int iGetResolutionY() const = 0;
		//-- Test
		virtual bool iGetCellPosition(
			const CELL &, // cell
			int &,		  // posx
			int &		  // posy
		) const = 0;
		virtual bool iGetCellCoordinates(
			const CELL &, // cell
			int &,		  // row_number
			int &		  // column_number
		) const = 0;
		virtual bool iGetCellNumber(
			int, // row_number
			int, // column_number
			CELL &) const = 0;
		virtual bool iGetContainingCell(
			int,   // posx
			int,   // posy
			CELL & // cell
		) const = 0;
		virtual bool iIsWithinCell(
			int,		 // posx
			int,		 // posy
			const CELL & // cell
		) const = 0;
		// initialize : the vector of cells, obstacle mask, etc.
		virtual void iInitialize() = 0;
	};
} // namespace env
#endif // !IGRID_H
