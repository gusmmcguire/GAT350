#pragma once
#include "Geometry.h"

class Plane : public Geometry {
public:
	Plane() = default;
	Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) :
		Geometry{ material },
		center{ center },
		normal{ normal }
	{
	}

	bool Hit(const ray_t& r, float tMin, float tMax, raycastHit_t& hit) override;

public:
	glm::vec3 center{ 0, 0, 0 };
	glm::vec3 normal{ 0, 0, 0 };
};