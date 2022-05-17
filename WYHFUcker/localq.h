#ifndef localq_h
#define localq_h
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "relationType.h"
#include "database.h"
using namespace std;



void daily_hosp_setZero(void);

class hospital;
class patient;
template<class T> class localQueue
{
	public:
		localQueue(int size = 10);
		T &operator[](int index);
		int getlength(void);
		bool isNull(void);
		T rear(void);  
		T front(void); 
		void En_queue(T value);
		patient_f De_queue(void);
		
    
	private:
		int maxsize, minsize;
		int first, last;
		int numitems;
		T *reprarray;
		
		void allocate(void);
		void deallocate(void);
};

class hospital{
	public:
		int hosp_id;
		int capacity_1;
		int capacity_2;
		int capacity_3;
		int loc;
		int content_1;
		int content_2;
		int content_3;

		hospital(){
			hosp_id = 0;
			capacity_1 = 0;
			capacity_2 = 0;
			capacity_3 = 0;
			loc = 0;
			content_1 = 0;
			content_2 = 0;
			content_3 = 0;
		}
		
		
};

class patient {
	public:
		int id;
		char name[30];
		char contact[11]; //number digit of 11
		char address[10]; //the address, not know how to use
		int prof; 
		int birth;  
		int risk;  
		int time;  // when he is registed
		int aging;   // the age group he is in
		int status; // whether he is in waiting , appointed, or else
		
		int treat_ddl;  //the deadline of the treated date
		int loc;    //the location of the patient
		
		/* Class Functions */
		patient(){
			int id = -1;
		char name[30];
		char contact[11]; //number digit of 11
		char address[10]; //the address, not know how to use
		int prof = -1; 
		int birth= -1;  
		int risk= -1;  
		int time= -1;  // when he is registed
		int aging= -1;   // the age group he is in
		int status; // w= -1hether he is in waiting , appointed, or else
		
		int treat_ddl= -1;  //the deadline of the treated date
		int loc= -1;    //the location of the patient
		}
		patient(const patient &c){
			//cout << c.prof;
			prof=c.prof;
			//cout << c.id;
			id = c.id;
			//
        	birth=c.birth;//
        	risk=c.risk;//
        	time=c.time;//
        
        	aging=c.aging;//
    
			treat_ddl=c.treat_ddl;//
			loc=c.loc;//
			strcpy(name,c.name);//
			strcpy(contact,c.contact);//
			strcpy(address,c.address);//
			status = c.status;
		}
		patient(int nid, char nam[30], int pro, int tim, int ris, int phone, int bir, int status);
		  //~patient();
		void age_rank(); // judge which age group he is in
		bool marked;
		int degree;
};

// Global variables
patient_f* N[1000];  // where patient are stored
int len_N=0;   // the number of patient
hospital* H[3]; //three hospital
int content_total_1 = 0;
int content_total_2 = 0;
int content_total_3 = 0;
int capacity_total_1 = 0;
int capacity_total_2 = 0;
int capacity_total_3 = 0;
localQueue<patient_f*> build_queue ();

#endif

