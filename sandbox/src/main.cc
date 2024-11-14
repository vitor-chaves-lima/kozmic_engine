#include <kozmic/win32_window.h>

int main() {
	const auto win32_window = new Win32Window({L"Kozmic Sandbox", 1280, 720});
	win32_window->Show();

	while (win32_window->IsOpen()) {
		win32_window->Update();
	}

	delete win32_window;
}