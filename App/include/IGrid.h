#ifndef IGRID_H
#define IGRID_H

#include <tuple>

class IGrid
{
public:
	typedef size_t CELL;
	typedef std::pair<float, float> Point;
	typedef std::pair<Point, Point> Segment;
	
	// Functor definition to apply on cell
	// We can inherit from this to function
	// to apply on cells
	class ICellFunctor {
	public:
		virtual void operator()(
			const CELL // cell_id
		) = 0;
	};
	// Functor definition to apply on segment
	// We can inherit from this to function
	// to apply on segments
	class ISegmentFunctor {
	public:
		virtual void operator()(
			const Segment& // cell_id
		) = 0;
	};
	virtual ~IGrid() = default ;
	virtual size_t iGetSizeX() const = 0;
	virtual size_t iGetSizeY() const = 0;
	virtual size_t iGetNumberOfCells() const = 0;
	virtual double iGetResolutionX() const = 0;
	virtual double iGetResolutionY() const = 0;
	//-- functors
	virtual void iApplyOnCells(ICellFunctor&) const = 0;
	virtual void iApplyOnSegments(ISegmentFunctor&) const = 0;
	//-- Test
	virtual bool iGetCellPosition(
		CELL, // cell_id
		double&, // posx
		double& // posy
	) const = 0;
	virtual bool iGetCellCoordinates(
		CELL, // cell_id
		size_t&, // row_number
		size_t& // column_number
	) const = 0;
	virtual bool iGetCellNumber(
		size_t, // row_number
		size_t, // column_number
		CELL&
	) const = 0;
	virtual bool iGetContainingCell(
		const float, // posx
		const float, // posy
		CELL& // cell_id
	) const = 0;
	virtual bool iIsWithinCell(
		const float, // posx
		const float, // posy
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
