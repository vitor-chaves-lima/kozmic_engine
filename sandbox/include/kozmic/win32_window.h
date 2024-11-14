#ifndef SANDBOX_WIN32_WINDOW_H_
#define SANDBOX_WIN32_WINDOW_H_

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

class Win32Window {
private:
	WindowData window_data_{};

	HINSTANCE hinstance_;
	HWND hwnd_;

	bool is_open_;

public:
	explicit Win32Window(WindowData window_data);
	~Win32Window();

	void Show() const;
	void Update();
	[[nodiscard]] bool IsOpen() const;
};

#endif //SANDBOX_WIN32_WINDOW_H_