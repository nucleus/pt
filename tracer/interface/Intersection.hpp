/*
 * Header file for the Intersection class.
 */

#ifndef INTERSECTION_HPP_
#define INTERSECTION_HPP_

#include <glm/interface/glm.hpp>

namespace geometry {
	class Shape;
}

namespace tracer {
	class Intersection {
	public:
		Intersection(): valid(false) {}
		~Intersection() {}
		
	public:
		bool valid;
		const geometry::Shape* object;
		glm::vec3 point, normal;
	};
}

#endif
