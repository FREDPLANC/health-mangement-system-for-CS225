
template<class T> class relation
{
    public:
        void insert();

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
