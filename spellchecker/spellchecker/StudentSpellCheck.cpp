#include "StudentSpellCheck.h"
#include <string>
#include <vector>

#include <iostream>
#include <fstream>

//using namespace std;

SpellCheck* createSpellCheck()
{
    
    return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck() {
    // TODO
    delete root;
    root = nullptr;
}


bool StudentSpellCheck::load(std::string dictionaryFile) {
    ifstream infile(dictionaryFile);    // infile is a name of our choosing
        if ( ! infile )                // Did opening the file fail?
        {
            cerr << "Error: Cannot open" <<dictionaryFile<< endl;
            return false;
        }
   
   
      // getline returns infile; the while tests its success/failure state
    std::string s;
    string t;
    while(std::getline(infile, s)) {
        
        Node* cur = root;
        for(int i = 0; i<s.length(); i++){
            if(s[i] == '\''){
                if(cur->children[26] == nullptr){
                    cur->children[26] = new Node(s[i]);
                }
                cur = cur->children[26];
                continue;
            }
            if(isalpha(s[i])){
                if(cur->children[s[i] - 'a'] == nullptr){
                    cur->children[s[i] -'a'] = new Node(tolower(s[i]));
                }
            }
            cur = cur->children[s[i] - 'a'];
            continue;
        }
        cur->isWord = true;
       
     
    }

    return true; // TODO
}

bool StudentSpellCheck::checkRestWord(std::string word, Node* n, int pos, std::vector<std::string>& suggestions,int max_sug){
    
    
    for(int i = 0; i<27;i++){
        //cerr<<i<<endl;
        string s = word.substr(0,pos);
        //cerr<<s<<endl;
        (i == 26)?s+= '\'':s+= char('a' + i);
        //cerr<<s<<endl;
        //cerr<<i<<endl;
        Node* temp = n;
        temp = temp->children[i];
        if(temp == nullptr){
            continue;
        }
        //cerr<<temp->m_c<<endl;
            
        //cerr<<word[pos]<<endl;
        for(int j = pos+1; j<word.length();j++){
            //cerr<<"inside"<<endl;
            if(temp->children[word[j]-'a'] ==  nullptr){
                break;
            }
            //cerr<<word[j]<<endl;
            if(word[j] == temp->children[word[j] - 'a']->m_c){
                
                temp=temp->children[word[j] -'a'];
                s+=temp->m_c;
            }
        }
        if(temp->isWord && word.length() == s.length()){
            //cerr<<s<<endl;
            if(suggestions.size()<max_sug){
                suggestions.push_back(s);
            }
        }
    }
    //cerr<<
    return false;
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {

    Node*cur = root;
    for(int k = 0;k<word.length();k++){
        word[k] = tolower(word[k]);
    }
    
    for(int i = 0; i<word.length(); i++){
        if((word[i] == '\'' && cur->children[26] != nullptr)||(cur->children[word[i] - 'a']!= nullptr)){
            if(word[i] == '\''){
                checkRestWord(word, cur, i,suggestions, max_suggestions);
                cur = cur->children[26];
                continue;
            }
            if(word[i] == cur->children[word[i] - 'a']->m_c){
                checkRestWord(word, cur, i, suggestions,max_suggestions);
                cur = cur->children[word[i] - 'a'];
                continue;
            }
           
        }
        if((word[i] == '\'' && cur->children[26] == nullptr)){
            if(checkRestWord(word, cur, i,suggestions,max_suggestions)){
                return false;
            }
            
            else{
                return false;
            }
        }
        else if(cur->children[word[i] -'a'] == nullptr ||cur->children[word[i] -'a']->m_c !=  word[i]){
            
            if(checkRestWord(word, cur, i, suggestions,max_suggestions)){
                return false;
            }
            
            else{
                return false;
            }
        }
    }
    if(cur->isWord){
        suggestions.clear();
        return true;
    }
    return false;
}


vector<string> StudentSpellCheck::breakUpLine(string s,std::vector<SpellCheck::Position>& problems ){
    vector<string> sug;
    vector<string> v;
    string temp;
    Position* p = new Position();
    int wStart = 0;
    int wEnd = 0;
    for(int i = 0; i<s.length(); i++){
        if((!(isalpha(s[i]) || s[i] == '\''))){
            if(!(temp=="")){
                if(spellCheck(temp,0,sug)){
                    v.push_back(temp);
                    wEnd = i-1;
                    wStart = i-(int(temp.length()));
                    p->end = wEnd;
                    p->start = wStart;
                    problems.push_back(*p);
                }
                temp = "";
            }
        }
        else if(i == s.length()-1){
            temp+=s[i];
            
            if(spellCheck(temp, 0, sug)){
                v.push_back(temp);
                wEnd = i;
                wStart = i+1 -(int(temp.length()));
                p->end = wEnd;
                p->start = wStart;
                problems.push_back(*p);
            }
        }
        else{
            temp += s[i];
        }
    }
    return v;
}
void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
    vector<string> v = breakUpLine(line, problems);
    for(int i = 0; i<v.size(); i++){
        cerr<<v[i]<<endl;
    }
    vector<SpellCheck::Position>::iterator it;
    for(it = problems.begin(); it!=problems.end(); it++){
        cerr<<(*it).start<<"  "<<(*it).end<<endl;
    }
    
    
}


