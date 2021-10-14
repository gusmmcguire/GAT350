#pragma once
#include "Renderer.h"

struct ColorBuffer {
	~ColorBuffer() {
		delete[] data;
	}
	uint8_t* data{ nullptr };
	int width = 0;
	int height = 0;
	int pitch = 0;
}
;