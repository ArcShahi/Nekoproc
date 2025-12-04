#include <print>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <queue>
#include <deque>


namespace fs = std::filesystem;
using Input = std::vector<std::string>;

Input load_data(fs::path path)
{
	std::ifstream file{ path };

	Input data{};
	data.reserve(140);

	std::string line{};

	while (std::getline(file, line))
		data.push_back(std::move(line));

	return data;
}


bool in_bounds(int i, int j, int row, int colm)
{
	return (i >= 0 && i < row && j >= 0 && j < colm);
}

// Test in 3x3 Matrix, with current elemnt at center
int check_adjacent(const Input& grid, int x, int y)
{

	const int rows = static_cast<int>(grid.size());
	const int colm = static_cast<int>(grid[0].size());

	int count{ 0 };

	for (int i{ x - 1 }; i <= x + 1; ++i)
		for (int j{ y - 1 }; j <= y + 1; ++j)
		{
			if (x == i && y == j) continue;

			if (in_bounds(i, j, rows, colm) && grid[i][j] == '@')
				++count;
		}
	
	return count;

}

// PART 1:

namespace p1
{
	

	int rolls(const Input& input)
	{
		int count{ 0 };

		for (int i{ 0 }; i < input.size(); ++i)
			for (int j{ 0 }; j < input[0].size(); ++j)
				if (input[i][j]=='@' && check_adjacent(input, i, j) < 4) ++count;

		return count;
	}
	
}

// PART 2 :
namespace p2
{
     int rolls(Input& input)
     {
          int removed{ 0 };
          const int rows = static_cast<int>(input.size());
          const int col = static_cast<int>(input[0].size());

          std::deque<std::pair<int, int>> q{};

        // Add accesible rolls to queue
          for (int i{ 0 }; i < rows; ++i)
               for (int j{ 0 }; j < col; ++j)
                    if (input[i][j] == '@' && check_adjacent(input, i, j) < 4)
                         q.push_back({ i, j });

          while (!q.empty())
          {
               auto [x, y] = q.front();
               q.pop_front();

               // Skip if it's already removed
               if (input[x][y] != '@') continue;

               input[x][y] = 'X'; // remove current roll
               ++removed;
         
			// Check all 8 adjacent
			for (int i{ x - 1 }; i <= x+1; ++i)
				for (int j{ y - 1 }; j <= y + 1; ++j)
					if (in_bounds(i, j, rows, col) && input[i][j] == '@' && 
						check_adjacent(input, i, j) < 4)
						q.push_back({ i,j });
          }

          return removed;
     }
}   

int main(int argc, char* argv[])
{
	 auto input{ load_data(argv[1]) };
	std::println("Total rolls can be accessed : {} ",p1::rolls(input));
	std::println("Total rolls can be removed : {}", p2::rolls(input));
}