#include <stdio.h>
#include "pico/stdlib.h"

int main(void)
{
  stdio_init_all();

  while (1)
  {
    printf("Hello, world!\n");

    sleep_ms(250);

    printf("What's going on\n");
  }

  return 0;
}
