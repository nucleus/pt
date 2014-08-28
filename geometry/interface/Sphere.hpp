/*
 * Header file for the Sphere class.
 */

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <glm/interface/glm.hpp>
#include <geometry/interface/Shape.hpp>

namespace geometry {
	
	class Sphere : public Shape {
	public:
		Sphere();
		Sphere(const glm::vec3& _position, float _radius);
		Sphere(const glm::vec3& _position, float _radius, const material::Material& material);
		
		~Sphere();
		
	public:
		bool intersect(const tracer::Ray& ray, tracer::Intersection& isect) const;
	
		void drawGL() const;
		
		const Sphere& getBoundingSphere() const;
	
	public:
		glm::vec3 normal(const glm::vec3& surfacePoint) const;
	
	public:
		glm::vec3 position;
		float radius;
	};
	
}

#endif