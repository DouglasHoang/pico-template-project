#pragma once

#include "pico/stdlib.h"
#include <inttypes.h>
#include <stdio.h>

#define D_PIN_A 0
#define D_PIN_B 1
#define D_PIN_C 2
#define D_PIN_D 3
#define D_PIN_E 4
#define D_PIN_F 5
#define D_PIN_G 6
#define D_PIN_C1 7
#define D_PIN_C2 8
#define D_PIN_C3 9
#define D_PIN_C4 10
#define D_PIN_P 11

typedef struct {
  uint16_t pins[12];
} Display_I;

typedef void Display;

enum Digit {
  DigitOne = D_PIN_C1,
  DigitTwo = D_PIN_C2,
  DigitThree = D_PIN_C3,
  DigitFour = D_PIN_C4,
};

enum Segment {
  SegZero,
  SegOne,
  SegTwo,
  SegThree,
  SegFour,
  SegFive,
  SegSix,
  SegSeven,
  SegEight,
  SegNine,
  SegA,
  SegB,
  SegC,
  SegD,
  SegE,
  SegF,
};

static inline Display *d_init_display(uint16_t a, uint16_t b, uint16_t c,
                                      uint16_t d, uint16_t e, uint16_t f,
                                      uint16_t g, uint16_t c1, uint16_t c2,
                                      uint16_t c3, uint16_t c4, uint16_t p) {
  gpio_init(a);
  gpio_init(b);
  gpio_init(c);
  gpio_init(d);
  gpio_init(e);
  gpio_init(f);
  gpio_init(g);
  gpio_init(c1);
  gpio_init(c2);
  gpio_init(c3);
  gpio_init(c4);
  gpio_init(p);

  gpio_set_dir(a, 1);
  gpio_set_dir(b, 1);
  gpio_set_dir(c, 1);
  gpio_set_dir(d, 1);
  gpio_set_dir(e, 1);
  gpio_set_dir(f, 1);
  gpio_set_dir(g, 1);

  // Ideally should use transistor
  gpio_set_dir(c1, 1);
  gpio_set_dir(c2, 1);
  gpio_set_dir(c3, 1);
  gpio_set_dir(c4, 1);

  // Turn off all the digits
  gpio_put(c1, 1);
  gpio_put(c2, 1);
  gpio_put(c3, 1);
  gpio_put(c4, 1);

  gpio_set_dir(p, 1);

  Display_I *v = malloc(sizeof *v);

  v->pins[0] = a;
  v->pins[1] = b;
  v->pins[2] = c;
  v->pins[3] = d;
  v->pins[4] = e;
  v->pins[5] = f;
  v->pins[6] = g;
  v->pins[7] = c1;
  v->pins[8] = c2;
  v->pins[9] = c3;
  v->pins[10] = c4;
  v->pins[11] = p;

  return (void *)v;
}

static inline void d_display_character(Display *d, enum Digit digit,
                                       enum Segment segment) {
  Display_I *display = (Display_I *)d;

  bool segments[16][8] = {
      {0, 0, 1, 1, 1, 1, 1, 1}, // 0
      {0, 0, 0, 0, 0, 1, 1, 0}, // 1
      {0, 1, 0, 1, 1, 0, 1, 1}, // 2
      {0, 1, 0, 0, 1, 1, 1, 1}, // 3
      {0, 1, 1, 0, 0, 1, 1, 0}, // 4
      {0, 1, 1, 0, 1, 1, 0, 1}, // 5
      {0, 1, 1, 1, 1, 1, 0, 1}, // 6
      {0, 0, 0, 0, 0, 1, 1, 1}, // 7
      {0, 1, 1, 1, 1, 1, 1, 1}, // 8
      {0, 1, 1, 0, 1, 1, 1, 1}, // 9
      {0, 1, 1, 1, 0, 1, 1, 1}, // A
      {0, 1, 1, 1, 1, 1, 0, 0}, // B
      {0, 0, 1, 1, 1, 0, 0, 1}, // C
      {0, 1, 0, 1, 1, 1, 1, 0}, // D
      {0, 1, 1, 1, 1, 0, 0, 1}, // E
      {0, 1, 1, 1, 0, 0, 0, 1}, // F
  };

  bool *selected_seg = segments[segment];

  int pin = 0;
  for (int i = 7; i > 0; i--) {
    gpio_put(display->pins[pin], selected_seg[i]);
    pin++;
  }

  gpio_put(display->pins[digit], 0);
}

static inline void d_clear_display(Display *d) {
  Display_I *display = (Display_I *)d;

  gpio_put(display->pins[D_PIN_C1], 1);
  gpio_put(display->pins[D_PIN_C2], 1);
  gpio_put(display->pins[D_PIN_C3], 1);
  gpio_put(display->pins[D_PIN_C4], 1);

  gpio_put(display->pins[D_PIN_A], 0);
  gpio_put(display->pins[D_PIN_B], 0);
  gpio_put(display->pins[D_PIN_C], 0);
  gpio_put(display->pins[D_PIN_D], 0);
  gpio_put(display->pins[D_PIN_E], 0);
  gpio_put(display->pins[D_PIN_F], 0);
  gpio_put(display->pins[D_PIN_G], 0);
}
