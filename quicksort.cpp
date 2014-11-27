template<typename RandomIter>
void quicksort(RandomIter first, RandomIter last)
{
	if (first!=last)
	{
		RandomIter left = first, right = last, pivot = left++;
		while (left != right)
		{
			if (*left < *pivot)
			{
				left++;
			}
			else
			{
				while (left != right && *right>*pivot)
					right--;
				iter_swap(left, right);
			}
		}
		--left;
		iter_swap(left, pivot);
		quicksort(first, left);
		quicksort(right, last);
	}
	
}
