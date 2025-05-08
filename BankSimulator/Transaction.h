// Transaction.h - 거래 내역 클래스
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string type;         // 거래 종류: 입금, 출금, 초기입금 등
    double amount;            // 거래 금액
    std::string timestamp;    // 거래 시각

public:
    Transaction(const std::string& type, double amount, const std::string& timestamp);
    std::string toString() const; // 거래 내역을 문자열로 반환
};

#endif
