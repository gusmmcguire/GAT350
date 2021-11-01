#pragma once
#include "Types.h"
#include "Ray.h"

class Camera {
	public:
	Camera() = default;
	Camera(const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up, float fov, const glm::ivec2& screenSize, float aperture, float focalLength);
	
	void Set(const glm::vec3& eye, const glm::vec3& lookAt,const glm::vec3& up, float fov);

	glm::vec2 ScreenToViewport(const glm::vec2& screen);
	ray_t ViewportToRay(const glm::vec2& viewport);

	public:
	glm::vec3 eye{0,0,0};

	glm::vec3 right{0,0,0};
	glm::vec3 up{0,0,0};
	glm::vec3 forward{0,0,0};

	glm::vec3 lowerLeft{ 0,0,0 };
	glm::vec3 horizontal{ 0,0,0 };
	glm::vec3 vertical{ 0,0,0 };

	glm::ivec2 screenSize{0,0};
	float aspectRatio = 0;
	float viewportWidth = 0;
	float viewportHeight = 0;

	float aperture = 0;
	float focalLength = 0;
	float lensRadius = 0;
};