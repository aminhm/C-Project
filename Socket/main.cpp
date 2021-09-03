#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* 1-create an acount
 * 2-log in
 *
 *
 *
 */
int main(){
    char what;
    scanf("%c",&what);
    if (what=='1'){
        printf("Please Enter Your Username : ");
        char user;
        scanf("%s",&user);
        printf("Please Enter Your Password : ");
        char password;
        scanf("%s",&password);
    }
    return 0;
}