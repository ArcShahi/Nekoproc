#include <print>
#include <fstream>
#include <unordered_map>
#include <set>
#include <filesystem>


namespace fs = std::filesystem;

struct Cord
{
	int x{}, y{};
	auto operator<=>(const Cord&) const = default;

	void operator+=(const Cord& other)
	{
		x += other.x;
		y += other.y;
	}
};


std::pair<int, int> puzzle_sln(fs::path path)
{
	std::ifstream input{ path };

	if (!input)
	{
		std::println("Error: can't open {}", path.string());
		return { -1,-1 };
	}

	const std::unordered_map<char, Cord> fly{
		{'^',{0,1}},
		{'v',{0,-1}},
		{'<',{-1,0}},
		{'>',{1,0}}
	};


	// I'm using set cuz I don't wanna write  a custom hash for unordered_map	

	  // PART 1
	Cord santa1{ 0,0 };
	std::set<Cord> list1{};
	list1.insert({ 0,0 });

	// PART 2
	Cord santa2{ 0,0 };
	Cord robosanta{ 0,0 };
	std::set<Cord>  list2{};
	list2.insert({ 0,0 });
	bool turn{ true }; // Taking turn
	char cmd{};


	while (input.get(cmd))
	{
		santa1 += fly.at(cmd);
		list1.insert(santa1);


		if (turn)
		{
			santa2 += fly.at(cmd);
			list2.insert(santa2);
		}
		else
		{
			robosanta += fly.at(cmd);
			list2.insert(robosanta);
		}

		turn = !turn; // alterate the turns
	}

	return { list1.size(),list2.size() };

}

int main(int argc, char* argv[])
{
	const std::string file{ argv[1] };
	const auto [part1, part2] = puzzle_sln(file);

	std::print("Santa delivered gits to {} house and Santa and Robo Santa delivered {} houses next year", part1, part2);

}