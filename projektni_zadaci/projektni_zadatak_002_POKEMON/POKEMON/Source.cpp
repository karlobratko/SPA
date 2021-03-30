#include "Core.h"

int main() {
	WriteHeaderToConsole();
	WaitUserInput("Press any key to continue...");

	ProgramState program_state{ ProgramState::VOID };
	char input_program_state{};
	std::vector<Pokemon> vec{};
	do {
		try {
			ReadProgramStateFromConsole(input_program_state);
			DetermineProgramState(input_program_state, program_state);
			ManageState(program_state, vec);
		}
		catch (const std::exception& err) {
			ClearConsole();
			std::cout << err.what() << std::endl;
		}

	} while (program_state != ProgramState::EXIT);

	return 0;
}