#ifndef RELATIONTYPE_H
#define RELATIONTYPE_H

#include <string>
#include <typeinfo>
#include <vector>
#include <string.h>
using namespace std;

class IDdata;
class Person;
class Medical_Status;
class Registration;
class Treatment;


class patient_f {
	public:
        int priority;
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
		
        int treat_time; 
        int treatment_type;
        int treat_hospital;
		/* Class Functions */
		patient_f(){
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
		patient_f(const patient_f &c){
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
            treat_time = c.treat_time;
            treatment_type = c.treatment_type;
            treat_hospital = c.treat_hospital;
		}
		patient_f(int nid, char nam[30], int pro, int tim, int ris, int phone, int bir, int status);
		  //~patient();
		void age_rank(); // judge which age group he is in
		bool marked;
		int degree;
};


class IDdata { //IDdata 存放了独一无二的identity作为主键。
    public:
        bool operator< (const IDdata& temp_data) const{
            return this->ID < temp_data.ID;
        }

        void setID(int NEWID) {
            this->ID = NEWID;
            return;
        }
        int getID() {
            return this->ID;
        }
    private:
        int ID;
};


class Person: public IDdata {
    public:
        char name[30];
	    char contact[11]; //number digit of 11
	    char address[10]; //the address, not know how to use
        int prof;
        int birthday;
        int aging;
        int priority;
        int loc;
        int time;
        Person(){};
        Person(patient_f *P){
                this->priority = P->priority;
                this->setID(P->id);
                strcpy(this->name,P->name);
                strcpy(this->contact,P->contact);
                strcpy(this->address,P->address);
                this->prof = P->prof;
                this->birthday = P->birth;
                this ->aging = P->aging;
                this->loc = P->loc;
                this->time = P->time;
        }
        void modify(patient_f *P){
                this->setID(P->id);
                strcpy(this->name,P->name);
                strcpy(this->contact,P->contact);
                strcpy(this->address,P->address);
                this->prof = P->prof;
                this->birthday = P->birth;
                this ->aging = P->aging;
                this->loc = P->loc;
                this->time = P->time;
        }
      
        /*void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout.width(20);
            cout << name << "|";
            cout.width(20);
            cout << email << "|";
            cout.width(20);
            cout << profession << "|";
            cout.width(10);
            cout << birthday << "|";
            cout.width(5);
            cout << age_group << endl;
        }*/
};


class Medical_Status: public IDdata {
    public:
        int risk;
        Medical_Status(patient_f*P){
            this->setID(P->id);
            this->risk = P->risk;
        }
        void modify(patient_f * P){
            this->setID(P->id);
            this->risk = P->risk;
        }
        /*void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << risk_status << endl;
        }*/
};
class Registration: public IDdata {
    public:
        int priority;
        int treatment_type;
        int register_time;
        int status;
        int treat_ddl;
       // int treated_time;
        Registration(){};
        Registration(patient_f *P){
            this->setID(P->id);
            this->priority = P->priority;
            this->treatment_type = P->treatment_type;
            this->register_time = P->time;
            this->status = P->status;
            this->treat_ddl = P->treat_ddl;
            //this->waiting_time = P.

        }
        void modify(patient_f *P){
            this->setID(P->id);
            this->priority = P->priority;
            this->treatment_type = P->treatment_type;
            this->register_time = P->time;
            this->status = P->status;
            this->treat_ddl = P->treat_ddl;
        }
       /* void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << priority << endl;
        }*/
};


class Treatment: public IDdata {
    public:
        int treatment_time;
        int treat_hospital;
        Treatment(){

        };
        Treatment(patient_f *P){
            this->setID(P->id);
            this->treatment_time = P->treat_time;
            this->treat_hospital = P->treat_hospital;
        }
        void modify(patient_f *P){
            this->setID(P->id);
            this->treatment_time = P->treat_time;
            this->treat_hospital = P->treat_hospital;
        }
        /*void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << location << endl;
        }*/
};


#endif