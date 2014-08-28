/*
 * Implementation file for the Sphere class.
 */

#include <GL/gl.h>
#include <GL/glut.h>

#include <geometry/interface/Sphere.hpp>

#include <cmath>

geometry::Sphere::Sphere(): position(0.0f), radius(0.0f) { 
	
}

geometry::Sphere::Sphere(const glm::vec3& _position, float _radius): position(_position), radius(_radius) { 
	
}

geometry::Sphere::Sphere(const glm::vec3& _position, float _radius, const material::Material& _material):
	Shape(_material), position(_position), radius(_radius) {
	
}

geometry::Sphere::~Sphere() { 
	
}

bool geometry::Sphere::intersect(const tracer::Ray& ray, tracer::Intersection& isect) const {
	glm::vec3 op = position - ray.org; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
	float t;
	float eps=1e-4f;
	float b = glm::dot(op, ray.dir);
	float det = b * b - glm::dot(op, op) + radius * radius;
	if (det < 0.0f) {
		return false; 
	} else {
		det = (float)sqrt(det);
	}
	
	if ((t=b-det) > eps) {
		isect.point = ray(t);
		isect.normal = normal(isect.point);
		isect.object = this;
		return true;
	} else if ((t=b+det) > eps) {
		isect.point = ray(t);
		isect.normal = normal(isect.point);
		isect.object = this;
		return true;
	}
	
	return false;
}

void geometry::Sphere::drawGL() const {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(position.x, position.y, position.z);
	glutWireSphere(radius, 10, 10);
	glPopMatrix();
}

const geometry::Sphere& geometry::Sphere::getBoundingSphere() const {
	return *this;
}

glm::vec3 geometry::Sphere::normal(const glm::vec3& surfacePoint) const {
	return glm::normalize(surfacePoint - position);
}