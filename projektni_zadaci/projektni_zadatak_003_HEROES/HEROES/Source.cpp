#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <random>
#include <chrono>
#include <functional>

#include "application_t.h"
#include "powers_t.h"

std::vector<const char*> program_header{
	"_____________________                              _____________________",
	"`-._:  .:'   `:::  .:\\           |\\__/|           /::  .:'   `:::  .:.-'",
	"    \\      :          \\          |:   |          /         :       /",
	"     \\     ::    .     `-_______/ ::   \\_______-'   .      ::   . /",
	"      |  :   :: ::'  :   :: ::'  :   :: ::'      :: ::'  :   :: :|",
	"      |     ;::         ;::         ;::         ;::         ;::  |",
	"      |  .:'   `:::  .:'   `:::  .:'   `:::  .:'   `:::  .:'   `:|",
	"      /     :           :           :           :           :    \\",
	"     /______::_____     ::    .     ::    .     ::   _____._::____\\",
	"                   `----._:: ::'  :   :: ::'  _.----'",
	"                          `--.       ;::  .--'",
	"                              `-. .:'  .-'",
	"                                 \\    /",
	"                                  \\  /",
	"                                   \\/"
};

int main() {
	application_t application{ program_header };
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