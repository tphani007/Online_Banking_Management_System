#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include "records.h"
#include "client.h"

// Start interface for the client i.e Login
void start(int fd)
{
    int option;
    write(1,"Choose one of the following options:\n",38);
    write(1, "1: User Login\n", 15);
	write(1, "2: Joint User Login\n", 21);
	write(1, "3: Admin Login\n", 16);

    write(1, "Enter your option: ", 20);
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        user_login(fd);
        break;
    
    case 2:
        joint_login(fd);
        break;
    
    case 3:
        admin_login(fd);
        break;

    default:
        write(1, "Please select a valid option.\n",31);
        start(fd);
        break;
    }
}

// Menu screen for Users (including Joint Users)
void user_menu(int fd)
{
    int choice;
    write(1, "Choose one of the following options:\n", 38);
	write(1, "1: Deposit\n", 12);
	write(1, "2: Withdraw\n", 13);
	write(1, "3: Check Balance\n", 18);
	write(1, "4: Password Change\n", 20);
	write(1, "5: Exit\n", 9);

    write(1, "Enter your option: ", 20);
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        deposit(fd);
        break;
    
    case 2:
        withdraw(fd);
        break;

    case 3:
        check_balance(fd);
        break;

    case 4:
        password_change(fd);
        break;

    case 5:
        write(fd,&select,sizeof(int));
		write(1, "Thank you for using the system!\n", 33);
		exit(0);

    default:
        write(1, "Please select a valid option.\n",31);
		user_menu(fd);
		break;
    }
}

// Menu screen for Administrators.
void admin_menu(int fd)
{
    int choice;
    write(1, "Choose one of the following options:\n", 38);
	write(1, "1: Create Account\n", 19);
	write(1, "2: Remove Account\n", 19);
	write(1, "3: Modify Account\n", 19);
	write(1, "4: Exit\n", 9);

    write(1, "Enter your option: ", 20);
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        create_account(fd);
        break;
    
    case 2:
        remove_account(fd);
        break;
    
    case 3:
        modify_account(fd);
        break;
    
    case 4:
        write(fd,&choice,sizeof(int));
		write(1, "Thank you for using the system!\n", 33);
		exit(0);

    default:
        write(1, "Please select a valid option.\n",31);
		admin_menu(fd);
        break;
    }
}

void user_login(int fd)
{
    bool result;
    User u;
    int option = 1;
    write(1, "Please enter your user ID: ", 28);
	scanf("%d", &u.id);
	int uid = u.id;
	write(1, "Please enter your password: ", 29);
	scanf("%s", u.password);

    write(fd,&option,sizeof(int));
	write(fd,&u,sizeof(User));

    read(fd,&result,sizeof(result));
    if(result)
    {
        write(1, "Login was successful\n", 22);
        user_menu(fd);
    }
    else
    {
        write(1, "Invalid login\n", 15);
		start(fd);
    }
}

void joint_login(int fd)
{
    bool result;
    Joint u;
    int option = 2;
    write(1, "Please enter your user ID: ", 28);
	scanf("%d", &u.id);
	int uid = u.id;
	write(1, "Please enter your password: ", 29);
	scanf("%s", u.password);

    write(fd,&option,sizeof(int));
	write(fd,&u,sizeof(Joint));

    read(fd,&result,sizeof(result));
    if(result)
    {
        write(1, "Login was successful\n", 22);
        user_menu(fd);
    }
    else
    {
        write(1, "Invalid login\n", 15);
		start(fd);
    }
}

void admin_login(int fd)
{
    bool result;
    Admin u;
    int option = 3;
    write(1, "Please enter your user ID: ", 28);
	scanf("%d", &u.id);
	int uid = u.id;
	write(1, "Please enter your password: ", 29);
	scanf("%s", u.password);

    write(fd,&option,sizeof(int));
	write(fd,&u,sizeof(Admin));

    read(fd,&result,sizeof(result));
    if(result)
    {
        write(1, "Login was successful\n", 22);
        admin_menu(fd);
    }
    else
    {
        write(1, "Invalid login\n", 15);
		start(fd);
    }
}

void deposit(int fd)
{
    int amount;
    int choice = 1;
    bool result;

    write(1, "Enter the amount you wish to deposit: Rs.", 42);
	scanf("%d", &amount);

    write(fd, &choice, sizeof(int));
	write(fd, &amount, sizeof(int));

    read(fd, &result, sizeof(result));
    
    if(result)
        write(1, "Your amount was deposited successfully\n", 40);
    else
        write(1, "An error was encountered while depositing\n", 43);
    
    user_menu(fd);
}

void withdraw(int fd)
{
    int amount;
    int choice = 2;
    bool result;

    write(1, "Enter the amount you wish to withdraw: Rs.", 43);
	scanf("%d", &amount);

    write(fd, &choice, sizeof(int));
	write(fd, &amount, sizeof(int));

    read(fd, &result, sizeof(result));
    
    if(result)
        write(1, "Your amount was withdrawn successfully\n", 40);
    else
        write(1, "An error was encountered while withdrawing\n", 44);
    
    user_menu(fd);
}

void check_balance(int fd)
{
    int amount;
    int choice = 3;

    write(fd, &choice, sizeof(int));
    read(fd, &amount, sizeof(int));

    printf("\nBalance: Rs.%d\n",amount);
    user_menu(fd);
}

void password_change(int fd)
{
    int choice = 4;
	char new_password[20];
	bool result;

    write(1, "Enter your new password (max 20 characters): ", 46);
	scanf("%s", new_password);

    write(fd, &choice, sizeof(int));
	write(fd, new_password, sizeof(new_password));

    read(fd, &result, sizeof(result));

    if(result)
        write(1,"Your password was changed successfully\n", 40);
    else
        write(1, "An error was encountered while changing your password\n", 55);
    user_menu(fd);
}

void create_account(int fd)
{
    int choice = 1;
    int type;
    bool result;

    write(fd, &choice, sizeof(int));

    write(1, "Enter the type account (1: Normal Account 2: Joint Account) you wish to create: ", 81);
	scanf("%d", &type);

    write(fd, &type, sizeof(int));

    if(type == 1)
    {
        User u;
        write(1, "Name of the account holder: ", 29);
		scanf(" %[^\n]", u.name);
		write(1, "Password (max 20 characters): ", 31);
		scanf("%s", u.password);
		u.balance = 1000;
        write(fd, &u, sizeof(User));
    }

    else if(type == 2)
    {
        Joint j;
        write(1, "Name of the first account holder: ", 35);
		scanf(" %[^\n]", j.name1);
		write(1, "Name of the second account holder: ", 36);
		scanf(" %[^\n]", j.name2);
		write(1,"Password (max 20 characters): ", 31);
		scanf("%s", j.password);
		j.balance = 1000;
        write(fd, &j, sizeof(Joint));
    }

    read(fd,&result,sizeof(result));

	if(result)
    {
		write(1,"The account was created successfully\n", 36);
	}
	else
    {
		write(1, "An error was encountered while creating the account\n", 51);
	}

	admin_menu(fd);
}

void remove_account(int fd)
{
    int choice = 2;
    int type, id;
    bool result;

    write(fd, &choice, sizeof(int));
    write(1, "Enter the type account (1: Normal Account 2: Joint Account) you wish to remove: ", 81);
	scanf("%d", &type);

    write(fd, &type, sizeof(int));

    write(1,"User ID: ", 10);
	scanf("%d", &id);
	write(fd, &id, sizeof(int));

    read(fd,&result,sizeof(result));

    if(result)
    {
		write(1,"The account was removed successfully\n", 38);
	}
	else
    {
		write(1,"An error was encountered while removing the account, please re-check the User ID you provided\n", 95);
	}

    admin_menu(fd);
}

void modify_account(int fd)
{
    int choice = 1;
    int type;
    bool result;

    write(fd, &choice, sizeof(int));

    write(1, "Enter the type account (1: Normal Account 2: Joint Account) you wish to create: ", 81);
	scanf("%d", &type);

    write(fd, &type, sizeof(int));

    if(type == 1)
    {
        User u;
        write(1, "Name of the account holder: ", 29);
		scanf(" %[^\n]", u.name);
		write(1, "Password (max 20 characters): ", 31);
		scanf("%s", u.password);
		u.balance = 1000;
        write(fd, &u, sizeof(User));
    }

    else if(type == 2)
    {
        Joint j;
        write(1, "Name of the first account holder: ", 35);
		scanf(" %[^\n]", j.name1);
		write(1, "Name of the second account holder: ", 36);
		scanf(" %[^\n]", j.name2);
		write(1,"Password (max 20 characters): ", 31);
		scanf("%s", j.password);
		j.balance = 1000;
        write(fd, &j, sizeof(Joint));
    }

    read(fd,&result,sizeof(result));

	if(result)
    {
		write(1,"An error was encountered while modifying the account, please re-check the User ID you provided\n", 96);
	}
	else
    {
		write(1,"The account was modified successfully\n", 39);
	}

	admin_menu(fd);
}

void main()
{
    struct sockaddr_in server;
    int sd, msg_len;
    char buffer[50];
    char result;

    sd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;

    server.sin_addr.s_addr = INADDR_ANY;

    server.sin_port = htons(5555);
    connect(sd, (struct sockaddr *)(&server), sizeof(server));

    start(sd);
    close(sd);
}