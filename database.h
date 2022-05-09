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
    void remove(patient_f* p);

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
        void modify(int id,patient_f* p);
    
    private:
        list<Block<T>> blocks;
};

template<class T> class block
{
    public:
        std::vector<T> array;
        std::vector<T> overflowBuffer;
        int index;


    private:
        


};

