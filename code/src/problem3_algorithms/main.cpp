#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

enum class PClass
{
    Upper = 1,
    Middle = 2,
    Lower = 3,
    NoInfo
};

enum class Sex
{
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
    
    Passenger() {}
    
    
    Passenger(int number)
    {
        id = number;
    }
};

struct PassengerWithCity : public Passenger
{
    std::string cityName;
    
    PassengerWithCity(int number)
        :Passenger(number)
    {
        cityName = "default";
    }
    
};

// task 2
// Potential problems:
// 1. No file
// 2. Data type is incorrect
// 3. Data row is not full.
enum class ErrorCode
{
    noFile,
};

// task 1
// https://en.cppreference.com/w/cpp/error/exception
class AppExcept : public std::runtime_error
{
    ErrorCode _code;
public:
    // task 3
    AppExcept(ErrorCode code, const char* errorMessage = "") 
        :std::runtime_error("")
    {
        _code = code;
    }
    
    ErrorCode getCode() const {return _code;}
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
        throw AppExcept(ErrorCode::incorrectType);
        std::cerr << "std::invalid_argument: " << ex.what() << "\n";
        std::cerr << "Could not parse string: '" << buffer <<"'\n";
        std::cerr << "Using value " << DEFAULT_AGE << " as default" << '\n';
        i = DEFAULT_AGE;
    }

    return i;
    
}


Passenger extractData(std::istream& in)
{
    Passenger newPassenger;
    std::string buffer;
    
    std::getline(in, buffer, ','); // ID
    newPassenger.id = toInt(buffer);
    
    std::getline(in, buffer, ','); // survived
    newPassenger.survived = buffer == "1";
    
    std::getline(in, buffer, ','); // pclass
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

    if(!std::getline(in, buffer, '\n'))
    {
        throw...
    }
    // Embarked
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
        Passenger newPass = extractData(lineStream);
        passengers.push_back(newPass);
    }
    return passengers;
}


int main ()
{
    
    PassengerWithCity a(10);
    a.age = 10;
//    a.
    
    const std::string INPUT_FILE_NAME = "../../data/titanic.csv";
    std::ifstream inputFile;
    
    // task 4
    try {
    
        inputFile.open(INPUT_FILE_NAME);
        
        if(!inputFile.is_open())
        {
            throw AppExcept(ErrorCode::noFile);
        }
        
        VecPassengers passengers = loadData(inputFile);
        std::cout << passengers[0];
    }
    catch (const AppExcept& e){
        
        switch (e.getCode()) {
        case ErrorCode::noFile:
            std::cout << "something";
            break;
        case ErrorCode::secondError:
            // no file
            break;
        default:
            break;
        }
    }
    catch (...) {
    }
    
}
