// BankSimulator.cpp
// - 사용자 및 관리자 메뉴를 포함한 콘솔 기반 CBank++ 실행 파일의 메인 진입점
// - 회원가입, 로그인, 사용자 기능(계좌 개설, 입출금, 거래 내역 확인 등)을 처리
// - 입력 유효성 검사, 로그인 시도 제한, 중복 아이디 검사 및 프로그램 종료 메뉴 포함

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "User.h"

// 문자열이 숫자인지 확인하는 유틸리티 함수
bool isNumber(const std::string& s) {
    for (char ch : s) {
        if (!std::isdigit(ch)) return false;
    }
    return !s.empty();
}

// 이미 존재하는 사용자 ID인지 확인
bool isDuplicateId(const std::vector<User>& users, const std::string& id) {
    for (const auto& u : users) {
        if (u.getUsername() == id) return true;
    }
    return false;
}

int main() {
    std::vector<User> users;           // 전체 사용자 목록
    User* currentUser = nullptr;       // 현재 로그인한 사용자 포인터
    std::string input;                 // 메뉴 입력용 문자열
    int menu;                          // 정수 메뉴 코드

    // 관리자 계정 생성
    users.emplace_back("admin", "admin123");

    while (true) {
        std::cout << "\n===== CBank++ 사용자 메뉴 =====\n";
        std::cout << "1. 회원가입\n";
        std::cout << "2. 로그인\n";
        std::cout << "0. 종료\n";
        std::cout << "메뉴 선택: ";
        std::cin >> input;

        // 입력이 숫자가 아니면 무시하고 재입력 요구
        if (!isNumber(input)) {
            std::cout << "[오류] 숫자를 입력해주세요.\n";
            std::cin.clear(); std::cin.ignore(1000, '\n');
            continue;
        }

        menu = std::stoi(input);
        if (menu == 0) break;

        // 회원가입
        if (menu == 1) {
            std::string id, pw;
            std::cout << "아이디 입력: "; std::cin >> id;
            if (isDuplicateId(users, id)) {
                std::cout << "[오류] 이미 존재하는 아이디입니다. 다른 아이디를 사용해주세요.\n";
                continue;
            }
            std::cout << "비밀번호 입력: "; std::cin >> pw;
            users.emplace_back(id, pw);
            std::cout << "회원가입 완료!\n";
        }
        // 로그인
        else if (menu == 2) {
            std::string id, pw;
            std::cout << "아이디 입력: "; std::cin >> id;
            std::cout << "비밀번호 입력: "; std::cin >> pw;

            bool found = false;
            for (auto& user : users) {
                if (user.getUsername() == id) {
                    if (user.getLoginAttempts() >= 5) {
                        std::cout << "[경고] 해당 계정은 잠금 상태입니다.\n";
                        found = true;
                        break;
                    }
                    if (user.checkPassword(pw)) {
                        std::cout << "로그인 성공!\n";
                        user.resetLoginAttempts();
                        currentUser = &user;
                        found = true;
                        break;
                    }
                    else {
                        user.incrementLoginAttempts();
                        std::cout << "비밀번호 오류 (시도: " << user.getLoginAttempts() << "/5)\n";
                        if (user.getLoginAttempts() >= 5)
                            std::cout << "[경고] 5회 이상 실패. 계정 잠금.\n";
                        found = true;
                        break;
                    }
                }
            }
            if (!found) std::cout << "존재하지 않는 사용자입니다.\n";
        }

        // 사용자 로그인 이후 메뉴 (관리자 제외)
        if (currentUser && currentUser->getUsername() != "admin") {
            std::string inputAction;
            int action;
            while (currentUser) {
                std::cout << "\n===== 사용자 메뉴 =====\n";
                std::cout << "1. 계좌 개설\n2. 입금\n3. 출금\n4. 계좌 조회\n5. 거래 내역 조회\n6. 로그아웃\n0. 종료\n";
                std::cout << "선택: ";
                std::cin >> inputAction;

                if (!isNumber(inputAction)) {
                    std::cout << "[오류] 숫자를 입력해주세요.\n";
                    std::cin.clear(); std::cin.ignore(1000, '\n');
                    continue;
                }

                action = std::stoi(inputAction);
                std::string accNum, amountStr;
                double amount;

                switch (action) {
                case 1: // 계좌 개설
                    std::cout << "예금주 이름: "; std::cin >> accNum;
                    std::cout << "초기 입금액: "; std::cin >> amountStr;
                    if (!isNumber(amountStr)) {
                        std::cout << "[오류] 숫자로 된 입금액을 입력해주세요.\n";
                        std::cin.clear(); std::cin.ignore(1000, '\n');
                        break;
                    }
                    amount = std::stod(amountStr);
                    currentUser->addAccount(accNum, amount);
                    break;
                case 2: // 입금
                    std::cout << "입금할 계좌번호: "; std::cin >> accNum;
                    std::cout << "입금액: "; std::cin >> amountStr;
                    if (!isNumber(amountStr)) {
                        std::cout << "[오류] 숫자로 된 입금액을 입력해주세요.\n";
                        std::cin.clear(); std::cin.ignore(1000, '\n');
                        break;
                    }
                    amount = std::stod(amountStr);
                    if (auto* acc = currentUser->findAccount(accNum)) acc->deposit(amount);
                    else std::cout << "계좌 없음\n";
                    break;
                case 3: // 출금
                    std::cout << "출금할 계좌번호: "; std::cin >> accNum;
                    if (auto* acc = currentUser->findAccount(accNum)) {
                        while (true) {
                            std::cout << "출금액: "; std::cin >> amountStr;
                            if (!isNumber(amountStr)) {
                                std::cout << "[오류] 숫자로 된 출금액을 입력해주세요.\n";
                                std::cin.clear(); std::cin.ignore(1000, '\n');
                                continue;
                            }
                            amount = std::stod(amountStr);
                            if (amount > acc->getBalance()) {
                                std::cout << "[오류] 출금액이 잔액을 초과했습니다. 다시 입력해주세요.\n";
                                continue;
                            }
                            acc->withdraw(amount);
                            break;
                        }
                    }
                    else {
                        std::cout << "계좌 없음\n";
                    }
                    break;
                case 4: // 계좌 조회
                    currentUser->displayAccounts();
                    break;
                case 5: // 거래 내역
                    std::cout << "조회할 계좌번호: "; std::cin >> accNum;
                    if (auto* acc = currentUser->findAccount(accNum)) acc->displayTransactionHistory();
                    else std::cout << "계좌 없음\n";
                    break;
                case 6: // 로그아웃
                    std::cout << "로그아웃 되었습니다.\n";
                    currentUser = nullptr;
                    break;
                case 0: // 프로그램 종료
                    std::cout << "프로그램 종료\n";
                    return 0;
                default:
                    std::cout << "잘못된 선택입니다.\n";
                }
            }
        }
    }

    std::cout << "프로그램 종료\n";
    return 0;
}
