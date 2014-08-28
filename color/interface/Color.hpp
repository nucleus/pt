/*
 * Header file for color related functionality.
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <cmath>

namespace color {
	
	glm::vec3 gammaCompress(const glm::vec3& color) {
		return glm::vec3(pow(color.x, 1/2.2), pow(color.y, 1/2.2), pow(color.z, 1/2.2));
	}
	
	glm::vec3 gammaDecompress(const glm::vec3& color) {
		return glm::vec3(pow(color.x, 2.2), pow(color.y, 2.2), pow(color.z, 2.2));
	}
	
}

#endif