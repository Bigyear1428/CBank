// Transaction.cpp - �ŷ� ���� Ŭ���� ����
#include "Transaction.h"
#include "utils.h"
#include <sstream>
#include <iomanip>

// ������ ����
Transaction::Transaction(const std::string& type, double amount, const std::string& timestamp)
    : type(type), amount(amount), timestamp(timestamp) {
}

// �ŷ� ������ ���ڿ��� ��ȯ (��: [2025-04-30 22:33:01] �Ա� - 10,000��)
std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "[" << timestamp << "] " << type << " - " << formatWithCommas(amount) << "��";
    return oss.str();
}
