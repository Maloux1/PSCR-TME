#pragma once

#include <cstdlib>
#include <mutex>
#include <condition_variable>
#include <cstring>

using namespace std;

namespace pr {

	// MT safe version of the Queue, blocking.
	template <typename T>
	class Queue {
		T ** tab;
		const size_t allocsize;
		size_t begin;
		size_t sz;
		condition_variable cv;
		mutable std::mutex m;
		bool blocking;

		// fonctions private, sans protection mutex
		bool empty() const {
			return sz == 0;
		}
		bool full() const {
			return sz == allocsize;
		}
	public:
		Queue(size_t size) :allocsize(size), begin(0), sz(0), blocking(true) {
			tab = new T*[size];
			memset(tab, 0, size * sizeof(T*));
		}
		void setBlocking(bool isBlocking) {
			blocking = isBlocking;
			if (!isBlocking) {
				cv.notify_all();
			}
		}
		size_t size() const {
			std::unique_lock<std::mutex> lg(m);
			return sz;
		}
		T* pop() {
			std::unique_lock<std::mutex> lg(m);
			while (empty()) {
				if (!blocking) {
					return nullptr;
				}
				cv.wait(lg);
			}
			T* ret = tab[begin];
			tab[begin] = nullptr;
			sz--;
			begin = (begin + 1) % allocsize;
			cv.notify_all();
			return ret;
		}
		bool push(T* elt) {
			std::unique_lock<std::mutex> lg(m);
			while (full()) {
				cv.wait(lg);
			}
			tab[(begin + sz) % allocsize] = elt;
			sz++;
			cv.notify_all();
			return true;
		}
		~Queue() {
			// ?? lock a priori inutile, ne pas detruire si on travaille encore avec
			for (size_t i = 0; i < sz; i++) {
				auto ind = (begin + i) % allocsize;
				delete tab[ind];
			}
			delete[] tab;
		}
	};

}
