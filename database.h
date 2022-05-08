#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;
template <class T> class Maindata
{
    public:
    void insert(patient_f* p);
    bool search(int id);
    void modify(int id,patient_f* p);
    void modifyperson(int id,patient_f* p);
    void modifystatus(int id,patient_f* p);
    void modifyregistration(int id,patient_f* p);
    void modifytreatment(int id,patient_f* p);


    private:
    relation<Person> person;
    relation<Medical_Status> medical_status;
    relation<Registration> registration;
    relation<Treatment> treatment;

};
template<class T> class relation

{
    public:
        bool insert(patient_f* p);
        bool search(int id);
        bool remove(int key);
        T retrieve(int key);
        bool merge(int blockID_1, int blockID_2);
        int 

    private:
        list<Block<T>> blocks;
};

template<class T> class block
{
    public:
        int max_length = 5;
        std::vector<T> array;
        std::vector<T> overflowBuffer;
        int index;
        bool full() {
            return ((int)array.size() == MAX_LENGTH || (int)overflowBuffer.size() == MAX_LENGTH);
        }
        int size() {
            if ((int)array.size() != 0) return (int)array.size();
            else return (int)overflowBuffer.size();
        }
        void Sort();
};
template<class T> void block<T>::Sort() {
    std::sort(this->overflowBuffer.begin(), this->overflowBuffer.end());
    overflowBuffer.swap(array);
    overflowBuffer.clear();
}

class ID
{
    public:
        int id;
        void getid();
        void setid();


}
;
class Person: public ID
{
    public:

    private:

};
class Medical_Status : public ID
{
    public:

    private:

    
};
class Registration :public ID
{
    public:

    private:
    
};
class Treatment :public ID
{
    public:

    private:
};
template<class T> T relation<T>::retrieve(int key) {
    // search through the link
    for (typename list< Block<T> >::iterator iter=this->blocks.begin(); iter != this->blocks.end(); ++iter) {
        vector<T>& A = (iter->full()) ? iter->array : iter->overflowBuffer;
        for (int i=0;i<(int)A.size();i++)
        if (A[i].getRecordID() == key)
        return A[i];
    }
    T x;
    x.setRecordID(-1);
    return x;
}
