// linear.cpp
// Dhruv Chakraborty, UID: 204-962-098
// UCLA CS32, HW3: part 2

bool somePredicate(double x)
{
	return x < 0; // in this case, checking if x is negative
}

// anyTrue returns true is any element of input array satisfies predicate in somePredicate
bool anyTrue(const double a[], int n)
{
	if (n <= 0)  // we treat a negative input for number of elements as 0, as advised by spec
		return false;

	if (somePredicate(a[0]))
		return true;
	else
		return anyTrue(a + 1, n - 1);
}

// countTrue returns the number of elements of the input array that satisfy prediacte in somePredicate
int countTrue(const double a[], int n)
{
	if (n <= 0)
		return 0;

	if (somePredicate(a[0]))
		return (1 + countTrue(a + 1, n - 1));
	else
		return countTrue(a + 1, n - 1);

}

// firstTrue returns position for first element of input array that satisfies somePredicate
// if no element satisfies somPredicate, returns 0
int firstTrue(const double a[], int n)
{
	if (n <= 0)
		return -1;

	if (somePredicate(a[0]))
		return 0;

	int pos = firstTrue(a + 1, n - 1);

	if (pos == -1)
		return -1;
	else
		return 1 + pos;
}

// positionOfMin returns position of smallest element of input array
int positionOfMin(const double a[], int n)
{
	if (n <= 0)
		return -1;

	if (n == 1)
		return 0;

	int minPos = 1 + positionOfMin(a + 1, n - 1);

	if (a[0] <= a[minPos])
		return 0;
	else
		return minPos;
}

// includes returns whether the first array contains all of the second array or not
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n1 < 0 || n2 < 0 || n1 < n2)
		return false;

	if (n2 == 0)
		return true;

	if (n1 == 0)
		return false;

	if (a1[0] == a2[0])
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
		return includes(a1 + 1, n1 - 1, a2, n2);

}