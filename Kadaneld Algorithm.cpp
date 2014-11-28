template <typename ForwardIterator>
typename std::iterator_traits<ForwardIterator>::value_type
kadaneld(ForwardIterator start, ForwardIterator end)
{
	typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
	value_type maxall = 0, maxstart = 0;
	while (start != end)
	{
		maxstart = std::max(maxstart + *start, 0);
		maxall = std::max(maxall, maxstart);
	}
	return maxall;
}
