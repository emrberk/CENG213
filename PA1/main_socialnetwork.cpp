#include <iostream>

#include "SocialNetwork.h"

int main() {
    SocialNetwork snetwork;

    
/*
    snetwork.addProfile("john", "doe", "john@doe.com");




    snetwork.addProfile("jim", "tester", "email1@email");

    snetwork.addProfile("jan", "tester", "email2@email");

    snetwork.addProfile("michael", "pester", "email3@email");

    snetwork.addProfile("dwight", "ester", "email4@email");

    snetwork.addPost("this is a test post!", "email1@email");

    snetwork.addPost("this is second testcase!", "email2@email");

    snetwork.addPost("Hello world! My name is John Doe.", "john@doe.com");

    snetwork.addPost("will the system fail?", "email3@email");





    snetwork.makeFriends("john@doe.com", "email3@email");
    snetwork.makeFriends("john@doe.com", "email2@email");
    snetwork.makeFriends("john@doe.com", "email1@email");
    snetwork.makeFriends("john@doe.com", "email4@email");
    snetwork.makeFriends("email2@email", "email4@email");
    snetwork.makeFriends("email3@email", "email4@email");
    snetwork.makeFriends("email1@email", "email4@email");


    snetwork.likePost(4, "email2@email");
    snetwork.likePost(2, "email1@email");
    snetwork.likePost(3, "email4@email");
    snetwork.likePost(3, "email3@email");
    snetwork.likePost(3, "john@doe.com");
    snetwork.likePost(1, "email4@email");
    snetwork.likePost(2 , "email3@email");
    snetwork.likePost(4, "email3@email");
    snetwork.likePost(1, "email3@email");
    snetwork.print();

    snetwork.deleteProfile("email1@email"); 
    snetwork.deleteProfile("john@doe.com");
    snetwork.unlikePost(4, "email2@email");

    snetwork.unlikePost(3, "email4@email");
    snetwork.unlikePost(3, "email3@email");



    snetwork.unlikePost(4, "email3@email");
    snetwork.unlikePost(2, "email3@email");
    snetwork.unlikePost(3, "john@doe.com");
    snetwork.deleteProfile("email4@email");
    snetwork.print();
        snetwork.deleteProfile("email3@email");
        snetwork.print();
    snetwork.deleteProfile("email2@email");
    snetwork.print();
    snetwork.deleteProfile("email2@email");



    snetwork.print();

*/
    snetwork.addProfile("emma", "johnson", "emma@johnson");
    snetwork.addProfile("noah", "brown", "noah@brown");
    snetwork.addProfile("oliver", "martinez", "oliver@martinez");
    snetwork.addProfile("liam", "smith", "liam@smith");
    snetwork.addProfile("olivia", "williams", "olivia@williams");

    snetwork.addPost("this is liam", "liam@smith");
    snetwork.addPost("this is olivia", "olivia@williams");
    snetwork.addPost("this is noah", "noah@brown");
    snetwork.addPost("this is emma", "emma@johnson");
    snetwork.addPost("this is oliver", "oliver@martinez");

    snetwork.makeFriends("noah@brown", "liam@smith");
    snetwork.makeFriends("noah@brown", "emma@johnson");
    snetwork.makeFriends("oliver@martinez", "emma@johnson");
    snetwork.makeFriends("liam@smith", "olivia@williams");

    snetwork.likePost(2, "noah@brown");
    snetwork.likePost(5, "emma@johnson");
    snetwork.likePost(2, "liam@smith");
    snetwork.likePost(3, "liam@smith");
    snetwork.print();


    snetwork.deleteProfile("liam@smith");
    snetwork.print();

    snetwork.deleteProfile("olivia@williams");
    snetwork.print();

    snetwork.deleteProfile("noah@brown");
    snetwork.print();

    snetwork.deleteProfile("emma@johnson");
    snetwork.print();

    snetwork.deleteProfile("oliver@martinez");



    snetwork.print();

    return 0;
}
