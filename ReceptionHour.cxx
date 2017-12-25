#include "ReceptionHour.h"

#include <pthread.h>

ReceptionHour::ReceptionHour(unsigned int max_waiting_students) {
	this->max_waiting_students = max_waiting_students;
	this->waiting_students_list  = new waiting_students_t();
	students_num = 0;
	this->doorClosed = false;
	pthread_create(ta, NULL, taThreadHandler, NULL);
}

void* ReceptionHour::studentThreadHandler() {

	waitForTeacher();
	askQuestion();
	waitForAnswer();
}

void* ReceptionHour::taThreadHandler() {
	waitForStudent();
	waitForQuestion();
	giveAnswer();
}

ReceptionHour::~ReceptionHour() {
}

void ReceptionHour::startStudent(unsigned int id) {
	//TODO lock
	waiting_students_t curr = new waiting_students_t();
	curr->studentID=id;
	if (!this->doorClosed)
	{
		curr->next = this->waiting_students_list->next;
		this->students_num++;
		if (this->students_num > this->max_waiting_students)
		{
			curr->status = StudentStatus::LEFT_BECAUSE_NO_SEAT;
		}
		else
		{
			curr->status = StudentStatus::ENTERED;
			pthread_t newStudent;
			pthread_create(&newStudent, NULL, studentThreadHandler, NULL);
			curr->waitingStudents=newStudent;
			waiting_students_t itr_st = this->waiting_students_list;
			while (NULL != itr_st)
			{
				if (id == itr_st->studentID){
					pthread_join(itr_st->waitingStudents,NULL);
				}
				itr_st = itr_st->next;
			}
		}

	}
	else
	{
		curr->status = StudentStatus::LEFT_BECAUSE_DOOR_CLOSED;
	}
	this->waiting_students_list->next=curr;
//TODO unlock

}

StudentStatus ReceptionHour::finishStudent(unsigned int id) {
	//TODO lock if needed
	waiting_students_t itr_st = this->waiting_students_list;
	StudentStatus status;
	while (NULL != itr_st->next)
	{
		if (id == itr_st->next->studentID){
			StudentStatus tempStatus = itr_st->next->status;
			waiting_students_t itr_st_temp = itr_st->next;
			itr_st->next = itr_st_temp->next;
			this->students_num--;
			delete itr_st_temp;
			return tempStatus;
		}
		itr_st = itr_st->next;
	}
	return status;
}

void ReceptionHour::closeTheDoor() {
	this->doorClosed = true;
}

bool ReceptionHour::waitForStudent() {
    if (0==students_num && doorClosed){
        return false;
    }
	if() //new student has arrived

}

void ReceptionHour::waitForQuestion() {
}

void ReceptionHour::giveAnswer() {
}

StudentStatus ReceptionHour::waitForTeacher() {

	return StudentStatus::ENTERED; //FIXME
}

void ReceptionHour::askQuestion() {
}

void ReceptionHour::waitForAnswer() {
}

