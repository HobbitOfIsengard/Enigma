#include "encryptor.h"
#include <iostream>
#include <sstream>
#include <utility>


void printWelcome(){
    for(int i = 0;i<80;i++){
        std::cout<<'*';
    }
    std::cout<<std::endl;
    std::cout<<"|    |   |  ______           ___    __             ______"<<std::endl;
    std::cout<<"|    |   | |       |        /      /  \\    /\\ /\\  |      "<<std::endl;
    std::cout<<"|    |   | |______ |       /      /    \\  / \\/  \\ |______"<<std::endl;
    std::cout<<" \\   |   / |       |       \\      \\    /  |  |  | |      "<<std::endl;
    std::cout<<"  \\_/\\_/   |______ |______  \\___   \\__/   |  |  | |______"<<std::endl;
    for(int i = 0;i<80;i++){
        std::cout<<'*';
    }
    std::cout<<std::endl;
}
std::vector<char> stringToVector(std::string s){
    std::vector<char> charVec(0);
    for(char c: s){
        charVec.push_back(c);
    }
    return charVec;
}
bool tryParse(std::string& input, int& output) {
    try{
        output = std::stoi(input);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}
int main(){
    Encryptor e{};
    std::string text;
    int seed,rotorCount;

    for(int i = 0;i<80;i++){
        std::cout<<'*';
    }
    std::cout<<std::endl;
    std::cout<<"welcome to the Enigma,"<<std::endl;
    std::cout<<"enter the alphabet used, press enter to use default.  use the style ABCDEFG"<<std::endl;
    std::getline(std::cin,text);
    if(!text.empty()){
        e.setAlphabet(text);
    }
    std::cout<<"enter the plugboard pairs by pairing letters to be connected after eachother eg. ACDB. To use default press enter"<<std::endl;
    std::getline(std::cin,text);
    if(!text.empty()){
        e.setPlugboard(text);
    }
    std::cout<<"enter rotor seed or leave blank for random"<<std::endl;
    std::getline(std::cin,text);
    if(text.empty()){
        seed = 0;
    }else{
        while (!tryParse(text, seed)){
            std::cout << "Bad entry. Enter a NUMBER: ";
            getline(std::cin, text);
        }
    }
    std::cout<<"enter rotor amount or leave blank for 3"<<std::endl;
    std::getline(std::cin,text);
    if(text.empty()){
        rotorCount = 3;
    }else{
        while (!tryParse(text, rotorCount)){
            std::cout << "Bad entry. Enter a NUMBER: ";
            getline(std::cin, text);
        }
    }
    std::cout<<"enter Text"<<std::endl<<std::endl;
    std::getline(std::cin,text);
    e.encrypt(text,rotorCount,seed);
}