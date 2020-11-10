#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>

namespace geometry
{
	// definition of a point (typedef is sufficient)
	typedef std::pair<int, int> Point;
	// definition of a segment (typedef is sufficient)
	typedef std::pair<Point, Point> Segment;

	// Functor definition to apply on segment
	// We can inherit from this to function
	// to apply display instruction on segments
	class ISegmentFunctor {
	public:
		// operator function to apply on each segment 
		// (should concretized according to the need)
		virtual void operator()(
			const Segment& // cell_id
		) = 0;
	};
}
#endif // !GEOMETRY_H
