#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <sstream>
#include <iomanip>

#include "Utils.h"
#include "ProgramState.h"
#include "Pokemon.h"
#include "Benchmarker.h"
#include "Finally.h"

void ClearConsole();
void WriteHeaderToConsole();
void WaitUserInput(const std::string&);

void ReadProgramStateFromConsole(char&);
void DetermineProgramState(const char&, ProgramState&);

void ManageState(ProgramState&, std::vector<Pokemon>&);
void ManageStateExit(ProgramState&);
void ManageStateInputPath();
void ManageStateReadData(std::vector<Pokemon>&);
void ManageStateWriteData(std::vector<Pokemon>&);
void ManageStateFight(std::vector<Pokemon>&);

void ReadExistingData(std::vector<Pokemon>&, std::fstream&, long long&);
void ReadNewData(std::vector<Pokemon>&, std::fstream&, long long&);
bool TestLoadFileExistance(std::fstream&);
void ReadPathFromBinaryFile(std::string&, std::fstream&);
std::size_t CountLinesInTextFile(std::fstream&, const std::string&);
void ReadDataFromTextFile(std::vector<Pokemon>&, const std::size_t&, std::fstream&, const std::string&);
void WriteDataToBinaryFile(std::vector<Pokemon>&, std::fstream&);
void ReadDataFromBinaryFile(std::vector<Pokemon>&, std::fstream&);
void WriteDataToConsole(std::vector<Pokemon>&);
Pokemon& FindPokemonByNameInVector(const std::string&, std::vector<Pokemon>&);
