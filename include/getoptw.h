#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

// disable warning comparing signed and unsigned types
#pragma warning (disable : 4018)


namespace __tools {
	bool starts_with(const std::string& str, const char* substr) {
		return str.rfind(substr, 0) == 0;
	}
	void args_to_umap(std::unordered_map<std::string, std::string>& umap, int argc, char** argv) {
		std::unordered_map<std::string, std::string> tmp;
		std::string key{};
		std::string value{};
		for (size_t i = 1; i < argc; i++) {
			key = "#";
			value = "";

			if (starts_with(argv[i], "-"))
				key = argv[i];
			else
				value += argv[i];

			for (i++; i < argc && not starts_with(argv[i], "-"); i++) {
				if (!value.empty())
					value += " ";
				value += argv[i];
			}
			i--;

			tmp.emplace(key, value);
		}
		std::swap(umap, tmp);
	}
}

namespace getoptw {
	class args final {
	private:
		std::unordered_map<std::string, std::string> args_map;
	public:
		args() {}
		args(int argc, char** argv) {
			__tools::args_to_umap(args_map, argc, argv);
		}
		void push(int argc, char** argv) {
			__tools::args_to_umap(args_map, argc, argv);
		}
		const char* operator[](const std::string& key) const {
			auto r = args_map.find(key);
			if (r == args_map.end())
				return nullptr;			
			return r->second.c_str();
		}
		auto begin() const {
			return args_map.begin();
		}
		auto end() const {
			return args_map.end();
		}
	};
}