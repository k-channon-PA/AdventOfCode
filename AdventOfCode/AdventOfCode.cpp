#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Common.hpp"
#include "DiagnosticLog.hpp"
#include "BoatSystems.hpp"
#include "AdventOfCode.hpp"
#include "Lanternfish.hpp"
#include "CrabSorter.hpp"

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

template<>
std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<aoc::bingo::Board::State_t>(const aoc::bingo::Board::State_t& state)
{
	switch (state)
	{
	case aoc::bingo::Board::State_t::no_win: return L"no win";
	case aoc::bingo::Board::State_t::win: return L"win";
	default:
		return L"UNKNOWN";
	}
}


const auto DATA_DIR = std::filesystem::path(R"(..\..\AdventOfCode\Data)"s);

namespace program
{
TEST_CLASS(Story)
{
public:
	TEST_METHOD(_)
	{
		using namespace aoc;

		auto sub = Submarine{};

		// Day 1
		{
			Logger::WriteMessage("Day 1:\n");

			using Iter_t = std::istream_iterator<uint32_t>;
			{
				// Part 1
				std::ifstream data_file(DATA_DIR / "Day1_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto depth_score_1 = sub.boat_systems().depth_score<1>(Iter_t{ data_file }, Iter_t{});
				Logger::WriteMessage(std::format("\tCalculated depth score with window-size of 1: {}\n", depth_score_1).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day1_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto depth_score_3 = sub.boat_systems().depth_score<3>(Iter_t{ data_file }, Iter_t{});
				Logger::WriteMessage(std::format("\tCalculated depth score with window-size of 3: {}\n", depth_score_3).c_str());
			}
		}

		// Day 2
		{
			Logger::WriteMessage("Day 2:\n");

			using Iter_t = std::istream_iterator<aoc::Direction>;

			// Part 1
			{
				std::ifstream data_file(DATA_DIR / "Day2_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto net_direction = sub.boat_systems().net_direction(Iter_t{ data_file }, Iter_t{});
				Logger::WriteMessage(std::format("\tNet direction: ({}, {})\n", net_direction.x, net_direction.y).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day2_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto net_aiming = sub.boat_systems().net_aiming(Iter_t{ data_file }, Iter_t{});
				Logger::WriteMessage(std::format("\tNet aiming: ({}, {})\n", net_aiming.x, net_aiming.y).c_str());
			}
		}

		// Day 3
		{
			Logger::WriteMessage("Day 3:\n");

			// Part 1
			{
				std::ifstream data_file(DATA_DIR / "Day3_input.txt");
				Assert::IsTrue(data_file.is_open());

				auto log = aoc::DiagnosticLog{ data_file };

				const auto power_consumption = aoc::Submarine().boat_systems().power_consumption(log);

				Logger::WriteMessage(std::format("\tPower: {}\n", power_consumption).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day3_input.txt");
				Assert::IsTrue(data_file.is_open());

				auto log = aoc::DiagnosticLog{ data_file };

				Logger::WriteMessage(std::format("\tLife support rating: {}\n",
					aoc::Submarine().boat_systems().life_support_rating(log)).c_str());
			}
		}

		// Day 4
		{
			Logger::WriteMessage("Day 4:\n");

			// Part 1
			{
				std::ifstream data_file(DATA_DIR / "Day4_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto game_score = aoc::Submarine().entertainment().bingo_game()
					.load(data_file)
					.play_to_win()
					.score();

				Logger::WriteMessage(std::format("\tWinning bingo score: {}\n", *game_score).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day4_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto game_score = aoc::Submarine().entertainment().bingo_game()
					.load(data_file)
					.play_to_lose()
					.score();

				Logger::WriteMessage(std::format("\tLosing bingo score: {}\n", *game_score).c_str());
			}
		}

		// Day 5
		{
			Logger::WriteMessage("Day 5:\n");

			// Part 1
			{
				std::ifstream data_file(DATA_DIR / "Day5_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto vent_score = aoc::Submarine()
					.boat_systems()
					.detect_vents<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical>(data_file);

				Logger::WriteMessage(std::format("\tHorizontal|vertical vent score: {}\n", vent_score).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day5_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto vent_score = aoc::Submarine()
					.boat_systems()
					.detect_vents<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical | aoc::VentAnalyzer::diagonal>(data_file);

				Logger::WriteMessage(std::format("\tHorizontal|vertical|diagonal vent score: {}\n", vent_score).c_str());
			}
		}

		// Day 6
		{
			Logger::WriteMessage("Day 6:\n");

			// Part 1
			{
				std::ifstream data_file(DATA_DIR / "Day6_input.txt");
				Assert::IsTrue(data_file.is_open());

				auto shoal = aoc::LanternfishShoal{}.load(data_file);

				const auto number_of_fish = aoc::LanternfishShoalModel{ shoal }.run_for(std::chrono::days(80)).shoal_size();

				Logger::WriteMessage(std::format("\tShoal size after 80 days: {}\n", number_of_fish).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day6_input.txt");
				Assert::IsTrue(data_file.is_open());

				auto shoal = aoc::LanternfishShoal{}.load(data_file);

				const auto number_of_fish = aoc::LanternfishShoalModel{ shoal }.run_for(std::chrono::days(256)).shoal_size();

				Logger::WriteMessage(std::format("\tShoal size after 256 days: {}\n", number_of_fish).c_str());
			}
		}

		// Day 7
		{
			Logger::WriteMessage("Day 7:\n");

			// Part 1
			{
				std::ifstream data_file(DATA_DIR / "Day7_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto [best_position, cost] = aoc::CrabSorter{}.load(data_file).best_position_and_cost([](uint32_t distance) { return distance; });

				Logger::WriteMessage(std::format("\tBest position: {}, cost: {}\n", best_position, cost).c_str());
			}

			// Part 2
			{
				std::ifstream data_file(DATA_DIR / "Day7_input.txt");
				Assert::IsTrue(data_file.is_open());

				const auto [best_position, cost] = aoc::CrabSorter{}
					.load(data_file)
					.best_position_and_cost([](uint32_t distance) {
					return (distance * (1 + distance)) / 2;
						});

				Logger::WriteMessage(std::format("\tBest position: {}, cost: {}\n", best_position, cost).c_str());
			}
		}
	}
};
}

namespace common
{
TEST_CLASS(Vec2d)
{
public:

	TEST_METHOD(CanBeAdded)
	{
		const auto v1 = aoc::Vec2d<int>{ 1, 2 };
		const auto v2 = aoc::Vec2d<int>{ 3, 4 };

		const auto v3 = v1 + v2;

		Assert::AreEqual(4, v3.x);
		Assert::AreEqual(6, v3.y);
	}

	TEST_METHOD(StreamExtractionWorksForValidStream)
	{
		std::stringstream ss("1,2");
		auto v = aoc::Vec2d<uint32_t>{};

		ss >> v;

		Assert::AreEqual(uint32_t{ 1 }, v.x);
		Assert::AreEqual(uint32_t{ 2 }, v.y);
	}

	TEST_METHOD(StreamExtractionFailsIfMalformed)
	{
		std::stringstream ss("09");
		auto v = aoc::Vec2d<uint32_t>{};

		Assert::ExpectException<aoc::Exception>([&]() { ss >> v; });

		Assert::IsTrue(ss.fail());
	}

	TEST_METHOD(StreamExtractionFailsIfThereAreNonnumericElements)
	{
		std::stringstream ss("0,X");
		auto v = aoc::Vec2d<uint32_t>{};

		Assert::ExpectException<aoc::Exception>([&]() { ss >> v; });

		Assert::IsTrue(ss.fail());
	}
};

TEST_CLASS(Line2d)
{
public:
	TEST_METHOD(StreamExtractionWorksForValidStream)
	{
		std::stringstream ss("0,9 -> 5,7");
		auto line = aoc::Line2d<uint32_t>{};

		ss >> line;

		Assert::AreEqual(uint32_t{ 0 }, line.start.x);
		Assert::AreEqual(uint32_t{ 9 }, line.start.y);
		Assert::AreEqual(uint32_t{ 5 }, line.finish.x);
		Assert::AreEqual(uint32_t{ 7 }, line.finish.y);
	}

	TEST_METHOD(StreamExtractionFailsIfStartIsMalformed)
	{
		std::stringstream ss("09 -> 5,7");
		auto line = aoc::Line2d<uint32_t>{};

		Assert::ExpectException<aoc::Exception>( [&]() { ss >> line; });

		Assert::IsTrue(ss.fail());
	}

	TEST_METHOD(StreamExtractionFailsIfFinishIsMalformed)
	{
		std::stringstream ss("0,9 -> 57");
		auto line = aoc::Line2d<uint32_t>{};

		Assert::ExpectException<aoc::Exception>([&]() { ss >> line; });

		Assert::IsTrue(ss.fail());
	}

	TEST_METHOD(StreamExtractionFailsIfArrowIsMalformed)
	{
		std::stringstream ss("0,9 , 5,7");
		auto line = aoc::Line2d<uint32_t>{};

		Assert::ExpectException<aoc::Exception>([&]() { ss >> line; });

		Assert::IsTrue(ss.fail());
	}

	TEST_METHOD(StreamExtractionFailsIfThereAreNonnumericElements)
	{
		std::stringstream ss("0,X , 5,7");
		auto line = aoc::Line2d<uint32_t>{};

		Assert::ExpectException<aoc::Exception>([&]() { ss >> line; });

		Assert::IsTrue(ss.fail());
	}

	TEST_METHOD(ExtractMoreThanOneLineFromStream)
	{
		std::stringstream ss("0,9 -> 5,7\n8,0 -> 0,8");
		auto line1 = aoc::Line2d<uint32_t>{};
		auto line2 = aoc::Line2d<uint32_t>{};

		ss >> line1 >> line2;

		Assert::AreEqual(uint32_t{ 0 }, line1.start.x);
		Assert::AreEqual(uint32_t{ 9 }, line1.start.y);
		Assert::AreEqual(uint32_t{ 5 }, line1.finish.x);
		Assert::AreEqual(uint32_t{ 7 }, line1.finish.y);

		Assert::AreEqual(uint32_t{ 8 }, line2.start.x);
		Assert::AreEqual(uint32_t{ 0 }, line2.start.y);
		Assert::AreEqual(uint32_t{ 0 }, line2.finish.x);
		Assert::AreEqual(uint32_t{ 8 }, line2.finish.y);
	}

	TEST_METHOD(FromMethodReadsFromStream)
	{
		std::stringstream ss("7,0 -> 7,4");

		const auto line = aoc::Line2d<uint32_t>{}.from(ss);

		Assert::AreEqual(uint32_t{ 7 }, line.start.x);
		Assert::AreEqual(uint32_t{ 0 }, line.start.y);
		Assert::AreEqual(uint32_t{ 7 }, line.finish.x);
		Assert::AreEqual(uint32_t{ 4 }, line.finish.y);
	}

	TEST_METHOD(IsVerticalIdentifiesAnUpwardVerticalLine)
	{
		Assert::IsTrue(aoc::is_vertical(aoc::Line2d<uint32_t>{ {7, 0}, {7, 4} }));
	}

	TEST_METHOD(IsVerticalIdentifiesADownwardVerticalLine)
	{
		Assert::IsTrue(aoc::is_vertical(aoc::Line2d<uint32_t>{ {10, 5}, {10, 1} }));
	}

	TEST_METHOD(IsVerticalIsFalseForNonVerticalLines)
	{
		Assert::IsFalse(aoc::is_vertical(aoc::Line2d<uint32_t>{ {10, 5}, {9, 1}}));
	}

	TEST_METHOD(IsHorizontalIdentifiesALeftHorizontalLine)
	{
		Assert::IsTrue(aoc::is_horizontal(aoc::Line2d<uint32_t>{ {7, 0}, {10, 0}}));
	}

	TEST_METHOD(IsHorizontalIdentifiesARightHorizontalLine)
	{
		Assert::IsTrue(aoc::is_horizontal(aoc::Line2d<uint32_t>{ {10, 5}, {4, 5}}));
	}

	TEST_METHOD(IsHorizontalIsFalseForNonVerticalLines)
	{
		Assert::IsFalse(aoc::is_horizontal(aoc::Line2d<uint32_t>{ {3, 5}, {9, 1}}));
	}

	TEST_METHOD(IsDiagonalIdentifiesUpRightDiagonalLine)
	{
		Assert::IsTrue(aoc::is_diagonal(aoc::Line2d<uint32_t>{ {1, 1}, { 5, 5 }}));
	}

	TEST_METHOD(IsDiagonalIdentifiesUpLeftDiagonalLine)
	{
		Assert::IsTrue(aoc::is_diagonal(aoc::Line2d<uint32_t>{ {9, 7}, { 5, 11 }}));
	}
	
	TEST_METHOD(IsDiagonalIdentifiesDownRightDiagonalLine)
	{
		Assert::IsTrue(aoc::is_diagonal(aoc::Line2d<uint32_t>{ {1, 6}, { 6, 1 }}));
	}

	TEST_METHOD(IsDiagonalIdentifiesDownLeftDiagonalLine)
	{
		Assert::IsTrue(aoc::is_diagonal(aoc::Line2d<uint32_t>{ {6, 6}, { 1, 1 }}));
	}

	TEST_METHOD(IsDiagonalIsFalseForNonDiagonalLine)
	{
		Assert::IsFalse(aoc::is_diagonal(aoc::Line2d<uint32_t>{ {1, 1}, { 3, 5 }}));
	}

	TEST_METHOD(RasterizeVerticalLinesWorks)
	{
		using Line_t = aoc::Line2d<uint32_t>;
		const auto points = aoc::rasterize<Line_t::horizontal | Line_t::vertical>(Line_t{ {1, 1}, { 1, 5 } });

		const auto expected_points = std::vector<aoc::Vec2d<uint32_t>>{ {1,1}, {1,2}, {1,3}, {1,4}, {1,5} };

		Assert::IsTrue(std::equal(expected_points.begin(), expected_points.end(), points.begin()));
	}
	TEST_METHOD(RasterizeHorizontalLinesWorks)
	{
		using Line_t = aoc::Line2d<uint32_t>;
		const auto points = aoc::rasterize<Line_t::horizontal | Line_t::vertical>(Line_t{ {1, 1}, { 5, 1 } });

		const auto expected_points = std::vector<aoc::Vec2d<uint32_t>>{ {1,1}, {2,1}, {3,1}, {4,1}, {5,1} };

		Assert::IsTrue(std::equal(expected_points.begin(), expected_points.end(), points.begin()));
	}

	TEST_METHOD(RasterizeThrowsForNonHorizontalOrVerticalLines)
	{
		using Line_t = aoc::Line2d<uint32_t>;
		Assert::ExpectException<aoc::Exception>([]() {
			aoc::rasterize<Line_t::horizontal | Line_t::vertical>(Line_t{ {1, 2}, { 5, 1 } });
		});
	}

	TEST_METHOD(RasterizeDownwardVerticalLinesWorks)
	{
		using Line_t = aoc::Line2d<uint32_t>;
		const auto points = aoc::rasterize<Line_t::horizontal | Line_t::vertical>(Line_t{ {1, 5}, { 1, 1 } });

		const auto expected_points = std::vector<aoc::Vec2d<uint32_t>>{ {1,1}, {1,2}, {1,3}, {1,4}, {1,5} };

		Assert::IsTrue(std::equal(expected_points.begin(), expected_points.end(), points.begin()));
	}

	TEST_METHOD(RasterizeLeftHorizontalLinesWorks)
	{
		using Line_t = aoc::Line2d<uint32_t>;
		const auto points = aoc::rasterize<Line_t::horizontal | Line_t::vertical>(Line_t{ {5, 1}, { 1, 1 } });

		const auto expected_points = std::vector<aoc::Vec2d<uint32_t>>{ {1,1}, {2,1}, {3,1}, {4,1}, {5,1} };

		Assert::IsTrue(std::equal(expected_points.begin(), expected_points.end(), points.begin()));
	}
};
}

namespace string_operations
{
TEST_CLASS(SplitString)
{
public:

	TEST_METHOD(splitStringWorksWhenDropEmptyOptionIsSet)
	{
		const auto str = "1 2 3"s;
		const auto split_str = split(str, ' ', SplitBehaviour::drop_empty);

		Assert::AreEqual(size_t{ 3 }, split_str.size());
	}

	TEST_METHOD(splitStringWorksWhenDropEmptyOptionIsNotSet)
	{
		const auto str = "1 2 3"s;
		const auto split_str = split(str, ' ');

		Assert::AreEqual(size_t{ 3 }, split_str.size());
	}

	TEST_METHOD(SplitStringDropsConsecutiveDelimitersWhenOptionIsSet)
	{
		const auto str = "1  2      3"s;
		const auto split_str = split(str, ' ', SplitBehaviour::drop_empty);

		Assert::AreEqual(size_t{ 3 }, split_str.size());
	}

	TEST_METHOD(SplitStringDropsConsecutiveDelimitersAtBeginning)
	{
		const auto str = "   1 2      3"s;
		const auto split_str = split(str, ' ', SplitBehaviour::drop_empty);

		Assert::AreEqual(size_t{ 3 }, split_str.size());
	}

	TEST_METHOD(SplitStringDropsConsecutiveDelimitersAtEnd)
	{
		const auto str = "1 2      3   "s;
		const auto split_str = split(str, ' ', SplitBehaviour::drop_empty);

		Assert::AreEqual(size_t{ 3 }, split_str.size());
	}

	TEST_METHOD(SplitStringEmptyResultWhenStringIsOnlyDelimiters)
	{
		const auto str = "   "s;
		const auto split_str = split(str, ' ', SplitBehaviour::drop_empty);

		Assert::IsTrue(split_str.empty());
	}

	TEST_METHOD(SplitStringNonEmptyResultWhenStringIsOnlyUndroppedDelimiters)
	{
		const auto str = "    "s;
		const auto split_str = split(str, ' ', SplitBehaviour::none);

		Assert::AreEqual(size_t{ 4 }, split_str.size());
	}
};
}

namespace boat_systems
{
TEST_CLASS(DirectionAndAiming)
{
public:
	TEST_METHOD(InvalidInputDirectionThrows)
	{
		Assert::ExpectException<aoc::Exception>([]() {
			std::stringstream ss("wibble 5"s);
			auto d = aoc::Direction{};
			ss >> d;
			});
	}

	TEST_METHOD(InvalidInputNumberThrows)
	{
		Assert::ExpectException<aoc::Exception>([]() {
			std::stringstream ss("forward xx"s);
			auto d = aoc::Direction{};
			ss >> d; });
	}

	TEST_METHOD(CreateDirectionFromInputRow_forward)
	{
		std::stringstream ss("forward 9");
		auto direction = aoc::Direction{};

		ss >> direction;

		Assert::AreEqual(9, direction.x);
		Assert::AreEqual(0, direction.y);
	}

	TEST_METHOD(CreateDirectionFromInputRow_up)
	{
		std::stringstream ss("up 5"s);
		auto direction = aoc::Direction{};

		ss >> direction;

		Assert::AreEqual(0, direction.x);
		Assert::AreEqual(-5, direction.y);
	}

	TEST_METHOD(CreateDirectionFromInputRow_down)
	{
		std::stringstream ss("down 30"s);
		auto direction = aoc::Direction{};

		ss >> direction;

		Assert::AreEqual(0, direction.x);
		Assert::AreEqual(30, direction.y);
	}

	TEST_METHOD(ParseDirectionsFromStream)
	{
		std::stringstream ss("forward 3\ndown 3\nforward 12\ndown 5\nup 2");

		using StreamIter_t = std::istream_iterator<aoc::Direction>;
		const auto net_direction = aoc::Submarine().boat_systems().net_direction(StreamIter_t(ss), StreamIter_t());

		Assert::AreEqual(15, net_direction.x);
		Assert::AreEqual(6, net_direction.y);
	}

	TEST_METHOD(DirectionsCanBeAddedAimings)
	{
		auto aiming = aoc::Aiming{};

		aiming = aiming + aoc::Direction{ 5, 0 };

		Assert::AreEqual(5, aiming.x);
		Assert::AreEqual(0, aiming.aim);
		Assert::AreEqual(0, aiming.depth);

		aiming = aiming + aoc::Direction{ 0, 5 };

		Assert::AreEqual(5, aiming.x);
		Assert::AreEqual(5, aiming.aim);
		Assert::AreEqual(0, aiming.depth);

		aiming = aiming + aoc::Direction{ 8, 0 };

		Assert::AreEqual(13, aiming.x);
		Assert::AreEqual(5, aiming.aim);
		Assert::AreEqual(40, aiming.depth);

		aiming = aiming + aoc::Direction{ 0, -3 };

		Assert::AreEqual(13, aiming.x);
		Assert::AreEqual(2, aiming.aim);
		Assert::AreEqual(40, aiming.depth);

		aiming = aiming + aoc::Direction{ 0, 8 };

		Assert::AreEqual(13, aiming.x);
		Assert::AreEqual(10, aiming.aim);
		Assert::AreEqual(40, aiming.depth);

		aiming = aiming + aoc::Direction{ 2, 0 };

		Assert::AreEqual(15, aiming.x);
		Assert::AreEqual(10, aiming.aim);
		Assert::AreEqual(60, aiming.depth);
	}

	TEST_METHOD(ConvertingAimingToDirectionWorks)
	{
		const auto d = aoc::Aiming{ 1, 2, 3 }.to_direction();

		Assert::AreEqual(1, d.x);
		Assert::AreEqual(3, d.y);
	}

	TEST_METHOD(AimingFromStreamWorks)
	{
		std::stringstream ss("forward 5\ndown 5\nforward 8\nup 3\ndown 8\nforward 2");

		using StreamIter_t = std::istream_iterator<aoc::Direction>;
		const auto net_aim = aoc::Submarine().boat_systems().net_aiming(StreamIter_t(ss), StreamIter_t());

		Assert::AreEqual(15, net_aim.x);
		Assert::AreEqual(60, net_aim.y);
	}
};

TEST_CLASS(DepthMeasurements)
{
public:

	TEST_METHOD(CountNetIncreaseFromVector)
	{
		auto measurements = std::vector<uint32_t>{ 1, 2, 3, 2, 1, 2, 3 };

		auto depth_score = aoc::Submarine().boat_systems().depth_score<1>(measurements.begin(), measurements.end());

		Assert::AreEqual(uint32_t{ 4 }, depth_score);
	}

	TEST_METHOD(DepthScoreVectorWithVariousJumps)
	{
		auto measurements = std::vector<uint32_t>{ 1, 22, 3, 200, 1000, 2, 3, 4, 100 };

		auto depth_score = aoc::Submarine().boat_systems().depth_score<1>(measurements.begin(), measurements.end());

		Assert::AreEqual(uint32_t{ 6 }, depth_score);
	}

	TEST_METHOD(ExampleValues)
	{
		auto measurements = std::vector<uint32_t>{ 199, 200, 208, 210, 200, 207, 240, 269, 260, 263 };

		auto depth_score = aoc::Submarine().boat_systems().depth_score<1>(measurements.begin(), measurements.end());

		Assert::AreEqual(uint32_t{ 7 }, depth_score);
	}
};

TEST_CLASS(LifeSupportSystems)
{
public:

	TEST_METHOD(LifeSupportFilterBitsWorks)
	{
		const auto target_entry = aoc::DiagnosticLog::Entry_t{ 0,1,1,0,1,0,0,1,0,1,1,0 };

		constexpr auto log_lines =
			"111011110101\n"
			"011000111010\n"
			"100000010010";

		std::stringstream ss(log_lines);
		const auto best_match = aoc::LifeSupport(aoc::DiagnosticLog{ ss }).filter_using_most_frequent_bits();

		Assert::AreEqual(aoc::DiagnosticLog::entry_as<uint32_t>({ 1,1,1,0,1,1,1,1,0,1,0,1 }), best_match);
	}

	TEST_METHOD(FilterBitsForMostCommonOnExampleData)
	{
		constexpr auto log_lines =
			"000000000100\n"
			"000000011110\n"
			"000000010110\n"
			"000000010111\n"
			"000000010101\n"
			"000000001111\n"
			"000000000111\n"
			"000000011100\n"
			"000000010000\n"
			"000000011001\n"
			"000000000010\n"
			"000000001010";

		std::stringstream ss(log_lines);
		const auto log = aoc::DiagnosticLog{ ss };

		const auto best_match = aoc::LifeSupport(log).filter_using_most_frequent_bits();
		Assert::AreEqual(uint32_t{ 0b10111 }, best_match);
	}

	TEST_METHOD(FilterBitsForLeastCommonOnExampleData)
	{
		constexpr auto log_lines =
			"001000000000\n"
			"111100000000\n"
			"101100000000\n"
			"101110000000\n"
			"101010000000\n"
			"011110000000\n"
			"001110000000\n"
			"111000000000\n"
			"100000000000\n"
			"110010000000\n"
			"000100000000\n"
			"010100000000";

		std::stringstream ss(log_lines);
		const auto log = aoc::DiagnosticLog{ ss };

		const auto best_match = aoc::LifeSupport(log).filter_using_least_frequent_bits();
		Assert::AreEqual(uint32_t{ 0b10100000000 }, best_match);
	}
};

TEST_CLASS(VentAnalysis)
{
public:
	TEST_METHOD(VentAnalyserScoresExampleData)
	{
		constexpr auto data_str =
			"0,9 -> 5,9\n"
			"8,0 -> 0,8\n"
			"9,4 -> 3,4\n"
			"2,2 -> 2,1\n"
			"7,0 -> 7,4\n"
			"6,4 -> 2,0\n"
			"0,9 -> 2,9\n"
			"3,4 -> 1,4\n"
			"0,0 -> 8,8\n"
			"5,5 -> 8,2";

		std::stringstream data{ data_str };

		Assert::AreEqual(uint32_t{ 5 }, aoc::VentAnalyzer{ data }.score<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical>());
	}
	TEST_METHOD(VentAnalyserScoresExampleDataWithDiagonals)
	{
		constexpr auto data_str =
			"0,9 -> 5,9\n"
			"8,0 -> 0,8\n"
			"9,4 -> 3,4\n"
			"2,2 -> 2,1\n"
			"7,0 -> 7,4\n"
			"6,4 -> 2,0\n"
			"0,9 -> 2,9\n"
			"3,4 -> 1,4\n"
			"0,0 -> 8,8\n"
			"5,5 -> 8,2";

		std::stringstream data{ data_str };

		Assert::AreEqual(uint32_t{ 12 }, aoc::VentAnalyzer{ data }
		.score<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical | aoc::VentAnalyzer::diagonal>());
	}
};
}

namespace diagnostic_log
{
TEST_CLASS(DiagnosticLog)
{
public:

	TEST_METHOD(ReadLogEntriedFromStream)
	{
		std::stringstream ss("111011110101");
		auto log_entry = aoc::DiagnosticLog::Entry_t{};

		ss >> log_entry;

		auto a1 = aoc::DiagnosticLog::Entry_t{ 1,1,1,0,1,1,1,1,0,1,0,1 };
		for (auto i = 0; i < a1.size(); ++i)
		{
			Assert::AreEqual(a1[i], log_entry[i]);
		}
	}

	TEST_METHOD(ReadMultiplePowerParamsFromStream)
	{
		std::stringstream ss("111011110101\n011000111010");
		auto v = std::vector<aoc::DiagnosticLog::Entry_t>{};

		using Iter_t = std::istream_iterator<aoc::DiagnosticLog::Entry_t>;

		std::copy(Iter_t(ss), Iter_t(), std::back_inserter(v));

		Assert::AreEqual(size_t{ 2 }, v.size());

		const auto entry_1 = aoc::DiagnosticLog::Entry_t{ 1,1,1,0,1,1,1,1,0,1,0,1 };
		for (auto i = 0; i < entry_1.size(); ++i)
		{
			Assert::AreEqual(entry_1[i], v[0][i]);
		}

		const auto Entry_2 = aoc::DiagnosticLog::Entry_t{ 0,1,1,0,0,0,1,1,1,0,1,0 };
		for (auto i = 0; i < Entry_2.size(); ++i)
		{
			Assert::AreEqual(Entry_2[i], v[1][i]);
		}
	}

	TEST_METHOD(DiagnosticLogEntryAsWorks)
	{
		Assert::AreEqual(uint32_t{ 0b111000110010 },
			aoc::DiagnosticLog::entry_as<uint32_t>({ 1,1,1,0,0,0,1,1,0,0,1,0 }));
	}

	TEST_METHOD(DiagnosticLogFlippedEntryAsWorks)
	{
		Assert::AreEqual(uint32_t{ 0b000111001101 },
			aoc::DiagnosticLog::flipped_entry_as<uint32_t>({ 1,1,1,0,0,0,1,1,0,0,1,0 }));
	}

	TEST_METHOD(BadDiagnosticLogEntryCausesException)
	{
		// First entry has too many bits in it.
		std::stringstream ss("1110111101011\n011000111010\n100000010010");
		auto log = aoc::DiagnosticLog{};

		Assert::ExpectException<aoc::Exception>([&]() { log.load(ss); });
	}

	TEST_METHOD(BadDiagnosticLogEntrySetsStreamFailbit)
	{
		// First entry has too many bits in it.
		std::stringstream ss("1110111101011\n011000111010\n100000010010");
		auto log = aoc::DiagnosticLog{};

		try { log.load(ss); }
		catch (const aoc::Exception&) {}

		Assert::IsTrue(ss.fail());
	}

	TEST_METHOD(DiagnosticLogBeginAndEndAreCorrect)
	{
		std::stringstream ss("111011110101\n011000111010\n100000010010");
		auto log = aoc::DiagnosticLog{ ss };

		Assert::AreEqual(ptrdiff_t{ 3 }, std::distance(log.begin(), log.end()));
	}

	TEST_METHOD(InvalidCharacterInLogCausesException)
	{
		// Second entry has an invalid character in it.
		std::stringstream ss("111011110101\n011000121010\n100000010010");
		auto log = aoc::DiagnosticLog{};

		Assert::ExpectException<aoc::Exception>([&]() { log.load(ss); });
	}

	TEST_METHOD(DiagnosticLogMostFrequentBitsWorks)
	{
		std::stringstream ss("111011110101\n"
			"011000111010\n"
			"100000010010");

		const auto log = aoc::DiagnosticLog{ ss };

		const auto most_frequent_bits = log.get_most_frequent_bits();
		const auto expected = aoc::DiagnosticLog::Entry_t{ 1,1,1,0,0,0,1,1,0,0,1,0 };

		Assert::IsTrue(std::equal(expected.begin(), expected.end(), most_frequent_bits.begin()));
	}

	TEST_METHOD(DiagnosticLogLeastFrequentBitsWorks)
	{
		std::stringstream ss("111011110101\n"
			"011000111010\n"
			"100000010010");

		const auto log = aoc::DiagnosticLog{ ss };

		const auto least_frequent_bits = log.get_least_frequent_bits();
		const auto expected = aoc::DiagnosticLog::Entry_t{ 0,0,0,1,1,1,0,0,1,1,0,1 };

		Assert::IsTrue(std::equal(expected.begin(), expected.end(), least_frequent_bits.begin()));
	}
};
}

namespace entertainment
{
TEST_CLASS(BingoGame)
{
public:

	TEST_METHOD(LoadExampleDraws)
	{
		std::stringstream ss{ "7, 4, 9, 5\n" };

		auto draws = aoc::bingo::FileBasedNumberDrawer<uint8_t>{};

		draws.load(ss);

		const auto expected_draws = { 7, 4, 9, 5 };
		Assert::IsTrue(std::equal(expected_draws.begin(), expected_draws.end(), draws.begin()));
	}

	TEST_METHOD(BoardIdReturnsCorrectId)
	{
		Assert::AreEqual(aoc::bingo::Board::Id_t{ 10 }, aoc::bingo::Board{ 10, 3 }.id());
	}

	TEST_METHOD(LoadBoard)
	{
		constexpr auto board_str =
			"22 13 17 11  0\n"
			" 8  2 23  4 24\n"
			"21  9 14 16  7\n"
			" 6 10  3 18  5\n"
			" 1 12 20 15 19\n"
			"\n";

		std::stringstream ss{ board_str };

		auto board = aoc::bingo::Board{ 0, 5 };

		board.load(ss);
	}

	TEST_METHOD(IterateBoardWorks)
	{
		constexpr auto board_str =
			"22 13 17 11  0\n"
			" 8  2 23  4 24\n"
			"21  9 14 16  7\n"
			" 6 10  3 18  5\n"
			" 1 12 20 15 19\n"
			"\n";

		std::stringstream ss{ board_str };

		auto board = aoc::bingo::Board{ 0, 5 };

		board.load(ss);

		const auto expected_values = { 22, 8, 21, 6, 1, 13, 2, 9, 10, 12, 17, 23, 14, 3, 20, 11, 4, 16, 18, 15, 0, 24, 7, 5, 19 };
		auto cell = board.begin();
		for (auto expected = expected_values.begin(); expected != expected_values.end(); ++expected, ++cell) {
			Assert::AreEqual(static_cast<uint8_t>( *expected ), (*cell).value);
		}
	}

	TEST_METHOD(LoadGame)
	{
		constexpr auto game_str =
			"7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1\n"
			"\n"
			"22 13 17 11  0\n"
			"8  2 23  4 24\n"
			"21  9 14 16  7\n"
			"6 10  3 18  5\n"
			"1 12 20 15 19\n"
			"\n"
			"3 15  0  2 22\n"
			"9 18 13 17  5\n"
			"19  8  7 25 23\n"
			"20 11 10 24  4\n"
			"14 21 16 12  6\n"
			"\n"
			"14 21 17 24  4\n"
			"10 16 15  9 19\n"
			"18  8 23 26 20\n"
			"22 11 13  6  5\n"
			"2  0 12  3  7";

		std::stringstream ss{ game_str };

		auto game = aoc::bingo::Game<aoc::bingo::FileBasedNumberDrawer<uint8_t>>{}.load(ss);
	}

	TEST_METHOD(PlayGame)
	{
		constexpr auto game_str =
			"7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1\n"
			"\n"
			"22 13 17 11  0\n"
			"8  2 23  4 24\n"
			"21  9 14 16  7\n"
			"6 10  3 18  5\n"
			"1 12 20 15 19\n"
			"\n"
			"3 15  0  2 22\n"
			"9 18 13 17  5\n"
			"19  8  7 25 23\n"
			"20 11 10 24  4\n"
			"14 21 16 12  6\n"
			"\n"
			"14 21 17 24  4\n"
			"10 16 15  9 19\n"
			"18  8 23 26 20\n"
			"22 11 13  6  5\n"
			"2  0 12  3  7";

		std::stringstream ss{ game_str };

		auto game = aoc::bingo::Game<aoc::bingo::FileBasedNumberDrawer<uint8_t>>{}.load(ss).play_to_win();
	}

	TEST_METHOD(PlayingWithoutABoardCausesAnException)
	{
		Assert::ExpectException<aoc::Exception>([]() {aoc::bingo::Player().play_number(10); });
	}

	TEST_METHOD(PlayerCanCheckBoardIfBoardHasWon)
	{
		constexpr auto board_str =
			"22 13 17\n"
			" 8  2 23\n"
			"21  9 14";

		std::stringstream ss{ board_str };

		auto board = aoc::bingo::Board{ 0, 3 }.load(ss);

		auto player = aoc::bingo::Player().assign_board(board);

		Assert::AreEqual(aoc::bingo::Board::State_t::no_win, player.play_number(22));
		Assert::AreEqual(aoc::bingo::Board::State_t::no_win, player.play_number(13));
		Assert::AreEqual(aoc::bingo::Board::State_t::win, player.play_number(17));
	}

	TEST_METHOD(GameDetectsRowWin)
	{

		constexpr auto game_str =
			"7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1\n"
			"\n"
			"22 13 17 11  0\n"
			"8  2 23  4 24\n"
			"21  9 14 16  7\n"
			"6 10  3 18  5\n"
			"1 12 20 15 19\n"
			"\n"
			"3 15  0  2 22\n"
			"9 18 13 17  5\n"
			"19  8  7 25 23\n"
			"20 11 10 24  4\n"
			"14 21 16 12  6\n"
			"\n"
			"14 21 17 24  4\n"
			"10 16 15  9 19\n"
			"18  8 23 26 20\n"
			"22 11 13  6  5\n"
			"2  0 12  3  7";

		std::stringstream ss{ game_str };

		auto winner = aoc::bingo::Game<aoc::bingo::FileBasedNumberDrawer<uint8_t>>{}
			.load(ss)
			.play_to_win()
			.get_winner();

		Assert::IsTrue(std::nullopt != winner);
		Assert::AreEqual(uint8_t{ 24 }, winner->number);
		Assert::AreEqual(aoc::bingo::Board::Id_t{ 2 }, winner->board.id());
	}

	TEST_METHOD(GameDetectsColumnWin)
	{

		constexpr auto game_str =
			"1, 2, 3, 4, 5, 6, 7\n"
			"\n"
			"22 13 17 11  0\n"
			" 8  2 23  4 24\n"
			"21  9 14 16  7\n"
			" 6 10  3 18  5\n"
			" 1 12 20 15 19\n"
			"\n"
			" 8  1  0 30 22\n"
			" 9  2 13 17 21\n"
			"19  3  7 25 23\n"
			"20  4 10 24 11\n"
			"14  5 16 12  6\n"
			"\n"
			"14 21 17 24  4\n"
			"10 16 15  9 19\n"
			"18  8 23 26 20\n"
			"22 11 13  6  5\n"
			" 2  0 12  3  7";

		std::stringstream ss{ game_str };

		auto winner = aoc::bingo::Game<aoc::bingo::FileBasedNumberDrawer<uint8_t>>{}
			.load(ss)
			.play_to_win()
			.get_winner();

		Assert::IsTrue(std::nullopt != winner);
		Assert::AreEqual(uint8_t{ 5 }, winner->number);
		Assert::AreEqual(aoc::bingo::Board::Id_t{ 1 }, winner->board.id());
	}
};
}

namespace modelling
{
TEST_CLASS(LanternFish)
{
public:
	TEST_METHOD(FishFromIntHasCorrectLife)
	{
		Assert::AreEqual(uint32_t{ 3 }, aoc::Lanternfish{ 3 }.days_until_spawning());
	}

	TEST_METHOD(ShoalOfFishCanBeReadFromStream)
	{
		std::stringstream data("3,4,3,1,2");
		const auto shoal = aoc::LanternfishShoal{}.load(data);

		Assert::AreEqual(aoc::LanternfishShoal::Size_t{ 5 }, shoal.size());
	}

	TEST_METHOD(ReadingShoalFromMalformedStringRaisesAocException)
	{
		std::stringstream data("3,4,X,1,2");
		Assert::ExpectException<aoc::Exception>([&data]() { aoc::LanternfishShoal{}.load(data); });
		Assert::IsTrue(data.fail());
	}

	TEST_METHOD(ReadingShoalFromStringWithOutOfRangeValueRaisesAocException)
	{
		std::stringstream data("3,4,5,-3,2");
		Assert::ExpectException<aoc::Exception>([&data]() { aoc::LanternfishShoal{}.load(data); });
		Assert::IsTrue(data.fail());
	}

	TEST_METHOD(ExampleShoalIsCorrectAfter18Days)
	{
		std::stringstream data("3,4,3,1,2");
		auto shoal = aoc::LanternfishShoal{}.load(data);

		const auto number_of_fish = aoc::LanternfishShoalModel{ shoal }.run_for(std::chrono::days(18)).shoal_size();

		Assert::AreEqual(aoc::LanternfishShoal::Size_t{ 26 }, number_of_fish);
	}

	TEST_METHOD(DecrementingTimeToSpawningBelowZeroResetsTime)
	{
		auto fish = aoc::Lanternfish{ 0 };
		fish.decrement_time_to_spawning();
		Assert::AreEqual(aoc::Lanternfish::days_until_spawning_reset_value, fish.days_until_spawning());
	}
};
}

namespace day_1
{
TEST_CLASS(SingleValueDepthScores)
{
public:

	TEST_METHOD(CountNetIncreaseFromFile)
	{
		std::ifstream data_file(DATA_DIR / "Day1_input.txt");
		Assert::IsTrue(data_file.is_open());

		auto depth_score = aoc::Submarine().boat_systems().depth_score<1>(std::istream_iterator<uint32_t>(data_file), std::istream_iterator<uint32_t>());

		Assert::AreEqual(uint32_t{ 1502 }, depth_score);
	}
};

TEST_CLASS(TripleValueDepthScores)
{
public:
	TEST_METHOD(RollingWindow3ExampleValues)
	{
		auto measurements = std::vector<uint32_t>{ 199, 200, 208, 210, 200, 207, 240, 269, 260, 263 };

		auto depth_score = aoc::Submarine().boat_systems().depth_score<3>(measurements.begin(), measurements.end());

		Assert::AreEqual(uint32_t{ 5 }, depth_score);
	}

	TEST_METHOD(RollingWindow3FromFile)
	{
		std::ifstream data_file(DATA_DIR / "Day1_input.txt");
		Assert::IsTrue(data_file.is_open());

		auto depth_score = aoc::Submarine().boat_systems().depth_score<3>(std::istream_iterator<uint32_t>(data_file), std::istream_iterator<uint32_t>());

		Assert::AreEqual(uint32_t{ 1538 }, depth_score);
	}
};
}

namespace day_2
{

TEST_CLASS(TestDay2)
{
public:

	TEST_METHOD(ParseDirectionsFromFile)
	{
		std::ifstream data_file(DATA_DIR / "Day2_input.txt");
		Assert::IsTrue(data_file.is_open());

		using StreamIter_t = std::istream_iterator<aoc::Direction>;
		const auto net_direction = aoc::Submarine().boat_systems().net_direction(StreamIter_t(data_file), StreamIter_t());

		Assert::AreEqual(1895, net_direction.x);
		Assert::AreEqual(894, net_direction.y);
	}
};
}

namespace day_3
{
TEST_CLASS(TestDay3)
{
public:

	TEST_METHOD(CalculatePowerParamsFromFile)
	{
		std::ifstream data_file(DATA_DIR / "Day3_input.txt");
		Assert::IsTrue(data_file.is_open());

		auto log = aoc::DiagnosticLog{ data_file };

		const auto power_consumption = aoc::Submarine().boat_systems().power_consumption(log);

		Logger::WriteMessage(std::format("Power: {}", power_consumption).c_str());
		Assert::AreEqual(uint32_t{ 693486 }, power_consumption);
	}

	TEST_METHOD(LifeSupportRatingIsCalculatedFromFile)
	{
		std::ifstream data_file(DATA_DIR / "Day3_input.txt");
		Assert::IsTrue(data_file.is_open());

		auto log = aoc::DiagnosticLog{ data_file };

		Assert::AreEqual(uint32_t{ 3379326 }, aoc::Submarine().boat_systems().life_support_rating(log));
	}
};
}

namespace day_4
{
TEST_CLASS(TestDay4)
{
public:
	TEST_METHOD(ExampleGameScoreIsCorrect)
	{
		constexpr auto game_str =
			"7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1\n"
			"\n"
			"22 13 17 11  0\n"
			"8  2 23  4 24\n"
			"21  9 14 16  7\n"
			"6 10  3 18  5\n"
			"1 12 20 15 19\n"
			"\n"
			"3 15  0  2 22\n"
			"9 18 13 17  5\n"
			"19  8  7 25 23\n"
			"20 11 10 24  4\n"
			"14 21 16 12  6\n"
			"\n"
			"14 21 17 24  4\n"
			"10 16 15  9 19\n"
			"18  8 23 26 20\n"
			"22 11 13  6  5\n"
			"2  0 12  3  7";

		std::stringstream ss{ game_str };

		const auto game_score = aoc::bingo::Game<aoc::bingo::FileBasedNumberDrawer<uint8_t>>{}
			.load(ss)
			.play_to_win()
			.score();

		Assert::IsTrue(std::nullopt != game_score);
		Assert::AreEqual(uint32_t{ 4512 }, *game_score);
	}

	TEST_METHOD(FindWinningScoreForFullInput)
	{
		std::ifstream data_file(DATA_DIR / "Day4_input.txt");
		Assert::IsTrue(data_file.is_open());

		const auto game_score = aoc::Submarine().entertainment().bingo_game()
			.load(data_file)
			.play_to_win()
			.score();

		Assert::IsTrue(std::nullopt != game_score);
		Assert::AreEqual(uint32_t{ 2745 }, *game_score);
	}

	TEST_METHOD(PlayingToLoseOnExampleData)
	{

		constexpr auto game_str =
			"7, 4, 9, 5, 11, 17, 23, 2, 0, 14, 21, 24, 10, 16, 13, 6, 15, 25, 12, 22, 18, 20, 8, 19, 3, 26, 1\n"
			"\n"
			"22 13 17 11  0\n"
			" 8  2 23  4 24\n"
			"21  9 14 16  7\n"
			" 6 10  3 18  5\n"
			" 1 12 20 15 19\n"
			"\n"
			" 3 15  0  2 22\n"
			" 9 18 13 17  5\n"
			"19  8  7 25 23\n"
			"20 11 10 24  4\n"
			"14 21 16 12  6\n"
			"\n"
			"14 21 17 24  4\n"
			"10 16 15  9 19\n"
			"18  8 23 26 20\n"
			"22 11 13  6  5\n"
			" 2  0 12  3  7";

		std::stringstream ss{ game_str };

		auto winner = aoc::bingo::Game<aoc::bingo::FileBasedNumberDrawer<uint8_t>>{}
			.load(ss)
			.play_to_lose()
			.get_winner();

		Assert::IsTrue(std::nullopt != winner);
		Assert::AreEqual(uint8_t{ 13 }, winner->number);
		Assert::AreEqual(aoc::bingo::Board::Id_t{ 1 }, winner->board.id());
	}

	TEST_METHOD(FindLosingScoreForFullInput)
	{
		std::ifstream data_file(DATA_DIR / "Day4_input.txt");
		Assert::IsTrue(data_file.is_open());

		const auto game_score = aoc::Submarine().entertainment().bingo_game()
			.load(data_file)
			.play_to_lose()
			.score();

		Assert::IsTrue(std::nullopt != game_score);
		Assert::AreEqual(uint32_t{ 6594 }, *game_score);
	}
};
}

namespace day_5
{
TEST_CLASS(TestDay5)
{
public:
	TEST_METHOD(FindVentScoreForFullInput)
	{
		std::ifstream data_file(DATA_DIR / "Day5_input.txt");
		Assert::IsTrue(data_file.is_open());

		const auto vent_score = aoc::Submarine()
			.boat_systems()
			.detect_vents<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical>(data_file);

		Assert::AreEqual(uint32_t{ 6267 }, vent_score);
	}

	TEST_METHOD(FindVentScoreWithDiagonalsForFullInput)
	{
		for (int i = 0; i < 100; ++i)
		{
			std::ifstream data_file(DATA_DIR / "Day5_input.txt");
			Assert::IsTrue(data_file.is_open());

			const auto vent_score = aoc::Submarine()
				.boat_systems()
				.detect_vents<aoc::VentAnalyzer::horizontal | aoc::VentAnalyzer::vertical | aoc::VentAnalyzer::diagonal>(data_file);

			Assert::AreEqual(uint32_t{ 20196 }, vent_score);
		}
	}
};
}

namespace day_6
{
TEST_CLASS(TestDay6)
{
public:
	TEST_METHOD(FindFishCountForFullInput_80Days)
	{
		std::ifstream data_file(DATA_DIR / "Day6_input.txt");
		Assert::IsTrue(data_file.is_open());

		auto shoal = aoc::LanternfishShoal{}.load(data_file);

		const auto number_of_fish = aoc::LanternfishShoalModel{ shoal }.run_for(std::chrono::days(80)).shoal_size();

		Assert::AreEqual(aoc::LanternfishShoal::Size_t{ 360268 }, number_of_fish);
	}

	TEST_METHOD(FindFishCountForFullInput_256Days)
	{
		std::ifstream data_file(DATA_DIR / "Day6_input.txt");
		Assert::IsTrue(data_file.is_open());

		auto shoal = aoc::LanternfishShoal{}.load(data_file);

		const auto number_of_fish = aoc::LanternfishShoalModel{ shoal }.run_for(std::chrono::days(256)).shoal_size();

		Assert::AreEqual(aoc::LanternfishShoal::Size_t{ 1632146183902 }, number_of_fish);
	}
};
}

namespace day_7
{
TEST_CLASS(CrabSorting)
{
public:
	TEST_METHOD(LoadCrabPositionsFromStream)
	{
		std::stringstream data("16,1,2,0,4,2,7,1,2,14");

		const auto sorter = aoc::CrabSorter{}.load(data);

		const auto expected_positions = { 16, 1, 2, 0, 4, 2, 7, 1, 2, 14 };
		Assert::IsTrue(std::equal(expected_positions.begin(), expected_positions.end(), sorter.positions().begin()));
	}

	TEST_METHOD(CalculateBestPosition)
	{
		std::stringstream data("16,1,2,0,4,2,7,1,2,14");

		const auto [best_position, cost] = aoc::CrabSorter{}.load(data).best_position_and_cost([](uint32_t distance) { return distance; });

		Assert::AreEqual(size_t{ 2 }, best_position);
		Assert::AreEqual(uint32_t{ 37 }, cost);
	}

	TEST_METHOD(CalculateBestPositionForAllInputWithLinCost)
	{
		std::ifstream data_file(DATA_DIR / "Day7_input.txt");
		Assert::IsTrue(data_file.is_open());

		const auto [best_position, cost] = aoc::CrabSorter{}.load(data_file).best_position_and_cost([](uint32_t distance) { return distance; });

		Assert::AreEqual(size_t{ 330 }, best_position);
		Assert::AreEqual(uint32_t{ 329389 }, cost);
	}

	TEST_METHOD(CalculateBestPositionForAllInputWithQuadraticCost)
	{
		std::ifstream data_file(DATA_DIR / "Day7_input.txt");
		Assert::IsTrue(data_file.is_open());

		const auto [best_position, cost] = aoc::CrabSorter{}
			.load(data_file)
			.best_position_and_cost([](uint32_t distance) { 
				return (distance * ( 1 + distance)) / 2;
			});

		Assert::AreEqual(size_t{ 459 }, best_position);
		Assert::AreEqual(uint32_t{ 86397080 }, cost);
	}
};
}
