// User.cpp - User Ŭ���� ���� ����
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

// ������: ����� �̸�, ��й�ȣ �ʱ�ȭ
User::User(const std::string& username, const std::string& password)
    : username(username), password(password), loginAttempts(0) {
}

// ����� ID ��ȯ
std::string User::getUsername() const {
    return username;
}

// ��й�ȣ �˻� (���� ��ȣȭ ���� ����)
bool User::checkPassword(const std::string& input) const {
    return password == input;
}

// �α��� ���� Ƚ�� ����
void User::incrementLoginAttempts() {
    loginAttempts++;
}

// �α��� ���� Ƚ�� �ʱ�ȭ
void User::resetLoginAttempts() {
    loginAttempts = 0;
}

// ���� �α��� ���� Ƚ�� ��ȯ
int User::getLoginAttempts() const {
    return loginAttempts;
}

// ���� �߰�
void User::addAccount(const std::string& ownerName, double initialBalance) {
    std::string accNum;

    // ���¹�ȣ �ߺ� ����
    do {
        accNum = generateRandomAccountNumber();
    } while (findAccount(accNum) != nullptr);

    Account acc(accNum, ownerName, initialBalance);
    accounts.push_back(acc);
    std::cout << "���� ���� �Ϸ�: " << accNum << "\n";
}



// ���� ����Ʈ ���� ��ȯ
std::vector<Account>& User::getAccounts() {
    return accounts;
}

// ��� ���� ���
void User::displayAccounts() const {
    if (accounts.empty()) {
        std::cout << "[�˸�] ������ ���°� �����ϴ�.\n";
    }
    else {
        for (const auto& acc : accounts) {
            acc.displayInfo();
            std::cout << "------------------------\n";
        }
    }
}

// ���¹�ȣ�� ���� �˻�
Account* User::findAccount(const std::string& number) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == number) return &acc;
    }
    return nullptr;
}

// ���¹�ȣ�� ���� ����
bool User::removeAccount(const std::string& number) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountNumber() == number) {
            accounts.erase(it);
            return true;
        }
    }
    return false;
}