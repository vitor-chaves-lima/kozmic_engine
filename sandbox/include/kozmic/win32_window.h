#ifndef SANDBOX_WIN32_WINDOW_H_
#define SANDBOX_WIN32_WINDOW_H_

#include <Windows.h>
#include <string>

struct WindowData {
	const wchar_t* title;
	int width;
	int height;
};

class Win32Window {
private:
	WindowData window_data_{};
	std::wstring window_class_name_;
	HINSTANCE hinstance_;
	HWND hwnd_;

	bool is_open_;

public:
	explicit Win32Window(WindowData window_data);
	~Win32Window();

	void Show() const;
	void Update();
	bool IsOpen() const;
};

#endif //SANDBOX_WIN32_WINDOW_H_