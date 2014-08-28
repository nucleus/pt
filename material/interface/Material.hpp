/*
 * Header file for the Material class.
 */

#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include <glm/interface/glm.hpp>

namespace material {
	
	class Material {
	public:
		enum Type {
			Type_diffuse,
			Type_reflective
		};
		
	public:
		Material(glm::vec3 _color = glm::vec3(0.0f), glm::vec3 _emission = glm::vec3(0.0f), Type _type = Type_diffuse):
			emission(_emission), color(_color), type(_type) { }
		
	public:
		glm::vec3 emission;
		glm::vec3 color;
		Type type;
	};
	
}

#endif