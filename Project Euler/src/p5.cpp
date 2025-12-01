#include <print>
#include <numeric>

// PROBLEM 5 : Smallest Multiple

/*

 We'll just iteratively caluclate lcm and reduce it
 https://stackoverflow.com/questions/185781/finding-the-lcm-of-a-range-of-numbers

 std::lcm does uses lcm(a,b)=|ab|/gcd(a,b); as it's implementation(llvm libcxx)

*/ 


// calculates the num that is evenly divisible all [1,n]
long long min_multiple(int n)
{
	long long res{1};
	for (int i = 2; i <= n; i++)
		res = std::lcm(res, static_cast<long long>(i));

	return res;
}

int main()
{
	std::println("The smallest number that evenly multiple every number from 1 to 20 = {}",
		min_multiple(20));
}