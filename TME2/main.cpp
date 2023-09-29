#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>

int* contains(std::vector<std::pair<std::string, int>>& v, const std::string& s){
  for (auto i = v.begin(); i != v.end(); i++) {
    if ((*i).first == s)
      return &((*i).second);
  }
  return nullptr;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("/tmp/WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

  std::vector mots_presents = std::vector<std::pair<std::string, int>>();

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
    if (word.empty())
      continue;
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
    int* res = contains(mots_presents, word);
    if (res == nullptr){
      mots_presents.push_back(make_pair(word, 1));
    }
    else {
      (*res)++;
    }
	}

	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Found a total of " << mots_presents.size() << " differents words." << std::endl;

    auto tab = std::vector<std::string>();
    tab.push_back("toto");
    tab.push_back("war");
    tab.push_back("peace");
    for (auto i = tab.begin(); i != tab.end(); i++) {
      int* res = contains(mots_presents, *i); 
      int r;
      if (res == nullptr){
        r = 0;
      }
      else {
        r = *res;
      }
      cout << "Il y a " << r << " fois le mot " << *i << " dans le livre." << endl; 
    }
    return 0;
}


