#ifndef CLIENT_H
#define CLIENT_H

void start(int fd);
void user_menu(int fd);
void admin_menu(int fd);
void user_login(int fd);
void joint_login(int fd);
void admin_login(int fd);
void deposit(int fd);
void withdraw(int fd);
void check_balance(int fd);
void password_change(int fd);
void create_account(int fd);
void remove_account(int fd);
void modify_account(int fd);

#endif