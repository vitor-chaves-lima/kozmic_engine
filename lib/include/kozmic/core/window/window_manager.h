#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <kozmic/core/window/window.h>

namespace kozmic {
class WindowManager {
   public:
	static Window* Create(WindowData window_data);
};
}  // namespace kozmic

#endif	//WINDOW_MANAGER_H