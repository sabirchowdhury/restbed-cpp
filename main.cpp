#include <memory>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <restbed>
#include <nlohmann/json.hpp>
#include <mysql\jdbc.h>

using json = nlohmann::json;

using namespace std;
using namespace restbed;

void post_method_handler(const shared_ptr<Session> session)
{
    const auto request = session->get_request();

    int content_length = request->get_header("Content-Length", 0);

    session->fetch(content_length, [](const shared_ptr<Session> session, const Bytes &body)
                   {
        fprintf( stdout, "\nBody size and data::\n%.*s\n", ( int ) body.size( ), body.data( ), "\n");

        // "%.*s\n"
        if (body.data( )) {
        json jsonData = json::parse(body.data());
        
        fprintf( stdout, "\n\nSQL command string:\n");
        fprintf( stdout, ((string) jsonData["sqlCommand"]).c_str());

        fprintf( stdout, "\n\nfull json string:\n");
        fprintf( stdout, jsonData.dump().c_str());



        if (((string) jsonData["sqlCommand"]) != "") {
            try {
                sql::Driver *driver;
                sql::Connection *con;
                sql::Statement *stmt;
                // sql::ResultSet *res;
                // sql::ResultSetMetaData *res_meta ;
                cout << "vars created successfully" << endl;

                /* Create a connection */
                driver = get_driver_instance();
                cout << "Driver instance created" << endl;
                con = driver->connect("tcp://127.0.0.1:3306", "root", "password");
                cout << "Successful connection" << endl;
                /* Connect to the MySQL test database */
                con->setSchema("mysqldb");
                cout << "schema set" << endl;
                stmt = con->createStatement();
                cout << "statement created" << endl;
                // res = stmt->executeQuery("SELECT * FROM Persons");
                stmt->execute(((string) jsonData["sqlCommand"]));
                cout << "statement executed" << endl;

                // res_meta = res -> getMetaData();
                // int columns = res_meta -> getColumnCount();
                // cout << "res executed" << endl;

                // //Loop for each row
                // while (res->next()) {
                //     /* Access column data by index, 1-indexed*/
                //     for (int i = 1; i <= columns; i++) {
                //     cout << res->getString(i) << "|" ;
                //     }
                //     cout << endl;
                // }

                cout << "data read" << endl;

                // delete res;
                // cout << "data read" << endl;

                delete stmt;
                cout << "clean stmt" << endl;

                delete con;

                cout << "clean con" << endl;


            } catch (sql::SQLException &e) {
                cout << "# ERR: SQLException in " << __FILE__;
                //   cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
                cout << "# ERR: " << e.what();
                cout << " (MySQL error code: " << e.getErrorCode();
                cout << ", SQLState: " << e.getSQLState() << " )" << endl;
            }
        };
        }
        
        cout << endl;

        session->close( OK, "Request recieved!", { { "Content-Length", "17" } } ); });
}

void get_method_handler(const shared_ptr<Session> session)
{
    session->close(OK, "get request!", {{"Content-Length", "12"}});
}

int main(const int, const char **)
{
    auto settings = make_shared<Settings>();
    settings->set_port(8080);
    settings->set_default_header("Connection", "close");

    auto resource = make_shared<Resource>();
    resource->set_path("/getsqldata");
    resource->set_method_handler("POST", post_method_handler);
    resource->set_method_handler("GET", get_method_handler);

    // loop
    Service service;
    service.publish(resource);

    service.start(settings);

    return EXIT_SUCCESS;
}