#pragma once

enum class ProgramState {
	EXIT = 0,
	INPUT_PATH,
	READ_DATA,
	WRITE_DATA,
	FIGHT,
	VOID,
	SIZE
};