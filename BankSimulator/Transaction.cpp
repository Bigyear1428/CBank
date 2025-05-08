// Transaction.cpp - 거래 내역 클래스 구현
#include "Transaction.h"
#include <sstream>
#include <iomanip>

// 생성자 정의
Transaction::Transaction(const std::string& type, double amount, const std::string& timestamp)
    : type(type), amount(amount), timestamp(timestamp) {
}

// 거래 정보를 문자열로 반환 (예: [2025-04-30 22:33:01] 입금 - 10000원)
std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "[" << timestamp << "] " << type << " - " << std::fixed << std::setprecision(0) << amount << "원";
    return oss.str();
}