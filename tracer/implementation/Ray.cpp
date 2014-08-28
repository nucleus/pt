/*
 * Implementation file for Ray related code.
 */

#include <util/interface/Util.hpp>
#include <tracer/interface/Ray.hpp>

std::ostream& operator<<(std::ostream& out, const tracer::Ray& ray) {
	out << "Ray(" << ray.org << ":" << ray.dir << ")";
	return out;
}