#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck() {root = new Node('$'); }
    virtual ~StudentSpellCheck();
    bool load(std::string dict_file);
    bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
    void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:

    
    struct Node{
        Node(char c){
            isWord = false;
            m_c = c;
        };
        vector<Node*>children = vector<Node*>(27);
        bool isWord;
        char m_c;
        
    };
    
    
    Node* root;
    bool checkRestWord(std::string word, Node* n, int i, std::vector<std::string>& suggestions, int max_sug);
    
    vector<string> breakUpLine(string s, std::vector<SpellCheck::Position>& problems);
};

#endif  // STUDENTSPELLCHECK_H_

