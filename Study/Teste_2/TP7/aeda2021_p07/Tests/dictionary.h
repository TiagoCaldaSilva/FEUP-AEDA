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


//TODO
class WordInexistent : public std::exception
{
    string w_before, w_after, wm_before, wm_after;
public:
    WordInexistent() {
        w_before = "";
        wm_before = "";
        w_after = "";
        wm_after = ""; }
    WordInexistent(const string &wb4,const string &wafter, const string &wmb4, const string &wmafter){
        w_before = wb4;
        wm_before = wmb4;
        w_after = wafter;
        wm_after = wmafter;
    }
    string getWordBefore() const { return w_before; }
    string getMeaningBefore() const { return wm_before; }
    string getWordAfter() const { return w_after; }
    string getMeaningAfter() const { return wm_after; }
};

#endif