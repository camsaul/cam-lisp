#pragma once

// #include <functional>
#include <string>

class Color {
 public:
    static const std::string Reset;
    static const std::string Red;
    static const std::string Green;

    Color(const std::string& color);
    ~Color();
};

/* namespace color { */
/*     static const std::string Reset = "\033[0m"; */
/*     static const std::string Red   = "\033[31m"; */
/* } */

/* void WithColor(const std::string& color, std::function<()> f); */

class NoCopy {
protected:
	NoCopy() = default;
	NoCopy(const NoCopy&) = delete;
	NoCopy& operator=(const NoCopy&) = delete;
};

class NoMove {
protected:
	NoMove() = default;
	NoMove(NoMove&&) = delete;
	NoMove& operator=(NoMove&&) = delete;
};