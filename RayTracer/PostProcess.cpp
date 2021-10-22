#include "PostProcess.h"

namespace PostProcess {
	void Invert(const ColorBuffer& colorBuffer) {
		for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++) {
			color_t& color = ((color_t*)colorBuffer.data)[i];
			color.r = 255 - color.r;
			color.g = 255 - color.g;
			color.b = 255 - color.b;
		}
	}
	void Monochrome(const ColorBuffer& colorBuffer) {
		for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++) {
			color_t& color = ((color_t*)colorBuffer.data)[i];
			uint16_t sum = color.r + color.b + color.g;
			uint8_t average = sum / 3;

			color.r = average;
			color.g = average;
			color.b = average;
		}
	}
	void Noise(const ColorBuffer& colorBuffer, uint8_t noise) {
		for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++) {
			color_t& color = ((color_t*)colorBuffer.data)[i];
			int16_t offset = (rand() % ((noise << 1) + 1)) - noise;
			int16_t r = color.r + offset;
			int16_t g = color.g + offset;
			int16_t b = color.b + offset;
			color.r = ((r < 0) ? 0 : (r > 255) ? 255 : r);
			color.g = ((g < 0) ? 0 : (g > 255) ? 255 : g);
			color.b = ((b < 0) ? 0 : (b > 255) ? 255 : b);
		}
	}
	void Brightness(const ColorBuffer& colorBuffer, int16_t brightness) {
		for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++) {
			color_t& color = ((color_t*)colorBuffer.data)[i];
			int16_t r = color.r + brightness;
			int16_t g = color.g + brightness;
			int16_t b = color.b + brightness;
			color.r = ((r < 0) ? 0 : (r > 255) ? 255 : r);
			color.g = ((g < 0) ? 0 : (g > 255) ? 255 : g);
			color.b = ((b < 0) ? 0 : (b > 255) ? 255 : b);
		}
	}
	void ColorBalance(const ColorBuffer& colorBuffer, int16_t ro, int16_t go, int16_t bo) {
		for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++) {
			color_t& color = ((color_t*)colorBuffer.data)[i];
			int16_t r = color.r + ro;
			int16_t g = color.g + go;
			int16_t b = color.b + bo;
			color.r = ((r < 0) ? 0 : (r > 255) ? 255 : r);
			color.g = ((g < 0) ? 0 : (g > 255) ? 255 : g);
			color.b = ((b < 0) ? 0 : (b > 255) ? 255 : b);
		}
	}
	void Threshold(const ColorBuffer& colorBuffer, uint8_t threshold) {
		for (int i = 0; i < colorBuffer.width * colorBuffer.height; i++) {
			color_t& color = ((color_t*)colorBuffer.data)[i];
			color.r = (color.r >= threshold) ? color.r : 0;
			color.b = (color.b >= threshold) ? color.b : 0;
			color.g = (color.g >= threshold) ? color.g : 0;
		}
	}
	void BoxBlur(const ColorBuffer& colorBuffer) {
		ColorBuffer source = colorBuffer;
		int16_t k[3][3] =
		{
			{ 1, 1, 1 },
		   { 1, 1, 1 },
		   { 1, 1, 1 },
		};

		for (int i = 0; i < source.width * source.height; i++) {
			int x = i % source.width;
			int y = i / source.width;

			if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

			uint16_t r = 0;
			uint16_t g = 0;
			uint16_t b = 0;
			for (int iy = -1; iy <= 1; iy++) {
				for (int ix = -1; ix <= 1; ix++) {
					r += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * k[1 + iy][1 + ix];
					g += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * k[iy + 1][ix + 1];
					b += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].b * k[iy + 1][ix + 1];
				}
			}

			color_t& color = ((color_t*)colorBuffer.data)[i];
			color.r = r / 9;
			color.g = g / 9;
			color.b = b / 9;
		}
	}
	void GaussianBlur(const ColorBuffer& colorBuffer) {
		ColorBuffer source = colorBuffer;
		int16_t k[3][3] =
		{
			{ 1, 2, 1 },
		   { 2, 4, 2 },
		   { 1, 2, 1 },
		};

		for (int i = 0; i < source.width * source.height; i++) {
			int x = i % source.width;
			int y = i / source.width;

			if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

			uint16_t r = 0;
			uint16_t g = 0;
			uint16_t b = 0;
			for (int iy = -1; iy <= 1; iy++) {
				for (int ix = -1; ix <= 1; ix++) {
					r += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * k[1 + iy][1 + ix];
					g += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * k[iy + 1][ix + 1];
					b += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].b * k[iy + 1][ix + 1];
				}
			}

			color_t& color = ((color_t*)colorBuffer.data)[i];
			color.r = r / 16;
			color.g = g / 16;
			color.b = b / 16;
		}
	}

	void Sharpen(const ColorBuffer& colorBuffer) {
		ColorBuffer source = colorBuffer;
		int16_t k[3][3] =
		{
			{  0, -1,  0 },
		   { -1,  5, -1 },
		   {  0, -1,  0 },
		};


		for (int i = 0; i < source.width * source.height; i++) {
			int x = i % source.width;
			int y = i / source.width;

			if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

			int16_t r = 0;
			int16_t g = 0;
			int16_t b = 0;
			for (int iy = -1; iy <= 1; iy++) {
				for (int ix = -1; ix <= 1; ix++) {
					r += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * k[1 + iy][1 + ix];
					g += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].g * k[iy + 1][ix + 1];
					b += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].b * k[iy + 1][ix + 1];
				}
			}

			color_t& color = ((color_t*)colorBuffer.data)[i];
			color.r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
			color.b = (b < 0) ? 0 : ((b > 255) ? 255 : b);
			color.g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
		}
	}
	void Edge(const ColorBuffer& colorBuffer, uint8_t threshold) {
		ColorBuffer source = colorBuffer;
		int16_t kh[3][3] =
		{
			{ 1, 0, -1 },
			{ 2, 0, -2 },
			{ 1, 0, -1 },
		};

		int16_t kv[3][3] =
		{
			{ -1, -2, -1 },
			{  0,  0,  0 },
			{  1,  2,  1 },
		};

		for (int i = 0; i < source.width * source.height; i++) {
			int x = i % source.width;
			int y = i / source.width;

			if (x < 1 || x + 1 >= source.width || y < 1 || y + 1 >= source.height) continue;

			int16_t h = 0;
			int16_t v = 0;
			for (int iy = -1; iy <= 1; iy++) {
				for (int ix = -1; ix <= 1; ix++) {
					h += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * kh[1 + iy][1 + ix];
					v += ((color_t*)source.data)[(x + ix) + (y + iy) * source.width].r * kv[1 + iy][1 + ix];
				}
			}

			uint16_t result = (uint16_t)sqrt((h * h) + (v * v));

			result = (result > threshold) ? result : 0;
			uint8_t c = (result < 0) ? 0 : ((result > 255) ? 255 : result);
			color_t& color = ((color_t*)colorBuffer.data)[i];

			color.r = c;
			color.g = c;
			color.b = c;
		}

	}
}
