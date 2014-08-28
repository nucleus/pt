/*
 * Header file for the Scene class.
 */

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include <geometry/interface/Sphere.hpp>
#include <tracer/interface/Camera.hpp>

#include <iostream>
#include <vector>

namespace tracer {

	class Scene {
	public:
		typedef std::vector< geometry::Shape* > Objects;
		
	public:
		Scene();
		~Scene();
		
	public:
		void read();
		
	public:
		glm::vec3 getBackgroundColor() const {
			return glm::vec3(0.0f);
		}
		
		tracer::Camera& getCamera() {
			return m_camera;
		}
		
		const tracer::Camera& getCamera() const {
			return m_camera;
		}
		
	public:
		Objects::iterator begin() {
			return m_objects.begin();
		}
		
		Objects::iterator end() {
			return m_objects.end();
		}
		
		Objects::const_iterator begin() const {
			return m_objects.begin();
		}
		
		Objects::const_iterator end() const {
			return m_objects.end();
		}
		
	protected:
		tracer::Camera m_camera;
		Objects m_objects;
	};
	
}

#endif