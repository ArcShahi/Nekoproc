#include <print>
#include <filesystem>
#include <fstream>
#include <array>
#include <string>
#include <utility>
#include <sstream>

namespace fs = std::filesystem;

// How many total square feet of wrapping paper should they order?

int paper_needed(const std::array<int,3>& dim)
{
	const int lw{ dim[0]*dim[1]};
	const int wh{ dim[1]*dim[2]};
	const int lh{ dim[0]*dim[2]};

	const int small_side{ std::min({lw,wh,lh}) };
	const int tsa{ (2 * lw) + (2 * wh) + (2 * lh) };

	return tsa + small_side;
}



// PART 2: How many total feet of ribbon should they order?

int ribbon_needed(std::array<int, 3>& dim)
{
	std::ranges::sort(dim);
	const int ribbon{ (2 * dim[0]) + (2 * dim[1]) };
	const int bow{ dim[0] * dim[1] * dim[2] };

	return ribbon + bow;
}


std::pair<int, int> puzzle_sln(fs::path path)
{
	std::ifstream input{ path };

	if (!input)
	{
		std::println("Error: can't open {}", path.string());
		return { -1,-1 };
	}

	std::string line{};
	int paper{}, ribbon{};
	
	std::array<int, 3> dim{};

	while (std::getline(input,line))
	{
		std::istringstream iss(line);
		char x{};
		iss >> dim[0] >> x >> dim[1] >> x >> dim[2];

		paper += paper_needed(dim);
		ribbon += ribbon_needed(dim);
	}

	return { paper,ribbon };

}

int main(int argc, char* argv[])
{
	const std::string file{ argv[1] };
	const auto sln{ puzzle_sln(file) };
	std::println("Elves need {} feet papers and {} feet of ribbon",sln.first,sln.second);
}