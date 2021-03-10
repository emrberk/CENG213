#include <iostream>

#include "SocialNetwork.h"

int main() {
    SocialNetwork snetwork;

    //snetwork.print();

    snetwork.addProfile("john", "doe", "john@doe.com");

    //snetwork.print();


    snetwork.addProfile("jim","tester","email1@email");

    snetwork.addProfile("jan","tester","email2@email");

    snetwork.addProfile("michael","pester","email3@email");

    snetwork.addProfile("dwight","ester","email4@email");

    snetwork.addPost("this is a test post!","email1@email");

    snetwork.addPost("this is second testcase!","email2@email");

    snetwork.addPost("Hello world! My name is John Doe.", "john@doe.com");

    snetwork.addPost("will the system fail?", "email3@email");

    //snetwork.testProfiles();



    snetwork.makeFriends("john@doe.com", "email3@email");
    snetwork.makeFriends("john@doe.com","email2@email");
    snetwork.makeFriends("john@doe.com","email1@email");
    snetwork.makeFriends("john@doe.com","email4@email");
    snetwork.likePost(4,"email2@email");
    snetwork.likePost(2,"email1@email");
    snetwork.deleteProfile("john@doe.com");
	snetwork.print();
    

    return 0;
}
