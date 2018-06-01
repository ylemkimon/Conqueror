/** @file Color.cpp */

#include "Color.h"

/**
*   Helper function for converting HSL colors to RGB colors.
*
*   @param[in] h   Hue relative to the target color
*   @param[in] s   Saturation
*   @param[in] l   Lightness
*/
float hslToRgb(float h, float s, float l)
{
	float q = l < .5f ? l * (s + 1) : l + s - l * s;
	float p = 2 * l - q;
	h = h < 0 ? h + 1 : (h > 1 ? h - 1 : h);
	if (h < (float)1 / 6) {
		return p + (q - p) * h * 6;
	}
	else if (h < (float)1 / 2) {
		return q;
	}
	else if (h < (float)2 / 3) {
		return p + (q - p) * ((float)2 / 3 - h) * 6;
	}
	return p;
}

Color::Color(float h, float s, float l, float a) :
	rgba{ s == 0 ? l : hslToRgb(h + (float)1 / 3, s, l),
		s == 0 ? l : hslToRgb(h, s, l),
		s == 0 ? l : hslToRgb(h - (float)1 / 3, s, l), a }
{
}
