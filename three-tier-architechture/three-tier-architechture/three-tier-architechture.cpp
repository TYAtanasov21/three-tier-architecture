#include <iostream>
#include <fstream>
#include <string>

struct Account
{
    std::string username;
    std::string password;
};

bool accountExists(std::fstream& accountFile, const std::string& username)
{
    Account checkAccount;
    while (accountFile >> checkAccount.username >> checkAccount.password)
    {
        if (checkAccount.username == username)
        {
            accountFile.clear();
            accountFile.seekg(0, std::ios::beg);
            return true;
        }
    }
    accountFile.clear();
    accountFile.seekg(0, std::ios::beg);
    return false;
}

bool registerAccount(std::fstream& accountFile, const std::string& username, const std::string& password)
{
    if (accountExists(accountFile, username))
    {
        std::cout << "Username already exists. Choose a different one." << std::endl;
        return false;
    }

    Account newAccount = { username, password };
    accountFile << newAccount.username << " " << newAccount.password << std::endl;
    std::cout << "Account registered successfully!" << std::endl;
    return true;
}

bool login(std::fstream& accountFile, const std::string& username, const std::string& password)
{
    Account currentAccount;
    while (accountFile >> currentAccount.username >> currentAccount.password)
    {
        if (currentAccount.username == username && currentAccount.password == password)
        {
            std::cout << "Login successful!" << std::endl;
            return true;
        }
    }

    std::cout << "Invalid username or password. Please try again." << std::endl;
    return false;
}

int main() {
    std::fstream accountFile("accounts.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!accountFile.is_open())
    {
        std::cout << "Error opening the account file." << std::endl;
        return 1;
    }

    std::cout << "1. Register " << std::endl << "2. Login" << std::endl << "Enter choice [1 or 2]: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        registerAccount(accountFile, username, password);
    }
    else if (choice == 2) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (login(accountFile, username, password)) {
            std::cout << "Welcome, " << username << "!" << std::endl;
        }
    }
    else {
        std::cout << "Invalid choice." << std::endl;
    }

    accountFile.close();
    return 0;
}