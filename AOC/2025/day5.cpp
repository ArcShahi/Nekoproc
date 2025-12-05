#include <print>
#include <vector>
#include <string>
#include <charconv>
#include <algorithm>
#include <utility>
#include <fstream>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;
namespace rng = std::ranges;
using Input = std::vector<std::string>;
using LLpair = std::pair<long long, long long>;


auto load_data(fs::path path)
{
	std::ifstream file{ path };

	Input ids_range{};
	Input items_id{};

	ids_range.reserve(100);
	items_id.reserve(1000);

	std::string line{};
	bool blank{ false };
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			blank = true;
			continue;
		}

		if (!blank)
			ids_range.push_back(std::move(line));
		else
			items_id.push_back(std::move(line));

	}

	ids_range.shrink_to_fit();
	items_id.shrink_to_fit();
	return std::make_pair(ids_range, items_id);
}


auto to_number(const std::string& str, long long& a, long long& b)
{
	const auto it{ str.find('-') };

	const auto x{ std::from_chars(str.data(),str.data() + it,a) };
	const auto y{ std::from_chars(str.data() + it + 1,str.data() + str.size(),b) };

	return x.ec == std::errc() && y.ec == std::errc();
}

auto to_number(const std::string& str, long long& a)
{
	const auto x{ std::from_chars(str.data(),str.data() + str.size(),a) };
	return x.ec == std::errc();
}

constexpr bool in_range(const long long& val, const LLpair& p)
{
	return p.first <= val && val <= p.second;
}


constexpr auto count_elements(auto m, auto n)
{
	return n - m + 1;
}

auto merge_range(std::vector<LLpair>&& vec)
{
	if (vec.empty()) return std::vector<LLpair>{};

	std::vector<LLpair> merged_range{};
	merged_range.reserve(vec.size());

	rng::sort(vec, [](const auto& a, const auto& b) {
		return a.first < b.first;
		});

	auto curr{ vec[0] };
	for (size_t i{ 1 }; i < vec.size(); ++i)
	{
		auto next{ vec[i] };  
		if (next.first <= curr.second + 1)  // +1 to merge ranges lilke [3,5] -> [6,9] 
		{
			curr.second = std::max(curr.second, next.second);
		}
		else
		{
			merged_range.push_back(curr);
			curr = next;
		}
	}

	merged_range.push_back(curr);
	return merged_range;
}


auto parse_range(const Input& ids_range)
{
	std::vector<LLpair> ranges{};

	for (const auto& str : ids_range)
	{
		// convert range to number
		long long f{}, s{};

		if (to_number(str, f, s))
			ranges.push_back({ f,s });
	}
	return ranges;

}

// PART 1:
namespace p1
{
	auto fresh_items(const std::vector<LLpair>& ids_range, const Input& items_id)->int
	{
		std::vector<long long> ids{};

		// Parse ids to numbers
		for (const auto& str : items_id)
		{
			long long id{};
			if (to_number(str, id))
				ids.push_back(id);
		}

		// Check if iterms are fresh
		int count{};

		for (const auto& id : ids) 
		{
			for (const auto& range : ids_range)
			{
				if (in_range(id, range))
				{
					++count;
					break;
				}

			}
		}

		return count;
	}
}

// PART 2:
namespace p2
{ 
	
	auto fresh_ids(const std::vector<LLpair>& ids_range)
	{
		long long count{ 0ll };
		for (const auto& [m, n] : ids_range)
			count += count_elements(m, n);

		return count;
	}
}

int main(int argc, char* argv[])
{
	 auto input{ load_data(argv[1]) };

	 // Parsing range to numerical range -> merged range
	 const auto ids_range{ merge_range(parse_range(input.first))};

	 std::println("Fresh Items : {},", p1::fresh_items(ids_range, input.second));
	 std::println("Fresh Ids : {}", p2::fresh_ids(ids_range));

}