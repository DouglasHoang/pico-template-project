#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "pico/stdlib.h"
#include "display.h"
#include "pico/time.h"

uint64_t start = 0;
bool counter_callback(struct repeating_timer *t) {
  printf("this is it %d", start);
  start++;
  return true;
}

int main(void)
{
  stdio_init_all();

  Display *d = d_init_display(
     0,
     1,
     2,
     3,
     4,
     5,
     6,
     7,
     8,
     9, 
     16,
     17
    );

  struct repeating_timer timer;
  add_repeating_timer_ms(200, counter_callback, NULL, &timer);

  while (1)
  {
    d_clear_display(d);
    d_display_character(d, DigitOne, start % 16);

    sleep_ms(5);

    d_clear_display(d);
    d_display_character(d, DigitTwo, (start+1) % 16);

    sleep_ms(5);

    d_clear_display(d);
    d_display_character(d, DigitThree, (start+2) % 16);

    sleep_ms(5);

    d_clear_display(d);
    d_display_character(d, DigitFour, (start+3) % 16);

    sleep_ms(5);
  }

  free(d);

  return 0;
}
