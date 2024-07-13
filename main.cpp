#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <SQLAPI.h>

int main(int, char**){
    printf("Hello, from login_registerkd!\n");
    SAConnection con;

    printf("We are connected 3!\n");
        try {
        con.Connect(_TSA("austinperrine"), _TSA("austinperrine"), _TSA("my_password"), SA_PostgreSQL_Client);
        printf("We are connected!\n");

        /*
        The rest of the tutorial goes here!
        */
        
        con.Disconnect();
        printf("We are disconnected!\n");
    }
    catch(SAException &x) {
        printf("%s\n", x.ErrText().GetMultiByteChars());
        con.Rollback();
        printf("%s\n", x.ErrText().GetMultiByteChars());
    }
    
 printf("We are outs!!!!\n");
    return 0;
}