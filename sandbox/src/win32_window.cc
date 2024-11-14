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

template <typename STRING_TYPE>
void RegisterWindow(const HINSTANCE& hinstance,
					const STRING_TYPE& window_class_name) {
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

template <typename STRING_TYPE>
void UnregisterWindow(const HINSTANCE& hinstance,
					  const STRING_TYPE& window_class_name) {
	UnregisterClassW(window_class_name.c_str(), hinstance);
}

template <typename STRING_TYPE>
HWND CreateWin32Window(const HINSTANCE& hinstance,
					   const STRING_TYPE& window_class_name,
					   const STRING_TYPE& title,
					   const int width, const int height) {
	const HWND& hwnd = CreateWindowExW(
		0,																// dwExStyle
		window_class_name.c_str(),										// lpClassName
		title.c_str(),													// lpWindowName
		WS_OVERLAPPEDWINDOW,											// dwStyle
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,				// X, Y, nWidth, nHeight
		nullptr, nullptr, hinstance, nullptr);	// hWndParent, hMenu, hInstance, lpParam

	if (hwnd == nullptr) {
		const char* error_message = FormatLastWindowsError();
		throw std::runtime_error(error_message);
	}

	ShowWindow(hwnd, SW_HIDE);

	return hwnd;
}

Win32Window::Win32Window(const WindowData window_data) {
	this->hinstance_ = GetModuleHandle(nullptr);
	this->window_data_ = window_data;

	RegisterWindow(this->hinstance_, kWindowClassName);

#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
	this->hwnd_ = CreateWin32Window<std::wstring>(
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
	if (PeekMessage(&msg, nullptr, NULL, NULL, PM_REMOVE)) {
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
