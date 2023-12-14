#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <cstddef>
#include <iterator>

template <typename iterator>
size_t count(iterator begin, iterator end) {
	size_t i=0;
	while (begin++ != end) {
		i++;
	}
	return i;
}

bool operator==(std::pair<std::string, int> a, std::string b) {
	if (a.first == b) {
		return true;
	}
	return false;
}

template <typename iterator, typename T>
size_t count_if_equal(iterator begin, iterator end, const T & val) {
	size_t i=0;
	while (begin != end) {
		if (*begin == *end){
			i++;
		}
		begin++;
	}
	return i;
}

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

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

  std::map<std::string, int> mots_presents = std::map<std::string, int>();

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
      mots_presents[word] += 1;
    
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
      cout << "Il y a " << mots_presents[*i] << " fois le mot " << *i << " dans le livre." << endl; 
    }
    std::vector<std::pair<std::string, int>> vector_copy_from_map(mots_presents.begin(), mots_presents.end());
    std::sort(vector_copy_from_map.begin(), vector_copy_from_map.end(), [] (const std::pair<std::string, int> & a, const std::pair<std::string, int> & b) {return a.second > b.second;});
    for (auto i=0; i<10 && i< vector_copy_from_map.size(); i++) {
      cout << "Le " << i+1 << "éme mot le plus présent est : " << vector_copy_from_map[i].first << endl;
    }
    cout << "test count (vector_copy_from_map): " << count(vector_copy_from_map.begin(), vector_copy_from_map.end()) << " " << vector_copy_from_map.size() << " end test." << endl;
    cout << "test count (mots_presents): " << count(mots_presents.begin(), mots_presents.end()) << " " << mots_presents.size() << " end test." << endl;

    return 0;
}


