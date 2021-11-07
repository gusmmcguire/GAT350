#pragma once
#include "Types.h"

struct raycastHit_t {
	float t{ 0 };
	glm::vec3 point;
	glm::vec3 normal;
	glm::vec2 uv;

	class Material* material;
};

struct ray_t {
public:
	glm::vec3 origin;
	glm::vec3 direction;

	ray_t() = default;
	ray_t(const glm::vec3 origin, const glm::vec3 direction) : origin{ origin }, direction{ direction } {};

	glm::vec3 pointAt(float t) const { return origin + (direction * t); }
};

inline glm::vec2 GetPlanarUV(const glm::vec3& point) {
	glm::vec2 uv{ point.x,point.z };

	float i;
	uv[0] = modf(uv[0], &i);
	uv[1] = modf(uv[1], &i);

	return uv;
}

inline glm::vec2 GetSphericalUV(const glm::vec3& point) {
	float theta = acos(-point.y);
	float phi = atan2(-point.z, point.x) + glm::pi<float>();

	glm::vec2 uv;

	uv[0] = phi / (2 * glm::pi<float>());
	uv[1] = theta / glm::pi<float>();

	return uv;
}