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

#pragma once
#include <pico/stdlib.h>

/*
 * Set our LED to given red/green/blue color.
 * No compensation is performed, this is raw control.
 */
void ws_set_rgb(uint8_t r, uint8_t g, uint8_t b);

/*
 * Set LED color using hue/saturation/value system with per-channel
 * brightness correction to compensate for our lower voltage.
 *
 * Inputs are:
 *
 *	0 <= hue <  360
 *	0 <= sat <= 1
 *	0 <= val <= 1
 *
 * Hue wraps, saturation and value are clamped.
 *
 * To learn more, visit <https://en.wikipedia.org/wiki/HSL_and_HSV>.
 */
void ws_set_hsv(float h, float s, float v);
