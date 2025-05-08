// User.h - ����� ������ �����ϴ� Ŭ���� ���
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Account.h"

class User {
private:
    std::string username;          // ����� ID
    std::string password;          // ��й�ȣ
    int loginAttempts;             // �α��� ���� Ƚ��
    std::vector<Account> accounts; // ����ڰ� ������ ���� ���
    int nextAccountNumber = 20240001; // ���¹�ȣ �ڵ� ������

public:
    // ������
    User(const std::string& username, const std::string& password);

    // ����� ���� ���� �Լ�
    std::string getUsername() const;
    bool checkPassword(const std::string& input) const;
    void incrementLoginAttempts();
    void resetLoginAttempts();
    int getLoginAttempts() const;

    // ���� ���� �Լ�
    void addAccount(const std::string& ownerName, double initialBalance);
    std::vector<Account>& getAccounts();
    void displayAccounts() const;
    Account* findAccount(const std::string& number);
    bool removeAccount(const std::string& number); //  ���� ���� �Լ� �߰�
};

#endif
