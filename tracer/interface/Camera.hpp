/*
 * Header file for the Camera class.
 */

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <glm/interface/glm.hpp>

namespace tracer {
	
	class Camera {
	public:
		Camera(const glm::vec3& _position, const glm::vec3& _eye, const glm::vec3& _up):
			position(_position), direction(_eye - _position), up(_up), right(glm::cross(direction, up)), width(2), height(2) { 
				
			direction = glm::normalize(direction);
			up = glm::normalize(glm::cross(right, direction));
			right = glm::normalize(right);
		}
	
	public:
		void setImagingPlaneResolution(unsigned _width, unsigned _height) {
			width = _width;
			height = _height;
		}
		
		Ray castRay(unsigned x, unsigned y) const {
			float normalizedX = (x/(float)width) - 0.5f;
			float normalizedY = (y/(float)height) - 0.5f;
			glm::vec3 rayDirection = direction + normalizedX * right + normalizedY * up;
			return Ray(position, glm::normalize(rayDirection));
		}
		
	protected:
		glm::vec3 position, direction, up, right;
		unsigned width, height;
	};
	
}

#endif
