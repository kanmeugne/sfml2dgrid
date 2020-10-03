#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>

namespace geometry
{
	typedef std::pair<unsigned int, unsigned int> Point;
	typedef std::pair<Point, Point> Segment;

	// Functor definition to apply on segment
	// We can inherit from this to function
	// to apply on segments
	class ISegmentFunctor {
	public:
		virtual void operator()(
			const Segment& // cell_id
		) = 0;
	};
}
#endif