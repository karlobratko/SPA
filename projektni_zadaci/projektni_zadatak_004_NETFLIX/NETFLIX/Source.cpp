#include "application_t.h"

std::vector<const char*> header{
" __   __     ______     ______   ______   __         __     __  __    ",
"/\\ \"-.\\ \\   /\\  ___\\   /\\__  _\\ /\\  ___\\ /\\ \\       /\\ \\   /\\_\\_\\_\\   ",
"\\ \\ \\-.  \\  \\ \\  __\\   \\/_/\\ \\/ \\ \\  __\\ \\ \\ \\____  \\ \\ \\  \\/_/\\_\\/_  ",
" \\ \\_\\\\\"\\_\\  \\ \\_____\\    \\ \\_\\  \\ \\_\\    \\ \\_____\\  \\ \\_\\   /\\_\\/\\_\\ ",
"  \\/_/ \\/_/   \\/_____/     \\/_/   \\/_/     \\/_____/   \\/_/   \\/_/\\/_/ "
};

int main() {
	application_t application{ header };
	application.header();
	do {
		try {
			application.determine_state();
			application.manage_state();
		}
		catch (const std::exception& err) {
			application.catch_e(err);
		}
	} while (application.is_running());
	return 0;
}