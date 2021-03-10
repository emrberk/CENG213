#include "moviestore.h"


MovieStore::MovieStore( ) //implemented, do not change
{
}


// IMPLEMENT
void
MovieStore::insert(const Movie & movie)
{
    Movie::SecondaryKey skey(movie.getTitle(), movie.getDirector());

    primaryIndex.insert(movie.getID(), movie);
    Movie* movieptr = &(primaryIndex.find(movie.getID())->data);
    secondaryIndex.insert(skey, movieptr);
    ternaryIndex.insert(skey, movieptr);

}


// IMPLEMENT
void
MovieStore::remove(const std::string & id)
{
    MovieStore::MSTP::Node* deleted = primaryIndex.find(id);
    if (deleted != nullptr) {
        Movie::SecondaryKey skey(deleted->data.getTitle(), deleted->data.getDirector());
        primaryIndex.remove(id);
        secondaryIndex.remove(skey);
        ternaryIndex.remove(skey);
    }

}


// IMPLEMENT
void
MovieStore::remove(const std::string & title,
                  const std::string & director)
{
    Movie::SecondaryKey skey(title, director);
    MovieStore::MSTS::Node* nodeptr = secondaryIndex.find(skey);
    if (nodeptr != nullptr) {
        primaryIndex.remove(nodeptr->data->getID());
        secondaryIndex.remove(skey);
        ternaryIndex.remove(skey);
    }
}


// IMPLEMENT
void
MovieStore::removeAllMoviesWithTitle(const std::string & title)
{
    Movie::SecondaryKey lowerkey(title, "a");
    Movie::SecondaryKey upperkey(title, "{");
    
    std::list<typename MSTT::Node*> deletedMovies = ternaryIndex.find(lowerkey, upperkey);
    
    for (std::list<typename MSTT::Node*>::const_iterator itr = deletedMovies.begin();
        itr != deletedMovies.end(); ++itr)
    {
        Movie::SecondaryKey currentKey( (*itr)->data->getTitle(), (*itr)->data->getDirector() );
        primaryIndex.remove((*itr)->data->getID());
        secondaryIndex.remove(currentKey);
        ternaryIndex.remove(currentKey);
    }

}


// IMPLEMENT
void
MovieStore::makeAvailable(const std::string & id)
{
    MovieStore::MSTP::Node* found = primaryIndex.find(id);
    if (found != nullptr) {
        found->data.setAvailable();
    }
}


// IMPLEMENT
void
MovieStore::makeUnavailable(const std::string & title,
                           const std::string & director)
{
    Movie::SecondaryKey skey(title, director);
    MovieStore::MSTS::Node* found = secondaryIndex.find(skey);
        if (found != nullptr) {
            MovieStore::MSTP::Node* foundNode = primaryIndex.find(found->data->getID());
            if (foundNode != nullptr) {
                foundNode->data.setUnavailable();
            }
        }
}


// IMPLEMENT
void
MovieStore::updateCompany(const std::string & director, 
                           const std::string & Company)
{
    Movie::SecondaryKey lower("a", director);
    Movie::SecondaryKey upper("z", director);
    std::list<typename MSTS::Node*> updatedMovies = secondaryIndex.find(lower, upper);

    for (std::list<typename MSTS::Node*>::const_iterator itr = updatedMovies.begin();
        itr != updatedMovies.end(); ++itr)
    {
        MovieStore::MSTP::Node* currentNode = primaryIndex.find((*itr)->data->getID());
        if (currentNode != nullptr) {
            currentNode->data.setCompany(Company);
        }
    }


}


// IMPLEMENT
void
MovieStore::printMoviesWithID(const std::string & id1,
                              const std::string & id2,
                              unsigned short since) const
{
    std::list<typename MSTP::Node*> movieList = primaryIndex.find(id1, id2);

    for (std::list<typename MSTP::Node*>::const_iterator itr = movieList.begin(); itr != movieList.end(); ++itr) {
        if ((*itr)->data.getYear() >= since) {
            std::cout << (*itr)->data << std::endl;
        }
    }
}


// IMPLEMENT
void
MovieStore::printMoviesOfDirector(const std::string& director,
    const std::string& first,
    const std::string& last) const
{
    Movie::SecondaryKey lower(first, director);
    Movie::SecondaryKey upper(last, director);
    DirectorComparator dc;

    std::list<typename MSTS::Node*> movieList = secondaryIndex.find(lower, upper);
    for (std::list<typename MSTS::Node*>::const_iterator itr = movieList.begin();
        itr != movieList.end(); ++itr)
    {
        MovieStore::MSTP::Node* currentNode = primaryIndex.find((*itr)->data->getID());
        if (currentNode != nullptr) {
            std::cout << currentNode->data << std::endl;
        }

    }


}



void  // implemented, do not change
MovieStore::printPrimarySorted( ) const
{
  printPrimarySorted(primaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printPrimarySorted(MSTP::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printPrimarySorted(t->left);
  std::cout << t->data << std::endl;
  printPrimarySorted(t->right);
}


void  // implemented, do not change
MovieStore::printSecondarySorted( ) const
{
  printSecondarySorted(secondaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printSecondarySorted(MSTS::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printSecondarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printSecondarySorted(t->right);
}


void  // implemented, do not change
MovieStore::printTernarySorted( ) const
{
  printTernarySorted(ternaryIndex.getRoot());
}


void  // implemented, do not change
MovieStore::printTernarySorted(MSTT::Node * t) const
{
  if (t == NULL)
  {
    return;
  }

  printTernarySorted(t->left);
  std::cout << *(t->data) << std::endl;
  printTernarySorted(t->right);
}

