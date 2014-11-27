#include <algorithm>
#include <array>
using Point = std::pair<int, int>;
template <int m,int n>
using TowDimArray = std::array<std::array<int,n>,m>;

template <int m, int n>
Point saddleback_search(TowDimArray<m, n> & a, int x)
{
	Point p(-1, -1);
	int i = 0,j = n - 1;
	while (i < m && j >= 0 && x != a[i][j])
	{
		if (a[i][j] < x)
			i++;
		else
			j--;
	}
	if (i == m || j == -1)i = -1, j = -1;
	p.first = i;
	p.second = j;
	return p;

}



int main()
{
	TowDimArray<4, 4> a = {
		2, 2, 3, 5,
		3, 4, 5, 6,
		3, 5, 6, 8,
		3, 6, 7, 9
	};
	Point p = saddleback_search<4, 4>(a, 11);
	return 0;
}
