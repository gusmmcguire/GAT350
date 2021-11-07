#pragma once
#include "Types.h"
#include "Ray.h"
#include "Sampler.h"

class Material {
	public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const = 0;
	virtual glm::vec3 Emitter(const glm::vec2& uv, const glm::vec3& point) {return glm::vec3{0,0,0}; }
};

class Lambertian : public Material {
	public:
	Lambertian(const glm::vec3& albedo) : albedo{std::make_shared<ColorSampler>(albedo)} {}
	Lambertian(std::shared_ptr<Sampler> albedo) : albedo{albedo} {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const override;

	protected:
	std::shared_ptr<Sampler> albedo;
};

class Metal : public Material {
	public:
	Metal(const glm::vec3& albedo, float fuzz) : albedo{ std::make_shared<ColorSampler>(albedo) }, fuzz{fuzz} {}
	Metal(std::shared_ptr<Sampler> albedo, float fuzz) : albedo{ albedo }, fuzz{fuzz} {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const override;

	protected:
	std::shared_ptr<Sampler> albedo;
	float fuzz = 0;
};

class Dielectric : public Material {
	public:
	Dielectric(const glm::vec3& albedo, float refractionIndex) : albedo{ std::make_shared<ColorSampler>(albedo) }, refractionIndex{refractionIndex}{}
	Dielectric(std::shared_ptr<Sampler> albedo, float refractionIndex) : albedo{ albedo }, refractionIndex{refractionIndex}{}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const override;

	protected:
	std::shared_ptr<Sampler> albedo;
	float refractionIndex{1};
};

class Emissive : public Material {
	public:
		Emissive(const glm::vec3& color) : emission{std::make_shared<ColorSampler>(color)} {}
		Emissive(std::shared_ptr<Sampler> emission) : emission{emission} {}

		virtual bool Scatter(const ray_t& ray, const raycastHit_t& hit, glm::vec3& attenuation, ray_t& scattered) const override {
			return false;
		}

		virtual glm::vec3 Emitter(const glm::vec2& uv, const glm::vec3& point) {
			return emission->value(uv,point);
		}

	protected:
	std::shared_ptr<Sampler> emission;
};