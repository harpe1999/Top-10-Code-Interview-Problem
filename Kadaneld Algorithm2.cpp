template <typename c>
std::tuple<typename std::iterator_traits<ForwardIterator>::value_type, , ForwardIterator, ForwardIterator>
kadaneld(ForwardIterator start, ForwardIterator end)
{
	typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
	value_type maxall = 0, maxstart = 0;
	ForwardIterator starti = start, sumstart, sumend;
	while (start != end)
	{
		maxstart += *start;
		if (maxstart < 0)
		{
			maxstart = 0;
			starti = start;
			++starti;
		}
		if (maxall < maxstart)
		{
			maxall = maxstart;
			sumstart = starti;
			sumend = start;
		}
		++start;
	}
	return std::make_tuple(maxall, sumstart, sumend);
}
