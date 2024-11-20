#ifndef _H_TOGGLE
#define _H_TOGGLE
namespace bhop::toggle {
  bool setup();
  bool isEnabled();
  void onChange(void (*handler)());
}
#endif
