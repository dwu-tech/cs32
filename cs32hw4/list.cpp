//
//  main.cpp
//  cs32h4p4
//
//  Created by Darren Wu on 3/1/21.
//


void listAll(const File* f, string path)  // two-parameter overload
{
    if(!f->name().empty()){
        cout<<'/'<<path<<f->name()<<endl;
    }
    if(f->files() == nullptr){
        return;
    }
       
    if (!f->name().empty()){
        path += f->name() + "/";
    }
        
    for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++){
        listAll(*it, path);
    }
}

