#ifndef RELATIONTYPE_H
#define RELATIONTYPE_H

#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

class IDdata;
class Person;
class Medical_Status;
class Registration;
class Treatment;

template<class T> class person;


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
        int profession;
        int birthday;
        int age_group;
      
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


class MedicalStatus: public IDdata {
    public:
        int risk_status;
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
        int waiting_time;
        int treated_loctation;
        int treated_time;
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
        string location;
        /*void print() {
            cout.setf(std::ios::left);
            cout.width(20);
            cout << this->getRecordID() << "|";
            cout << location << endl;
        }*/
};


template<class T> class patient{
    public:
    T priority;    //key value
    int degree;            // degree
    int id;
	char name[30];
	char contact[11]; //number digit of 11
	char address[10]; //the address, not know how to use
	int prof; 
	int birth;  
	int risk;  
	int register_time;  // when he is register
    int treated_time;  //the time to be treated
    int treated_location;   //the place to be treated
	int aging;   // the age group he is in
	int status; // whether he is in waiting , appointed, or else
		
	int treat_ddl;  //the deadline of the treated date
	int near_hospital;    //the closed hospital who can get treated
	int loc;
    
    
    
};

#endif