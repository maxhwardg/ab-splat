

#ifndef VIENNA_H
#define VIENNA_H

#include <string>
#include "rnainterval.h"
#include <vector>
#include <iostream>

//include external libs
extern "C" 
{
    #include "vienna/Lfold.h"
}

std::vector<RNAInterval> rnal_fold(const std::string& rna, int windowSize)
{
    char* ss = new char[rna.size()+1];
    struct mnode* n = mLfold(rna.c_str(), ss, windowSize);
    delete[] ss;
    std::vector<RNAInterval> tmp;
    std::string s;
    while(n->next != 0) 
    {
    	s = std::string(n->sstruct);

        //global left/right index
    	int ll = n->left - 1;
        int rr = ll + s.size() - 1;

        //trim dangling ends
    	int l = ll, r = rr; //l and r are used to store substring indexes in 's'
    	int i;
    	for(i = 0; s[i] == '.'; ++i)
    		++ll;
    	l = i;
    	for(i = s.size()-1; s[i] == '.'; --i)
    		--rr;
    	r = i;

        tmp.push_back( RNAInterval( ll, rr, -(n->fe), s.substr(l, (r - l) + 1) ) );
        struct mnode* prev = n;
        n = n->next;
        free (prev->sstruct);
        free (prev);
    }
    return tmp;
}



#endif
