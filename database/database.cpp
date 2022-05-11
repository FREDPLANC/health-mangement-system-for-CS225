#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
#include "database.h"
#include "relationType.h"

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
template <class T> void Maindata<T>::remove(patient_f* p)
{
    person.remove(p);
    medical_status.remove(p);
    registration.remove(p);
    treatment.remove(p);
    return;
}
template <class T> bool Maindata<T>::add_patient(patient_f* p)
{
    switch (p->treatment_type)
    {
    case 0/* constant-expression */:
        center1->add_patient(p);
        break;
    case 1
        center2->add_patient(p);
        break;

    case 2
        center3->add_patient(p);
        break;
    default:
        cout<<"wrong treatment type!"<<endl; 
        break;
    }
}
template <class T> T Maindata<T>::retrieveperson(int id)
{
    return person.retrieve(id);
}
template <class T> T Maindata<T>::retrievestatus(int id)
{
    return medical_status.retrieve(id);
}
template <class T> T Maindata<T>::retrieveregistration(int id)
{
    return registration.retrieve(id);
}
template <class T> T Maindata<T>::retrievetreatment(int id)
{
    return treatment.retrieve(id);
}






//relation 's member function

template <class T> bool relation<T>::insert(patient_f* p)
{
    
    bool all_full = true;
    T record=new T(patient_f* p;);
    // 遍历relation中的所有block
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter)
    {
        if (!iter->full()) { //若当前block未满, 放入overflowblock
        iter->overflowBuffer.push_back(record);
        //若插入后满, sort
        if (iter->full()) iter->Sort();
        all_full = false;
        return true;
        }
    }
    // 若当前relation为空或已满
    if (blocks.empty() || all_full) {
        block<T> newBlock;
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
template<class T> bool relation<T>::remove(int key) {
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
        if (A[i].getRecordID() == key) {
            bool full = iter->full();
            // delete this element
            swap(A[i], A[(int)A.size()-1]);
            A.pop_back();
            if (full) { // if after deletion the block is not full, put all elements back into overflowBuffer
                iter->array.swap(iter->overflowBuffer);
                iter->array.clear();
            }
            if (iter->size() == 0)
                this->blocks.erase(iter);
            return true;
        }
    }
    return false;
}