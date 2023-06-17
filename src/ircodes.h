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
#include <stdbool.h>
#include <stdint.h>

/* Single IR code to transmit. */
struct ir_code {
	bool en : 1;		/* Transmit or stay silent? */
	uint16_t us : 15;	/* Stay that way for 10× this number of μs. */
};

/* Just information about IR code region. */
enum ir_region {
	IR_USA = 0,
	IR_EUROPE = 1,
};

/* Script to turn off one TV model. */
struct ir_script {
	enum ir_region region;	/* Region where those TVs live. */
	unsigned freq;		/* Carrier frequency or 0. */
	unsigned num_codes;	/* How many codes are there. */
	struct ir_code codes[];	/* The codes to send. */
};

/* These are the scripts made available by the original TV-B-Gone project. */
#define NUM_IR_SCRIPTS 275
extern struct ir_script *ir_scripts[NUM_IR_SCRIPTS];
