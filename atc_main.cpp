#include <iostream>
#include <stdexcept>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>  // Include for sql::Statement
#include <cppconn/resultset.h>  // Include for sql::ResultSet

int main() {
    try {
        // Create a connection to the database
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        // Initialize the driver
        driver = sql::mysql::get_mysql_driver_instance();

        // Establish the connection
        con = driver->connect("tcp://127.0.0.1:3306", "root", "your_password"); // Change to your username and password

        // Select the database
        con->setSchema("AirTrafficControl");

        // Create a statement
        sql::Statement *stmt;
        stmt = con->createStatement();

        // Execute a query to insert a new plane record
        stmt->execute("INSERT INTO Planes (flight_number, altitude, speed, destination) "
                      "VALUES ('AA123', 35000, 500, 'New York')");

        // Execute a query to retrieve plane records
        sql::ResultSet *res;
        res = stmt->executeQuery("SELECT * FROM Planes");

        // Print out the results
        while (res->next()) {
            std::cout << "Plane ID: " << res->getInt("plane_id") << std::endl;
            std::cout << "Flight Number: " << res->getString("flight_number") << std::endl;
            std::cout << "Altitude: " << res->getInt("altitude") << std::endl;
            std::cout << "Speed: " << res->getInt("speed") << std::endl;
            std::cout << "Destination: " << res->getString("destination") << std::endl;
            std::cout << "-----------------" << std::endl;
        }

        // Clean up
        delete res;
        delete stmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "Error: SQLException" << std::endl;
        std::cerr << "Error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        std::cerr << "Error message: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (std::exception &e) {
        std::cerr << "Error: std::exception" << std::endl;
        std::cerr << "Error message: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
