#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "records.h"
#include "db.h"

int get_user()
{
    int fd = open("User", O_RDONLY, 0744);
    User rec;
    lseek(fd, -sizeof(User), SEEK_END);
    read(fd, &rec, sizeof(User));
    close(fd);
    return rec.id + 1;
}

int get_joint()
{
    int fd = open("Joint", O_RDONLY, 0744);
    Joint rec;
    lseek(fd, -sizeof(Joint), SEEK_END);
	read(fd, &rec, sizeof(Joint));
	close(fd);
	return rec.id + 1;
}

int get_admin()
{
    int fd=open("Admin", O_RDONLY, 0744);
	Admin rec;
	lseek(fd, -sizeof(Admin), SEEK_END);
	read(fd, &rec, sizeof(Admin));
	close(fd);
	return rec.id + 1;
}

// Initialize the database for the server.
void main()
{
    int fd = open("Admin", O_RDWR | O_CREAT, 0744);
    int opt = 0;
    Admin a;
    write(1, "Enter the name for the Administrator: ", 39);
    scanf(" %[^\n]",a.username);
    write(1, "Enter the password (max 20 characters): ", 41);
    scanf(" %[^\n]",a.password);
    a.id = 1;
    write(fd, &a, sizeof(Admin));
    write(1, "Do you want to add more admins (1-Yes/0-No) : ", 47);
    scanf("%d", &opt);
    while(opt)
    {
        write(1, "Enter the name for the Administrator: ", 39);
        scanf(" %[^\n]",a.username);
        write(1, "Enter the password (max 20 characters): ", 41);
        scanf(" %[^\n]",a.password);
        a.id = get_admin();
        write(1, "Do you want to add more admins (1-Yes/0-No) : ", 47);
        scanf("%d", &opt);
    }
    close(fd);

    fd = open("User", O_RDWR | O_CREAT, 0744);
    User u;
    write(1, "Enter the name of user: ", 25);
    scanf(" %[^\n]",u.name);
    write(1, "Enter the password (max 20 characters): ", 41);
    scanf(" %[^\n]",u.password);
    u.id = 1;
    u.balance = 1000;
    u.acc_num = 1000 + u.id;
    printf("User ID: %d\n", u.id);
    write(fd, &u, sizeof(Admin));
    write(1, "Do you want to add more users (1-Yes/0-No) : ", 46);
    scanf("%d", &opt);
    while(opt)
    {
        write(1, "Enter the name of user: ", 25);
        scanf(" %[^\n]",u.name);
        write(1, "Enter the password (max 20 characters): ", 41);
        scanf(" %[^\n]",u.password);
        u.id = get_user();
        u.balance = 1000;
        u.acc_num = 1000 + u.id;
        printf("User ID: %d\n", u.id);
        write(1, "Do you want to add more users (1-Yes/0-No) : ", 46);
        scanf("%d", &opt);
    }
    close(fd);

    fd=open("Joint",O_RDWR | O_CREAT,0744);
    Joint j;
    write(1, "Enter the name of the first user: ", 35);
    scanf(" %[^\n]",j.name1);
    write(1, "Enter the name of the second user: ", 36);
    scanf(" %[^\n]",j.name2);
    write(1, "Enter the password (max 20 characters): ", 41);
    scanf(" %[^\n]",u.password);
    j.id = 1;
    j.balance = 1000;
    j.acc_num = 1000 + u.id;
    printf("User ID: %d\n", u.id);
    write(fd, &j, sizeof(Admin));
    write(1, "Do you want to add more joint users (1-Yes/0-No) : ", 52);
    scanf("%d", &opt);
    while(opt)
    {
        write(1, "Enter the name of the first user: ", 35);
        scanf(" %[^\n]",j.name1);
        write(1, "Enter the name of the second user: ", 36);
        scanf(" %[^\n]",j.name2);
        write(1, "Enter the password (max 20 characters): ", 41);
        scanf(" %[^\n]",u.password);
        j.id = get_joint();
        j.balance = 1000;
        j.acc_num = 1000 + u.id;
        printf("User ID: %d\n", u.id);
        write(1, "Do you want to add more joint users (1-Yes/0-No) : ", 52);
        scanf("%d", &opt);
    }
    close(fd);
    printf("Database created successfully!\n");
}