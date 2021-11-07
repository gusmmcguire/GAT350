#pragma once
#include "Renderer.h"
#include "ColorBuffer.h"
#include <string>

class Image {
public:
	Image() = default;
	Image(const std::string& filename, uint8_t alpha = 255);

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

	friend class Framebuffer;


public:
	ColorBuffer colorBuffer;

};