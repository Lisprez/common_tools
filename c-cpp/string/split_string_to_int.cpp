std::vector<int> v;
std::string numbers = "1 2 3";
std::istringstream iss(numbers);

std::copy(std::istream_iterator<int>(iss),
	std::istream_iterator<int>(),
	std::back_inserter(v));

// v == [1, 2, 3]