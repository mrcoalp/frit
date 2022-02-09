#pragma once

#include <memory>
#include <stdexcept>
#include <string>

namespace frit {
namespace string_utils {

template <typename... Args>
std::string format(std::string&& format, Args&&... args) {
	// extra space for '\0'
	int size_s = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...) + 1;
	if (size_s <= 0) {
		throw std::runtime_error("error formatting string. invalid format size");
	}
	auto size = static_cast<size_t>(size_s);
	auto buf = std::make_unique<char[]>(size);
	std::snprintf(buf.get(), size, format.c_str(), std::forward<Args>(args)...);
	// we don't want the '\0' inside
	return {buf.get(), buf.get() + size - 1};
}

}  // namespace string_utils
}  // namespace frit
