#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
int clos;
char choice_gp[256];
FILE* Name;
FILE* groups;
FILE* gp_names;
char which_gp[256];
char gp_messages[256];
char group_names[256];
char group_name[256];
char nam[256];
char use[256];
char us[256];
int exi;
FILE* file;
int op;
int n;
char message[256];
FILE* user;
FILE* contact;
int hoi;
char contacts[256];
char name[256];
char username_password[256];
char point[200];
char Username[100];
char Password[100];
int y;
int u;
char login[256];
char U[100];
char P[100];
int which;
int result;
int num=1;
int nums;
char* User;
char mess[256];
char Pass[100];
char info[256];
char buff [256];
char uss[256];
int choice;
void first_page(int newsocketfd){
    recv(newsocketfd,&choice, sizeof(int),0);
}
void group_start(int newsocketfd){
    bzero(choice_gp,256);
    recv(newsocketfd, &choice_gp, sizeof(int), 0);
}
//void chats(int newsocketfd){
//            contact=fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/contact.txt", "r");
//        fread(&contacts, sizeof(char),256,contact);
//        send(newsocketfd,&contacts,strlen(contacts),0);
//        fclose(contact);
//        memset(User, 0,sizeof(char)*256);
//        memset(Name, 0,sizeof(char)*256);
//        recv(newsocketfd,&name,256,0);
//        strcpy(User, name);
//        if (User[strlen(User)-1]=='\n'){
//            User[strlen(User)-1]=0;
//        }
//        strcat(User, ".txt");
//        user = fopen(User, "r");
//        memset(message, 0,sizeof(char)*256);
//        fread(&message, sizeof(char),256,user);
//        send(newsocketfd,message,strlen(message),0);
//    while (1) {
//        bzero(buffer, sizeof(buffer));
//        // get user message
//        n = read(newsocketfd, buffer, 256);
//        if (n < 0)
//            error("Could not read from client");
////            printf("From clinet  : %s", buffer);
////            // echo back
//        char echoString[] = "Got your message";
//        n = write(newsocketfd, echoString, strlen(echoString));
//        if (n < 0)
//            error("Could not echo back to user");
//        if (strcmp(buffer, "//\n") == 0) {
////                    close(newsocketfd);
//            break;
//        }
//        user = fopen(User, "a");
//        fprintf(user, "%s", buffer);
//        fclose(user);
//    }
//}
char x[256];
char t[256];
void lines(int newsocketfd){
    file=fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/file.txt", "r");
    for (int i=0;i<200;i++) {
        fread(point, sizeof(char), 200, file);
        if (point[i-1]=='\n'&& point[i]=='\n'){
            break;
        }
    }
    fclose(file);
    send(newsocketfd,&point,strlen(point),0);
}
void take_username(char info[256]){
    int u=1;
    bzero(Username,100);
    while(info[u]!='\n'){
        Username[u-1]=info[u];
        u+=1;
    }
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: Port Number");
        exit(1);
    }
    int sockfd, newsocketfd, clinetlen, portnumber;
    struct sockaddr_in serverAddress, clientAddress;

    // zero out serverAddress
    bzero((char *) &serverAddress, sizeof(serverAddress));

    // port number
    portnumber = atoi(argv[1]);

    // setup server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portnumber);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // BIND
    int bindStatus = bind(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
    if (bindStatus < 0) {
        error("Could not bind");
    }

    // listen

    while (1) {

        listen(sockfd, 5);   // cannot fail so no error checking

        // accept client connection
        clinetlen = sizeof(clientAddress);
        newsocketfd = accept(sockfd,
                             (struct sockaddr *) &clientAddress, (socklen_t *) &clinetlen);
        if (newsocketfd < 0) {
            error("Could not accept clinet socket");
        }
        while (1) {
            recv(newsocketfd, &which, sizeof(which), 0);
            if (which == 1) {
                lines(newsocketfd);
                recv(newsocketfd, &result, sizeof(int), 0);
                if (result == 2) {
                    int results;
                    recv(newsocketfd, &results, sizeof(int), 0);
                    if (results == 5) {
                        char logged[] = "you logged in !\n";
                        send(newsocketfd, &logged, strlen(logged), 0);
                        bzero(U, sizeof(char) * 100);
                        recv(newsocketfd, &U, 100, 0);
                        //           printf("%s",U);
                        User = (char *) alloca(sizeof(char) * 256);
                        memset(User, 0, sizeof(char) * 256);
                        strcpy(User, U);
                        //         User[strlen(User) - 1]=0;
                        strcat(User, ".txt");
                        break;
                    }
                }
            }
            if (which == 2) {
                file = fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/file.txt", "a");
                bzero(info, sizeof(info));
                recv(newsocketfd, &info, 256, 0);
                fprintf(file, "%s\n", info);
                fclose(file);
                take_username(info);
                User = (char *) alloca(sizeof(char) * 256);
                memset(User, 0, sizeof(char) * 256);
                strcpy(User, Username);
                if (User[strlen(User) - 1] == '\n') {
                    User[strlen(User) - 1] = 0;
                }
                strcat(User, ".txt");
                user = fopen(User, "w");
                fclose(user);
                contact = fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/contact.txt", "a");
                printf("%s", Username);
                fprintf(contact, "%s\n", Username);
                fclose(contact);
            }
        }
        while (1) {
            exi=0;
            while (1) {
                first_page(newsocketfd);
                if (choice == 1) {
                    bzero(us,256);
                    bzero(use,256);
                    recv(newsocketfd,&us,256,0);
                    strcpy(use,us);
                    contact = fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/contact.txt", "r");
                    bzero(contacts, 256);
                    fread(&contacts, sizeof(char), 256, contact);
                    send(newsocketfd, &contacts, strlen(contacts), 0);
                    fclose(contact);
                    bzero(name, 256);
                    recv(newsocketfd, &name, 256, 0);
                    bzero(nam,256);
                    strcpy(nam,name);
                    if (strcmp(name, "<-") == 0) {
                        break;
                    }
                    user=fopen(us,"r");
                    if (name[strlen(name)-1]=='\n'){
                        name[strlen(name)-1]=0;
                    }
                    strcat(name,use);
                    strcat(name, ".txt");
                    Name=fopen(name,"a+");
                    strcat(us,nam);
                    strcat(us, ".txt");
                    user=fopen(us,"a+");
                    fclose(Name);
                    fclose(user);
                    user=fopen(us,"r");
                    bzero(message, 256);
                    fread(&message, sizeof(char), 256, user);
                    fclose(user);
                    if (strlen(message)==0){
                        char non[]="none message";
                        strcpy(message,non);
                    }
                    send(newsocketfd, message, strlen(message), 0);
                    fclose(user);
                    while (1) {
                        exi=0;
                        char buffer[256];
                        bzero(buffer, sizeof(buffer));
                        // get user message
                        n = read(newsocketfd, buffer, 256);
                        if (n < 0)
                            error("Could not read from client");
//            printf("From clinet  : %s", buffer);
//            // echo back
                        char echoString[] = "Got your message";
                        n = write(newsocketfd, echoString, strlen(echoString));
                        if (n < 0)
                            error("Could not echo back to user");
                        if (strcmp(buffer, "//\n") == 0) {
                            close(newsocketfd);
                            exi=1;
                            clos=8;
                            break;
                        }
                            if (strcmp(buffer, "<-\n") == 0) {
 //                           close(newsocketfd);
                                exi = 1;
                                break;
                            }
                        Name=fopen(name,"a");
                            user = fopen(us,"a");
                            fprintf(user, "%s : %s",use, buffer);
                        fprintf(Name, "%s : %s",use, buffer);
                            fclose(user);
                        fclose(Name);
                        }
                    if (exi == 1) {
                        break;
                    }
                    }
                if (choice==2){
                    recv(newsocketfd,&uss,256,0);
                    while (1) {
                        group_start(newsocketfd);
                        while (1) {
                            exi=0;
                            if (strcmp(choice_gp, "<-") == 0) {
                                exi=7;
                                break;
                            }
                            if (strcmp(choice_gp, "1") == 0) {
                                bzero(group_name, 256);
                             //   recv(newsocketfd, &group_name, 256, 0);
                                read(newsocketfd,&group_name,256);
                                if (strcmp(group_name, "<-") == 0) {
                                    exi=9;
                                    break;
                                }
                                gp_names = fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/group_names.txt", "a");
                                fprintf(gp_names, "%s\n", group_name);
                                fclose(gp_names);
                                strcat(group_name, ".txt");
                                groups = fopen(group_name, "w");
                                fclose(groups);
                                break;
                            }
                            if (strcmp(choice_gp, "2") == 0) {
                                gp_names = fopen("/Users/aminhasanzadehmoghadam/Desktop/Socket/group_names.txt", "r");
                                bzero(group_names, 256);
                                fread(&group_names, sizeof(char), 256, gp_names);
                                write(newsocketfd, &group_names, strlen(group_names));
                                fclose(gp_names);
                                bzero(which_gp, 256);
                             //   recv(newsocketfd, &which_gp, 256, 0);
                                read(newsocketfd, &which_gp, 256);
                                if (strcmp(which_gp, "<-") == 0) {
                                    exi=9;
                                    break;
                                }
                                if (which_gp[strlen(which_gp)-1]=='\n'){
                                    which_gp[strlen(which_gp)-1]=0;
                                }
                                strcat(which_gp, ".txt");
                                printf("%s\n",which_gp);
                                groups = fopen(which_gp, "r");
                                bzero(gp_messages, 256);
                                fread(&gp_messages, sizeof(char), 256, groups);
                                if (strlen(gp_messages) == 0) {
                                    char none_message[] = "none message";
                                    strcpy(gp_messages, none_message);
                                }
                                write(newsocketfd, &gp_messages, strlen(gp_messages));
                                while (1) {
                                    exi = 0;
                                    char buffer[256];
                                    bzero(buffer, sizeof(buffer));
                                    // get user message
                                    n = read(newsocketfd, buffer, 256);
                                    if (n < 0)
                                        error("Could not read from client");
//            printf("From clinet  : %s", buffer);
//            // echo back
                                    char echoString[] = "Got your message";
                                    n = write(newsocketfd, echoString, strlen(echoString));
                                    if (n < 0)
                                        error("Could not echo back to user");
                                    if (strcmp(buffer, "//\n") == 0) {
                                        close(newsocketfd);
                                        exi = 1;
                                        clos = 8;
                                        break;
                                    }
                                    if (strcmp(buffer, "<-\n") == 0) {
                                        //                           close(newsocketfd);
                                        exi = 1;
                                        break;
                                    }
                                    groups = fopen(group_name, "a");
                                    fprintf(groups, "%s : %s", uss, buffer);
                                    fclose(groups);
                                }
                                if (exi == 1  ) {
                                    break;
                                }
                            }
                            if (exi == 1 ) {
                                break;
                            }
                        }
                        if (exi==1 || exi==7){
                            break;
                        }
                    }
                }
                if (exi == 1||exi==7 ) {
                    break;
                }
                }
            if (clos==8){
                break;
            }
            }

//            while (1) {
//                char buffer[256];
//                bzero(buffer, sizeof(buffer));
//                // get user message
//                n = read(newsocketfd, buffer, 256);
//                if (n < 0)
//                    error("Could not read from client");
////            printf("From clinet  : %s", buffer);
////            // echo back
//                char echoString[] = "Got your message";
//                n = write(newsocketfd, echoString, strlen(echoString));
//                if (n < 0)
//                    error("Could not echo back to user");
//                if (strcmp(buffer, "//\n") == 0) {
////                    close(newsocketfd);
//                    break;
//                }
//                user = fopen(User, "a");
//                fprintf(user, "%s", buffer);
//                fclose(user);
//           }
        }

        return 0;

}
