#include <print>

// Multiples of 3 or 5

// Cardinility , Imagine them like collecting a set contain multiple of 'k'
int N(int n, int k)
{	
	const int c{ n / k }; // Count of multiples of k in range [1,n]
	return k * c * (c + 1) / 2; // Sum of multiples
}

int summation(int x1,int x2,int n)
{
	// Using Inclusion-Exclusion N( 3 u 5)= N(3) + N(5) -N(A n B)
	return N(n, x1) + N(n, x2) - N(n, x1*x2);
}

int main()
{
	std::println("Sum of Multiples of 3 or 5 : {}", summation(3,5,999));
}