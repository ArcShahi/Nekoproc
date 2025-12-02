#include <print>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
#include <system_error>

namespace fs = std::filesystem;
using Input = std::vector<std::string>;


Input load_data(fs::path path)
{
	std::ifstream file{ path };

	Input data{};
	data.reserve(100);

	std::string line{};

	while (std::getline(file, line,','))
		data.push_back(std::move(line));

	return data;
}

int digit_count(long long n)
{
	int c{};
	for (; n != 0; n /= 10)
		++c;
	return c;
}

 // Returns Interger form of Range
auto parse_range(const std::string& s, long long& a, long long& b)
{
	const auto it{ s.find('-') };

	const auto x{ std::from_chars(s.data(),s.data() + it,a) };
	const auto y{ std::from_chars(s.data() + it + 1,s.data() + s.size(),b) };

	return x.ec == std::errc() && y.ec == std::errc();
}

// PART 1:
namespace p1
{

	bool invalid_id(long long n)
	{
		const int k{ digit_count(n) };

		long long h{ 1 };
		for (int i{ 0 }; i < k / 2; ++i)
			h *= 10;

		const long long f{ n / h };
		const long long s{ n % h };

		return f == s;
	}
	long long sum_ids(long long m, long long n)
	{
		long long sum{ 0 };

		for (auto i{ m }; i <= n; ++i)
			if (invalid_id(i))
				sum += i;

		return  sum;
	}

	
	long long puzzle(const Input& input)
	{
		long long sum{ 0 };

		for (const auto& range : input)
		{
			long long a{}, b{};
			if (parse_range(range, a, b))
				sum += sum_ids(a, b);
		
		}

		return sum;
	}

}

// PART 2
namespace p2
{
	bool invalid_id(long long n)
	{
		const auto s{ std::to_string(n) };
		std::string t{};
		t.reserve(s.size() * 2);
		t.append(s);
		t.append(s);

		return t.find(s, 1) < s.size();
	}

	long long sum_ids(long long m, long long n)
	{
		long long sum{ 0 };

		for (auto i{ m }; i <= n; ++i)
			if (invalid_id(i))
				sum += i;

		return  sum;
	}

	
	long long puzzle(const Input& input)
	{
		
		long long sum{};
		for (const auto& range : input)
		{
			long long a{}, b{};
			if (parse_range(range, a, b))
				sum += sum_ids(a, b);
		}
		

		return sum;
	}
}

int main(int argc,char* argv[])
{
	const auto input{ load_data(argv[1]) };

	std::println("Invalid Id sum for pattern 1: {} and Pattern 2: {}", p1::puzzle(input),
		p2::puzzle(input));
}