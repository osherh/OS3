#ifndef RECEPTIONHOUR_H_
#define RECEPTIONHOUR_H_

#include <unordered_map>
#include <pthread.h>

enum StudentStatus {
	ENTERED = 0,
	LEFT_BECAUSE_NO_SEAT,
	LEFT_BECAUSE_DOOR_CLOSED
};

class ReceptionHour {
public:
	ReceptionHour(unsigned int max_waiting_students);
	~ReceptionHour();

	void startStudent(unsigned int id);
	StudentStatus finishStudent(unsigned int id);
	
	void closeTheDoor();

	bool waitForStudent();
	void waitForQuestion();
	void giveAnswer();

	StudentStatus waitForTeacher();
	void askQuestion();
	void waitForAnswer();

	void* taThreadHandler();
	void* studentThreadHandler();


protected:
	unsigned int students_num;
	unsigned int max_waiting_students;
	typedef struct waiting_students {
		struct waiting_students *next;
		unsigned int studentID;
		StudentStatus status;
		pthread_t waitingStudents;
	}* waiting_students_t;
	waiting_students_t waiting_students_list;
	pthread_t * ta;
	bool doorClosed;
	// TODO: define the member variables
	// Remember: you can only use mutexes and condition variables!
};

#endif // RECEPTIONHOUR_H_

