#include "moviestore.h"


//Expected output is in "main_moviestore.out"

void printAllMoviesSorted(const MovieStore & store)
{
  std::cout << "All movies (id sorted):" << std::endl;
  store.printPrimarySorted();
  std::cout << "---------------------------------" << std::endl;

  std::cout << "All movies (director-title sorted):" << std::endl;
  store.printSecondarySorted();
  std::cout << "---------------------------------" << std::endl;

  std::cout << "All movies (title-director sorted):" << std::endl;
  store.printTernarySorted();
  std::cout << "---------------------------------" << std::endl;
}


int main()
{
	MovieStore myStore;

	for (int i = 0; i < 999; i++) {
		std::string str = std::to_string(i);
		std::string str2 = std::to_string(i + 2);
		std::string str3 = std::to_string(i + 1);
		myStore.insert(Movie(str, str2, str3, str, 100, 120));
	}

	return 0;
}

