/*
 * Header file for the Ray class.
 */ 

#ifndef RAY_HPP_
#define RAY_HPP_

#include <iostream>

namespace tracer {
	class Ray {
	public:
		Ray(): org(0.0f), dir(0.0f) { }
		Ray(const glm::vec3& _org, const glm::vec3& _dir): org(_org), dir(_dir) { }
		
	public:
		glm::vec3 operator()(float t) const {
			return org + t * dir;
		}
		
	public:
		glm::vec3 org, dir;
	};
}

std::ostream& operator<<(std::ostream& out, const tracer::Ray& ray);



#endif