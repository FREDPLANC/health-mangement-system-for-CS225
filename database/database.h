#ifndef DATABASE_H
#define DATABASE_H

#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include "relationType.h"
#include "../b_tree/BPlustree.h"
#include"../b_tree/BPlus_node.h"
#include"../b_tree/BPlus_node.cpp"
#include "../b_tree/BPlustree.cpp"

int Global_Block_count = 0;
int data_number = 0;
using namespace std;

template<class T> class relation;
template<class T> class block;

template <class T> class Maindata
{
    public:
    Maindata(){
        center1 = new centerheap();
        center2 = new centerheap();
        center3 = new centerheap();
        relation<Person> person;
        relation<Medical_Status> medical_status;
        relation<Registration> registration;
        relation<Treatment> treatment;
        CBPlusTree mainBP_Tree;

    };
    int insert(patient_f* p); // 成功则返回database ID, 失败则返回-1
    bool search(int block_rank);
    bool search(int id);
    void modify(int id,patient_f* p);
    void modifyperson(int id,patient_f* p);
    void modifystatus(int id,patient_f* p);
    void modifyregistration(int id,patient_f* p);
    void modifytreatment(int id,patient_f* p);
    T retrieveperson(int id);
    T retrievestatus(int id);
    T retrieveregistration(int id);
    T retrievetreatment(int id);
    void remove(patient_f* p);
    void build();
    bool add_patient(patient_f* p);
    centerheap<T>* center1;
    centerheap<T>* center2;
    centerheap<T>* center3;
    CBPlusTree mainBP_Tree;
    private:
    relation<Person> person;
    relation<Medical_Status> medical_status;
    relation<Registration> registration;
    relation<Treatment> treatment;

};
template<class T> class relation

{
    public:
        relation();
        int insert(patient_f* p);
        bool search(int id);
        int indx_to_id(int block_rank); // 若有, 则返回id,若无,则返回-1
        bool remove(int id);
        T retrieve(int id);
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
            //std::sort(this->overflowBuffer.begin(), this->overflowBuffer.end());
            overflowBuffer.swap(array);
            overflowBuffer.clear();
        }
        int getsize(){
            return array.size() + overflowBlock.size();
        }
    private:
        
        vector<T> array;
        vector<T> overflowBlock;
        int Block_number;


};
#endif