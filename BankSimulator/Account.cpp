// Account.cpp - Account Ŭ������ ���� ����
#include "Account.h"
#include "utils.h"
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

// ���� �ð� ���ڿ��� ��ȯ�ϴ� �Լ� (��: 2025-04-30 22:35)
std::string getCurrentTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char buf[100];
    std::tm localTime;
    localtime_s(&localTime, &now_c);  // ������ ���
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);
    return std::string(buf);
}

// ������
Account::Account(const std::string& number, const std::string& name, double initialBalance)
    : accountNumber(number), ownerName(name), balance(initialBalance) {
    // ���� ���� �� �ʱ� �Ա� ��� �߰�
    if (initialBalance > 0) {
        transactionHistory.emplace_back("�ʱ��Ա�", initialBalance, getCurrentTimeString());
    }
}

// �Ա� �Լ�
void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        transactionHistory.emplace_back("�Ա�", amount, getCurrentTimeString());
    }
}

// ��� �Լ�
bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactionHistory.emplace_back("���", amount, getCurrentTimeString());
        return true;
    }
    return false;
}

// ���� ���� ���
void Account::displayInfo() const {
    std::cout << "���¹�ȣ: " << accountNumber << "\n"
        << "������: " << ownerName << "\n"
        << "�ܾ�: " << formatWithCommas(balance) << "��\n";
}

// �ŷ� ���� ��� �Լ�
void Account::displayTransactionHistory() const {
    std::cout << "\n[�ŷ� ���� - ���¹�ȣ: " << accountNumber << "]\n";
    if (transactionHistory.empty()) {
        std::cout << "�ŷ� ������ �����ϴ�.\n";
        return;
    }
    for (const auto& t : transactionHistory) {
        std::cout << t.toString() << "\n";
    }
}

// ���¹�ȣ ��ȯ
std::string Account::getAccountNumber() const {
    return accountNumber;
}

// �ܾ� ��ȯ
double Account::getBalance() const {
    return balance;
}
