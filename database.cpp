#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
#include "database.h"

template <class T> void Maindata<T>::insert(patient_f* p)
{
    person.insert(p);
    medical_status.insert(p);
    registration.insert(p);
    treatment.insert(p);
    return;
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

//relation 的类成员函数

template <class T> bool relation<T>::insert(patient_f* p)
{
    
    bool all_full = true;
    T record=new T(patient_f* p;);
    // iterate through the list
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter)
    {
        if (!iter->full()) { // if this block is not full, insert into it
        iter->overflowBuffer.push_back(record);
        // if after insertion the block is full, sort it.
        if (iter->full()) iter->Sort();
        all_full = false;
        return true;
        }
    }
    // if new block is needed
    if (blocks.empty() || all_full) {
        Block<T> newBlock;
        newBlock.overflowBuffer.push_back(record);
        blocks.push_back(newBlock);
        return true;
    }

    // unreachable
    return false;
}
template <class T> bool relation<T>::search(int id)
{
    T* x = this->retrieve(key);
    return (x->getid() != -1);
}
template <class T> T relation<T>::retrieve(int id)
{
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
        if (A[i].getid() == key)
        return A[i];
    }
    T x;
    x.setid(-1);
    return x;
}
template <class T> void relation<T>::modify(int id,patient_f* p)
{
    T* tmp=retrive(id);
    if (T->getid()==-1)
    {
        return;
    }
    remove(id);
    insert(p);
    return;

}


    


