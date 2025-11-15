#include "perpustakaan.h"

//ini fungsi untuk login admin
int loginAdmin() {
    login log;
    FILE *f;
    f = fopen("data_login.txt", "r");
    if (!f){
        printf("File tidak ditemukan. Membuat akun Admin default...\n");
        FILE *fa = fopen("data_login.txt", "w");
        fprintf(fa, "admin|1234\n");
        fclose(fa);
        f = fopen("data_login.txt", "r");
    }

    char username[50], password[50], line[256];

    printf("Username: "); 
    scanf ("%s", username);

    printf("Password: "); 
    scanf ("%s", password);
    
    while (fgets(line, sizeof(line), f)){
        int n = sscanf(line, "%49[^|] %49s", log.username, log.password);
        if (n != 2){
            continue;
        }

        if (strcmp(username, log.username) == 0 && strcmp(password, log.password) == 0){
            fclose(f);
            printf("Login berhasil! \n");
            return 1;    
        }
    }
    fclose(f);
    return 0;
}