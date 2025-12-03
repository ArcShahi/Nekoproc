#include <print>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <ranges>

namespace fs = std::filesystem;
namespace rng = std::ranges;
using Input = std::vector<std::string>;

Input load_data(fs::path path)
{
	std::ifstream input{ path };

	Input data{};
	data.reserve(200);

	std::string line{};
	while (std::getline(input, line))
		data.push_back(std::move(line));

	return data;
}



namespace p1
{
	// Largest 2  digit that appear in order

	int  joltage(const std::string& str)
	{

		int max_jolt{ 0 }, prev{ 0 };

		for (auto&& [i, c] : rng::views::enumerate(str))
		{
			const int n{ c - '0' };
			const int jolt{ prev * 10 + n };

			max_jolt = std::max(max_jolt, jolt);
			prev = std::max(prev, n);
		}
		return max_jolt;
	}

	int output(const Input& input)
	{
		int jolt{};

		for (const auto& bank : input)
			jolt += joltage(bank);
		
		return jolt;
	}

}

namespace p2
{
	long long joltage(const std::string& str)
	{
		// maximum number taht can be formed using i digits
		std::vector<long long> dp(13, 0);

		for (auto&& [idx, c] : rng::views::enumerate(str))
		{
			const int n{ c - '0' };

			// iterating backwards to prevent using the same digit twice
			for (int len = 12; len >= 1; --len)
			{
				long long candidate = dp[len - 1] * 10 + n;
				dp[len] = std::max(dp[len], candidate);
			}
		}

		return dp[12];
	}


	long long output(const Input& input)
	{
		long long jolt{ 0ll };

		for (const auto& bank : input)
			jolt += joltage(bank);

		return jolt;
	}
}

int main(int argc, char* argv[])
{

	const auto input{ load_data(argv[1]) };
	std::println("Total Output Joltage 1 : {} Total output Joltage 2: {}",
		p1::output(input),p2::output(input));
}