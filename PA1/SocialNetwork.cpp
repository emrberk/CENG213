#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {
    
}

void SocialNetwork::addProfile(const std::string &firstname, const std::string &lastname, const std::string &email) {
    Profile newProfile(firstname, lastname, email);
    profiles.insertSorted(newProfile);
}

void SocialNetwork::addPost(const std::string &message, const std::string &email) {
    
    Post* newPost = new Post(message);
    
    Node<Profile>* currprof;
    
    posts.insertAtTheTail(*newPost);

    for(currprof=profiles.getFirstNode(); currprof!=nullptr; currprof=currprof->next) {
        if(currprof->data.getEmail() == email) {
            currprof->data.addPost(newPost);
        }
    }


}



void SocialNetwork::deleteProfile(const std::string &email) {
    
    Node<Profile>* currprof;
    Profile* deletedProfile;
    Node<Profile*>* currfriend;
    
    for(currprof=profiles.getFirstNode(); currprof!=nullptr; currprof=currprof->next) {
        if(currprof->data.getEmail()== email) {
            deletedProfile = &currprof->data;
            std::cout << "a" << std::endl;
        }
    std::cout << *deletedProfile << std::endl;
    break;
    }
    for(currfriend=deletedProfile->getFriends().getFirstNode();currfriend!=nullptr;currfriend=currfriend->next) {

        currfriend->data->dropFriend(deletedProfile);
    }
    

}

void SocialNetwork::makeFriends(const std::string &email1, const std::string &email2) {
    Node<Profile>*current;
    Node<Profile>*first=nullptr;
    Node<Profile>*second=nullptr;

    for(current=profiles.getFirstNode(); current!=nullptr; current=current->next) {

        if(current->data.getEmail()==email1 || current->data.getEmail()==email2) {
            if(first==nullptr) first = current;
            else {second=current;}
        }
    }
    first->data.addFriend(&second->data);
    second->data.addFriend(&first->data);
}

void SocialNetwork::likePost(int postId, const std::string &email) {
    
    Node<Profile>*current;
    Node<Post>*currpost;
    Post* result;
    for(currpost=posts.getFirstNode(); currpost!=nullptr; currpost=currpost->next) {
        if(currpost->data.getPostId()==postId) {
            result = &(currpost->data);
            break;
        }
    }
    for(current=profiles.getFirstNode(); current!=nullptr; current=current->next) {

        if(current->data.getEmail()==email) {
            
            current->data.addLike(result);
            break;

        }    
    }
}

void SocialNetwork::unlikePost(int postId, const std::string &email) {
    /* TODO */
}

LinkedList<Profile *> SocialNetwork::getMutualFriends(const std::string &email1, const std::string &email2) {
    /* TODO */
}

LinkedList<Post *> SocialNetwork::getListOfMostRecentPosts(const std::string &email, int k) {
    /* TODO */
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}
