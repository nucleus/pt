/*
 * Implementation file for the Scene class.
 */

#include <tracer/interface/Scene.hpp>

tracer::Scene::Scene(): m_camera(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 0.0f, -10000.0f), glm::vec3(0.0f, 1.0f, 0.0f)) {
	read();
}
		
tracer::Scene::~Scene() {
	
}

void tracer::Scene::read() {
	m_objects.push_back( 
		new geometry::Sphere(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, material::Material(glm::vec3(0.75f, 0.75f, 0.75f))) ); // ground
	m_objects.push_back( 
		new geometry::Sphere(glm::vec3(0.0f, 0.0f, -1000.0f), (1000.0f-2.0f), material::Material(glm::vec3(0.75f, 0.75f, 0.75f))) ); // back
	m_objects.push_back( 
		new geometry::Sphere(glm::vec3(-1000.0f, 0.0f, 0.0f), (1000.0f-1.5f), material::Material(glm::vec3(0.75f, 0.25f, 0.25f))) ); // left
	m_objects.push_back( 
		new geometry::Sphere(glm::vec3(1000.0f, 0.0f, 0.0f), (1000.0f-1.5f), material::Material(glm::vec3(0.25f, 0.25f, 0.75f))) ); // right
	m_objects.push_back( 
		new geometry::Sphere(glm::vec3(0.0f, 100.0f, 0.0f), 85.0f, material::Material(glm::vec3(0.0f), glm::vec3(10.0f, 10.0f, 10.0f))) ); // light
	m_objects.push_back(
		new geometry::Sphere(glm::vec3(0.6f, 0.6f, -0.1f), 0.6f, material::Material(glm::vec3(0.25f, 0.75f, 0.25f))) ); // sphere 1
	m_objects.push_back( 
		new geometry::Sphere(glm::vec3(-0.6f, 0.5f, 0.75f), 0.5f, material::Material(glm::vec3(0.999f, 0.999f, 0.999f), glm::vec3(0.0f), material::Material::Type_reflective)) ); // sphere 2
}
