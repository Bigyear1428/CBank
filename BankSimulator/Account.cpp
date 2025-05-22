// Account.cpp - Account 클래스의 구현 파일
#include "Account.h"
#include "utils.h"
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

// 현재 시간 문자열을 반환하는 함수 (예: 2025-04-30 22:35)
std::string getCurrentTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char buf[100];
    std::tm localTime;
    localtime_s(&localTime, &now_c);  // 안전한 방식
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localTime);
    return std::string(buf);
}

// 생성자
Account::Account(const std::string& number, const std::string& name, double initialBalance)
    : accountNumber(number), ownerName(name), balance(initialBalance) {
    // 계좌 개설 시 초기 입금 기록 추가
    if (initialBalance > 0) {
        transactionHistory.emplace_back("초기입금", initialBalance, getCurrentTimeString());
    }
}

// 입금 함수
void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        transactionHistory.emplace_back("입금", amount, getCurrentTimeString());
    }
}

// 출금 함수
bool Account::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        transactionHistory.emplace_back("출금", amount, getCurrentTimeString());
        return true;
    }
    return false;
}

// 계좌 정보 출력
void Account::displayInfo() const {
    std::cout << "계좌번호: " << accountNumber << "\n"
        << "예금주: " << ownerName << "\n"
        << "잔액: " << formatWithCommas(balance) << "원\n";
}

// 거래 내역 출력 함수
void Account::displayTransactionHistory() const {
    std::cout << "\n[거래 내역 - 계좌번호: " << accountNumber << "]\n";
    if (transactionHistory.empty()) {
        std::cout << "거래 내역이 없습니다.\n";
        return;
    }
    for (const auto& t : transactionHistory) {
        std::cout << t.toString() << "\n";
    }
}

// 계좌번호 반환
std::string Account::getAccountNumber() const {
    return accountNumber;
}

// 잔액 반환
double Account::getBalance() const {
    return balance;
}
