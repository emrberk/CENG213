#ifndef _title_h__
#define _title_h__

#include "movie.h"
#include <cstring>


class TitleComparator
{
  public:
    // IMPLEMENT BELOW (inline)
    bool operator( ) (const Movie::SecondaryKey & key1, 
                      const Movie::SecondaryKey & key2) const
    { 
        std::string firstTitle = key1.getTitle();
        std::string secondTitle = key2.getTitle();
        for (int i = 0; i < firstTitle.size(); i++) {
            firstTitle[i] = tolower(firstTitle[i]);

        }
        for (int i = 0; i < secondTitle.size(); i++) {
            secondTitle[i] = tolower(secondTitle[i]);
        }
        if (firstTitle < secondTitle) {
            return true;
        }
        else if (firstTitle == secondTitle) {
            
            std::string firstDirector = key1.getDirector();
            std::string secondDirector = key2.getDirector();
            for (int i = 0; i < firstDirector.size(); i++) {
            firstDirector[i] = tolower(firstDirector[i]);

            }
            for (int i = 0; i < secondDirector.size(); i++) {
                 secondDirector[i] = tolower(secondDirector[i]);
            }
            if (firstDirector < secondDirector) {
                return true;
            }
        }
        return false;
        
    }

};

#endif
