/*
 * Header file for utility code.
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <glm/interface/glm.hpp>

#include <iostream>
#include <sstream>

namespace util {
	
	template<typename T, typename U>
	static T lexical_cast(U in) {
		std::stringstream ss;
		ss << in;
		T out;
		ss >> out;
		return out;
	}
	
}

std::ostream& operator<<(std::ostream& out, const glm::vec3& a);

#endif