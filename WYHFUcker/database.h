#ifndef DATABASE_H
#define DATABASE_H

#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include "BPlustree.h"
#include"BPlus_node.h"
#include"BPlus_node.cpp"
#include "BPlustree.cpp"
#include "btree.h"
#include"centerheap.h"

int Global_Block_count = 0;
int data_number = 0;
//int week_counter = 0;
using namespace std;

template<class T> class relation;
template<class T> class block;

// 1. 输入id,通过b+树,得到block_index,
// 2. 对每个relation,调用indx_to_id(), 输入block_index,返回id
// 3. 其余继续调用relation和Maindata的函数
template<class T> class relation

{
    public:
        relation(){};
        int insert(patient_f* p);
        bool search(int id);
        int indx_to_id(int block_rank); // 若有, 则返回id,若无,则返回-1
        bool remove(int id);
        T *retrieve(int id);
        void modify(int id,patient_f* p);
    
    private:
        list<block<T>> blocks;
        static const int MAX_BLOCK_CAPACITY = 5;
};

template<class T> class block
{
    public:
       static const int MAX_LENGTH = 5;
        block() {
            this->array.clear();
            this->overflowBlock.clear();
            
        }
        bool full() {
            return ((int)array.size() == MAX_LENGTH || (int)overflowBlock.size() == MAX_LENGTH);
        }
        int size() {
            if ((int)array.size() != 0) return (int)array.size();
            else return (int)overflowBlock.size();
        }
        void Sort(){
            
            overflowBlock.swap(array);
            overflowBlock.clear();
        }
        int getsize(){
            return array.size() + overflowBlock.size();
        }
        vector<T> array;
        vector<T> overflowBlock;
        int Block_number;


};

template<class T> class Maindata
{
    public:
    Maindata(){
        center1 = new centerHeap<T>();
        center2 = new centerHeap<T>();
        center3 = new centerHeap<T>();
        relation<Person> person;
        relation<Medical_Status> medical_status;
        relation<Registration> registration;
        relation<Treatment> treatment;
        CBPlusTree mainBP_Tree;

    };
    bool cmp(int x,int y);
    int insert(patient_f* p); // 成功则返回database ID, 失败则返回-1
    int indx_to_id (int indx);
    bool search(int id);
    void modify(int id,patient_f* p);
    void modifyperson(int id,patient_f* p);
    void modifystatus(int id,patient_f* p);
    void modifyregistration(int id,patient_f* p);
    void modifytreatment(int id,patient_f* p);
    Person*retrieveperson(int id);
    Medical_Status*retrievestatus(int id);
    Registration*retrieveregistration(int id);
    Treatment*retrievetreatment(int id);
    patient_f retrievepatient_f(int id);
    void remove(patient_f* p);
    void build(BTree<op>* btree_registered_1 , BTree<op>* btree_appointment_1, BTree<op>* btree_delaytreated_1,BTree<op>* btree_registered_2 , BTree<op>* btree_appointment_2, BTree<op>* btree_delaytreated_2,BTree<op>* btree_registered_3 , BTree<op>* btree_appointment_3, BTree<op>* btree_delaytreated_3);
    bool add_patient(patient_f p,BTree<op>* btree_registered_1 , BTree<op>* btree_appointment_1, BTree<op>* btree_delaytreated_1,BTree<op>* btree_registered_2 , BTree<op>* btree_appointment_2, BTree<op>* btree_delaytreated_2,BTree<op>* btree_registered_3 , BTree<op>* btree_appointment_3, BTree<op>* btree_delaytreated_3);
    centerHeap<int>* center1;
    centerHeap<int>* center2;
    centerHeap<int>* center3;
    CBPlusTree mainBP_Tree;
    void report_treated(BTree<op>* btree_treated);
    void report_registered(BTree<op>* btree_registered);
    void report_appointment(BTree<op>* btree_appointment);
    //BTree btree_treated;
    //BTree btree_appointment;
    //BTree btree_registered;
    void week_report(BTree<op>* btree_treated,BTree<op>* btree_appointment,BTree<op>* btree_registered);
    void month_report(BTree<op>* btree_treated,BTree<op>* btree_appointment,BTree<op>* btree_registered,int withdraw);
     void appointment_process(int date, BTree<op>* btree_delaytreated, BTree<op>* btree_treated, BTree<op>* btree_appointment, BTree<op>* btree_registered, centerHeap<T>* center );//process the appoint
    void mediumRisk_process(int date, BTree<op>* btree_delaytreated, BTree<op>* btree_treated, BTree<op>* btree_appointment, BTree<op>* btree_registered, centerHeap<T>* center); //medium risk process;  
    void treatment_process(int date, BTree<op>* btree_delaytreated, BTree<op>* btree_treated, BTree<op>* btree_appointment, BTree<op>* btree_registered, centerHeap<T>* center );  // process the treatment
    void pop_patient_wrtddl(centerNode<T> *root, int ddl, BTree<op>* btree_registered, BTree<op>* btree_appointment,int date,centerHeap<T>* center);
    void withdraw(int id, BTree<op>* btree_delaytreated,  BTree<op>* btree_appointment, BTree<op>* btree_registered, centerHeap<T>* center);
    private:
    relation<Person> person;
    relation<Medical_Status> medical_status;
    relation<Registration> registration;
    relation<Treatment> treatment;

};


#endif