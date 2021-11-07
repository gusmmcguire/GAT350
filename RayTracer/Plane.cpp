#include "Plane.h"

bool Plane::Hit(const ray_t& r, float tMin, float tMax, raycastHit_t& hit) {
	float denominator = glm::dot(r.direction, normal);
	if (abs(denominator) < glm::epsilon<float>())	return false; // direction and plane parallel, no intersection

	float t = glm::dot(center - r.origin, normal) / denominator;
	if (t < 0) return false; // ray origin is behind the plane (backside of plane)

	if (t >= tMin && t <= tMax) 	{
		hit.t = t;
		hit.point = r.pointAt(t);
		hit.normal = normal;
		hit.material = material.get();
		hit.uv = GetPlanarUV(hit.point);
		return true;
	}

	return false;
}