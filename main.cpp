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