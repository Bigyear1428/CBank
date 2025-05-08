// BankSystem.h - 계좌를 종합적으로 관리하는 시스템 클래스의 선언부
#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <vector>
#include <string>
#include "Account.h"

// BankSystem 클래스: 여러 개의 계좌를 관리하는 클래스
class BankSystem {
private:
    std::vector<Account> accounts;       // 계좌 목록을 저장하는 벡터
    int nextAccountNumber = 20240001;    // 자동 계좌번호 생성용 초기값

public:
    // 자동 계좌번호로 계좌 생성
    void createAccount(const std::string& name, double initialBalance);

    // 수동 계좌번호로 계좌 생성 (오버로딩)
    void createAccount(const std::string& number, const std::string& name, double initialBalance);

    // 계좌번호로 계좌 찾기
    Account* findAccount(const std::string& number);

    // 입금 함수: 특정 계좌에 금액 입금
    void depositToAccount(const std::string& number, double amount);

    // 출금 함수: 특정 계좌에서 금액 출금
    void withdrawFromAccount(const std::string& number, double amount);

    // 계좌 간 이체 함수: from → to로 금액 이체
    void transfer(const std::string& fromAccount, const std::string& toAccount, double amount);

    // 전체 계좌 목록 출력
    void displayAllAccounts() const;
};

#endif
