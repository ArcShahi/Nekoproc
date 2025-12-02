#include <print>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

namespace fs = std::filesystem;
using Input = std::vector<std::string>;


Input load_data(fs::path path)
{
	std::ifstream file{ path};

	Input data{};
	data.reserve(100);

	std::string line{};

	while (std::getline(file, line))
		data.push_back(std::move(line));

	return data;		 
}

// PART 1:
namespace p1
{

	int password(const Input& input)
	{
		constexpr int N{ 100 }; // Dial number from 0-99
		int dial{ 50 }; // current dial position
		int counter{ 0 };

		for (const auto& line : input)
		{
			char dir{ line[0] };
			
			int rot{ std::stoi(line.substr(1)) };
			rot = dir == 'R' ? rot : -rot;

			dial = ((dial + rot) % N + N) % N;
			if (dial == 0) ++counter;
		}

		return counter;
	}

}

// PART 2 :
namespace p2
{

	int crosses_zero(int start, int rot, int N = 100)
	{
		int counter{ 0 };

		// Count full lap
		counter += std::abs(rot) / N;

		const int end{ (start + rot + N * 10) % N };

		// Check if reaches 0 during rotation
		if (start != 0 && end != 0)
		{
			if (rot > 0 && end < start) ++counter;
			if (rot < 0 && start < end) ++counter;
		}

		// If at 0
		if (end == 0) ++counter;

		return counter;
	}


	int password(const Input& input)
	{

		constexpr int N{ 100 }; // Dial number from 0-99
		int dial{ 50 }; // current dial position
		int counter{ 0 };

		for (const auto& line : input)
		{
			const char dir{ line[0] };

			int rot{ std::stoi(line.substr(1)) };
			rot = dir == 'R' ? rot : -rot;

			counter += crosses_zero(dial, rot);

			dial = ((dial + rot) % N + N) % N;
		}
		return counter;

	}
}

int main(int argc, char* argv[])
{
	const auto input{ load_data(argv[1]) };

	std::println("Password 1 : {}\n Password 2: {}",p1::password(input),p2::password(input));
}