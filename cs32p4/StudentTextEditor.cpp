#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
//This was edited with the word processor
#include <iostream>
#include <fstream>
using namespace std;

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
     m_col = 0;  //initialize cursor col/row to zero
     m_row = 0;
}

StudentTextEditor::~StudentTextEditor()
{
    linesList.clear();
}


bool StudentTextEditor::load(std::string file) {
    ifstream infile(file);    // infile is a name of our choosing
        if ( ! infile )                // Did opening the file fail?
        {
            cerr << "Error: Cannot open: " <<file<< endl;
            return false;
        }
    linesList.clear();
    std::string s;
          // getline returns infile; the while tests its success/failure state
    
        while (getline(infile, s))
        {
            for(int i = 0; i<s.length(); i++){
                if(s[i] == '\r'){
                    s = s.substr(0,i)+s.substr(i+1,s.length()-1); //skip over '\r'
                }
            }
            linesList.push_back(s);
        }
    reset();   //clear undo stack set cursor to zero
    currLine = linesList.begin();
    return true;
}

bool StudentTextEditor::save(std::string file) {
    ofstream outfile(file);   // outfile is a name of our choosing.
        if ( ! outfile )           // Did the creation fail?
        {
            return false;
        }
    list<string>::iterator it;
    for(it = linesList.begin();it!=linesList.end(); it++){
        outfile <<(*it)+"\n";
    }
        
	return true;
}

void StudentTextEditor::reset() {
    getUndo()->clear();
    m_col = 0;
    m_row = 0;
}

void StudentTextEditor::move(Dir dir) {
    if(m_row == 0){
        currLine = linesList.begin();  //set ptr to the current line
    }
    switch (dir) {
        case Dir::UP:
            if(!(m_row == 0)){
                currLine--;
                if(m_col>(*currLine).size()){
                    m_col = (*currLine).size();   //automatically adjust cursor to end if too far ahead
                }
                m_row--;
            }
            break;
        case Dir::DOWN:
            if(m_row<linesList.size()){
                currLine++;
                if(m_col>(*currLine).size()){    //automatically adjust cursor to end if too far ahead
                    m_row++;
                    m_col = (*currLine).size();
                }
                else{
                    m_row++;
                }
            }
            else{
                m_row++;
            }
            break;
            
        case Dir::LEFT:
            if(!(m_col == 0)){
                m_col--;
            }
            break;
        case Dir::RIGHT:{
            if(*currLine == ""){  //can't move right if no words
                break;
            }
            if((m_col)>=(*currLine).size() && m_row<linesList.size()-1){ //move to next line
                m_row++;
                currLine++;
                m_col = 0;
            }
            else if(m_col<(*currLine).size()){
                m_col++;
            }
            
                break;
            }
        case Dir::HOME:
            m_col = 0;  //go to begnning of current line
           
            break;
        case Dir::END:
            m_col = (*currLine).size(); //jump to end of current line
            break;
        default:
            break;
    }

}

void StudentTextEditor::del() {
    
    if(*currLine == ""){
        
        currLine = linesList.erase(currLine);
        getUndo()->submit(Undo::Action::JOIN, m_row, m_col);  //join previous line
    }
    else if((*currLine).size()== m_col){ //joins previous line, appends that lines text as well
        string s = (*currLine);
        currLine = linesList.erase(currLine);
        (*currLine) = s+(*currLine);
        getUndo()->submit(Undo::Action::JOIN, m_row, m_col);
    }
    else{
        char c = (*currLine)[m_col];   //normal delete
        (*currLine).erase(m_col,1);
        getUndo()->submit(Undo::Action::DELETE, m_row, m_col,c);
    }
    
}

void StudentTextEditor::backspace() {
    if(*currLine=="" ||m_col <= 0){
        if(m_row!=0){                 //joining deleted line to current line
            string s = (*currLine);
            linesList.erase(currLine);
            currLine--;
            (*currLine) += s;
            getUndo()->submit(Undo::Action::JOIN, m_row, m_col);
            m_row--;
            m_col = (*currLine).size()-(s.size()-1);
            
        }
       
    }
    else{
        char c = (*currLine)[m_col-1];     //delete char one to the left of cursor
        getUndo()->submit(Undo::Action::DELETE, m_row, m_col-1,c);
        (*currLine).erase(m_col-1,1);
        
    }
    move(Dir::LEFT); //move cursor
}

void StudentTextEditor::insert(char ch) {
    if(ch == '\t'){
        int i = 0;
        while(i<4){
            insert(' ');  //tab, 4 spaces
            
            i++;
        }
        return;
    }
    if(m_row == 0){
        currLine = linesList.begin();
    }
    string s ="";
    s += ch;
    if(*currLine == "" && linesList.size()<=m_row){
        linesList.push_back(s);     //insert to a new line
    }
   
    else{
        (*currLine).insert(m_col, s);  //insert at m_col position
    }
    move(Dir::RIGHT);
    getUndo()->submit(Undo::Action::INSERT, m_row, m_col,ch);
}
    

void StudentTextEditor::enter() {
	
    string s = (*currLine).substr(m_col); //splits two lines, appens text at split to next line
    (*currLine).erase(m_col);
    currLine++;
    linesList.insert(currLine, s);
    currLine--;
    m_row ++;
    m_col = 0;
    
}

void StudentTextEditor::getPos(int& row, int& col) const {
    col = m_col;
	row = m_row;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    
    if(startRow<0|| numRows<0||startRow>linesList.size()){
        return -1;
    }
    
    list<string>::const_iterator it;
    it = linesList.begin();
    lines.clear();
    for(int i = 0; i<startRow;i++){
        it++;
    }
    for(int i = startRow;(it != linesList.end());i++){
        lines.push_back(*it);     //push back until view window is filled
        it++;
    }
    if(startRow == linesList.size()){
        lines.clear();
        return lines.size();  //return line size, if start is equal to linesize
    }

    return lines.size();  //return items in the lines parameter
}

void StudentTextEditor::undo() {

    Undo::Action temp_action;
    
    int temp_row;
    int temp_col;
    int temp_count;
    string temp_text;
    temp_action = getUndo()->get(temp_row, temp_col, temp_count, temp_text);
    
    switch (temp_action) {
        case Undo::Action::DELETE:{
            while(temp_count>0){
                if(*currLine==""){
                        string s = (*currLine);
                        linesList.erase(currLine);
                        currLine--;
                        (*currLine) += s;
                        temp_row--;
                        temp_col = (*currLine).size()-(s.size()-1);
                    
                }
                else{
                    (*currLine).erase(temp_col-1,1);;
                }
                move(Dir::LEFT);
                temp_count--;
            }
            break;
        }
        case Undo::Action::INSERT:{
            string s ="";
            s += temp_text;
            (*currLine).insert(temp_col, s);
            break;
        }
        case Undo::Action::SPLIT:{
            string s = (*currLine).substr(temp_col);
            (*currLine).erase(temp_col);
            currLine++;
            linesList.insert(currLine, s);
            currLine--;
            m_col = 0;
            break;
        }
           
        case Undo::Action::JOIN:{
            string s = (*currLine);
            linesList.erase(currLine);
            currLine--;
            (*currLine) += s;
            m_row--;
            m_col = (*currLine).size()-(s.size()-1);
            break;
        }
        case Undo::Action::ERROR:{
            
            break;
        }
         
        default:
            
            break;
    }

}
