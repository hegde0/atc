#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

// Base class for password management
class PasswordManager {
public:
    PasswordManager(const string& correctPassword) : correctPassword(correctPassword) {}

    // Function to check if the entered password is correct
    bool authenticate() {
        string enteredPassword;
        cout << "Enter the password: ";
        cin >> enteredPassword;
        return enteredPassword == correctPassword;
    }

private:
    string correctPassword;
};

// Base class Aircraft
class Aircraft {
public:
    Aircraft(const string& aircraftType, int numSeats, const string& filename)
        : type(aircraftType), seats(numSeats), filename(filename) {}

    virtual void readDetailsFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            file >> type >> seats >> ids;
            file.close();
        } else {
            cerr << "Error: Unable to open file " << filename << endl;
            type = "Unknown";
            seats = 0;
            ids = "Unknown";
        }
    }

    tuple<string, int, string> getDetails() const {
        return make_tuple(type, seats, ids);
    }

    void displayDetails() const {
        cout << "Aircraft Type: " << type << endl;
        cout << "Number of Seats: " << seats << endl;
        cout << "Aircraft IDs: " << ids << endl;
    }

protected:
    string type;
    int seats;
    string ids;
    string filename;
};

class IndigoAircraft : public Aircraft {
public:
    IndigoAircraft(const string& filename) : Aircraft("Indigo Aircraft", 0, filename) {
        readDetailsFromFile();
    }
};

class AirIndiaAircraft : public Aircraft {
public:
    AirIndiaAircraft(const string& filename) : Aircraft("Air India Aircraft", 0, filename) {
        readDetailsFromFile();
    }
};

class VistaraAircraft : public Aircraft {
public:
    VistaraAircraft(const string& filename) : Aircraft("Vistara Aircraft", 0, filename) {
        readDetailsFromFile();
    }
};

// Base class Airport
class Airport {
public:
    Airport(const string& airportName, const string& filename) : name(airportName), filename(filename) {}

    virtual void readDetailsFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            file >> runways >> weatherForecast >> capacity;
            file.close();
        } else {
            cerr << "Error: Unable to open file " << filename << endl;
            runways = 0;
            weatherForecast = "Unknown";
            capacity = 0;
        }
    }

    tuple<int, string, int> getDetails() const {
        return make_tuple(runways, weatherForecast, capacity);
    }

    void displayDetails() const {
        cout << "Airport Name: " << name << endl;
        cout << "Runways: " << runways << endl;
        cout << "Weather Forecast: " << weatherForecast << endl;
        cout << "Capacity: " << capacity << " flights at the same time" << endl;
        if(weatherForecast == "cloudy")
        {
         cout << "AS Weather Forecast is " << weatherForecast << "The flights which are landing are redirected for go Around and Departuture airplanes are held at pause \n Please check For updates"<< endl;  
         exit(0); 
        }
    }

protected:
    string name;
    int runways;
    string weatherForecast;
    int capacity;
    string filename;
};

class MumbaiAirport : public Airport {
public:
    MumbaiAirport(const string& filename) : Airport("Mumbai Airport", filename) {
        readDetailsFromFile();
    }
};

class DelhiAirport : public Airport {
public:
    DelhiAirport(const string& filename) : Airport("Delhi Airport", filename) {
        readDetailsFromFile();
    }
};

class BangaloreAirport : public Airport {
public:
    BangaloreAirport(const string& filename) : Airport("Bangalore Airport", filename) {
        readDetailsFromFile();
    }
};

class Plane {
public:
    Plane(int id, bool isDeparture, int time) : id(id), isDeparture(isDeparture), time(time) {}

    int getId() const {
        return id;
    }

    bool isDeparturePlane() const {
        return isDeparture;
    }

    int getTime() const {
        return time;
    }

private:
    int id;
    bool isDeparture;
    int time;
};

class ATC {
public:
    void addPlane(const Plane& plane) {
        planes.push_back(plane);
        if (plane.isDeparturePlane()) {
            cout << "Departure Plane " << plane.getId() << " scheduled for takeoff at time " << plane.getTime() << ".\n";
        } else {
            cout << "Arrival Plane " << plane.getId() << " scheduled for landing at time " << plane.getTime() << ".\n";
        }
    }

    void printSchedule() const {
        cout << "\nCurrent Schedule:\n";
        for (const auto& plane : planes) {
            if (plane.isDeparturePlane()) {
                cout << "Departure Plane " << plane.getId() << " at time " << plane.getTime() << ".\n";
            } else {
                cout << "Arrival Plane " << plane.getId() << " at time " << plane.getTime() << ".\n";
            }
        }
    }

    void processPlanes() {
        sort(planes.begin(), planes.end(), [](const Plane& a, const Plane& b) {
            if (a.getTime() != b.getTime()) {
                return a.getTime() < b.getTime();
            } else {
                cout << "As the arrival time and departure time are conflicting, the runway of flight " << a.getId() << " arriving is shifted to the next runway.\n";
                return a.isDeparturePlane() && !b.isDeparturePlane();
            }
        });

        for (const auto& plane : planes) {
            if (plane.isDeparturePlane()) {
                cout << "Departure Plane " << plane.getId() << " cleared for takeoff at time " << plane.getTime() << ".\n";
            } else {
                cout << "Arrival Plane " << plane.getId() << " cleared for landing at time " << plane.getTime() << ".\n";
            }
        }
        planes.clear();
    }

private:
    vector<Plane> planes;
};

int main() {
    // Password for authentication
    string correctPassword = "rohit";

    // Create an instance of PasswordManager
    PasswordManager passwordManager(correctPassword);

    // Check if the entered password is correct
    if (!passwordManager.authenticate()) {
        cout << "Incorrect password. Exiting the program. Goodbye!\n";
        return 0; // Exit the program if the password is incorrect
    }

    // Proceed with the program if the password is correct

    // Provide filenames for each airport
    string mumbaiFilename = "mumbai.txt";
    string delhiFilename = "delhi.txt";
    string bangaloreFilename = "bangalore.txt";

    // Create instances of each airport subclass with user-defined filenames
    MumbaiAirport mumbai(mumbaiFilename);
    DelhiAirport delhi(delhiFilename);
    BangaloreAirport bangalore(bangaloreFilename);

    // Provide filenames for each airline's aircraft
    string indigoFilename = "indigo.txt";
    string airIndiaFilename = "airindia.txt";
    string vistaraFilename = "vistara.txt";

    // Create instances of each airline's aircraft subclass with user-defined filenames
    IndigoAircraft indigo(indigoFilename);
    AirIndiaAircraft airIndia(airIndiaFilename);
    VistaraAircraft vistara(vistaraFilename);

    // Plane scheduling
    ATC atc;

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Get details of all airports\n";
        cout << "2. Get details of all airplanes\n";
        cout << "3. Schedule planes\n";
        cout << "4. Print the schedule\n";
        cout << "5. Process the scheduling\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nDetails of Mumbai Airport:\n";
                mumbai.displayDetails();

                cout << "\nDetails of Delhi Airport:\n";
                delhi.displayDetails();

                cout << "\nDetails of Bangalore Airport:\n";
                bangalore.displayDetails();
                break;

            case 2:
                cout << "\nDetails of Indigo Aircraft:\n";
                indigo.displayDetails();

                cout << "\nDetails of Air India Aircraft:\n";
                airIndia.displayDetails();

                cout << "\nDetails of Vistara Aircraft:\n";
                vistara.displayDetails();
                break;

            case 3:
                int id, time;
                bool isDeparture;
                cout << "Enter plane ID: ";
                cin >> id;
                cout << "Is it a departure plane? (1 for yes, 0 for no): ";
                cin >> isDeparture;
                cout << "Enter time: ";
                cin >> time;
                atc.addPlane(Plane(id, isDeparture, time));
                break;

            case 4:
                atc.printSchedule();
                break;

            case 5:
                atc.processPlanes();
                break;

            case 6:
                cout << "Exiting the program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
