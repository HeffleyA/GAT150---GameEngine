#pragma once
#include "MathUtils.h"
#include <cmath>
#include <stdint.h>

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color() = default;
	Color(float r, float g, float b, float a = 0) { this->r = r; this->g = g; this->b = b; this->a = a; }

	float operator [] (unsigned int inder) const { return  (&r)[inder]; }
	float& operator [] (unsigned int inder) { return  (&r)[inder]; }

	Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g, b + c.b, a + c.a }; }
	Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g, b - c.b, a - c.a }; }
	Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g, b * c.b, a * c.a }; }
	Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g, b / c.b, a / c.a }; }

	//Color operator + (float s) const { return Color{ r + s, y + s }; }
	//Color operator - (float s) const { return Color{ r - s, y - s }; }
	//Color operator * (float s) const { return Color{ r * s, y * s }; }
	//Color operator / (float s) const { return Color{ r / s, y / s }; }

	//Color& operator += (const Color& c) { r += c.r; y += c.y; return *this; }
	//Color& operator -= (const Color& c) { r -= c.r; y -= c.y; return *this; }
	//Color& operator *= (const Color& c) { r *= c.r; y *= c.y; return *this; }
	//Color& operator /= (const Color& c) { r /= c.r; y /= c.y; return *this; }

	//Color& operator += (float s) { r += s; y += s; return *this; }
	//Color& operator -= (float s) { r -= s; y -= s; return *this; }
	//Color& operator *= (float s) { r *= s; y *= s; return *this; }
	//Color& operator /= (float s) { r /= s; y /= s; return *this; }

	static uint8_t ToInt(float value) { return static_cast<uint8_t>(Math::Clamp(value, 0.0f, 1.0f) * 255); }
};