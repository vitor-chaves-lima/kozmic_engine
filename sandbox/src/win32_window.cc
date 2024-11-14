#include <kozmic/win32_window.h>
#include <kozmic/win32_utils.h>
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

void RegisterWindow(const HINSTANCE hinstance,
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

HWND CreateWin32Window(HINSTANCE hinstance, const wchar_t* window_class_name,
					   const wchar_t* title, const int width, const int height) {
	const HWND& hwnd = CreateWindowExW(
		0,																// dwExStyle
		window_class_name,												// lpClassName
		title,															// lpWindowName
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

	this->window_class_name_ = std::wstring(L"KOZMIC_WINDOW");

	RegisterWindow(this->hinstance_, this->window_class_name_);

	this->hwnd_ = CreateWin32Window(
		this->hinstance_, window_class_name_.c_str(), this->window_data_.title,
		this->window_data_.width, this->window_data_.height);

	this->is_open_ = true;
}

Win32Window::~Win32Window() {
	UnregisterClassW(this->window_class_name_.c_str(), this->hinstance_);
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
