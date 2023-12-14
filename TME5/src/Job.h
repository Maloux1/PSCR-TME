#pragma once

#include "Barrier.h"

#include <thread>
#include <iostream>

using namespace std;

namespace pr {

	class Job {
	public:
		virtual void run () = 0;
		virtual ~Job() {};
	};

	// Job concret : exemple

	class SleepJob : public Job {
		int calcul (int v) {
			std::cout << "Computing for arg =" << v << std::endl;
			// traiter un gros calcul
			this_thread::sleep_for(1s);
			int ret = v % 255;
			std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
			return ret;
		}
		int arg;
		int * ret;
		Barrier& barrier;
	public :
		SleepJob(int arg, int * ret, Barrier& b) : arg(arg), ret(ret), barrier(b) {}
		void run () {
			* ret = calcul(arg);
			barrier.done();
		}
		~SleepJob(){}
	};

}
