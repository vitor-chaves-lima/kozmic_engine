#include <kozmic/win32_utils.h>

const char* FormatLastWindowsError() {
	LPVOID message_buffer = nullptr;
	const DWORD last_error_id = GetLastError();
	constexpr INT flags =
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER;
	constexpr INT lang_id = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	const size_t message_size = FormatMessageA(flags, nullptr, last_error_id, lang_id,
										 reinterpret_cast<LPSTR>(&message_buffer), 0, nullptr);

	if (!message_size)
		return "";

	const auto message_string = static_cast<LPCSTR>(message_buffer);
	LocalFree(message_buffer);

	return message_string;
}