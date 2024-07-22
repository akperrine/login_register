#include <iostream>
#include <stdio.h>
#include <libpq-fe.h>
#include <string>
using std::string;

struct Credentials {
    string username;
    string password;
};

Credentials requestCredentials() {
    string username;
    std::cout << "Enter your username: ";
    std::cin >> username;

    string password;
    std::cout << "Enter your password: ";
    std::cin >> password;

    return Credentials{username, password};
}

void insertUser(PGconn *conn) {
    Credentials credentials = requestCredentials();
    string insertQuery = "INSERT INTO users (username, password) VALUES('"+ credentials.username + "', '" + credentials.password + "');";

 
    PGresult *res = PQexec(conn, insertQuery.c_str());
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cout << "Insert into user table failed: " << PQresultErrorMessage(res) << '\n';
        exit(1);
    } else {
        std::cout << "User successfully registered into the database!\n";
    }
}

void getUser(PGconn *conn) {
    Credentials credentials = requestCredentials();
    string selectQuery = "SELECT * FROM users WHERE username = '"+ credentials.username +"';\n";
    std::cout << selectQuery.c_str() << '\n';
    PGresult *res = PQexec(conn, selectQuery.c_str());
    std::cout<<"Working??\n";
    
    ExecStatusType status = PQresultStatus(res);
    printf("Execution status: %d\n", status);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cout << "Retrieval of user from users failed: " << PQresultErrorMessage(res) << " end\n";
        exit(1);
    } else {
        printf("works\n");
        for (int i = 0; i < PQnfields(res); i++) {
            std::cout << PQfname(res, i) << '\n';
        }
        for (int i = 0; i < PQntuples(res); i++) {
            for (int j = 0; j < PQnfields(res); j++) {
                std::cout << PQgetvalue(res, i, j) << "   ";
            }
      std::cout << std::endl;
    }
    }

}


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
        std::cout << "Welcome to University Registry UI: How can we help?:\nLogin: press 1 \nRegister: press 2\nUpdate: press 3\nDelete: press 4\nLog Off: press 5\n";
        std::cin >> choice;

        switch(choice) {
        case 1: 
            printf("option 1: Login");
            getUser(conn);
            break;
        case 2: 
            printf("option 2: Register");
            insertUser(conn);
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
    // Close the connection and free the memory
    PQfinish(conn);
    printf("We are outs!!!!\n");
    return 0;
}

