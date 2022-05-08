
template <class T> class Maindata
{
    public:
    void insert(patient* p);
    bool search(int id);
    void modify(int id,patient* p);
    void modifyperson(int id,patient* p);
    void modifystatus(int id,patient* p);
    void modifyregistration(int id,patient* p);
    void modifytreatment(int id,patient* p);


    private:
    relation<Person> person;
    relation<Medical_Status> medical_status;
    relation<Registration> registration;
    relation<Treatment> treatment;

};
template<class T> class relation

{
    public:
        bool insert(patient* p);
        bool search(int id);
        bool remove(int key);
        T retrieve(int key);
        bool merge(int blockID_1, int blockID_2);
        

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

class ID
{
    public:
        int id;
        int getid();
        void setid(int t);


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
