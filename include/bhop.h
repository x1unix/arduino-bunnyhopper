#ifndef _H_BHOP
#define _H_BHOP
#include "config.h"
#include "timer.h"
#include "toggle.h"

namespace bhop {
  bool hasError();
  bool setup();
  bool tick();
  void setLedStatus(uint8_t val);
}
#endif
