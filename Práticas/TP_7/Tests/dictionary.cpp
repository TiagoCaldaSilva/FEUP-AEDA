#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return word < wm1.word;
}

void Dictionary::readDictionary(ifstream &f)
{
    string w, m;
    while(getline(f, w, '\n')) {
        getline(f, m, '\n');
        WordMeaning temp(w, m);
        words.insert(temp);
    }
}

string Dictionary::searchFor(string word) const
{
    WordMeaning x(word, " ");
    WordMeaning temp = words.find(x);
    if(temp.getWord() == "")
        throw WordInexistent(words, word);
    return temp.getMeaning();
}

bool Dictionary::correct(string word, string newMeaning)
{
    WordMeaning x(word, newMeaning);
    WordMeaning temp = words.find(x);
    if(temp.getWord() == ""){
        words.insert(x);
        return false;
    }
    words.remove(temp);
    temp.setMeaning(newMeaning);
    words.insert(temp);
    return true;
}

void Dictionary::print() const
{
    words.printTree();
}

ostream & operator<<(ostream & out, const WordMeaning &wm){
    out << wm.word << "-" << wm.meaning << std::endl;
    return out;
}

