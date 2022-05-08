#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
#include "database.h"

template <class T> void relation<T>::insert()
{
    //加油哦；
}
class ID:: int getid()
{
    return id;
}

class ID:: void setid(int t)
{
   id= t;
}

template <class T> void Maindata<T>::insert(patient* p)
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
template <class T> void Maindata<T>::modify(int id,patient* p)
{
    person.modify(id,p);
    medical_status.modify(id,p);
    registration.modify(id,p);
    treatment.modify(id,p);
    return;
}
template <class T> void Maindata<T>::modifyperson(int id,patient* p)
{
    person.modify(id,p);
    
    return;
}
template <class T> void Maindata<T>::modifystatus(int id,patient* p)
{
    
    medical_status.modify(id,p);
    
    return;
}
template <class T> void Maindata<T>::modifyregistration(int id,patient* p)
{
    
    registration.modify(id,p);
    return;
}
template <class T> void Maindata<T>::modifytreatment(int id,patient* p)
{
    
    treatment.modify(id,p);
    return;
}


