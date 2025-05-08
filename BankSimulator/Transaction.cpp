// Transaction.cpp - �ŷ� ���� Ŭ���� ����
#include "Transaction.h"
#include <sstream>
#include <iomanip>

// ������ ����
Transaction::Transaction(const std::string& type, double amount, const std::string& timestamp)
    : type(type), amount(amount), timestamp(timestamp) {
}

// �ŷ� ������ ���ڿ��� ��ȯ (��: [2025-04-30 22:33:01] �Ա� - 10000��)
std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "[" << timestamp << "] " << type << " - " << std::fixed << std::setprecision(0) << amount << "��";
    return oss.str();
}