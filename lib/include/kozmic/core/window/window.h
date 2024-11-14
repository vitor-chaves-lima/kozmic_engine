#ifndef WINDOW_H
#define WINDOW_H

namespace kozmic {
struct WindowData {
#if KOZMIC_UNICODE_SUPPORT == KOZMIC_TRUE
	const wchar_t* title;
#else
	const char* title;
#endif
	int width;
	int height;
};

class Window {
   public:
	virtual ~Window() = default;

	virtual void Show() = 0;
	virtual void Update() = 0;

	[[nodiscard]] virtual bool IsOpen() const = 0;
};
}  // namespace kozmic

#endif	//WINDOW_H