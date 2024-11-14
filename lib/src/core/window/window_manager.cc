#include <kozmic/core/window/window_manager.h>

#if KOZMIC_PLATFORM == KOZMIC_PLATFORM_WINDOWS
#include <kozmic/platform/win32/win32_window.h>
#else
#error "Invalid platform"
#endif

kozmic::Window* kozmic::WindowManager::Create(const WindowData window_data) {
#if KOZMIC_PLATFORM == KOZMIC_PLATFORM_WINDOWS
	return new platform::win32::Win32Window(window_data);
#else
#error "Invalid platform"
#endif
}
