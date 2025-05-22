// utils.cpp - 공용 유틸리티 함수 구현
#include "utils.h"
#include <sstream>
#include <iomanip>
#include <locale>

std::string formatWithCommas(double value) {
    std::stringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << std::setprecision(0) << value;
    return ss.str();
}
