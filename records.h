#ifndef RECORDS_H
#define RECORDS_H
#define PWDSIZE 20
#define USRSIZE 100

// Normal user
typedef struct user
{
    int id;
	char name[USRSIZE];
	char password[PWDSIZE];
	int acc_num;
	int balance;
} User;

// Joint user
typedef struct joint_user
{
	int id;
	char name1[USRSIZE];
	char name2[USRSIZE];
	char password[PWDSIZE];
	int acc_num;
	int balance;
} Joint;

// The Administrator
typedef struct admin
{
	int id;
	char username[USRSIZE];
	char password[PWDSIZE];
} Admin;

#endif
