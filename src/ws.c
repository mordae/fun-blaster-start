/*
 * Copyright Jan Hamal Dvořák <mordae@anilinux.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "ws.h"

#include <math.h>


/*
 * Written in assembler due to precise timing requirements.
 * Sends a 24 bit long command to control a single WS2812B LED.
 */
extern void ws_send_raw(uint32_t cmd);


void ws_set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t rr = r, gg = g, bb = b;
	uint32_t cmd = (gg << 24) | (rr << 16) | (bb << 8);
	ws_send_raw(cmd);
}


void ws_set_hsv(float h, float s, float v)
{
	h = fmodf(h, 360.0f);
	s = fmaxf(0.0f, fminf(s, 1.0f));
	v = fmaxf(0.0f, fminf(v, 1.0f));

	float c = v * s;
	float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
	float m = v - c;

	int i = h / 60.0f;

	float r, g, b;

	switch (i) {
		case 0: r = c, g = x, b = 0; break;
		case 1: r = x, g = c, b = 0; break;
		case 2: r = 0, g = c, b = x; break;
		case 3: r = 0, g = x, b = c; break;
		case 4: r = x, g = 0, b = c; break;
		default: r = c, g = 0, b = x; break;
	}

#if defined(LED_RED_MUL)
	r *= LED_RED_MUL;
#endif
#if defined(LED_GREEN_MUL)
	g *= LED_GREEN_MUL;
#endif
#if defined(LED_BLUE_MUL)
	b *= LED_BLUE_MUL;
#endif

	uint8_t rr = fminf(255.0f, 255.0f * (r + m));
	uint8_t gg = fminf(255.0f, 255.0f * (g + m));
	uint8_t bb = fminf(255.0f, 255.0f * (b + m));

	ws_set_rgb(rr, gg, bb);
}
