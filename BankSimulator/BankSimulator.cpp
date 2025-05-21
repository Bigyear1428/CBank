// BankSimulator.cpp - 사용자 + 관리자 콘솔 메뉴 포함
#include <iostream>
#include <string>
#include <vector>
#include "User.h"

int main() {
    std::vector<User> users;
    User* currentUser = nullptr;
    int menu;

    // 기본 관리자 계정 생성
    users.emplace_back("admin", "admin123");

    // 첫 화면 
    while (true) {
        std::cout << "\n===== CBank++ 사용자 메뉴 =====\n";
        std::cout << "1. 회원가입\n";
        std::cout << "2. 로그인\n";
        std::cout << "0. 종료\n";
        std::cout << "메뉴 선택: ";
        std::cin >> menu;

        if (menu == 0) break;

        if (menu == 1) {
            std::string id, pw;
            std::cout << "아이디 입력: "; std::cin >> id;
            std::cout << "비밀번호 입력: "; std::cin >> pw;
            users.emplace_back(id, pw);
            std::cout << "회원가입 완료!\n";

        }
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
                        if (user.getLoginAttempts() >= 5) {
                            std::cout << "[경고] 5회 이상 실패. 계정 잠금.\n";
                        }
                        found = true;
                        break;
                    }
                }
            }
            if (!found) std::cout << "존재하지 않는 사용자입니다.\n";
        }

        // 관리자 계정이면 관리자 메뉴 진입
        if (currentUser && currentUser->getUsername() == "admin") {
            int adminChoice;
            while (true) {
                std::cout << "\n===== 관리자 메뉴 =====\n";
                std::cout << "1. 전체 사용자 목록 조회\n";
                std::cout << "2. 특정 사용자 계좌 조회\n";
                std::cout << "3. 계좌 삭제\n";
                std::cout << "0. 로그아웃\n";
                std::cout << "선택: ";
                std::cin >> adminChoice;

                if (adminChoice == 0) {
                    currentUser = nullptr;
                    std::cout << "관리자 로그아웃 완료.\n";
                    break;
                }

                switch (adminChoice) {
                case 1:
                    std::cout << "[전체 사용자 목록]\n";
                    for (const auto& u : users) {
                        std::cout << "- " << u.getUsername() << "\n";
                    }
                    break;
                case 2: {
                    std::string target;
                    std::cout << "사용자 ID 입력: "; std::cin >> target;
                    bool found = false;
                    for (auto& u : users) {
                        if (u.getUsername() == target) {
                            u.displayAccounts();
                            found = true;
                            break;
                        }
                    }
                    if (!found) std::cout << "사용자 없음\n";
                    break;
                }
                case 3: {
                    std::string target, accNum;
                    std::cout << "사용자 ID 입력: "; std::cin >> target;
                    std::cout << "삭제할 계좌번호 입력: "; std::cin >> accNum;
                    bool deleted = false;
                    for (auto& u : users) {
                        if (u.getUsername() == target) {
                            if (u.removeAccount(accNum)) {
                                std::cout << "계좌 삭제 완료\n";
                            }
                            else {
                                std::cout << "해당 계좌 없음\n";
                            }
                            deleted = true;
                            break;
                        }
                    }
                    if (!deleted) std::cout << "사용자 없음\n";
                    break;
                }
                default:
                    std::cout << "잘못된 선택입니다.\n";
                }
            }
        }
        // 일반 사용자 메뉴 진입 (admin이 아닐 때)
        if (currentUser && currentUser->getUsername() != "admin") {
            int action;
            while (currentUser) {
                std::cout << "\n===== 사용자 메뉴 =====\n";
                std::cout << "1. 계좌 개설\n2. 입금\n3. 출금\n4. 계좌 조회\n5. 거래 내역 조회\n0. 로그아웃\n";
                std::cout << "선택: ";
                std::cin >> action;

                std::string accNum;
                double amount;

                switch (action) {
                case 1:
                    std::cout << "예금주 이름: "; std::cin >> accNum;
                    std::cout << "초기 입금액: "; std::cin >> amount;
                    currentUser->addAccount(accNum, amount);
                    break;
                case 2:
                    std::cout << "입금할 계좌번호: "; std::cin >> accNum;
                    std::cout << "입금액: "; std::cin >> amount;
                    if (auto* acc = currentUser->findAccount(accNum)) acc->deposit(amount);
                    else std::cout << "계좌 없음\n";
                    break;
                case 3:
                    std::cout << "출금할 계좌번호: "; std::cin >> accNum;
                    std::cout << "출금액: "; std::cin >> amount;
                    if (auto* acc = currentUser->findAccount(accNum)) acc->withdraw(amount);
                    else std::cout << "계좌 없음\n";
                    break;
                case 4:
                    currentUser->displayAccounts();
                    break;
                case 5:
                    std::cout << "조회할 계좌번호: "; std::cin >> accNum;
                    if (auto* acc = currentUser->findAccount(accNum)) acc->displayTransactionHistory();
                    else std::cout << "계좌 없음\n";
                    break;
                case 0:
                    std::cout << "로그아웃 되었습니다.\n";
                    currentUser = nullptr;
                    break; 

                default:
                    std::cout << "잘못된 선택입니다.\n";
                }
            }
        }

    }

    std::cout << "프로그램 종료\n";
    return 0;
}