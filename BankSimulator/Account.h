// Account.h - 계좌 클래스 정의
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <vector>
#include "Transaction.h"

class Account {
private:
    std::string accountNumber;    // 계좌번호
    std::string ownerName;        // 예금주 이름
    double balance;               // 현재 잔액
    std::vector<Transaction> transactionHistory; // 거래 내역

public:
    Account(const std::string& number, const std::string& name, double initialBalance);

    void deposit(double amount);              // 입금
    bool withdraw(double amount);            // 출금
    void displayInfo() const;                // 계좌 정보 출력
    void displayTransactionHistory() const;  // 거래 내역 출력

    std::string getAccountNumber() const;    // 계좌번호 반환
    double getBalance() const;               // 잔액 반환
};

#endif
