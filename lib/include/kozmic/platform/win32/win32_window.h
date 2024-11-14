#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include <Windows.h>
#include <kozmic/core/window/window.h>
#include <string>

namespace kozmic::platform::win32 {
#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
const std::wstring kWindowClassName = L"KOZMIC_WINDOW";
#else
const std::string kWindowClassName = "KOZMIC_WINDOW";
#endif

    class Win32Window final : public Window {
	WindowData window_data_{};

	HINSTANCE hinstance_;
    	HWND hwnd_;

    	bool is_open_;

    public:
	 explicit Win32Window(WindowData window_data);
	 ~Win32Window() override;

	 void Show() override;
	 void Update() override;

	 [[nodiscard]] bool IsOpen() const override;
	};
	}  // namespace kozmic::platform::win32

#endif	//WIN32_WINDOW_H