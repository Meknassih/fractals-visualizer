#include "listep_op.h"
#include "ez-draw.h"
#include "ez-image.h"

int main(int argc, char *argv[]) {
  if (ez_init() < 0)
    exit(1);

  ez_window_create(500, 500, "SURFACE", NULL);

  ez_main_loop();
  exit(0);

  return 0;
}
