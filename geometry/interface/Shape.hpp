/*
 * Header file for the Shape base class.
 */

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <tracer/interface/Ray.hpp>
#include <tracer/interface/Intersection.hpp>
#include <material/interface/Material.hpp>

namespace geometry {
	
	class Sphere;
	
	class Shape {
	public:
		Shape() { }
		Shape(const material::Material& _material): material(_material), id(nextShapeID++) { }
		
	public:
		virtual bool intersect(const tracer::Ray& ray, tracer::Intersection& isect) const = 0;
		
		virtual void drawGL() const = 0;
		
	public:
		virtual const material::Material& getMaterial() const {
			return material;
		}
		
		virtual unsigned getId() const {
			return id;
		}
		
		virtual const Sphere& getBoundingSphere() const = 0;
		
	protected:
		material::Material material;
		unsigned id;
		
		static unsigned nextShapeID;
	};
	
}

#endif