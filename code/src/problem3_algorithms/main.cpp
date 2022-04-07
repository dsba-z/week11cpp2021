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

int toDouble(const std::string& buffer)
{
    double i;
    try
    {
      i =  std::stod(buffer);
    }
    catch(std::invalid_argument const& ex)
    {
//      std::cerr << "std::invalid_argument: " << ex.what() << "\n";
//      std::cerr << "Could not parse string: '" << buffer <<"'\n";
//      std::cerr << "Using value " << DEFAULT_AGE << " as default" << '\n';
      i = 0;
    }

    return i;
    
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
//      std::cerr << "std::invalid_argument: " << ex.what() << "\n";
//      std::cerr << "Could not parse string: '" << buffer <<"'\n";
//      std::cerr << "Using value " << DEFAULT_AGE << " as default" << '\n';
      i = DEFAULT_AGE;
    }

    return i;
    
}

void getLineWithException(std::istream& in, std::string& buffer, char delimiter)
{
    if (!std::getline(in, buffer, delimiter))
    {
        throw std::runtime_error("Corrupt data");
    }
}

Passenger extractData(std::istream& in)
{
    Passenger newPassenger;
    std::string buffer;
    
    getLineWithException(in, buffer, ','); // ID
    newPassenger.id = toInt(buffer);
    
    getLineWithException(in, buffer, ','); // survived
    newPassenger.survived = buffer == "1";
    
    getLineWithException(in, buffer, ','); // pclass
    newPassenger.pclass = toPClass(buffer);
    
    getLineWithException(in, buffer, ','); // full name
    newPassenger.name = buffer;
    
    getLineWithException(in, buffer, ','); // sex
    newPassenger.sex = buffer == "male"? Sex::Male : Sex::Female;
    
    getLineWithException(in, buffer, ','); // age
    newPassenger.age = toInt(buffer);
    
    getLineWithException(in, buffer, ','); // sibsp
    newPassenger.sibsp = toInt(buffer);
    
    getLineWithException(in, buffer, ','); // parch
    newPassenger.parch = toInt(buffer);
    
    getLineWithException(in, buffer, ','); // ticket
    newPassenger.ticket = buffer;
    
    getLineWithException(in, buffer, ','); // fare
    newPassenger.fare = toDouble(buffer);

    getLineWithException(in, buffer, ','); // Cabin
    newPassenger.cabin = buffer;

    getLineWithException(in, buffer, '\n'); // Embarked
    newPassenger.embarked = buffer;
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
        try
        {
            Passenger newPass = extractData(lineStream);
            passengers.push_back(newPass);
        }
        catch(std::runtime_error const& ex)
        {
            std::cout << ex.what() << std::endl;
            std::cout << buffer << std::endl;
        }
    }
    return passengers;
}


int main ()
{
    const std::string INPUT_FILE_NAME = "../../data/titanic_no_columns.csv";
    std::ifstream inputFile;
    inputFile.open(INPUT_FILE_NAME);
    VecPassengers passengers = loadData(inputFile);
    std::cout << passengers[0];
}
