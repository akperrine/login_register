#include <iostream>
#include <stdio.h>
#include <libpq-fe.h>
#include <string>
using std::string;

int main(int argc, char* argv[]){
    printf("Hello, from login_registerkd!\n");
    char *conninfo = "dbname=university user=austinperrine password=your_password host=localhost port=5432";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Error connecting to database: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    } else {
        std::cout<< "Connection to database succeeded.\n";
    }

    // We have successfully established a connection to the database server
    printf("Connection Established\n");
    printf("Port: %s\n", PQport(conn));
    printf("Host: %s\n", PQhost(conn));
    printf("DBName: %s\n", PQdb(conn));

    bool on = true;
    bool home = true;
    while (on) {
        int choice;
        if (home) {
        std::cout << "Welcome to University Registry UI: How can we help?:\nLogin: press 1 \nRegister: press 2\nUpdate: press 3\nDelete: press 4\nLog Off: press 5\n";
        std::cin >> choice;
        }

        switch(choice) {
        case 1: 
            printf("option 1: Login");
            home = false;
            break;
        case 2: 
            printf("option 2: Register");
            break;
        case 3: 
            printf("option 3: Update");
            break;
        case 4: 
            printf("option 4: Delete");
            break;
        case 5:
            printf("option 5: Log off... bye bye");
            on = false;
            break;
        }
    }

    string username;
    std::cout << "Enter your username";
    std::cin >> username;

    string password;
    std::cout << "Enter your password";
    std::cin >> password;
    string insertCmd = "INSERT INTO users (username, password) VALUES('"+ username + "', '" + password + "');";
    PGresult *res = PQexec(conn, insertCmd.c_str());
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cout << "Insert into user table failed: " << PQresultErrorMessage(res) << '\n';
        exit(1);
    }



    // Close the connection and free the memory
    PQfinish(conn);
    printf("We are outs!!!!\n");
    return 0;
}