#include <print>


// Problem 6 : Sum Square Difference

int sln(int n )
{
	// Sum of Squares in range [1,n] : (n(n+1)2(n+1))/6
	const int s1{ (n * (n + 1) * ((2*n) + 1)) / 6};

	// Square of Sum in range [1,n] : (n(n+1)/2)^2
	const int t{ n * (n + 1) / 2 };
	const int s2{ t * t };

	return std::abs(s1-s2);
}

int main()
{
	std::println("The difference between sum of squares and square of sum [1,n]: {}", sln(100));
}