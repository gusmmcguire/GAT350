#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/color_space.hpp>
#include <memory>

#include <sdl.h>

using color_t = SDL_Color;

inline color_t Vec3ToColor(const glm::vec3& vec3) {
    color_t color;

    color.r = static_cast<std::uint8_t>(glm::clamp(vec3[0], 0.0f, 1.0f) * 255);
    color.g = static_cast<std::uint8_t>(glm::clamp(vec3[1], 0.0f, 1.0f) * 255);
    color.b = static_cast<std::uint8_t>(glm::clamp(vec3[2], 0.0f, 1.0f) * 255);
    color.a = 0;

    return color;
}

inline glm::vec3 ColorToVec3(const color_t color) {
    glm::vec3 out_color;

    out_color.r = color.r / (float) 255;
    out_color.g = color.g / (float) 255;
    out_color.b = color.b / (float) 255;

    return out_color;
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2) {
    return glm::vec3{
           v1.y * v2.z - v1.z * v2.y,
           v1.z * v2.x - v1.x * v2.z,
           v1.x * v2.y - v1.y * v2.x
    };
}

inline float angle(const glm::vec3& v1, const glm::vec3& v2) {
    return glm::acos(dot(v1, v2));
}

inline float random01() {
    return rand() / (float)RAND_MAX;
}

inline float random(float min, float max) {
    return min + (max - min) * random01();
}

inline glm::vec3 randomInUnitSphere() {
    glm::vec3 p;
    do     {
        p = glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1) };
    } while (glm::length2(p) >= 1);

    return p;
}

inline glm::vec3 randomInUnitDisk() {
    glm::vec3 p;
    do {
        p = glm::vec3{ random(-1, 1), random(-1, 1), 0 };
    } while (glm::length2(p) >= 1);
    return p;
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - (2*dot(v,n)*n);
}

inline bool refract(const glm::vec3& v, const glm::vec3& n, float refractionIndex, glm::vec3& refracted) {
    glm::vec3 nv = glm::normalize(v);
    float dt = dot(nv, n);
    float discriminant = 1 - (refractionIndex * refractionIndex) * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = refractionIndex * (nv - (n*dt)) - (n * std::sqrt(discriminant));
        return true;
    }
    return false;
}

inline float schlick(float cosine, float index) {
    float r0 = (1-index) / (1 + index);
    r0 = r0 * r0;
    return (float)(r0 + (1-r0) * std::pow((1-cosine),5));
}

