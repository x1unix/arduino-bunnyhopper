#ifndef _H_TIMER
#define _H_TIMER
#include "config.h"

namespace bhop::timer {
bool ticked();
void setup();
void reset();
int getInterval();
}
#endif
