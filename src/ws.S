#include "pico/asm_helper.S"

pico_default_asm_setup

.section .time_critical.ws_led
.global ws_send_raw
.type ws_send_raw,%function
.thumb_func

// r0 holds 24 bits to send followed by 8 padding bits
ws_send_raw:
	// TODO: This needs to be written.

	bx lr		// return

.global literals
literals:
.ltorg

.end
