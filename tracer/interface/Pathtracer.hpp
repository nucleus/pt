/*
 * Header file for Pathtracer class.
 */

#ifndef PATHTRACER_HPP_
#define PATHTRACER_HPP_

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/interface/glm.hpp>
#include <tracer/interface/Scene.hpp>

#include <random>

#define MAX(a,b,c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))

namespace tracer {

	class Pathtracer {
	public:
		typedef std::vector< glm::vec4 > Image;
		
	public:
		Pathtracer(Image& output);
		~Pathtracer();
		
	public:
		void setSamples(int samples) { m_samples = samples; }
		
	public:
		void render(unsigned width, unsigned height);
		
		void trace(const Ray& ray);
		
	protected:
		glm::vec3 radiance(const Ray& ray, std::mt19937& engine, unsigned depth = 0, bool debug = false); 
		
	protected:
		Scene m_scene;
		Image& m_output;
		
		unsigned m_maxDepth;
		unsigned m_samples;
		
		static float epsilon;
	};

}

#endif
