#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

using namespace std;

namespace pr {


	void poolWorker(Queue<Job>& q) {
		Job * job_ptr;
		while ((job_ptr = q.pop()) != nullptr) {
			job_ptr->run();
		}
		delete job_ptr;
	}

	class Pool {
		Queue<Job> queue;
		std::vector<std::thread> threads;
	public:
		Pool(int qsize) : queue(qsize) {

		}
		void start (unsigned int nbthread) {
			for (unsigned int i=0; i< nbthread; i++) {
				threads.push_back(thread(poolWorker, std::ref(queue)));
			}
		}
		void submit (Job * job) {
			queue.push(job);
		}
		void stop() {
			queue.setBlocking(false);
			unsigned int i;
			for (i=0; i< threads.size(); i++) {
				threads[i].join();
			}
		}
		~Pool() {}
	};

}

