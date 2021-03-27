//
//  main.cpp
//  cs32h4p3b
//
//  Created by Darren Wu on 3/1/21.
//
   
      // Remove the movies in li with a rating below 55 and destroy them.
      // It is acceptable if the order of the remaining movies is not
      // the same as in the original list.
    void removeBad(list<Movie*>& li)
    {
        list<Movie*>::iterator it;
        for(it = li.begin();it!=li.end();){
            if((*it)->rating()<55){
                delete *it;
                it = li.erase(it);
            
            }
            else{
                it++;
            }
        }
    }

    
