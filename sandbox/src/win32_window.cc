#include <kozmic/win32_utils.h>
#include <kozmic/win32_window.h>
#include <stdexcept>

LRESULT CALLBACK WndProc(const HWND hwnd, const UINT message, const WPARAM wparam,
						 const LPARAM lparam) {
	switch (message) {
		case WM_CREATE: {
			break;
		}
		case WM_PAINT: {
			ValidateRect(hwnd, nullptr);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default:;
	}

	return DefWindowProc(hwnd, message, wparam, lparam);
}

#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
void RegisterWindow(const HINSTANCE& hinstance,
					const std::wstring& window_class_name) {
	const WNDCLASSEXW window_class = {
		.cbSize = sizeof(WNDCLASSEXW),
		.lpfnWndProc = &WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hinstance,
		.hIcon = nullptr,
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
		.lpszMenuName = nullptr,
		.lpszClassName = window_class_name.c_str(),
		.hIconSm = nullptr};

	if (RegisterClassExW(&window_class) == 0) {
		const char* error_message = FormatLastWindowsError();
		throw std::runtime_error(error_message);
	}
}

void UnregisterWindow(const HINSTANCE& hinstance,
					  const std::wstring& window_class_name) {
	UnregisterClassW(window_class_name.c_str(), hinstance);
}

HWND CreateWin32Window(const HINSTANCE& hinstance,
					   const std::wstring& window_class_name,
					   const std::wstring& title, const int width,
					   const int height) {
	const HWND& hwnd = CreateWindowExW(0,
		window_class_name.c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		nullptr, nullptr, hinstance, nullptr);

	if (hwnd == nullptr) {
		const char* error_message = FormatLastWindowsError();
		throw std::runtime_error(error_message);
	}

	ShowWindow(hwnd, SW_HIDE);

	return hwnd;
}
#else
void RegisterWindow(const HINSTANCE& hinstance,
					const std::string& window_class_name) {
	const WNDCLASSEXA window_class = {
		.cbSize = sizeof(WNDCLASSEXA),
		.lpfnWndProc = &WndProc,
		.cbClsExtra = 0,
		.cbWndExtra = 0,
		.hInstance = hinstance,
		.hIcon = nullptr,
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)),
		.lpszMenuName = nullptr,
		.lpszClassName = window_class_name.c_str(),
		.hIconSm = nullptr};

	if (RegisterClassExA(&window_class) == 0) {
		const char* error_message = FormatLastWindowsError();
		throw std::runtime_error(error_message);
	}
}

void UnregisterWindow(const HINSTANCE& hinstance,
					  const std::string& window_class_name) {
	UnregisterClassA(window_class_name.c_str(), hinstance);
}

HWND CreateWin32Window(const HINSTANCE& hinstance,
					   const std::string& window_class_name,
					   const std::string& title, const int width,
					   const int height) {
	const HWND& hwnd = CreateWindowExA(0,
		window_class_name.c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		nullptr, nullptr, hinstance, nullptr);

	if (hwnd == nullptr) {
		const char* error_message = FormatLastWindowsError();
		throw std::runtime_error(error_message);
	}

	ShowWindow(hwnd, SW_HIDE);

	return hwnd;
}
#endif

Win32Window::Win32Window(const WindowData window_data) {
	this->hinstance_ = GetModuleHandle(nullptr);
	this->window_data_ = window_data;

	RegisterWindow(this->hinstance_, kWindowClassName);

#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
	this->hwnd_ = CreateWin32Window(
		this->hinstance_, kWindowClassName, this->window_data_.title,
		this->window_data_.width, this->window_data_.height);
#else
	this->hwnd_ = CreateWin32Window<std::string>(
		this->hinstance_, kWindowClassName, this->window_data_.title,
		this->window_data_.width, this->window_data_.height);
#endif

	this->is_open_ = true;
}

Win32Window::~Win32Window() {
	UnregisterWindow(this->hinstance_, kWindowClassName);
	DestroyWindow(this->hwnd_);
}

void Win32Window::Update() {
	MSG msg;
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			this->is_open_ = false;
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Win32Window::Show() const {
	ShowWindow(this->hwnd_, SW_SHOW);
}

bool Win32Window::IsOpen() const {
	return this->is_open_;
}
