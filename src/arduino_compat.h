/*
  arduino_compat.h - Zephyr compatibility functions for Arduino functions

  LICENSE

  The MIT License (MIT)

  Copyright (c) 2026  Elinor Montmasson

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.

*/

#ifndef ARDUINO_COMPAT_h
#define ARDUINO_COMPAT_h

#include <zephyr/kernel.h>
#include <zephyr/random/random.h>
#include <zephyr/sys/util.h>

#include <math.h>
#include <limits.h>

// PROGMEM related macros and functions are irrelevant with Zephyr, the compilers
// should detect by itself data which is const to keep it in ROM
typedef char __FlashStringHelper;
#define F(s) (reinterpret_cast<const __FlashStringHelper *>(s))

// Zephyr's clamp() and min() cannot be used as not defined for C++ to avoid conflicts
// with std::min() and std::clamp().
// Instead, use CLAMP and MIN macros even if they evalutes expressions multiple times.
#define constrain(val, low, high) CLAMP(val, low, high)
#define min(a, b) MIN(a, b)

inline unsigned long millis() { return k_uptime_get_32(); }
inline void delay(unsigned long d) { k_msleep(d); }
inline long map(long val, long src_low, long src_high, long dest_low, long dest_high)
{
    return (val - src_low) * (dest_high - dest_low) / (src_high - src_low) + dest_low;
}

inline long random(long min, long max) { return map(sys_rand32_get(), LONG_MIN, LONG_MAX, min, max); }
inline long random(long max) { return random(0, max); }

#endif  // ARDUINO_COMPAT_h
