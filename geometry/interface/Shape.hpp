/*
 * Header file for the Shape base class.
 */

#ifndef SHAPE_HPP_
#define SHAPE_HPP_

#include <tracer/interface/Ray.hpp>
#include <tracer/interface/Intersection.hpp>
#include <material/interface/Material.hpp>

namespace geometry {
	
	class Shape {
	public:
		Shape() { }
		Shape(const material::Material& _material): material(_material) { }
		
	public:
		virtual bool intersect(const tracer::Ray& ray, tracer::Intersection& isect) const = 0;
		
		virtual void drawGL() const = 0;
		
		virtual const material::Material& getMaterial() const {
			return material;
		}
		
	protected:
		material::Material material;
	};
	
}

#endif