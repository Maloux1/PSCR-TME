#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	int fils = 0;
	std::cout << "main pid=" << getpid() << std::endl;
	for (int i=1, j=N; i<=N && j==N; i++ ) {
		if (fork() == 0) {
			fils = 0;
			std::cout << " i:j " << i << ":" << j << std::endl;
			for (int k=1; k<=i && j==N ; k++) {
				if ( fork() == 0) {
					fils = 0;
					j=0;
					std::cout << " k:j " << k << ":" << j << std::endl;
				}
				else {
					fils++;
				}
			}
		}
		else {
			fils++;
			break;
		}
	}
	for (int i=0; i<fils; i++){
		std::cout << "J'attends mon fils." << std::endl;
		wait(NULL);
	}
	return 0;
}
