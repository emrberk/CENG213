#include "SocialNetwork.h"

#include <iostream>

SocialNetwork::SocialNetwork() {

}

void SocialNetwork::addProfile(const std::string& firstname, const std::string& lastname, const std::string& email) {
    Profile newProfile(firstname, lastname, email);
    profiles.insertSorted(newProfile);
}



void SocialNetwork::addPost(const std::string& message, const std::string& email) {

    Post newPost(message);

    Node<Profile>* currprof;

    posts.insertAtTheTail(newPost);

    for (currprof = profiles.getFirstNode(); currprof != nullptr; currprof = currprof->next) {
        if (currprof->data.getEmail() == email) {
            Post* postptr = &(posts.getLastNode()->data);
            currprof->data.getPosts().insertAtTheTail(postptr);
            break;
        }
    }


}

bool SocialNetwork::likes(Profile* prof, Post*post) {
    Node<Post*>* current;
    for (current = prof->getLikes().getFirstNode(); current != nullptr; current = current->next) {

        if (current->data == post) {
            return true;
        }
    }
    return false;

}

void SocialNetwork::deleteProfile(const std::string& email) {

    Node<Profile>* currprof;
    Node<Profile>* currprof1;
    Profile* deletedProfile = nullptr;
    Node<Profile*>* currfriend;
    Node<Post*>* currpost;
    Node<Post*>* current;



    for (currprof1 = profiles.getFirstNode(); currprof1 != nullptr; currprof1 = currprof1->next) {
        if (currprof1->data.getEmail() == email) {
            deletedProfile = &currprof1->data;
            break;
        }

    }
    if (deletedProfile == nullptr) {
        return;
    }

    for (currfriend = deletedProfile->getFriends().getFirstNode(); currfriend != nullptr; currfriend = currfriend->next) {

        currfriend->data->dropFriend(deletedProfile);
    }
   
   for (currpost = deletedProfile->getPosts().getFirstNode(); currpost != nullptr; currpost = currpost->next) {

        for (currprof = profiles.getFirstNode(); currprof != nullptr; currprof = currprof->next) {

            if (likes(&currprof->data, currpost->data)) {
                currprof->data.dropLike(currpost->data);
            }
        }

    }
    for (current = deletedProfile->getPosts().getFirstNode(); current != nullptr; current = current->next) {
        posts.removeNode(*current->data);

    }



    deletedProfile->getFriends().removeAllNodes();
    deletedProfile->getLikes().removeAllNodes();
    deletedProfile->getPosts().removeAllNodes();


    profiles.removeNode(*deletedProfile);


}

void SocialNetwork::makeFriends(const std::string& email1, const std::string& email2) {
    Node<Profile>* current;
    Node<Profile>* first = nullptr;
    Node<Profile>* second = nullptr;

    for (current = profiles.getFirstNode(); current != nullptr; current = current->next) {

        if (current->data.getEmail() == email1 || current->data.getEmail() == email2) {
            if (first == nullptr) first = current;
            else { second = current; }
        }
    }
    Profile* prof1 = &first->data;
    Profile* prof2 = &second->data;
    first->data.addFriend(prof2);
    second->data.addFriend(prof1);
}

void SocialNetwork::likePost(int postId, const std::string& email) {

    Node<Profile>* current;
    Node<Post>* currpost;
    Post* result = nullptr;
    for (currpost = posts.getFirstNode(); currpost != nullptr; currpost = currpost->next) {
        if (currpost->data.getPostId() == postId) {
            result = &(currpost->data);
            break;
        }
    }
    for (current = profiles.getFirstNode(); current != nullptr; current = current->next) {

        if (current->data.getEmail() == email) {

            current->data.addLike(result);
            break;

        }
    }
}

void SocialNetwork::unlikePost(int postId, const std::string& email) {

    Node<Profile>* current;
    Node<Post>* currpost;
    Post* result = nullptr;
    for (currpost = posts.getFirstNode(); currpost != nullptr; currpost = currpost->next) {
        if (currpost->data.getPostId() == postId) {
            result = &(currpost->data);
            break;
        }
    }
    for (current = profiles.getFirstNode(); current != nullptr; current = current->next) {

        if (current->data.getEmail() == email) {

            current->data.dropLike(result);
            break;

        }
    }
}

LinkedList<Profile*> SocialNetwork::getMutualFriends(const std::string& email1, const std::string& email2) {
    Node<Profile*>* currentprof1;
    Node<Profile*>* currentprof2;
    Node<Profile>* current;
    LinkedList<Profile*> mutuals;
    Node<Profile>* first = nullptr;
    Node<Profile>* second = nullptr;
    for (current = profiles.getFirstNode(); current != nullptr; current = current->next) {

        if (current->data.getEmail() == email1) {
            first = current;
           
        }
        else if (current->data.getEmail() == email2) {
            second = current;
        }
    }

    for (currentprof1 = first->data.getFriends().getFirstNode(); currentprof1 != nullptr; currentprof1 = currentprof1->next) {
        
        for (currentprof2 = second->data.getFriends().getFirstNode(); currentprof2 != nullptr; currentprof2 = currentprof2->next) {

            if (currentprof1->data == currentprof2->data) {
                mutuals.insertAtTheTail(currentprof1->data);
            }

        }
    }
    return mutuals;

}

LinkedList<Post*> SocialNetwork::getListOfMostRecentPosts(const std::string& email, int k) {
    Node<Profile>* current;
    Node<Post*>* currpost;
    LinkedList<Post*> recents;
    Node<Profile>* prof=nullptr;
    int i = 0;
    for (current = profiles.getFirstNode(); current != nullptr; current = current->next) {
    
        if (current->data.getEmail() == email) {
            prof = current;
            break;
        }
    
    
    }
    for (currpost = prof->data.getPosts().getLastNode(); currpost != nullptr; currpost = currpost->prev) {
        i++;
        if (i > k) {
            return recents;
        }
        else {
            recents.insertAtTheTail(currpost->data);
        }

    }
    
	return recents;
}

void SocialNetwork::print() const {
    std::cout << "# Printing the social network ..." << std::endl;

    std::cout << "# Number of profiles is " << profiles.getNumberOfNodes() << ":" << std::endl;
    profiles.print();

    std::cout << "# Number of posts is " << posts.getNumberOfNodes() << ":" << std::endl;
    posts.print();

    std::cout << "# Printing is done." << std::endl;
}

