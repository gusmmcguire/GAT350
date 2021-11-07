#include "Sampler.h"

glm::vec3 CheckerSampler::value(const glm::vec2& uv, const glm::vec3& p) const {
	auto sines = sin(scale * p.x) * sin(scale * p.y) * sin(scale * p.z);
	return (sines < 0) ? odd->value(uv, p) : even->value(uv,p);
}

glm::vec3 TextureSampler::value(const glm::vec2& uv, const glm::vec3& p) const {
    float u = fabs(uv[0]) * scale;
    float v = fabs(uv[1]) * scale;

    float i;
    u = modf(u, &i);
    v = modf(v, &i);

    int x = (int)(u * image->colorBuffer.width);
    int y = (int)(v * image->colorBuffer.height);

    color_t color = ((color_t*)image->colorBuffer.data)[x + (y * image->colorBuffer.width)];

    return ColorToVec3(color);
}

