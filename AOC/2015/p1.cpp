#include <fstream>
#include <print>
#include <filesystem>

namespace fs = std::filesystem;


// Part 1 : To what floor do the instructions take Santa?

int floor_num(fs::path path)
{
	std::ifstream input{ path};

	if (!input)
	{
		std::println("Error: can't open {}", path.string());
		return -1;
	}

	char c{};
	int floor{};
	while (input.get(c))
	{
		if (c == '(') ++floor;
		else --floor;
	}

	return floor;
}

// What is the position of the character that causes Santa to first enter the basement?
int in_basement(fs::path path)
{
	std::ifstream input{ path };

	if (!input)
	{
		std::println("Error: can't open {}", path.string());
		return -1;
	}

	char c{};
	int floor{};
	int counter{ 0 };
	while (input.get(c) && floor!=-1)
	{
		if (c == '(') ++floor;
		else --floor;
		++counter;
	}

	return counter;
}

int main(int argc, char* argv[])
{
	std::string file{ argv[1] };

	std::println("Santa is on Floor : {} and he reached there on instruction: {}",
		floor_num(file),in_basement(file));
}