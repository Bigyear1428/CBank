// User.h - 사용자 정보를 관리하는 클래스 헤더
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Account.h"

class User {
private:
    std::string username;          // 사용자 ID
    std::string password;          // 비밀번호
    int loginAttempts;             // 로그인 실패 횟수
    std::vector<Account> accounts; // 사용자가 소유한 계좌 목록
    int nextAccountNumber = 20240001; // 계좌번호 자동 생성용

public:
    // 생성자
    User(const std::string& username, const std::string& password);

    // 사용자 정보 관련 함수
    std::string getUsername() const;
    bool checkPassword(const std::string& input) const;
    void incrementLoginAttempts();
    void resetLoginAttempts();
    int getLoginAttempts() const;

    // 계좌 관련 함수
    void addAccount(const std::string& ownerName, double initialBalance);
    std::vector<Account>& getAccounts();
    void displayAccounts() const;
    Account* findAccount(const std::string& number);
    bool removeAccount(const std::string& number); //  계좌 삭제 함수 추가
};

#endif
