#!/usr/bin/env python

import sys
import yaml


class BitBuffer:
    number: int
    width: int
    offset: int

    def __init__(self, bstr: list[int], width: int) -> None:
        self.width = width
        self.offset = len(bstr) * 8 - 1
        self.number = 0

        for byte in bstr:
            self.number = (self.number << 8) + byte

    def pop(self) -> int:
        result: int = 0

        for _ in range(self.width):
            assert self.offset >= 0
            bit = (self.number >> self.offset) & 1
            self.offset -= 1
            result = (result << 1) + bit

        return result


with open(sys.argv[1]) as fp:
    data = yaml.load(fp, yaml.SafeLoader)

output = {}

for region, signals in data.items():
    output.setdefault(region, [])

    for signal in signals:
        freq = signal["freq"]
        bits = signal["bits"]
        ntimes = signal["ntimes"]
        avail = len(signal["codes"]) * 8 / bits
        assert ntimes <= avail

        buf = BitBuffer(signal["codes"], signal["bits"])

        script = {
            "freq": freq,
            "codes": [],
        }

        for _ in range(signal["ntimes"]):
            pair = signal["times"][buf.pop()]

            if pair[0]:
                script["codes"].append({"en": True, "us": pair[0]})

            if pair[1]:
                script["codes"].append({"en": False, "us": pair[1]})

        if script["codes"][-1]["en"]:
            script["codes"].append({"en": False, "us": 0})

        output[region].append(script)


total: int = sum([len(x) for x in output.values()])

print("/* AUTOMATICALLY GENERATED, DO NOT EDIT. */")
print("")
print('#include "ircodes.h"')

i = 0

for region, scripts in output.items():
    for script in scripts:
        print()
        print(f"static struct ir_script ir_script_{i:03} = {'{'}")
        print(f"\t.region = {'IR_USA' if region == 'na' else 'IR_EUROPE'},")
        print(f"\t.freq = {script['freq']},")
        print(f"\t.num_codes = {len(script['codes'])},")
        print(f"\t.codes = {'{'}")

        for code in script["codes"]:
            print(f"\t\t{'{'}{1 if code['en'] else 0}, {code['us']:5}{'}'},")

        print("\t},")
        print("};")

        i += 1

print()
print("struct ir_script *ir_scripts[NUM_IR_SCRIPTS] = {")

for x in range(total):
    print(f"\t&ir_script_{x:03},")

print("};")
