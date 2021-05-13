#include "Core.h"

int main() {
	WriteHeaderToConsole();
	WaitUserToPressKey();

	program_state_t program_state{ program_state_t::VOID };
	std::vector<pokemon_t> vec{};

	do {
		try {
			DetermineProgramState(
				ReadProgramStateFromConsole(), 
				program_state
			);
			ManageProgramState(program_state, vec);
		}
		catch (const std::exception& err) {
			program_state = program_state_t::VOID;
			ClearConsole();
			WriteToConsole(err.what());
			WaitUserToPressKey();
		}

	} while (program_state != program_state_t::EXIT);
	return 0;
}