#pragma once
#include "Renderer.h"
#include "ColorBuffer.h"
#include <string>

class Image {
public:

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip();

	friend class Framebuffer;


public:
	ColorBuffer colorBuffer;

};