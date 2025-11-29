#include <fstream>
#include <print>
#include <filesystem>

namespace fs = std::filesystem;


// Part 1 : To what floor do the instructions take Santa?
// Part 2: What is the position of the character that causes Santa to first enter the basement?

std::pair<int, int> puzzle_sln(fs::path path)
{

	std::ifstream input{ path };

	if (!input)
	{
		std::println("Error: can't open {}", path.string());
		return { -1,-1 };
	}

	int floor_num{}, counter{0};
	bool in_basement{false};
	char c{};

	while (input.get(c))
	{
		if (c == '(') ++floor_num;
		else --floor_num;

		if (!in_basement) ++counter;
		if (floor_num == -1) in_basement = true;
		
	}
	return { floor_num,counter };
}

int main(int argc, char* argv[])
{
	std::string file{ argv[1] };
	const auto sln{ puzzle_sln(file) };

	std::println("Santa is on Floor : {} and he reached there on instruction: {}",
		sln.first,sln.second);
}