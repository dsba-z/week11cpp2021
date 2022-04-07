#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

enum class PClass{
    Upper = 1,
    Middle = 2,
    Lower = 3,
    NoInfo
};

enum class Sex{
    Male,
    Female,
    NoInfo
};

struct Passenger
{
    unsigned int id;
    bool survived;
    PClass pclass;
    std::string name;
    Sex sex;
    unsigned int age;
    unsigned int sibsp;
    unsigned int parch;
    std::string ticket;
    double fare;
    std::string cabin;
    std::string embarked;
};

typedef std::vector<Passenger> VecPassengers;

const int DEFAULT_AGE = 0;


std::ostream& operator<<(std::ostream& out, Passenger p)
{
    out << std::setw(4) << p.id << ",";
    out << p.survived << ",";
    out << static_cast<int>(p.pclass) << ",";
    out << p.name << ",";
    out << static_cast<int>(p.sex) << ",";
    out << p.age << ",";
    out << p.sibsp << ",";
    out << p.parch << ",";
    out << p.ticket << ",";
    out << p.fare << ",";
    out << p.cabin << ",";
    out << p.embarked << "\n";
    return out;
}


PClass toPClass(const std::string& buffer)
{
    std::stringstream sspcl(buffer);
    int pclassInt = 0;
    sspcl >> pclassInt;
    PClass pclass = static_cast<PClass>(pclassInt);
    return pclass;
}


int toInt(const std::string& buffer)
{
    int i;
    try
    {
      i =  std::stoi(buffer);
    }
    catch(std::invalid_argument const& ex)
    {
      std::cerr << "std::invalid_argument: " << ex.what() << "\n";
      std::cerr << "Could not parse string: '" << buffer <<"'\n";
      std::cerr << "Using value " << DEFAULT_AGE << " as default" << '\n';
      i = DEFAULT_AGE;
    }

    return i;
    
}

void getlineWithException(std::istream& in, std::string& buffer, char delimiter)
{
    bool successfullyRead = bool(std::getline(in, buffer, delimiter));
    if (!successfullyRead) {
        throw std::runtime_error("Corrupt data for pclass");
    }
}

Passenger extractData(std::istream& in, bool ignoreErrors)
{
    Passenger newPassenger;
    std::string buffer;
    
    bool isDataCorrupt = false;
    
    isDataCorrupt = isDataCorrupt || !std::getline(in, buffer, ','); // ID
    newPassenger.id = toInt(buffer);
    
    getlineWithException(in, buffer, ','); // survived
    newPassenger.survived = buffer == "1";
    
    getlineWithException(in, buffer, ',');
    newPassenger.pclass = toPClass(buffer);
    
    std::getline(in, buffer, ','); // full name
    newPassenger.name = buffer;
    
    std::getline(in, buffer, ','); // sex
    newPassenger.sex = buffer == "male"? Sex::Male : Sex::Female;
    
    std::getline(in, buffer, ','); // age
    newPassenger.age = toInt(buffer);
    
    std::getline(in, buffer, ','); // sibsp
    newPassenger.sibsp = toInt(buffer);
    
    std::getline(in, buffer, ','); // parch
    newPassenger.parch = toInt(buffer);
    
    std::getline(in, buffer, ','); // ticket
    newPassenger.ticket = buffer;
    
    std::getline(in, buffer, ','); // fare
    newPassenger.fare = std::stod(buffer);

    std::getline(in, buffer, ','); // Cabin
    newPassenger.cabin = buffer;

    std::getline(in, buffer, '\n'); // Embarked
    newPassenger.embarked = buffer;
    
    if (isDataCorrupt) {
        throw std::runtime_error("Corrupt data");
    }
    
    return newPassenger;
}

VecPassengers loadData(std::istream& in)
{
    VecPassengers passengers;
    std::string buffer;
    std::getline(in, buffer); // header
    while(std::getline(in, buffer))
    {
        std::stringstream lineStream(buffer);
        bool ignoreErrors = false;
        try
        {
           Passenger newPass = extractData(lineStream, ignoreErrors);
           passengers.push_back(newPass);
        }
        catch(std::runtime_error const& ex)
        {
            // if ignoring errors
            Passenger newPass = extractData(lineStream, true);
           // warn the user that a row was skipped
        }
    }
    return passengers;
}


int main ()
{
    const std::string INPUT_FILE_NAME = "../../data/titanic.csv";
    std::ifstream inputFile;
    inputFile.open(INPUT_FILE_NAME);
    VecPassengers passengers = loadData(inputFile);
    std::cout << passengers[0];
}
