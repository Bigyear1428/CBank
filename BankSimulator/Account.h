// Account.h - ���� Ŭ���� ����
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

class Account {
private:
    std::string accountNumber;    // ���¹�ȣ
    std::string ownerName;        // ������ �̸�
    double balance;               // ���� �ܾ�
    std::vector<Transaction> transactionHistory; // �ŷ� ����

public:
    Account(const std::string& number, const std::string& name, double initialBalance);

    void deposit(double amount);              // �Ա�
    bool withdraw(double amount);            // ���
    void displayInfo() const;                // ���� ���� ���
    void displayTransactionHistory() const;  // �ŷ� ���� ���

    std::string getAccountNumber() const;    // ���¹�ȣ ��ȯ
    double getBalance() const;               // �ܾ� ��ȯ
};

#endif
