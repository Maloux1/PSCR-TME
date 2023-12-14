#pragma once

#include <mutex>
#include <condition_variable>

using namespace std;

namespace pr {

	class Barrier {
		private:
			mutable mutex m;
			unsigned int compteur;
			unsigned int n;
			condition_variable cv;
		public:
			Barrier(unsigned int n) : compteur(0), n(n){

			}
			~Barrier() {

			}
			void done() {
				std::unique_lock<std::mutex> lg(m);
				compteur++;
				while (compteur != n) {
					cv.wait(lg);
				}
				cv.notify_all();
			}
			void waitFor() {
				std::unique_lock<std::mutex> lg(m);
				if (compteur != n) {
					cv.wait(lg);
				}
			}
	};

}