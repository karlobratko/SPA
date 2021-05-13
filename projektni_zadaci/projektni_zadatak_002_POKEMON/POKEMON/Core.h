#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <iterator>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <iomanip>
#include <functional>

#include "program_state_t.h"
#include "program_state_except_t.h"
#include "pokemon_t.h"
#include "benchmarker_t.h"
#include "finally_t.h"
#include "file_t.h"

// CONSOLE:
void ClearConsole();
void WaitUserInput();
void WriteToConsole(const char*);
void WriteMsgToConsole(const std::string&);
void WaitUserToPressKey();
void WriteHeaderToConsole();

// DETERMINE STATE:
std::string ReadProgramStateFromConsole();
void DetermineProgramState(const std::string&, program_state_t&);

// MANAGE PROGRAM STATE:
void ManageProgramState(program_state_t&, std::vector<pokemon_t>&);
void ManageStateExit(program_state_t&);
void ManageStateInputPath();
void ManageStateReadData(std::vector<pokemon_t>&);
void ManageStateWriteData(std::vector<pokemon_t>&);
void ManageStateFight(std::vector<pokemon_t>&);
void ManageStateFileCopy();
void ManageStateProcessing(std::vector<pokemon_t>&);
void ManageStateSimulation(std::vector<pokemon_t>&);
void ManageStateSpeedogram(std::vector<pokemon_t>&);
void ManageStateTransaction(std::vector<pokemon_t>&);

// HELPER FUNCTIONS:
void ReadExistingData(std::vector<pokemon_t>&, long long&);
void ReadNewData(std::vector<pokemon_t>&, long long&);
bool TestLoadFileExistance();
std::string ReadPathFromBinaryFile();
void WriteDataToBinaryFile(std::vector<pokemon_t>&);
void ReadDataFromBinaryFile(std::vector<pokemon_t>&);
pokemon_t& FindPokemonByNameInVector(const std::string&, std::vector<pokemon_t>&);

template <typename Cont>
void WriteDataToConsole(Cont&);
