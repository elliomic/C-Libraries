#include "gc.h"
#include "typedefs.h"
#include "debug.h"
#include "LinkedList.h"
#include "String.h"

void start(List(String) *);

int main(int argc, char_p *argv)
{
  tgc_start(&gc, &argc);
  List(String) *args = convertArgs(argc, argv);
#ifdef DEBUG
  signal(SIGSEGV, segv_handler);
#endif

  start(args);

  tgc_stop(&gc);
  return 0;
}
