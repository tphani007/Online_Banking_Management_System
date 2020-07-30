#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include "server.h"

User get_user(int id)
{
    User u;
    id -= 1;
    int fd = open("User", O_RDONLY, 0744);

    struct flock lock;

    lock.l_type = F_RDLCK; 
	lock.l_whence = SEEK_SET;

    lock.l_start = id*sizeof(User);
	lock.l_len = sizeof(User);
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, id*sizeof(User), SEEK_SET);
    read(fd, &u, sizeof(User));

    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

    close(fd);

	return u;
}

Joint get_joint(int id)
{
    Joint j;
    id -= 1;

    int fd = open("Joint", O_RDONLY, 0744);

    struct flock lock;

    lock.l_type = F_RDLCK; 
	lock.l_whence = SEEK_SET;

    lock.l_start = id*sizeof(Joint);
	lock.l_len = sizeof(Joint);
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, id*sizeof(Joint), SEEK_SET);
    read(fd, &j, sizeof(Joint));

    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

    close(fd);

	return j;
}

Admin get_admin(int id)
{
    Admin a;
    id -= 1;
    int fd = open("Admin", O_RDONLY, 0744);

    struct flock lock;

    lock.l_type = F_RDLCK; 
	lock.l_whence = SEEK_SET;

    lock.l_start = id*sizeof(Admin);
	lock.l_len = sizeof(Admin);
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, id*sizeof(Admin), SEEK_SET);
    read(fd, &a, sizeof(Admin));

    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

    close(fd);

	return a;
}

bool check_user(User u)
{
    int n = u.id - 1;
    int fd = open("User", O_RDONLY, 0744);
    bool result;
    User temp;

    struct flock lock;
    lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = n*sizeof(User);    	     
	lock.l_len = sizeof(User);	            
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, n*sizeof(User), SEEK_SET);  
	read(fd, &temp, sizeof(User));

    if(!strcmp(temp.password, u.password))
    {
        result = true;
    }
	else
    {
        result = false;
    }

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool check_joint(Joint j)
{
    int n = j.id - 1;
    int fd = open("Joint", O_RDONLY, 0744);
    bool result;
    Joint temp;

    struct flock lock;
    lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = n*sizeof(Joint);    	     
	lock.l_len = sizeof(Joint);	            
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, n*sizeof(Joint), SEEK_SET);  
	read(fd, &temp, sizeof(Joint));

    if(!strcmp(temp.password, j.password))
    {
        result = true;
    }
	else
    {
        result = false;
    }

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool check_admin(Admin a)
{
    int n = a.id - 1;
    int fd = open("Admin", O_RDONLY, 0744);
    bool result;
    Admin temp;

    struct flock lock;
    lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = n*sizeof(Admin);    	     
	lock.l_len = sizeof(Admin);	            
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, n*sizeof(Admin), SEEK_SET);  
	read(fd, &temp, sizeof(Admin));

    if(!strcmp(temp.password, a.password))
    {
        result = true;
    }
	else
    {
        result = false;
    }

	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool deposit(int type, int id, int amount)
{
    id -= 1;
    if(type == 1)
    {
        User u;
        int fd = open("User", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(User);    
		lock.l_len = sizeof(User);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(User), SEEK_SET);  
		read(fd, &u, sizeof(User));

        u.balance += amount;
        lseek(fd, sizeof(User)*(-1), SEEK_CUR);
		write(fd, &u, sizeof(User));

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
        return true;
    }
    else if(type == 2)
    {
        Joint j;
        int fd = open("Joint", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(Joint);    
		lock.l_len = sizeof(Joint);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(Joint), SEEK_SET);  
		read(fd, &j, sizeof(Joint));

        j.balance += amount;
        lseek(fd, sizeof(Joint)*(-1), SEEK_CUR);
		write(fd, &j, sizeof(Joint));

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
        return true;
    }
    return false;
}

bool withdraw(int type, int id, int amount)
{
    id -= 1;
    if(type == 1)
    {
        User u;
        int fd = open("User", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(User);    
		lock.l_len = sizeof(User);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(User), SEEK_SET);  
		read(fd, &u, sizeof(User));

        u.balance -= amount;
        lseek(fd, sizeof(User)*(-1), SEEK_CUR);
		write(fd, &u, sizeof(User));

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
        return true;
    }
    else if(type == 2)
    {
        Joint j;
        int fd = open("Joint", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(Joint);    
		lock.l_len = sizeof(Joint);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(Joint), SEEK_SET);  
		read(fd, &j, sizeof(Joint));

        j.balance -= amount;
        lseek(fd, sizeof(Joint)*(-1), SEEK_CUR);
		write(fd, &j, sizeof(Joint));

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
        return true;
    }
    return false;
}

int get_balance(int type, int id)
{
    id -= 1;
    int result = 0;
    if(type == 1)
    {
        User u;
        int fd = open("User", O_RDONLY, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(User);    
		lock.l_len = sizeof(User);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(User), SEEK_SET);  
		read(fd, &u, sizeof(User));

        result = u.balance;

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
    }
    else if(type == 2)
    {
        Joint j;
        int fd = open("Joint", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(Joint);    
		lock.l_len = sizeof(Joint);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(Joint), SEEK_SET);  
		read(fd, &j, sizeof(Joint));

        result = j.balance;

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
    }
    return result;
}

bool change_password(int type, int id, char newpassword[20])
{
    id -= 1;
    bool result;
    if(type == 1)
    {
        User u;
        int fd = open("User", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(User);    
		lock.l_len = sizeof(User);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(User), SEEK_SET);  
		read(fd, &u, sizeof(User));

        strcpy(u.password, newpassword);
        lseek(fd, sizeof(User)*(-1), SEEK_CUR);
		write(fd, &u, sizeof(User));

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
        return true;
    }
    else if(type == 2)
    {
        Joint j;
        int fd = open("Joint", O_RDWR, 0744);
        
        struct flock lock;

        lock.l_type = F_WRLCK; 
		lock.l_whence = SEEK_SET;

        lock.l_start = id*sizeof(Joint);    
		lock.l_len = sizeof(Joint);	            
		lock.l_pid = getpid();

        int fl = fcntl(fd, F_SETLKW, &lock);
        lseek(fd, id*sizeof(Joint), SEEK_SET);  
		read(fd, &j, sizeof(Joint));

        strcpy(j.password, newpassword);
        lseek(fd, sizeof(Joint)*(-1), SEEK_CUR);
		write(fd, &j, sizeof(Joint));

        lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);

		close(fd);
        return true;
    }
    return false;
}

bool add_user(User u)
{
    User temp;
    bool result;
    int fd = open("User", O_RDWR, 0744);

    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
	lock.l_start = (-1)*sizeof(User);    
	lock.l_len = sizeof(User);	             
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);
    lseek(fd, (-1)*sizeof(User), SEEK_END);  
	read(fd, &temp, sizeof(User));

    u.id = temp.id + 1;
    u.acc_num = temp.acc_num + 1;
    
    int ret = write(fd, &u, sizeof(User));
    if(ret==0)
        result = false;
    else
        result = true;
    
    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool add_joint(Joint j)
{
    Joint temp;
    bool result;
    int fd = open("Joint", O_RDWR, 0744);

    struct flock lock;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
	lock.l_start = (-1)*sizeof(Joint);    
	lock.l_len = sizeof(Joint);	             
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);
    lseek(fd, (-1)*sizeof(Joint), SEEK_END);  
	read(fd, &temp, sizeof(Joint));

    j.id = temp.id + 1;
    j.acc_num = temp.acc_num + 1;
    
    int ret = write(fd, &j, sizeof(Joint));
    if(ret==0)
        result = false;
    else
        result = true;
    
    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool delete_user(int id)
{
    User temp;
    id -= 1;
    bool result;
    int fd = open("User", O_RDWR, 0744);

    struct flock lock;
    lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = id*sizeof(User);    
	lock.l_len = sizeof(User);	             
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, id*sizeof(User), SEEK_END);  
	read(fd, &temp, sizeof(User));

    temp.balance = 0;
    lseek(fd, (-1)*sizeof(User), SEEK_CUR);
    int ret = write(fd, &temp, sizeof(User));
    if(ret==0)
        result = false;
    else
        result = true;
    
    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool delete_joint(int id)
{
    Joint temp;
    id -= 1;
    bool result;
    int fd = open("Joint", O_RDWR, 0744);

    struct flock lock;
    lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = id*sizeof(Joint);    
	lock.l_len = sizeof(Joint);	             
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, id*sizeof(Joint), SEEK_END);  
	read(fd, &temp, sizeof(Joint));

    temp.balance = 0;
    lseek(fd, (-1)*sizeof(Joint), SEEK_CUR);
    int ret = write(fd, &temp, sizeof(Joint));
    if(ret==0)
        result = false;
    else
        result = true;
    
    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool modify_user(User u)
{
    User temp;
    int n = u.id - 1;
    bool result;
    int fd = open("User", O_RDWR, 0744);

    struct flock lock;

    lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = n*sizeof(User);    
	lock.l_len = sizeof(User);	             
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, n*sizeof(User), SEEK_END);  
	read(fd, &temp, sizeof(User));
    if(u.acc_num == temp.acc_num)
    {
        lseek(fd, (-1)*sizeof(User), SEEK_CUR);
        int ret = write(fd, &u, sizeof(User));
        if(ret==0)
            result = false;
        else
            result = true;
    }
    else
        result = false;
    
    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

bool modify_joint(Joint j)
{
    Joint temp;
    int n = j.id - 1;
    bool result;
    int fd = open("Joint", O_RDWR, 0744);

    struct flock lock;

    lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;

    lock.l_start = n*sizeof(Joint);    
	lock.l_len = sizeof(Joint);	             
	lock.l_pid = getpid();

    int fl = fcntl(fd, F_SETLKW, &lock);

    lseek(fd, n*sizeof(Joint), SEEK_END);  
	read(fd, &temp, sizeof(Joint));
    if(j.acc_num == temp.acc_num)
    {
        lseek(fd, (-1)*sizeof(User), SEEK_CUR);
        int ret = write(fd, &j, sizeof(User));
        if(ret==0)
            result = false;
        else
            result = true;
    }
    else
        result = false;
    
    lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);

	close(fd);

	return result;
}

// The server reads the choices made by the client and runs accordingly.
void run_server(int nsd)
{
	int choice, type, option, accType, currUserID;
	bool result;
	while(1)
    {
		read(nsd, &option, sizeof(option));
		printf("Option: %d\n", option);

		if (option == 1)
        {
			User u1;
			accType = 1;
			read(nsd, &u1, sizeof(User));
			printf("UserID: %d\n", u1.id);
			printf("Password: %s\n", u1.password);
			currUserID = u1.id;
			result = check_user(u1);
			write(nsd, &result, sizeof(result));
		}
		else if (option == 2)
        {
			Joint u2;
			accType = 2;
			read(nsd, &u2, sizeof(Joint));
			currUserID = u2.id;
			printf("UserID: %d\n", u2.id);
			printf("Password: %s\n", u2.password);
			result = check_joint(u2);
			write(nsd, &result, sizeof(result));
		}
		else if (option == 3)
        {
			Admin u3;
			accType = 3;
			read(nsd, &u3, sizeof(Admin));
			currUserID = u3.id;
			printf("UserID: %d\n", u3.id);
			printf("Password: %s\n", u3.password);
			result = check_admin(u3);
			write(nsd, &result, sizeof(result));
		}
		else
        {
			result = false;
			write(nsd, &result, sizeof(result));
		}
		if(result)
        {
            break;
        }
	}

	while(1)
    {
		read(nsd, &choice, sizeof(int));
		if(option == 1 || option == 2)
        {
			if(choice == 1)
            {
				int amt;
				read(nsd, &amt, sizeof(int));
				result = deposit(accType, currUserID, amt);
				write(nsd, &result, sizeof(result));
			}
			else if(choice == 2)
            {
				int amt;
				read(nsd, &amt, sizeof(int));
				result = withdraw(accType, currUserID, amt);
				write(nsd,&result,sizeof(result));
			}
			else if(choice == 3)
            {
				int amt;
				amt = get_balance(accType, currUserID);
				write(nsd, &amt, sizeof(int));
			}
			else if(choice == 4)
            {
				char pwd[15];
				read(nsd, pwd, sizeof(pwd));
				result = change_password(accType, currUserID, pwd);
				write(nsd, &result, sizeof(result));
			}
			else if(choice == 6)
            {
                break;
            }
		}
		else if(option == 3)
        {
			read(nsd, &type, sizeof(int));
			if(choice == 1)
            {
				if(type == 1)
                {
					User u1;
					read(nsd, &u1, sizeof(User));
					result = add_user(u1);
					write(nsd, &result, sizeof(result));
				}
				else if(type == 2)
                {
					Joint u2;
					read(nsd, &u2, sizeof(Joint));
					result = add_joint(u2);
					write(nsd, &result, sizeof(result));
				}
			}
			else if(choice == 2)
            {
				if(type == 1)
                {
					int id1;
					read(nsd, &id1, sizeof(int));
					result = delete_user(id1);
					write(nsd, &result, sizeof(result));
				}
				else if(type == 2)
                {
					int id2;
					read(nsd, &id2, sizeof(int));
					result = delete_joint(id2);
					write(nsd, &result, sizeof(result));
				}
			}
			else if(choice == 3)
            {
				if(type == 1)
                {
					User u1;
					read(nsd, &u1, sizeof(User));
					result = modify_user(u1);
					write(nsd, &result, sizeof(result));
				}
				else if(type == 2)
                {
					Joint u2;
					read(nsd, &u2, sizeof(Joint));
					result = modify_joint(u2);
					write(nsd, &result, sizeof(result));
				}
			}
			else if(choice == 5)
            {
                break;
            }
		}
	}
	close(nsd);
	write(1, "Client session has come to an end\n", 35);
}

void main()
{
    struct sockaddr_in server, client;
	int sd, nsd, len;

    sd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET; // internet domain
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5555);

    bind(sd, (void *)(&server), sizeof(server)); // binds. gives it its local address. only server binds.
	listen(sd,5);

    write(1,"Waiting for the client.....\n", 29);

    while(1)
    {
        len = sizeof(client);
		nsd=accept(sd,(void *)(&client), &len);

		write(1,"Connected to the client.....\n", 30);
		if(!fork()){
			close(sd);	//child doesn't require sd
			run_server(nsd);
			exit(0);
		}
		else{
			close(nsd);	//child has nsd and parent doesn't require it
		}
	}

}