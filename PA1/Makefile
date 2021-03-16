CC=g++
CFLAGSNETWORK=-ggdb -ansi -Wall -pedantic-errors -O0 -std=c++11 SocialNetwork.cpp SocialNetwork.h SocialNetworkWrapper.cpp SocialNetworkWrapper.h utils.h Post.cpp Post.h Profile.cpp Profile.h LinkedList.h Node.h
CFLAGSLL=-ggdb -ansi -Wall -pedantic-errors -O0 -std=c++11 LinkedList.h Node.h

all: socialnetwork linkedlist

socialnetwork:
	$(CC) $(CFLAGSNETWORK) test6.cpp -o test6.out
	$(CC) $(CFLAGSNETWORK) test8.cpp -o test8.out 
	$(CC) $(CFLAGSNETWORK) test9.cpp -o test9.out 
	$(CC) $(CFLAGSNETWORK) customtest1SN.cpp -o ctest1.out 
	$(CC) $(CFLAGSNETWORK) customtest2SN.cpp -o ctest2.out
linkedlist:
	$(CC) $(CFLAGSLL) linkedlisttest.cpp -o lltest.out
.PHONY: out
out:
	./test8.out > out/8.txt
	./test6.out > out/6.txt
	./test9.out > out/9.txt
	./ctest1.out > out/c1.txt
	./ctest2.out > out/c2.txt
	./lltest.out > out/ll.txt
test: socialnetwork linkedlist out
	diff out/8.txt exp/8.txt > diff/8.txt 
	diff out/6.txt exp/6.txt > diff/6.txt
	diff out/9.txt exp/9.txt > diff/9.txt
	diff out/c1.txt exp/c1.txt > diff/c1.txt
	diff out/c2.txt exp/c2.txt > diff/c2.txt
	diff out/ll.txt exp/ll.txt > diff/ll.txt
clean:
	rm *.o
	rm linkedlist
	rm socialnetwork
