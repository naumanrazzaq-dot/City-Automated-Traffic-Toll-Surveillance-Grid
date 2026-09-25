#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Abstract Class
class TrafficCheckpoint {
protected:
    string checkpointID;
    int totalVehiclesPassed;

public:
    static int activeCheckpoints;
    static double totalRevenueCollectedPKR;

    TrafficCheckpoint(string id, int vehicles)
        : checkpointID(id), totalVehiclesPassed(vehicles) {
        activeCheckpoints++;
    }

    virtual ~TrafficCheckpoint() {
        cout << "[OFFLINE] Toll Checkpoint " << checkpointID << " feed closed. Barrier locked." << endl;
        activeCheckpoints--;
    }

    // Pure Virtual Functions
    virtual double calculateTotalTollAndFines() const = 0;
    virtual void generateTrafficReport() const = 0;
};

// Static member definitions outside class
int TrafficCheckpoint::activeCheckpoints = 0;
double TrafficCheckpoint::totalRevenueCollectedPKR = 0.0;

// Derived Class 1: Motorway Automated RFID Toll Plaza
class MotorwayExpresswayToll : public TrafficCheckpoint {
private:
    double tollRatePerCar;
    int commercialTrucksCount;
    double truckSurchargeRate;

public:
    MotorwayExpresswayToll(string id, int totalCars, double standardRate, int trucks, double surcharge)
        : TrafficCheckpoint(id, totalCars),
          tollRatePerCar(standardRate),
          commercialTrucksCount(trucks),
          truckSurchargeRate(surcharge) {}

    ~MotorwayExpresswayToll() override {
        cout << " -> Resetting RFID scanner sensors for " << checkpointID << "..." << endl;
    }

    double calculateTotalTollAndFines() const override {
        // Base car toll + heavy commercial truck surcharges
        double revenue = (totalVehiclesPassed * tollRatePerCar) + (commercialTrucksCount * truckSurchargeRate);
        return revenue;
    }

    void generateTrafficReport() const override {
        double revenue = calculateTotalTollAndFines();
        TrafficCheckpoint::totalRevenueCollectedPKR += revenue;

        cout << "\n==============================================" << endl;
        cout << "   MOTORWAY EXPRESSWAY TOLL: " << checkpointID << endl;
        cout << "==============================================" << endl;
        cout << "  Light Vehicles Logged : " << totalVehiclesPassed << endl;
        cout << "  Heavy Freight Trucks  : " << commercialTrucksCount << endl;
        cout << "  Standard Toll Rate    : PKR " << tollRatePerCar << endl;
        cout << "  Total Gate Collection : PKR " << fixed << setprecision(2) << revenue << endl;
        cout << "==============================================" << endl;
    }
};

// Derived Class 2: Urban AI Speed Trap & Signal Violations Camera
class UrbanSpeedCamera : public TrafficCheckpoint {
private:
    int overspeedingViolations;
    int redLightViolations;
    const double overspeedFineRate = 2500.0;
    const double redLightFineRate = 5000.0;

public:
    UrbanSpeedCamera(string id, int totalVehiclesTracked, int speedViolations, int redLightRuns)
        : TrafficCheckpoint(id, totalVehiclesTracked),
          overspeedingViolations(speedViolations),
          redLightViolations(redLightRuns) {}

    ~UrbanSpeedCamera() override {
        cout << " -> Flushing camera buffer and ANPR logs for " << checkpointID << "..." << endl;
    }

    double calculateTotalTollAndFines() const override {
        return (overspeedingViolations * overspeedFineRate) + (redLightViolations * redLightFineRate);
    }

    void generateTrafficReport() const override {
        double fines = calculateTotalTollAndFines();
        TrafficCheckpoint::totalRevenueCollectedPKR += fines;

        cout << "\n==============================================" << endl;
        cout << "   URBAN AI CAMERA SURVEILLANCE: " << checkpointID << endl;
        cout << "==============================================" << endl;
        cout << "  Vehicles Monitored    : " << totalVehiclesPassed << endl;
        cout << "  Overspeeding Infractions: " << overspeedingViolations << endl;
        cout << "  Signal Breach Offenses  : " << redLightViolations << endl;
        cout << "  Total Fines Imposed   : PKR " << fixed << setprecision(2) << fines << endl;
        cout << "==============================================" << endl;
    }
};

int main() {
    cout << "\n>>> STARTING CITY TRAFFIC COMMAND TELEMETRY <<<\n" << endl;

    const int TOTAL_CHECKPOINTS = 2;
    TrafficCheckpoint* grid[TOTAL_CHECKPOINTS];

    // Checkpoint 1: M-2 Motorway Interchange Toll (450 cars @ PKR 120, 80 trucks @ PKR 350)
    grid[0] = new MotorwayExpresswayToll("TOLL-M2-EXIT", 450, 120.0, 80, 350.0);

    // Checkpoint 2: City Center High-Speed AI Camera (1500 cars tracked, 35 speeding, 12 red lights)
    grid[1] = new UrbanSpeedCamera("CAM-MALL-ROAD-04", 1500, 35, 12);

    // Dynamic execution via base pointers
    for (int i = 0; i < TOTAL_CHECKPOINTS; i++) {
        grid[i]->generateTrafficReport();
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Highway Checkpoints : " << TrafficCheckpoint::activeCheckpoints << endl;
    cout << "City Revenue (Tolls & Fines): PKR " << fixed << setprecision(2) 
         << TrafficCheckpoint::totalRevenueCollectedPKR << endl;
    cout << "----------------------------------------------\n" << endl;

    cout << ">>> COMMENCING SYSTEM MAINTENANCE SHUTDOWN <<<\n" << endl;

    // Teardown with dynamic deallocation
    for (int i = 0; i < TOTAL_CHECKPOINTS; i++) {
        delete grid[i];
        grid[i] = nullptr;
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Highway Checkpoints After Teardown: " << TrafficCheckpoint::activeCheckpoints << endl;
    cout << "----------------------------------------------" << endl;

    return 0;
}