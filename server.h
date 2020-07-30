#ifndef SERVER_H
#define SERVER_H
#include "records.h"

User get_user(int id);
Joint get_joint(int id);
Admin get_admin(int id);
bool check_user(User u);
bool check_joint(Joint j);
bool check_admin(Admin a);
bool deposit(int type, int id, int amount);
bool withdraw(int type, int id, int amount);
int get_balance(int type, int id);
bool change_password(int type, int id, char newpassword[20]);
bool add_user(User u);
bool add_joint(Joint j);
bool delete_user(int id);
bool delete_joint(int id);
bool modify_user(User u);
bool modify_joint(Joint j);
void run_server(int nsd);

#endif