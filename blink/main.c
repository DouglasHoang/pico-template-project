#include <stdio.h>
#include "pico/stdlib.h"

int main(void)
{
  stdio_init_all();

  gpio_init(25);
  gpio_set_dir(25, 1);

  while (1)
  {
    gpio_put(25, 1);
    sleep_ms(500);
    gpio_put(25, 0);
    sleep_ms(500);
  }

  return 0;
}
