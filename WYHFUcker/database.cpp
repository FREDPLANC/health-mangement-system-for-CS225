#ifndef DATA_BASE
#define DATA_BASE
#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
#include "database.h"
#include "relationType.h"
extern int date_treat;

extern int data_number;
extern int Global_block_count;

template <class T> int Maindata<T>::insert(patient_f* p)
{   
    int a=-1, b =-1, c = -1, d = -1;
    a = person.insert(p);
    b = medical_status.insert(p);
    c = registration.insert(p);
    d = treatment.insert(p);
    if(a == b &&  b == c && c == d  && a!= -1) return a ;
    return 0;
}
template<class T> int Maindata<T>::indx_to_id(int indx){
    if(person.indx_to_id(indx) == medical_status.indx_to_id(indx) && medical_status.indx_to_id(indx) == registration.indx_to_id(indx) && registration.indx_to_id(indx) == treatment.indx_to_id(indx) && treatment.indx_to_id(indx) != -1) {
        return person.indx_to_id(indx);
    }  
    cout << "wrong fucking indx_to_id" << endl;
    return -1;
}
template <class T> bool Maindata<T>::search(int id)
{
    return person.search(id);
}
template <class T> void Maindata<T>::modify(int id,patient_f* p)
{
    person.modify(id,p);
    medical_status.modify(id,p);
    registration.modify(id,p);
    treatment.modify(id,p);
    return;
}
template <class T> void Maindata<T>::modify_withdrawl(int id,patient_f* p)
{
    Registration * temp = registration.retrieve(id);
    temp ->status = p->status;
    return;
}
template <class T> void Maindata<T>::modifyperson(int id,patient_f* p)
{
    person.modify(id,p);
    
    return;
}
template <class T> void Maindata<T>::modifystatus(int id,patient_f* p)
{
    
    medical_status.modify(id,p);
    
    return;
}
template <class T> void Maindata<T>::modifyregistration(int id,patient_f* p)
{
    
    registration.modify(id,p);
    return;
}
template <class T> void Maindata<T>::modifytreatment(int id,patient_f* p)
{
    
    treatment.modify(id,p);
    return;

}
template <class T> void Maindata<T>::remove(patient_f* p)
{
    int id = p->id;
    person.remove(id);
    medical_status.remove(id);
    registration.remove(id);
    treatment.remove(id);
    return;
}
template <class T> bool Maindata<T>::add_patient(patient_f p,BTree<op>* btree_registered_1 , BTree<op>* btree_appointment_1, BTree<op>* btree_delaytreated_1,BTree<op>* btree_registered_2 , BTree<op>* btree_appointment_2, BTree<op>* btree_delaytreated_2,BTree<op>* btree_registered_3 , BTree<op>* btree_appointment_3, BTree<op>* btree_delaytreated_3)
{
    switch (p.treatment_type)
    {
    case 0:
        
        if (p.status==54188)
        {
            withdraw(p.id,btree_delaytreated_1, btree_appointment_1,btree_registered_1,center1);
        }
        else{
            center1->insert(p);
            op tmp = op(date_treat,p.id);
            btree_registered_1->BTree_insert(tmp);
            
        }
        //center1.add_patient(p);
        break;
    case 1:
        if (p.status==54188)
        {
            withdraw(p.id,btree_delaytreated_2,btree_appointment_2,btree_registered_2,center2);
        }
        else{
            center2->insert(p);
            op tmp = op(date_treat,p.id);
            btree_registered_2->BTree_insert(tmp);
            
        }
        //center1.add_patient(p);
        break;

    case 2:
        if (p.status==54188)
        {
            withdraw(p.id,btree_delaytreated_3,btree_appointment_3,btree_registered_3,center3);
        }
        else{
            center3->insert(p);
            op tmp = op(date_treat,p.id);
            btree_registered_3->BTree_insert(tmp);
            
        }
        //center1.add_patient(p);
        break;
    default:
        cout<<"wrong treatment type!"<<endl; 
        return false;
        
    }
    return true;
}

template <class T> Person*Maindata<T>::retrieveperson(int id)
{
    return person.retrieve(id);
}
template <class T> Medical_Status*Maindata<T>::retrievestatus(int id)
{
    return medical_status.retrieve(id);
}
template <class T> Registration*Maindata<T>::retrieveregistration(int id)
{
    return registration.retrieve(id);
}
template <class T> Treatment*Maindata<T>::retrievetreatment(int id)
{
    return treatment.retrieve(id);
}

template <class T> patient_f Maindata<T>::retrievepatient_f(int id){

    patient_f temp;
    Person *t1 = retrieveperson(id);
    Medical_Status *t2 = retrievestatus(id);
    Registration *t3 = retrieveregistration(id);
    Treatment *t4 = retrievetreatment(id);
    if((t1 == NULL)||(t2 == NULL)||(t3 == NULL)||(t4 == NULL)){
        cout<<"ji"<<endl;
        return temp;
    }
    strcpy(temp.name,t1->name);
    strcpy(temp.contact,t1->contact);
    strcpy(temp.address,t1->address);
    temp.priority = t1->priority;
    temp.aging = t1->aging;
    temp.birth = t1->birthday;
    temp.id = t1->getID();
    temp.loc = t1->loc;
    temp.prof = t1->prof;
    temp.risk = t2->risk;
    temp.status = t3->status;
    temp.time = t1->time;
    temp.treat_ddl = t3->treat_ddl;
    temp.treat_hospital = t4->treat_hospital;
    temp.treat_time = t4->treatment_time;
    temp.treatment_type = t3->treatment_type;

    return temp;
}




//relation 's member function

template <class T > int relation<T>::insert(patient_f* p)// 永远先插入未满的空桶, 返回当前插入的是第几个位置(从1开始)
{
    
    bool all_full = true;
    T temp_1 (p);
    T * temp = &temp_1;
    extern int Global_Block_count;
    int block_count = 0;
    // 遍历relation中的所有block
    typename list< block<T> >::iterator iterator = this->blocks.begin();
    for ( iterator=this->blocks.begin(); iterator != this->blocks.end(); ++iterator, ++block_count)
    {
        if (!iterator->full()) { //若当前block未满, 放入overflowblock
        iterator->overflowBlock.push_back(*temp); 
        //若插入后满, sort
        if (iterator->full()) iterator->Sort();
        all_full = false;
        vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
        int result = Blocker.size() + block_count*MAX_BLOCK_CAPACITY; // result 返回当前插入block 是第几个, 从1开始
        return result;
        }
    }
    // 若当前relation为空或已满
    if (blocks.empty() || all_full) {
        block<T> newBlock;
        newBlock.overflowBlock.push_back(*temp);
        blocks.push_back(newBlock);
        Global_Block_count++;
        int result = block_count* MAX_BLOCK_CAPACITY +1;
        return result;
    }

    // unreachable
    return false;
}
template <class T> bool relation<T>::search(int id)
{
    T* x = this->retrieve(id);
    if (!x) return false;
    return  true;
}

template <class T> int relation<T> ::indx_to_id(int block_rank)
{
    int block_row = (block_rank-1) / MAX_BLOCK_CAPACITY; //记录是第几个block
    int block_column = block_rank - block_row * MAX_BLOCK_CAPACITY; //记录是该block 的第几个元素
    int i = 0;
    typename list< block<T> >::iterator iterator=this->blocks.begin();
    for (iterator=this->blocks.begin(); iterator != this->blocks.end() && i < block_row; ++iterator){
        i++;
    }

    vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
    return Blocker[block_column -1].getID();
}

template <class T> T *relation<T>::retrieve(int id)
{   
    typename list< block<T> >::iterator iterator=this->blocks.begin();
    for (iterator=this->blocks.begin(); iterator != this->blocks.end(); ++iterator) {
        vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
        for (int i=0;i<(int)Blocker.size();i++){
            if (Blocker[i].getID() == id)
            return &Blocker[i];
        }
    }
    cout<<"false in retrieve id"<<endl;
    return NULL;
}
template <class T> void relation<T>::modify(int id,patient_f* p)
{
    T *tmp=retrieve(id);
    if (tmp->getID()==-1)
    {
        cout<<"modify ji"<<endl;
        return;
    }
    tmp->modify(p);
    return;

}
template<class T> bool relation<T>::remove(int id) {
    typename list< block<T> >::iterator iterator=this->blocks.begin();
    for (iterator=this->blocks.begin(); iterator != this->blocks.end(); ++iterator) {
        vector<T>& Blocker = (iterator->full()) ? iterator->array : iterator->overflowBlock;
        for (int i=0;i<(int)Blocker.size();i++)
        if (Blocker[i].getID() == id) {
            bool judge_full = iterator->full();
            // 删除该元素
            swap(Blocker[i], Blocker[(int)Blocker.size()-1]);
            Blocker.pop_back();
            data_number--;// 记录datanumber的全局变量递减
            if (judge_full) { //若删除前block是满的, 则在删除后将主block里的元素倒进overflowBlock中
                iterator->array.swap(iterator->overflowBlock);
                iterator->array.clear();
            }
            if (iterator->size() == 0){
                this->blocks.erase(iterator);
                extern int Global_Block_count;
                Global_Block_count--;
                }
            return true;
        }
    }
    return false;
}

#endif