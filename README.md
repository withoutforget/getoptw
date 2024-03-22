## Getoptw
I had tried to search getopt function for windows, but I didn't found anything except boost. So I decided to make a new one for windows.
## Usage
Here's example:
```cpp
int main(int argc, char** argv) {
	getoptw::args args(argc, argv); // parsing arguments
	if (args["-param"] != nullptr) // try to find -param, if not found then returns nullptr
		std::cout << args["-param"] << std::endl; // output value of -param
	for (auto it = args.begin(); it != args.end(); ++it) {
		if (it->first == "-param2") {
			std::cout << "--param2=" << it->second << std::endl;
		}
	}
}
```
```
.\getoptw.exe -param hello -param2 world
hello
--param2=world
```
```
.\getoptw.exe -param hello world -param2 bye world
hello world
--param2=bye world
```
## Docs
```cpp
class args {
public:
	args();
	args(int argc, char** argv);	
	void push(int argc, char** argv); // add new args
	
	const char* operator[](const std::string& key) const; // search value by key
	
	auto begin() const;
	auto end() const;
};
```
