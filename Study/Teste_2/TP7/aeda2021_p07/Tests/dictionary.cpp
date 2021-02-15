#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.word;
}

//TODO
void Dictionary::readDictionary(ifstream &f){
    string text, text_meaning;
    while(getline(f, text, '\n')){
        getline(f, text_meaning, '\n');
        WordMeaning x(text, text_meaning);
        words.insert(x);
    }
}

//TODO
string Dictionary::searchFor(string word) const
{
    auto result = words.find(WordMeaning(word, ""));
    if(result.getWord() == "" && result.getMeaning() == ""){
        string wb4 = "", waft, wmb4 = "", wmaft;
        for(auto it = words.begin(); it != words.end(); it++){
            if(word < it.operator*().getWord()){
                wmaft = it.operator*().getMeaning();
                waft = it.operator*().getWord();
                throw WordInexistent(wb4, waft, wmb4, wmaft);
            }
            wb4 = it.operator*().getWord();
            wmb4 = it.operator*().getMeaning();
        }
        throw WordInexistent();
    }
    return result.getMeaning();
}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    auto result = words.find(WordMeaning(word, ""));
    if(result.getMeaning() == "" && result.getWord() == ""
    ){
        words.insert(WordMeaning(word, newMeaning));
        return false;
    }else{
        words.remove(result);
        result.setMeaning((newMeaning));
        words.insert(result);
        return true;
    }

}

//TODO
void Dictionary::print() const
{
    for(auto it = words.begin(); it != words.end(); it++){
        std::cout << it.operator*().getWord() << std::endl << it.operator*().getMeaning() << std::endl;
    }
}

