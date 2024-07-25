#include <iostream>
#include <stdio.h>
#include <libpq-fe.h>
#include <string>
using std::string;

struct Credentials {
    string username;
    string password;
};

struct User {
    string id;
    string username;
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

Credentials requestUpdateCredentials() {
    string username;
    std::cout << "Enter your new username: ";
    std::cin >> username;

    string password;
    std::cout << "Enter your new password: ";
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

User *getUser(PGconn *conn, Credentials credentials) {
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
        int idField;
        int passwordField;
        int usernameField;
        for (int i = 0; i < PQnfields(res); i++) {
            std::cout << PQfname(res, i) << '\n';

            if (string(PQfname(res, i)) == "password") {
                passwordField = i;
                printf("passoword found");
            } else if (string(PQfname(res, i)) == "id") {
                idField = i;
                printf("id found");
            } else if (string(PQfname(res, i)) == "username") {
                usernameField = i;
                printf("username found");
            };
        }
        if (string(PQgetvalue(res, 0, passwordField)) != credentials.password){
            std::cout << "Wrong password. Please try again \n\n\n";
            return nullptr;
        } else {
            User user {};
            for (int i = 0; i < PQntuples(res); i++) {
                        for (int j = 0; j < PQnfields(res); j++) {
                            std::cout << PQgetvalue(res, i, j) << "   ";
                            if (j == idField) {
                                 user.id = string(PQgetvalue(res, i, j));
                            } else if (j == usernameField) {
                                user.username = string(PQgetvalue(res,i, j));
                            }
                            // if (string(PQgetvalue(res, i, j)) == "id") {
                            //     user.id = string(PQgetvalue(res, i, j));
                            // } else if (string(PQgetvalue(res, i, j)) == "username") {
                            //     user.id = string(PQgetvalue(res, i, j));
                            // }
                        }
                std::cout << std::endl;
            }
            std::cout << user.id.c_str() << " " << user.username << '\n';
            if (user.id == "" || user.username == "") {
                printf("Not initialized\n");
                return nullptr;
            } else {
                return &user;
            }
        }
       
    }

}

void updateUser(PGconn *conn) {
    Credentials updateCredentials = requestCredentials();
    Credentials newCredentials = requestUpdateCredentials();
    printf(newCredentials.username.c_str());
    User *user = getUser(conn, updateCredentials);
    user->username = newCredentials.username;
    if (user == nullptr) {
        printf("undeclared");
    } else {
        string username = user->username;
        printf(user->username.c_str());
        string userId = user->id;
        string updateQuery = "UPDATE users SET username = '"+ username +"' WHERE id = '" + userId + "';\n";
        std::cout<< updateQuery << '\n';

        PGresult *res = PQexec(conn, updateQuery.c_str()); 

        ExecStatusType status = PQresultStatus(res);
        printf("Execution status: %d\n", status);

        if (PQresultStatus(res) == PGRES_COMMAND_OK) {
            std::cout << "Username was succesfully updated\n";
           
        } else {
             std::cout << "Retrieval of user from users failed: " << PQresultErrorMessage(res) << " end\n";
            exit(1);
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
        {
            printf("option 1: Login");
            Credentials credentials = requestCredentials();
            getUser(conn, credentials);
            break;
        }
        case 2: 
            printf("option 2: Register");
            insertUser(conn);
            break;
        case 3: 
        {
            printf("option 3: Update");
            updateUser(conn);
            break;
        }    
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

