#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

	void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
		//unique_lock<recursive_mutex> g(m);
		Compte & debiteur = comptes[deb];
		Compte & crediteur = comptes[cred];
		if (deb == cred) {
			return;
		}
		bool ok = false;
		while (!ok) {
			if (debiteur.try_lock()) {
				if (crediteur.try_lock()) {
					if (debiteur.debiter(val)) {
						crediteur.crediter(val);
					}
					ok = true;
					crediteur.unlock();
				}
				debiteur.unlock();
			}
			if (!ok) {
				this_thread::yield();
			}
		}
		/*
		if (deb < cred) {
			debiteur.lock();
			crediteur.lock();
		}
		else {
			crediteur.lock();
			debiteur.lock();
		}
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}
		debiteur.unlock();
		crediteur.unlock();
		*/
	}
	size_t Banque::size() const {
		return comptes.size();
	}
	bool Banque::comptabiliser (int attendu) const {
		//unique_lock<recursive_mutex> g(m);
		int bilan = 0;
		int id = 0;
		for (const auto & compte : comptes) {
			compte.lock();
			cout << "Compte " << id << " : " << compte.getSolde() << endl;
			bilan += compte.getSolde();
			id++;
		}
		for (const auto & compte : comptes) {
			compte.unlock();
		}
		if (bilan != attendu) {
			cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		else {
			cout << "Bilan comptable tout va bien : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		return bilan == attendu;
	}
}
