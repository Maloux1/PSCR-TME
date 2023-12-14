#include <cstdlib>
#include "Banque.h"

using namespace std;
using namespace pr;

const int NB_THREAD = 10;
const int SOLDE_INITIAL = 100;
const int NB_COMPTES = 100;

void func(Banque& b) {
	for (int i=0; i<1000; i++) {
		b.transfert(rand()%NB_COMPTES, rand()%NB_COMPTES, 1 + rand()%SOLDE_INITIAL);
		std::this_thread::sleep_for(20ms);
	}
}

void checker(Banque& b) {
	b.comptabiliser(SOLDE_INITIAL*NB_COMPTES);
}

int main () {
	Banque b(NB_COMPTES, SOLDE_INITIAL);
	vector<thread> threads;
	for (int i=0; i<NB_THREAD; i++) {
		threads.push_back(thread(func, std::ref(b)));
	}
	//threads.push_back(thread(checker, std::ref(b)));
	for (auto & t : threads) {
		t.join();
	}
	checker(b);
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
