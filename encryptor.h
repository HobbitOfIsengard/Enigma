#include <vector>
#include <stdint.h>
#include <string>

class Encryptor{
    std::vector<uint8_t> characters;
    std::vector<char> plugboard;
    std::vector<int> pos;

    std::vector<uint8_t> generateUmkehrwalze(int seed);
    std::vector<std::vector<uint8_t> > generateRotors (int quantity,int seed);
    std::vector<std::vector<uint8_t> > reverseRotors (std::vector<std::vector<uint8_t> > rotors);
    int charToInt(char c);

    public:
    Encryptor(std::vector<uint8_t> allCharacters = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29},std::vector<char> plugboardOrder = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','.','?',','});
    void rotorPositions(std::vector<int> rotorPositions);
    void encrypt(std::string text,int rotorAmount = 3,int rotorSeed = 0);
    void setAlphabet(std::string s);
    void setPlugboard(std::string s);
    void printPlugboard();
};
