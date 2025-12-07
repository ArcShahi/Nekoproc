#include <print>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using Input = std::vector<std::string>;
using Vec2LL = std::vector<std::vector<long long>>;

Input load_data(fs::path path)
{
	std::ifstream file{ path };

	Input data{};
	// data.reserve(140);

	std::string line{};

	while (std::getline(file, line))
		data.push_back(std::move(line));

	return data;
}



namespace p1
{
	void move_beam(Input& grid)
	{

		const size_t rows{ grid.size() };
		const size_t cols{ grid[0].size() };

		// start of beam lvl 0
		const size_t s{ grid[0].length() / 2 };

		// Move beam 1 level down
		grid[1][s] = '|';

		// Let's beam it all from level 1

		for (size_t i{ 1 }; i < rows - 1; ++i)
		{
			for (size_t j{ 0 }; j < cols; ++j)
			{
				// If beam is at this position
				if (grid[i][j] == '|')
				{
					// if splitter is below beam
					if (grid[i + 1][j] == '^')
					{
						// Beams hits the splitter ( split it into 2)
						grid[i + 1][j - 1] = '|';
						grid[i + 1][j + 1] = '|';
					}
					else if (grid[i + 1][j] == '.')
					{
						// continue moving down
						grid[i + 1][j] = '|';
					}
				}
			}
		}
	}

	int split_count(Input grid)
	{
		move_beam(grid);

		// Iterate again if '^' is found check if '|' is above it

		const size_t rows{ grid.size() };
		const size_t cols{ grid[0].size() };

		int count{ 0 };

		for (size_t i{ 1 }; i < rows - 1;++i)
		{
			for (size_t j{ 0 }; j < cols; ++j)
			{
				// If splitter found and | is above it, means the beam was splitted
				if (grid[i][j] == '^' && grid[i - 1][j] == '|')
					++count;

			}
		}

		return count;
	}
}

namespace p2
{
	auto quantum_beam(const Input& grid)
	{
		const size_t rows{ grid.size() };
		const size_t cols{ grid[0].size() };

		const size_t s{ grid[0].length() / 2 };


		Vec2LL timelines (rows, std::vector<long long>(cols, 0));
		timelines[1][s] = 1LL;

		for (size_t i{ 1 }; i < rows - 1; ++i)
		{
			for (size_t j{ 0 }; j < cols; ++j)
			{
				if (timelines[i][j] > 0)
				{
					if (grid[i + 1][j] == '^')
					{
						timelines[i + 1][j - 1] +=timelines[i][j];
						timelines[i + 1][j + 1] +=timelines[i][j];
					}
					else if (grid[i + 1][j] == '.')
					{
						timelines[i + 1][j] += timelines[i][j];
					}
				}
			}
		}
		return timelines;
     }

	long long timeline_count(const Input& grid)
	{

		const size_t rows{ grid.size() };
		const size_t cols{ grid[0].size() };

		const auto timelines{ quantum_beam(grid) };

		long long count{ 0LL };

		for (size_t j{ 0 }; j < cols; ++j)
			count += timelines[rows - 1][j];

		return count;

	}

}

int main(int argc,char* argv[])
{
	auto input{ load_data(argv[1]) };
	std::println("Beam splitted : {}", p1::split_count(input));
	std::println("Timelines count : {}", p2::timeline_count(input));
}