/*
 * Implementation file for the Pathtracer class.
 */

#include <tracer/interface/Pathtracer.hpp>
#include <tracer/interface/Camera.hpp>
#include <color/interface/Color.hpp>
#include <glm/interface/gtx/norm.hpp>
#include <util/interface/Util.hpp>

#ifdef REPORT_LEVEL
#undef REPORT_LEVEL
#endif
#define REPORT_LEVEL 2
#include <util/interface/Debug.hpp>

#include <time.h>
#include <iostream>

float tracer::Pathtracer::epsilon = 0.01f;

tracer::Pathtracer::Pathtracer(Image& output): m_output(output), m_maxDepth(5), m_samples(64) {
	
}

tracer::Pathtracer::~Pathtracer() {
	
}

void tracer::Pathtracer::render(unsigned width, unsigned height) {
	// initialize output texture
	m_output.clear();
	m_output.resize(width * height);
	std::fill(m_output.begin(), m_output.end(), glm::vec4(0.0f));

	// pinhole camera
	Camera& camera = m_scene.getCamera();
	camera.setImagingPlaneResolution(width, height);
	
	// random number generation
	std::random_device rd;
	std::mt19937 engine(rd());
	
	// progress printing
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	std::string status = "Rendering, done: ";
	float percentage = 0.0f, fraction = 100.0f/height;
	
	// rendering loop
	#pragma omp parallel for schedule(dynamic)
	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++) {
			glm::vec3 outputColor(0.0f);
			for (unsigned s = 0; s < m_samples; s++) {
				Ray ray = camera.castRay(x, y);
				outputColor += radiance(ray, engine) / (float)m_samples;
			}
			m_output[y*width+x] = glm::vec4(color::gammaCompress(glm::clamp(outputColor, 0.0f, 1.0f)), 1.0f);
		}
		#pragma omp critical
		{
		percentage += fraction;
		std::cout << "\r" << status << percentage << "%";
		}
	}
	std::cout << std::endl << std::endl;
}

void tracer::Pathtracer::trace(const Ray& ray) {
	// random number generation
	std::random_device rd;
	std::mt19937 engine(rd());
	const bool debug = true;
	glm::vec3 rad = radiance(ray, engine, 0, debug);
	std::cout << "returned radiance: " << rad << std::endl;
}

glm::vec3 tracer::Pathtracer::radiance(const Ray& ray, std::mt19937& engine, unsigned depth, bool debug) {
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	float distance, minimumDistance = std::numeric_limits<float>::max();
	Intersection tmp, isect;
	for (auto it = m_scene.begin(); it != m_scene.end(); ++it) {
		if ((*it)->intersect(ray, tmp)) {
			tmp.valid = true;
			if (debug) {
				std::cout << "testing intersection " << tmp.point << ", distance" << glm::distance2(ray.org, tmp.point) << std::endl;
			}
			if ((distance = glm::distance2(ray.org, tmp.point)) < minimumDistance) {
				minimumDistance = distance;
				isect = tmp;
			}
		}
	}
	
	if (isect.valid) {
		if (debug) { std::cout << "found intersection @ " << isect.point << ", normal: " << isect.normal << std::endl; }
		
		const material::Material& material = isect.object->getMaterial();
		glm::vec3 objectColor = material.color;
		glm::vec3 ex(1.0f, 0.0f, 0.0f), ey(0.0f, 1.0f, 0.0f), ez(0.0f, 0.0f, 1.0f);
		float p = MAX(objectColor.r, objectColor.g, objectColor.b);
		if (++depth > 5) {
			if (distribution(engine) < p) {
				objectColor = objectColor / p;
			} else {
				return material.emission;
			}
		}
		
		if (material.type == material::Material::Type_diffuse) {
			if (debug) { std::cout << "shading diffuse material" << std::endl; }
			
			// construct orthonormal system
			float r1 = 2 * M_PI * distribution(engine);
			float r2 = distribution(engine);
			float r2s = sqrt(r2);
			glm::vec3 w = isect.normal;
			glm::vec3 u = glm::normalize( glm::cross( (fabs(w.x) > 0.1f ? ey : ex), w ) );
			glm::vec3 v = glm::normalize( glm::cross(w, u) );
			glm::vec3 d = glm::normalize((float)(cos(r1) * r2s) * u + (float)(sin(r1) * r2s) * v + (float)sqrt(1-r2) * w);
			Ray scatteredRay(isect.point+epsilon*isect.normal, d);
			
			if (debug) { std::cout << "tracing next ray: " << scatteredRay << std::endl; }
			return material.emission + objectColor * radiance(scatteredRay, engine, depth, debug);
		} else if (material.type == material::Material::Type_reflective) {
			if (debug) { std::cout << "shading reflective material" << std::endl; }
			
			Ray reflectedRay(isect.point+epsilon*isect.normal, glm::reflect(ray.dir, isect.normal));
			return material.emission + objectColor * radiance(reflectedRay, engine, depth, debug); 
		} else {
			error("Unhandled material type detected");
			return m_scene.getBackgroundColor();
		}
	} else {
		if (debug) { std::cout << "found no intersection" << std::endl; }
		return m_scene.getBackgroundColor();
	}
}