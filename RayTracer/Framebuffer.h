#pragma once
#include "Renderer.h"
#include "ColorBuffer.h"
#include <vector>

class Framebuffer {
public:
	Framebuffer(Renderer* renderer, int width, int height);
	~Framebuffer();

	void Update();

	void Clear(const color_t& color);
	void DrawPoint(int x, int y, const color_t& color);
	void DrawRect(int x, int y, int width, int height, const color_t& color);
	void DrawLine(int x1, int y1, int x2, int y2, const color_t& color);
	void DrawCircleOctants(int cx, int cy, int x, int y, const color_t& color);
	void DrawCircle(int x, int y, int radius, const color_t& color);
	void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const color_t& color);

	void DrawSimpleCurve(int x1, int y1, int x2, int y2, int steps, const color_t& color);
	void DrawQuadraticCurve(int x1, int y1, int x2, int y2, int x3, int y3, int steps, const color_t& color);
	void DrawCubicCurve(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int steps, const color_t& color);

	void DrawImage(int x1, int y1, class Image* image);

	int Lerp(int a, int b, float t);

public:
	SDL_Texture* texture{ nullptr };
	ColorBuffer colorBuffer;
};
