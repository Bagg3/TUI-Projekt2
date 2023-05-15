#include <string>

class dbHandler

{
private:
    std::string dbHost_;

    // Function to encrypt/decrypt the data
    std::string xorCipher(std::string data, char key);

public:
    dbHandler(std::string dbHost);

    // Decrypts the data from the file and returns it
    std::string findData(std::string fileAdress); // Uses try catch syntax

    // Encrypts the data and saves it to the file
    void saveData(std::string fileAdress, std::string data); // Uses try catch syntax
};
