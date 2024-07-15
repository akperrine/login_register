#include <iostream>
#include <stdio.h>
#include <libpq-fe.h>

int main(int argc, char* argv[]){
    printf("Hello, from login_registerkd!\n");
    char *conninfo = "dbname=austinperrine user=austinperrine password=your_password host=localhost port=5432";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Error connecting to database: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    // We have successfully established a connection to the database server
    printf("Connection Established\n");
    printf("Port: %s\n", PQport(conn));
    printf("Host: %s\n", PQhost(conn));
    printf("DBName: %s\n", PQdb(conn));

    // Close the connection and free the memory
    PQfinish(conn);
    printf("We are outs!!!!\n");
    return 0;
}