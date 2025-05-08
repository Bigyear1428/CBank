// BankSystem.h - ���¸� ���������� �����ϴ� �ý��� Ŭ������ �����
#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <vector>
#include <string>
#include "Account.h"

// BankSystem Ŭ����: ���� ���� ���¸� �����ϴ� Ŭ����
class BankSystem {
private:
    std::vector<Account> accounts;       // ���� ����� �����ϴ� ����
    int nextAccountNumber = 20240001;    // �ڵ� ���¹�ȣ ������ �ʱⰪ

public:
    // �ڵ� ���¹�ȣ�� ���� ����
    void createAccount(const std::string& name, double initialBalance);

    // ���� ���¹�ȣ�� ���� ���� (�����ε�)
    void createAccount(const std::string& number, const std::string& name, double initialBalance);

    // ���¹�ȣ�� ���� ã��
    Account* findAccount(const std::string& number);

    // �Ա� �Լ�: Ư�� ���¿� �ݾ� �Ա�
    void depositToAccount(const std::string& number, double amount);

    // ��� �Լ�: Ư�� ���¿��� �ݾ� ���
    void withdrawFromAccount(const std::string& number, double amount);

    // ���� �� ��ü �Լ�: from �� to�� �ݾ� ��ü
    void transfer(const std::string& fromAccount, const std::string& toAccount, double amount);

    // ��ü ���� ��� ���
    void displayAllAccounts() const;
};

#endif
