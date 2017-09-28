#ifndef PRINTLISTLIB
#define PRINTLISTLIB

#include "typedefs.h"
#include "LinkedList.h"

printListDefinition(int, "%d")

printListDefinition(short, "%hd")

printListDefinition(long, "%ld")

printListDefinition(llong, "%lld")

printListDefinition(uint, "%u")

printListDefinition(ushort, "%hu")

printListDefinition(ulong, "%lu")

printListDefinition(ullong, "%llu")

printListDefinition(float, "%f")

printListDefinition(double, "%f")

printListDefinition(ldouble, "%Lf")

printListDefinition(char, "%c")

printListDefinition(char_p, "%s")

printListDefinition(void_p, "%p")

#endif
