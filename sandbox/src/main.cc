#include <kozmic/platform/win32/win32_window.h>

int main() {
	constexpr auto window_data = WindowData{L"Kozmic Sandbox", 1280, 720};
	const auto win32_window = new Win32Window(window_data);
	win32_window->Show();

	while (win32_window->IsOpen()) {
		win32_window->Update();
	}

	delete win32_window;
}