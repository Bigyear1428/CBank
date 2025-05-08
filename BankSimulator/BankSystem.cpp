// BankSystem.cpp - BankSystem Ŭ������ ��� ����
#include "BankSystem.h"
#include <iostream>

// ���� ���¹�ȣ�� ���� ����
void BankSystem::createAccount(const std::string& number, const std::string& name, double initialBalance) {
    accounts.emplace_back(number, name, initialBalance);
}

// �ڵ� ���¹�ȣ ���� �� ���� ����
void BankSystem::createAccount(const std::string& name, double initialBalance) {
    std::string generatedNumber = std::to_string(nextAccountNumber++);

    // Ȥ�� �ߺ� ���¹�ȣ�� ���� ��� ���ؼ� ����
    while (findAccount(generatedNumber) != nullptr) {
        generatedNumber = std::to_string(nextAccountNumber++);
    }

    accounts.emplace_back(generatedNumber, name, initialBalance);
    std::cout << "���°� �����Ǿ����ϴ�. ���¹�ȣ: " << generatedNumber << "\n";
}

// Ư�� ���¹�ȣ�� �ش��ϴ� ���� ��ü�� ��ȯ
Account* BankSystem::findAccount(const std::string& number) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == number)
            return &acc;
    }
    return nullptr;
}

// �Ա� ó�� �Լ�
void BankSystem::depositToAccount(const std::string& number, double amount) {
    Account* acc = findAccount(number);
    if (acc) acc->deposit(amount);
    else std::cout << "[����] ���¸� ã�� �� �����ϴ�.\n";
}

// ��� ó�� �Լ�
void BankSystem::withdrawFromAccount(const std::string& number, double amount) {
    Account* acc = findAccount(number);
    if (acc) {
        if (!acc->withdraw(amount)) {
            std::cout << "[����] ��� ����: �ܾ� ���� �Ǵ� �߸��� �ݾ��Դϴ�.\n";
        }
    }
    else {
        std::cout << "[����] ���¸� ã�� �� �����ϴ�.\n";
    }
}

// ���� �� ��ü �Լ�
void BankSystem::transfer(const std::string& fromAccount, const std::string& toAccount, double amount) {
    Account* from = findAccount(fromAccount);
    Account* to = findAccount(toAccount);

    if (!from || !to) {
        std::cout << "[����] ����� �Ǵ� ������ ���°� �������� �ʽ��ϴ�.\n";
        return;
    }

    if (from->withdraw(amount)) {
        to->deposit(amount);
    }
    else {
        std::cout << "[����] ��ü ����: ��� ���� �ܾ� ����.\n";
    }
}

// ��ü ���� ��� ���
void BankSystem::displayAllAccounts() const {
    for (const auto& acc : accounts) {
        acc.displayInfo();
        std::cout << "------------------------\n";
    }
}
