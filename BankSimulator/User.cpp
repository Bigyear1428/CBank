// User.cpp - User 클래스 구현 파일
#include "User.h"
#include <iostream>
#include <random>

std::string generateRandomAccountNumber() {
    std::string acc = "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    for (int i = 0; i < 10; ++i) {
        acc += std::to_string(dis(gen));
    }
    return acc;
}

// 생성자: 사용자 이름, 비밀번호 초기화
User::User(const std::string& username, const std::string& password)
    : username(username), password(password), loginAttempts(0) {
}

// 사용자 ID 반환
std::string User::getUsername() const {
    return username;
}

// 비밀번호 검사 (추후 암호화 대응 가능)
bool User::checkPassword(const std::string& input) const {
    return password == input;
}

// 로그인 실패 횟수 증가
void User::incrementLoginAttempts() {
    loginAttempts++;
}

// 로그인 실패 횟수 초기화
void User::resetLoginAttempts() {
    loginAttempts = 0;
}

// 현재 로그인 실패 횟수 반환
int User::getLoginAttempts() const {
    return loginAttempts;
}

// 계정 추가
void User::addAccount(const std::string& ownerName, double initialBalance) {
    std::string accNum;

    // 계좌번호 중복 방지
    do {
        accNum = generateRandomAccountNumber();
    } while (findAccount(accNum) != nullptr);

    Account acc(accNum, ownerName, initialBalance);
    accounts.push_back(acc);
    std::cout << "계좌 생성 완료: " << accNum << "\n";
}



// 계좌 리스트 참조 반환
std::vector<Account>& User::getAccounts() {
    return accounts;
}

// 모든 계좌 출력
void User::displayAccounts() const {
    if (accounts.empty()) {
        std::cout << "[알림] 보유한 계좌가 없습니다.\n";
    }
    else {
        for (const auto& acc : accounts) {
            acc.displayInfo();
            std::cout << "------------------------\n";
        }
    }
}

// 계좌번호로 계좌 검색
Account* User::findAccount(const std::string& number) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == number) return &acc;
    }
    return nullptr;
}

// 계좌번호로 계좌 삭제
bool User::removeAccount(const std::string& number) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == number) {
            accounts.erase(it);
            return true;
        }
    }
    return false;
}