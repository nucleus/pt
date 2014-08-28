/*
 * Implementation file for utility code.
 */

#include <util/interface/Util.hpp>

std::ostream& operator<<(std::ostream& out, const glm::vec3& a) {
	out << "(" << a.x << "," << a.y << "," << a.z << ")";
	return out;
}