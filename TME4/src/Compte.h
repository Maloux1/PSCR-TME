#pragma once
#include <thread>
#include <mutex>

using namespace std;

namespace pr {

	class Compte {
		mutable recursive_mutex m;
		int solde;
		public :
			Compte(int solde=0):solde(solde) {}
			void crediter (int val) {
				unique_lock<recursive_mutex> g(m);
				solde+=val ;
			}
			bool debiter (int val) {
				unique_lock<recursive_mutex> g(m);
				bool doit = solde >= val;
				if (doit) {
					solde-=val ;
				}
				return doit;
			}
			int getSolde() const {
				unique_lock<recursive_mutex> g(m);
				return solde;
			}
			// NB : vector exige Copyable, mais mutex ne l’est pas...
			Compte(const Compte & other) {
				other.m.lock();
				solde = other.solde;
				other.m.unlock();
			}
			void lock () const {
				m.lock();
			}
			void unlock() const {
				m.unlock();
			}
			bool try_lock () const {
				return m.try_lock();
			}
	};
}
