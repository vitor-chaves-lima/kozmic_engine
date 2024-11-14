#include <kozmic/core/window/window_manager.h>

int main() {
	constexpr auto window_data = kozmic::WindowData{L"Kozmic Sandbox", 1280, 720};
	const auto window = kozmic::WindowManager::Create(window_data);

	window->Show();

	while (window->IsOpen()) {
		window->Update();
	}

	delete window;
}