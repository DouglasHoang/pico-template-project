#include <stdio.h>
#include "pico/stdlib.h"

int main(void)
{
  setup_default_uart();
  printf("Hello, world!\n");

  while (1)
  {
  }

  return 0;
}