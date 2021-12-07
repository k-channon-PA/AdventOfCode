#pragma once

///////////////////////////////////////////////////////////////////////////////

#include "Common.hpp"
#include "DiagnosticLog.hpp"

#include <algorithm>
#include <vector>
#include <format>

///////////////////////////////////////////////////////////////////////////////

namespace aoc
{

///////////////////////////////////////////////////////////////////////////////

using Direction = Vec2d<int>;

///////////////////////////////////////////////////////////////////////////////

struct Aiming
{
	int x{};
	int aim{};
	int depth{};

	Direction to_direction() const
	{
		return { x, depth };
	}

	Aiming operator+(const Direction& d) const
	{
		const auto new_aim = this->aim + d.y;
		return {
			this->x + d.x,
			new_aim,
			this->depth + d.x * new_aim
		};
	}
};

///////////////////////////////////////////////////////////////////////////////

class LifeSupport
{
public:
	LifeSupport(const DiagnosticLog& log) : _log(log) {}

	static uint32_t score_entry(const DiagnosticLog::Entry_t& entry, const DiagnosticLog::Entry_t& target)
	{
		return static_cast<uint32_t>(std::distance(entry.begin(), std::mismatch(entry.begin(), entry.end(), target.begin()).first));
	}

	template<typename BitSelector_T>
	uint32_t filter_bits_matching(BitSelector_T bit_selector) const
	{
		auto entries = std::vector<DiagnosticLog::Entry_t>(_log.begin(), _log.end());

		auto curr_bit_idx = uint32_t{ 0 };
		auto end = entries.end();
		while (std::distance(entries.begin(), end) > 1) {
			auto bits_to_match = bit_selector(entries.begin(), end);
			end = std::remove_if(entries.begin(), end, [&bits_to_match, curr_bit_idx](auto e) {
				return e[curr_bit_idx] != bits_to_match[curr_bit_idx];
				});

			++curr_bit_idx;
		}

		return DiagnosticLog::entry_as<uint32_t>(entries.front());
	}

	uint32_t filter_using_most_frequent_bits() const
	{
		return filter_bits_matching(DiagnosticLog::most_frequent_bits<DiagnosticLog::Iterator_t>);
	}

	uint32_t filter_using_least_frequent_bits() const
	{
		return filter_bits_matching(DiagnosticLog::least_frequent_bits<DiagnosticLog::Iterator_t>);
	}

	uint32_t rating() const
	{
		const auto o2_gen_rating = filter_using_most_frequent_bits();
		const auto co2_scrubber_rating = filter_using_least_frequent_bits();

		return o2_gen_rating * co2_scrubber_rating;
	}

private:
	const DiagnosticLog& _log;
};

///////////////////////////////////////////////////////////////////////////////

struct LogProcessor
{
	static uint32_t power_consumption(const DiagnosticLog& log)
	{
		const auto most_frequent_bits = log.get_most_frequent_bits();
		return DiagnosticLog::entry_as<uint32_t>(most_frequent_bits) * DiagnosticLog::flipped_entry_as<uint32_t>(most_frequent_bits);
	}

	static uint32_t life_support_rating(const DiagnosticLog& log)
	{
		return LifeSupport(log).rating();
	}
};

///////////////////////////////////////////////////////////////////////////////

class BoatSystems
{
public:
	template<size_t WINDOW_SIZE, typename Iter_T>
	uint32_t depth_score(Iter_T begin, Iter_T end) const
	{
		auto current_idx = size_t{ 0 };

		auto window = std::array<typename Iter_T::value_type, WINDOW_SIZE>{};
		for (auto it = window.begin(); it < window.end(); ++it, ++current_idx) {
			*it = *begin++;
		}

		auto prev_score = std::accumulate(window.begin(), window.end(), uint32_t{ 0 });

		return std::accumulate(begin, end, 0, [&window, &prev_score, &current_idx](auto curr, auto next) {

			auto new_score = uint32_t{ prev_score - window[current_idx % window.size()] + next };

			auto out = new_score > prev_score ? ++curr : curr;

			prev_score = new_score;
			window[current_idx % window.size()] = next;
			++current_idx;

			return out;
			});
	}

	template<typename Iter_T>
	Direction net_direction(Iter_T begin, Iter_T end) const 
	{
		return std::accumulate(begin, end, Direction{});
	}

	template<typename Iter_T>
	Direction net_aiming(Iter_T begin, Iter_T end) const
	{
		return std::accumulate(begin, end, Aiming{}).to_direction();
	}

	uint32_t power_consumption(const DiagnosticLog& log) const
	{
		return LogProcessor::power_consumption(log);
	}

	uint32_t life_support_rating(const DiagnosticLog& log) const
	{
		return LogProcessor::life_support_rating(log);
	}
};

///////////////////////////////////////////////////////////////////////////////

}	// namespace: aoc

namespace std
{

///////////////////////////////////////////////////////////////////////////////

istream& operator>>(istream& is, aoc::Direction& direction)
{
	auto cmd = std::string{};

	direction = aoc::Direction{ 0, 0 };

	is >> cmd;

	if (cmd.empty())
		return is;

	if (cmd == "forward")
	{
		is >> direction.x;
	}
	else if (cmd == "up")
	{
		is >> direction.y;
		direction.y *= -1;
	}
	else if (cmd == "down")
	{
		is >> direction.y;
	}
	else {
		throw aoc::Exception(std::format("Invalid direction string"));
	}

	if (is.fail())
		throw aoc::Exception(std::format("Invalid direction string"));

	return is;
}

///////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////
