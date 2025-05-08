// Transaction.h - �ŷ� ���� Ŭ����
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string type;         // �ŷ� ����: �Ա�, ���, �ʱ��Ա� ��
    double amount;            // �ŷ� �ݾ�
    std::string timestamp;    // �ŷ� �ð�

public:
    Transaction(const std::string& type, double amount, const std::string& timestamp);
    std::string toString() const; // �ŷ� ������ ���ڿ��� ��ȯ
};

#endif
