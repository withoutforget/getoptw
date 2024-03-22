#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace __tools {
	bool starts_with(const std::string& str, const char* substr) {
		return str.rfind(substr, 0) == 0;
	}
	void args_to_umap(std::unordered_map<std::string, std::string>& umap, int argc, char** argv) {
		std::unordered_map<std::string, std::string> tmp;
		for (size_t i = 1; i < argc; i++) {
			auto el = argv[i];
			if (not __tools::starts_with(el, "-")) {
				tmp.emplace("#", el);
				continue;
			}
			// if we here then it's key
			if (i == argc - 1 || __tools::starts_with(argv[i + 1], "-")) {
				tmp.emplace(el, "");
				continue;
			}
			tmp.emplace(el, argv[i + 1]);
			i++; // skip the next because it has already been used
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
