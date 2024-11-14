#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

#include <Windows.h>
#include <string>

#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
const std::wstring kWindowClassName = L"KOZMIC_WINDOW";
#else
const std::string kWindowClassName = "KOZMIC_WINDOW";
#endif

struct WindowData {
#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
	const wchar_t* title;
#else
	const char* title;
#endif
	int width;
	int height;
};

namespace kozmic::platform::win32 {
    class Window {
    private:
    	WindowData window_data_{};

    	HINSTANCE hinstance_;
    	HWND hwnd_;

    	bool is_open_;

    public:
    	explicit Window(WindowData window_data);
    	~Window();

    	void Show() const;
    	void Update();
    	[[nodiscard]] bool IsOpen() const;
    };
}

#endif //WIN32_WINDOW_H