#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Person
{
    std::string name = "";
    std::string surname = "";
    std::string date = "";
    double payment = 0;
    std::string currency = "RUB";
};

bool isValidDate(std::string &date) {

    if (date.length() != 10) {
        if (date[1] == '.') date.insert(0, "0");
        if (date[4] == '.') date.insert(3, "0");
    }

    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));

    if (day < 1 || day > 31 || month < 1 ||  month > 12 || year < 1945 || year > 2025) {
        return false;
    }
    return true;
}

bool isValidName(std::string &str){

    std::string charsName = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz'-";
    bool match = true;
    for (int i = 0; i < str.length(); ++i) {
        for (int j = 0; j < charsName.length(); ++j){
            if (str[i] != charsName[j]){
                match = false;
            } else {
                match = true;
                break;
            }
        }
    }
    return match;
}

void readFile (std::ifstream &file, Person &recipient) {

    std::vector<Person> list;
    while (!file.eof()) {
        file >> recipient.name;
        file >> recipient.surname;
        file >> recipient.date;
        file >> recipient.payment;
        file >> recipient.currency;

        list.push_back(recipient);
    }

    for (int i = 0; i < list.size() - 1; ++i)
    {
        std::cout << list[i].name << " " << list[i].surname << " " << list[i].date << " ";
        std::cout.setf(std::ios::fixed);
        std::cout.precision(2);
        std::cout << list[i].payment << " " ;
        std::cout << list[i].currency << std::endl;
    }
}

void addToFile (std::ofstream &file, Person &recipient) {

    if (!isValidName(recipient.name)) {
        std::cerr << "Invalid name!" << std::endl;
        recipient.name = "__________";
    }
    if (!isValidName(recipient.surname)) {
        std::cerr << "Invalid surname!" << std::endl;
        recipient.surname = "_______________";
    }
    if (!isValidDate(recipient.date)) {
        std::cerr << "Invalid date!" << std::endl;
        recipient.date = "__.__.____";
    }

    file << recipient.name << " " << recipient.surname << " " << recipient.date << " ";
    file.setf(std::ios::showpoint);
    file.setf(std::ios::fixed);
    file.precision(2);
    file << recipient.payment << " " << recipient.currency << std::endl;
}

int main () {

    Person recipient;
    std::string command = "";

    std::cout << "Commands:\n"
                 "'add' - if you want to add new data to the statement,\n"
                 "'list' - if you want to read the statement,\n"
                 "Please enter the command:" << std::endl;
    std::cin >> command;

    if (command != "add" && command != "list") {
        std::cerr << "Invalid command! Exiting program." << std::endl;
    }

    if (command == "add")
    {
        std::ofstream file("..\\statement.txt", std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
        } else {
            std::cout << "Enter name (can contain only: latin letters a-z, A-Z, - and ' ):" << std::endl;
            std::cin >> recipient.name;
            std::cout << "Enter surname (can contain only: latin letters a-z, A-Z, - and ' ):" << std::endl;
            std::cin >> recipient.surname;
            std::cout << "Enter payment date (dd.mm.yyyy):" << std::endl;
            std::cin >> recipient.date;
            std::cout << "Enter payment amount: " << std::endl;
            std::cin >> recipient.payment;

            addToFile(file,recipient);
        }
        file.close();
    }

    if (command == "list") {
        std::ifstream file("..\\statement.txt");
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
        } else {
            readFile(file,recipient);
        }
        file.close();
    }

    return 0;
}
