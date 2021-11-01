#pragma once
#include "Types.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"

#include <memory>
#include <vector>

class Scene {
public:
    glm::vec3 Trace(const ray_t& r, float tMin, float tMax, raycastHit_t& hit);
    void Add(std::unique_ptr<Geometry> geometry);

protected:
    std::vector<std::unique_ptr<Geometry>> objects;
};