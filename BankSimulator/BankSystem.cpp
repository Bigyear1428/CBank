// BankSystem.cpp - BankSystem 클래스의 기능 구현
#include "BankSystem.h"
#include <iostream>

// 수동 계좌번호로 계좌 생성
void BankSystem::createAccount(const std::string& number, const std::string& name, double initialBalance) {
    accounts.emplace_back(number, name, initialBalance);
}

// 자동 계좌번호 생성 후 계좌 생성
void BankSystem::createAccount(const std::string& name, double initialBalance) {
    std::string generatedNumber = std::to_string(nextAccountNumber++);

    // 혹시 중복 계좌번호가 있을 경우 피해서 생성
    while (findAccount(generatedNumber) != nullptr) {
        generatedNumber = std::to_string(nextAccountNumber++);
    }

    accounts.emplace_back(generatedNumber, name, initialBalance);
    std::cout << "계좌가 생성되었습니다. 계좌번호: " << generatedNumber << "\n";
}

// 특정 계좌번호에 해당하는 계좌 객체를 반환
Account* BankSystem::findAccount(const std::string& number) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == number)
            return &acc;
    }
    return nullptr;
}

// 입금 처리 함수
void BankSystem::depositToAccount(const std::string& number, double amount) {
    Account* acc = findAccount(number);
    if (acc) acc->deposit(amount);
    else std::cout << "[오류] 계좌를 찾을 수 없습니다.\n";
}

// 출금 처리 함수
void BankSystem::withdrawFromAccount(const std::string& number, double amount) {
    Account* acc = findAccount(number);
    if (acc) {
        if (!acc->withdraw(amount)) {
            std::cout << "[오류] 출금 실패: 잔액 부족 또는 잘못된 금액입니다.\n";
        }
    }
    else {
        std::cout << "[오류] 계좌를 찾을 수 없습니다.\n";
    }
}

// 계좌 간 이체 함수
void BankSystem::transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    Account* from = findAccount(fromAccount);
    Account* to = findAccount(toAccount);

    if (!from || !to) {
        std::cout << "[오류] 출발지 또는 도착지 계좌가 존재하지 않습니다.\n";
        return;
    }

    if (from->withdraw(amount)) {
        to->deposit(amount);
    }
    else {
        std::cout << "[오류] 이체 실패: 출발 계좌 잔액 부족.\n";
    }
}

// 전체 계좌 목록 출력
void BankSystem::displayAllAccounts() const {
    for (const auto& acc : accounts) {
        acc.displayInfo();
        std::cout << "------------------------\n";
    }
}
