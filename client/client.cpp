#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
int exi;
int clos;
int a;
int n;
char choice_gp[256];
char gp_messages[256];
char buffertmp[256];
char which_gp[256];
char group_names[256];
int hoi;
char name[256];
FILE* message;
FILE* contact;
char group_name[256];
char start[256];
char messag[256];
char contacts[256];
char point[200];
char Username[100];
char Password[100];
int y;
int u;
char login[256];
char U[100];
char P[100];
int which;
int result=0;
int num=1;
int nums;
char username_password[256];
char User[100];
char Pass[100];
int q;
int choice;
char logged[100];
char mess[256];
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
void group_start(int sockfd){
    printf("1-create a group\n\n2-join a group\n\n");
    bzero(choice_gp,256);
    scanf("%s", choice_gp);
    send(sockfd, &choice_gp, 256, 0);
}
void first_page(int sockfd){
    printf("\n1.Chats\n\n2.Groups\n\n3.Channels\n\n");
    scanf("%d",&choice);
    send(sockfd,&choice, sizeof(int),0);
}
int max(int x,int y){
    if (x>=y){
         q= x;
    }
    if (y>=x){
         q= y;
    }
    return q;
}
void take_username_password(int nums) {
    bzero(U,100);
    bzero(P,100);
    y = nums+1;
    u=0;
    while (point[y] != '\n') {
        U[u] = point[y];
        u += 1;
        y += 1;
    }
    u=0;
    y+=2;
    while (point[y]!='\n'){
        P[u]=point[y];
        u+=1;
        y+=1;
    }
}
void menu(int sockfd) {
    printf("1 - Log In\n2 - SignUp\n");
    scanf("%d", &which);
    send(sockfd,&which, sizeof(which),0);
}
FILE* file;
void rec_lines(int sockfd){
    recv(sockfd,&point,200,0);
}
void check_login(int sockfd) {
        if (which == 1) {
            rec_lines(sockfd);
            printf("Enter Your Username:\n");
            printf("Enter Your Password:\n");
            scanf("%s", Username);
            scanf("%s", Password);
        }
        if (which == 2) {
            char info[256];
            printf("Enter Your Username:\n");
            printf("Enter Your Password:\n");
            scanf("%s", User);
            scanf("%s", Pass);
            bzero(info, sizeof(info));
            info[0] = '!';
            strcpy(info + 1, User);
            info[strlen(User) + 1] = '\n';
            info[strlen(User) + 2] = '@';
            strcpy(info + strlen(User) + 3, Pass);
            send(sockfd, &info, strlen(info), 0);
            menu(sockfd);
            check_login(sockfd);
        }
    }
int main(int argc, char *argv[]) {
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr,
          (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    a = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (a < 0) {
        error("ERROR connecting");
    }
    menu(sockfd);
    check_login(sockfd);
    while (1) {
        while (1) {
            int i = 0;
            while (i < strlen(point)) {
                nums = i;
                if (point[i] == '!') {
                    take_username_password(nums);
                    num = i + 1;
                    int m = 0;
                    for (int j = i + 1; j <= max(strlen(U), strlen(Username)) + i; j++) {
                        if (point[j] == Username[m]) {
                            m += 1;
                            num += 1;
                            if (j == max(strlen(U), strlen(Username)) + i) {
                                result = 2;
                                break;
                            }
                        }
                        else if (point[j] != Username[m]) {
                            break;
                        }
                    }
                    if (result == 2) {
                        break;
                    }
                    i += 1;
                }
                else {
                    i += 1;
                }
            }
            send(sockfd, &result, sizeof(int), 0);
            if (result != 2) {
                printf("Wrong Username\n");
                menu(sockfd);
                check_login(sockfd);
            }
            else
                break;
        }
        int k = 0;
        for (int j = num + 2; j <= num + max(strlen(P), strlen(Password)) + 1; j++) {
            if (point[j] == Password[k]) {
                k += 1;
                if (j == num + max(strlen(P), strlen(Password)) + 1) {
                    result = 5;
                    break;
                }
            }
            else {
                printf("Wrong Password\n");
                num = 1;
                result = 3;
                break;
            }
        }
        send(sockfd, &result, sizeof(int), 0);
        if (result != 5) {
            menu(sockfd);
            check_login(sockfd);
        }
        if (result == 5) {
            recv(sockfd, &logged, 100, 0);
            printf("\n%s", logged);
            send(sockfd, &Username, strlen(Username), 0);
            break;
        }
    }
    while (1) {
        exi=0;
        while (1) {
            first_page(sockfd);
            if (choice == 1) {
                send(sockfd,&Username,strlen(Username),0);
                bzero(contacts,256);
                recv(sockfd, &contacts, 256, 0);
                printf("\n%s\n", contacts);
                bzero(name, 256);
                scanf("%s", name);
                send(sockfd, &name, strlen(name), 0);
                if (strcmp(name, "<-") == 0) {
                    break;
                }
                bzero(messag, 256);
                recv(sockfd, &messag, 256, 0);
                if (strlen(messag)==0){
                    char non[]="none message";
                    strcpy(messag,non);
                }
                printf("%s\n", messag);
                while (1) {
                    char buffer[256];
                    bzero(buffer, 256);
                    fgets(buffer, 255, stdin);
                    strcpy(buffertmp, buffer);
                    buffertmp[strlen(buffertmp) - 1] = 0;
                    n = write(sockfd, buffer, strlen(buffer));
                    if (n < 0)
                        error("ERROR writing to socket");
            if (strcmp(buffertmp, "//") == 0) {
                exi=1;
                clos=8;
                break;
            }
                    bzero(buffer, 256);
                    n = read(sockfd, buffer, 255);
                    if (n < 0)
                        error("ERROR reading from socket");
                    printf("%s\n", buffer);
                    if (strcmp(buffertmp, "<-") == 0) {
                        exi = 1;
                        break;
                    }
                }
                if (exi == 1) {
                    break;
                }
            }
            if (choice==2){
                send(sockfd,&Username,strlen(Username),0);
                while (1) {
                    group_start(sockfd);
                    while (1) {
                        exi=0;
                        if (strcmp(choice_gp, "<-") == 0) {
                            exi = 7;
                            break;
                        }
                        if (strcmp(choice_gp, "1") == 0) {
                            printf("please enter your group name\n\n");
                            bzero(group_name, 256);
                            scanf("%s", group_name);
                            write(sockfd, &group_name, strlen(group_name));
                            if (strcmp(group_name, "<-") == 0) {
                                exi = 9;
                                break;
                            }
                            break;
                        }
                        if (strcmp(choice_gp, "2") == 0) {
                            bzero(group_names, 256);
                            read(sockfd, &group_names, 256);
                            printf("%s\n", group_names);
                            bzero(which_gp, 256);
                            scanf("%s", which_gp);
                            write(sockfd, &which_gp, strlen(which_gp));
                            if (strcmp(which_gp, "<-") == 0) {
                                exi=9;
                                break;
                            }
                            bzero(gp_messages, 256);
                            read(sockfd, &gp_messages, 256);
                            printf("%s\n", gp_messages);
                            while (1) {
                                char buffer[256];
                                bzero(buffer, 256);
                                fgets(buffer, 255, stdin);
                                strcpy(buffertmp, buffer);
                                buffertmp[strlen(buffertmp) - 1] = 0;
                                n = write(sockfd, buffer, strlen(buffer));
                                if (n < 0)
                                    error("ERROR writing to socket");
                                if (strcmp(buffertmp, "//") == 0) {
                                    exi = 1;
                                    clos = 8;
                                    break;
                                }
                                bzero(buffer, 256);
                                n = read(sockfd, buffer, 255);
                                if (n < 0)
                                    error("ERROR reading from socket");
                                printf("%s\n", buffer);
                                if (strcmp(buffertmp, "<-") == 0) {
                                    exi = 1;
                                    break;
                                }
                            }
                            if (exi == 1 ) {
                                break;
                            }
                        }
                        if (exi == 1 ) {
                            break;
                        }
                    }
                    if (exi==1 || exi==7 ){
                        break;
                    }
                }
            }
            if (exi == 1||exi==7 ) {
                break;
            }
        }
        if (clos==8 ){
            break;
        }
    }

//    recv(sockfd,&contacts,256,0);
//    printf("%s\n",contacts);
//    bzero(name,256);
//    scanf("%s",name);
//    send(sockfd,&name,strlen(name),0);
//    bzero(messag,256);
//    recv(sockfd,&messag,256,0);
//    printf("%s\n",messag);
//        char buffertmp[256];
//        while (1) {
//            bzero(buffer, 256);
//            fgets(buffer, 255, stdin);
//            strcpy(buffertmp, buffer);
//            buffertmp[strlen(buffertmp) - 1] = 0;
//            n = write(sockfd, buffer, strlen(buffer));
//            if (n < 0)
//                error("ERROR writing to socket");
////            if (strcmp(buffertmp, "//") == 0) {
////                close(sockfd);
////            }
//            bzero(buffer, 256);
//            n = read(sockfd, buffer, 255);
//            if (n < 0)
//                error("ERROR reading from socket");
//            printf("%s\n", buffer);
//        }

        return 0;
}
