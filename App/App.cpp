// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../AdventOfCode/Common.hpp"
#include "../AdventOfCode/DiagnosticLog.hpp"
#include "../AdventOfCode/BoatSystems.hpp"
#include "../AdventOfCode/AdventOfCode.hpp"
#include "../AdventOfCode/Lanternfish.hpp"
#include "../AdventOfCode/CrabSorter.hpp"

#include <vector>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <format>
#include <string>
#include <filesystem>
#include <algorithm>
#include <chrono>

using namespace std::string_literals;
using namespace std::chrono_literals;

const auto DATA_DIR = std::filesystem::path(R"(..\AdventOfCode\Data)"s);

int main()
{
	using namespace aoc;

	auto sub = Submarine{};

	std::cout << "Running..." << std::endl;

	for (int i = 0; i < 500; ++i)
	{
		std::ifstream data_file(DATA_DIR / "Day5_input.txt");
		if (!data_file)
		{
			std::cerr << "Failed to open file" << std::endl;
			return 1;
		}
		const auto vent_score = aoc::Submarine()
			.boat_systems()
			.detect_vents<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical | aoc::VentAnalyzer::diagonal>(data_file);
	}

	std::cout << "Done" << std::endl;

	return 0;
}
