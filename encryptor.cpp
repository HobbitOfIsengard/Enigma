#include <stdint.h>
#include <string>
#include <cstdint>
#include <array>
#include <random>
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "encryptor.h"

//this function swapps pairs or random values in the vector with eachother
std::vector<uint8_t> Encryptor::generateUmkehrwalze(int seed){
    std::vector<uint8_t> chars = characters;
    std::vector<uint8_t> swapped(chars.size());
    uint8_t pos = 0;
    std::mt19937 g(seed);
    std::shuffle(chars.begin(),chars.end(),g);
    for(int i = 0; i<chars.size()-1;i+=2){
        swapped[chars[i]]= chars[i+1];
        swapped[chars[i+1]] = chars[i];
    }
    return swapped;

}

std::vector<std::vector<uint8_t> > Encryptor::generateRotors (int quantity,int seed){
    if(seed == 0){
        std::random_device rd;
        seed = rd();
    }
    std::cout<<"the rotor seed is: "<<seed<<std::endl;
    std::mt19937 g(seed);

    std::vector<std::vector<uint8_t> > shuffleArray;

    const std::vector<uint8_t> plainArray = characters;

    for(uint8_t i = 0; i<quantity;i++){
        shuffleArray.push_back(plainArray);
        std::shuffle(shuffleArray[i].begin(),shuffleArray[i].end(),g);
    }
    shuffleArray.push_back(generateUmkehrwalze(seed));
    return shuffleArray;
}


std::vector<std::vector<uint8_t> > Encryptor::reverseRotors (std::vector<std::vector<uint8_t> > rotors){
    std::vector<std::vector<uint8_t> > reversedRotors(rotors.size(),std::vector<uint8_t> (rotors[0].size(), 0));
    for(int i = 0; i<rotors.size()-1;i++){
        for(int j = 0; j < rotors[i].size();j++){
            reversedRotors[i][rotors[i][j]] = j;
        }
    }
    return reversedRotors;
}

int Encryptor::charToInt(char c){
    return (std::find(plugboard.begin(),plugboard.end(),c)-plugboard.begin());
}


Encryptor::Encryptor(std::vector<uint8_t> allCharacters,std::vector<char> plugboardOrder) : characters(allCharacters),plugboard(plugboardOrder){
    //assert("uneven character amount",(characters.size()%2 = 0));
}

void Encryptor::rotorPositions(std::vector<int> rotorPositions){
    pos = rotorPositions;
}
void Encryptor::setAlphabet(std::string s){
    plugboard.clear();
    characters.clear();
    for(int i = 0;i<=s.length()-1;i++){
        plugboard.push_back(s[i]);
        characters.push_back(i);
    }

}
void Encryptor::setPlugboard(std::string s){
    for(int i = 0;i<s.length()-1;i++){
        std::iter_swap(std::find(plugboard.begin(),plugboard.end(),s[i]),std::find(plugboard.begin(),plugboard.end(),s[i+1]));
    }
}
void Encryptor::printPlugboard(){
    for(char c: plugboard){
        std::cout<<c<<' ';
    }
}


void Encryptor::encrypt(std::string text,int rotorAmount,int rotorSeed){

    std::vector<std::vector<uint8_t> > wheels = generateRotors(rotorAmount,rotorSeed);
    std::vector<std::vector<uint8_t> > reversedWheels = reverseRotors(wheels);
    pos.resize(wheels.size());
    for(char i:text){
        int value = charToInt(i);
        for(int i = 0; i<pos.size();i++){
            value+=pos[i];
            if (value>=wheels[0].size()){
                value -= wheels[0].size();
            }
            value = wheels[i][value];
        }
        for(int i = pos.size()-2; i>=0;i--){
            value = reversedWheels[i][value];
            value-=pos[i];            
            if (value<0){
                value += wheels[0].size();
            }
        }
        pos[0]++;
        for(int l = 0;l<pos.size()-1;l++){
            if(pos[l]>=wheels[0].size()){
                pos[l]=0;
                if(l<(pos.size()-2)){
                    pos[l+1]++;
                }
            }
        }
        std::cout<<plugboard[value];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    
}

