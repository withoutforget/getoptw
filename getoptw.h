#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

#if defined(_MSC_VER)
#define __cplusplus_v _MSVC_LANG
#else
#define __cplusplus_v __cplusplus
#endif

namespace __tools {
#if __cplusplus_v < 202002L
template<class T, class U>
bool cmp_less(T t, U u) noexcept
{
    if constexpr (std::is_signed<T>::value == std::is_signed<U>::value)
        return t < u;
    else if constexpr (std::is_signed<T>::value)
        return t < 0 || std::make_unsigned_t<T>(t) < u;
    else
        return u >= 0 && t < std::make_unsigned_t<U>(u);
}
#else
template<class T, class U>
bool cmp_less(T t, U u) noexcept
{
	return std::cmp_less<T, U>(t, u);
}
#endif

}


namespace __tools {
	bool starts_with(const std::string& str, const char* substr) {
		return str.rfind(substr, 0) == 0;
	}
	void args_to_umap(std::unordered_map<std::string, std::string>& umap, int argc, char** argv) {
		std::unordered_map<std::string, std::string> tmp;
		std::string key{};
		std::string value{};
		for (size_t i = 1; __tools::cmp_less(i, argc); i++) {
			key = "#";
			value = "";

			if (starts_with(argv[i], "-"))
				key = argv[i];
			else
				value += argv[i];

			for (i++; __tools::cmp_less(i, argc) && not starts_with(argv[i], "-"); i++) {
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