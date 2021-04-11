#include <stdio.h>
#include <stdlib.h>

int main() {

    int opt = 0;

    printf("Welcome! \nChoose an option from the menu bellow:\n");
    printf("1 - Login\n");
    printf("2 - Create new user\n");
    printf("3 - Quit\n");

    scanf("%d", &opt);

    switch(opt) {
        case 1:
            //login();
            printf("Loggin in...\n");
            break;
        case 2:
            //newUser();
            printf("Creating new user...\n");
            break;
        case 3:
            printf("Quiting...");
            exit(0);                        // 0 indicates sucessfull termination
            break;
    }

    return 0;
}

void login() {}

void newUser() {}