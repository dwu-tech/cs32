


void removeOdds(vector<int>& v)
{
    vector<int>::iterator it;
        for(it = v.begin();it!=v.end();){
            if((*it)%2 == 1){
                it = v.erase(it);
            }
        else{
            it++;
        }
    }
}

   
