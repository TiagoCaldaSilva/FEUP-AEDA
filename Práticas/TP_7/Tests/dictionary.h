#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
        friend ostream & operator<<(ostream & out, const WordMeaning &wm);
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};

class WordInexistent
{
    string word;
    BST<WordMeaning> bst;
public:
    WordInexistent(const BST<WordMeaning> &bst, string word) :bst(WordMeaning("", "")){
        this->word = word;
        this->bst = bst;
    }
    string getWordBefore() const {
        BSTItrIn<WordMeaning> it = bst, temp = bst;
        while(!it.isAtEnd()){
            if(it.retrieve().getWord() < word ){
                it.advance();
                if(it.retrieve().getWord() > word)
                    return temp.retrieve().getWord();
                temp.advance();
            }
        }
        return "";
    }

    string getMeaningBefore() const{
        BSTItrIn<WordMeaning> it = bst, temp = bst;
        while(!it.isAtEnd()){
            if(it.retrieve().getWord() < word ){
                it.advance();
                if(it.retrieve().getWord() > word)
                    return temp.retrieve().getMeaning();
                temp.advance();
            }
        }
        return "";
    }
    string getWordAfter() const {
        BSTItrIn<WordMeaning> it = bst;
        while(!it.isAtEnd()){
            if(it.retrieve().getWord() < word ){
                it.advance();
                if(it.retrieve().getWord() > word)
                    return it.retrieve().getWord();
            }
        }
        return "";
    }
    string getMeaningAfter() const {
        BSTItrIn<WordMeaning> it = bst;
        while(!it.isAtEnd()){
            if(it.retrieve().getWord() < word ){
                it.advance();
                if(it.retrieve().getWord() > word)
                    return it.retrieve().getMeaning();
            }
        }
        return "";
    }
};

#endif