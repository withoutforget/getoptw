#include <iostream>
#include <fstream>

#include "getoptw.h"

std::ostream& operator<<(std::ostream& stream, const std::pair<std::string, std::string>& pair) {
	stream << pair.first << "=" << pair.second;
	return stream;
}

template<typename Out, typename BegIt, typename EndIt>
void out_to(Out& stream, BegIt begin, EndIt end) {
	for (; begin != end; ++begin) {
		stream << *begin << std::endl;
	}
}

int main(int argc, char** argv) {

	getoptw::args args(argc, argv);

	if (args["-o"] != nullptr) {
		std::ofstream file(args["-o"]);
		if (file.is_open()) 
			out_to(file, args.begin(), args.end());
	}

	out_to(std::cout, args.begin(), args.end());


	return 0;
}
