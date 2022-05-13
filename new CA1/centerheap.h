#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
#include "../database/database.h"
#include "../database/relationType.h"
using namespace std;
#ifndef  centerheap_h
#define centerheap_h

template<class T> class centerNode  
{
    public:
    T key;    //key value
    int degree;            // degree
    centerNode<T> *left;    // left brother
    centerNode<T> *right;    // right brother
    centerNode<T> *child;    // the first child node
    centerNode<T> *parent;    // father node
    bool marked;        // whether to delete the first child
    int id;
	/*char name[30];
	char contact[11]; //number digit of 11
	char address[10]; //the address, not know how to use
	int prof; 
	int birth;  
	int risk;  
	int time;  // when he is register
    int treated_time;  //the time to be treated
    int treated_location;   //the place to be treated
	int aging;   // the age group he is in
	int status; // whether he is in waiting , appointed, or else
		
	int treat_ddl;  //the deadline of the treated date
	int near_hospital;    //the closed hospital who can get treated
	int loc;
    */
    
	/* Class Functions */
	centerNode(){
        
    };
    centerNode(centerNode<T>* N){
    
    left   = this;
    right  = this;
    parent = NULL;
    child  = NULL;
    key=N->key;
    degree=N->degree;
    id=N->id;
    
    /*
    prof=N->prof;
    birth=N->birth;
    risk=N->risk;
    time=N->time;
    treated_time=N->treated_time;
    treated_location=N->treated_location;
    aging=N->aging;
    
    treat_ddl=N->treat_ddl;
    near_hospital=N->near_hospital;
    loc=N->loc;
    strcpy(name,N->name);
    strcpy(contact,N->contact);
    strcpy(address,N->address);
    status =  N->status;
    */
    
    }
	  //~patient();
	void age_rank(); // judge which age group he is in




    centerNode(patient_f value): degree(0), marked(false), 
    left(NULL),right(NULL),child(NULL),parent(NULL) 
    {
        /*if(value.risk == 0 || 1)
        key    = value.prof * 100000 + value.aging * 10000 + value.time;
        else{
            key = value.prof * 100000 + value.aging * 10000 + value.time + value.risk *1000000;
        }
        */
        key=value.key;
        degree = 0;
        marked = false;
        left   = this;
        right  = this;
        parent = NULL;
        child  = NULL;
        id=value.id;//
    
        /*prof=value.prof;//
        birth=value.birth;//
        risk=value.risk;//
        time=value.time;//
        
        aging=value.aging;//
    
        treat_ddl=value.treat_ddl;//
        loc=value.loc;//
        strcpy(name,value.name);//
        strcpy(contact,value.contact);//
        strcpy(address,value.address);//
        status = value.status;
        */
    }

};


template<class T> class centerHeap
{     
    
    public:
        friend class patient_f;
        int keyNum;         // The total number of current nodes in the heap (not just the number of keys, which may be duplicated)
        int total_appointment_num;       // How many appointments have been made since the beginning
        int maxDegree;      // the biggest degree
        int withdraw_list[1000]; // Check if this ID has ever cancelled a reservation or waited
        int withdraw_number;     // Record the number of people that have been revoked
        int list_numb = 0;

        centerNode<T> *min;    // minimum node (the root node of a minimum heap)
        centerNode<T> **cons;    // Maximum memory area
        centerNode<T> *last_appointment; // Double linked list of daily appointments, last_appointment points to the last appointment of the day
        centerNode<T> *last_treatment;  // Double linked list to store total treatment list
        centerNode<T> *last_waiting;   // A double-linked list of queued people (each element in the Fibonacci heap)
        centerNode<T> *head_treatment;
        centerNode<T> *head_appointment;
        centerNode<T> *head_registered;
        centerNode<T> *last_mediumRisk;
        centerNode<T> *head_mediumRisk;
        centerNode<T> *curnode_mediumRisk;

        centerHeap();  //*********************************************************************************************
        ~centerHeap();  //***********************************************************************************************
        void insert(T key);   // Create a new node for the key and insert it into the Fibonacci heap
        void removeMin();    // Remove the smallest node in the Fibonacci heap
        void combine(centerHeap<T> *other);  // Merge other into the current heap
        bool minimum(T *pkey);  // Get the minimum key in the Fibonacci heap and save it in pkey;Returns true on success, false otherwise.
        void update(T oldkey, T newkey);   // Update the Fibonacci heap oldkey to newkey
        void remove(T key);   // Delete the node whose key is key
        void destroy();  // destroy
        centerNode<T>* search_id(centerNode<T> *root, int id);
        void appointment_process(int date, BTree btree_delaytreated, BTree btree_treated, BTree btree_appointment, Maindata<int> center );//process the appoint
        void mediumRisk_process(int date, BTree btree_delaytreated, BTree btree_treated, BTree btree_appointment, Maindata<int> center); //medium risk process;  
        void treatment_process(int date, BTree btree_delaytreated, BTree btree_treated, BTree btree_appointment, Maindata<int> center );  // process the treatment
        void pop_patient_wrtddl(centerNode<T> *root, int ddl);
        void withdraw(int id);
        int check_nearest(int loc_pat);
        //void build(); // Read the hospital general queue
        void add_patient(patient_f p);
        void insert(patient_f p);
        void report_treated(centerNode<T>* head_treatment);
        void report_appointment(centerNode<T>* head_appointment);
        void report_registered(centerNode<T>* head_waiting);

        void Listsort_prof(centerNode<T>* head);
        void Listsort_aging(centerNode<T>*  head);
        void Listsort_name(centerNode<T>* head);
        void List_registered();
        void listmake(centerNode<T> *N);
        centerNode<T> *copy(centerNode<T> *N);
        void set_head(centerNode<T>* head_appointment,centerNode<T>* head_treatment,centerNode<T>* head_waiting);
        void add_head(centerNode<T> *N,centerNode<T> *H);
        int count_list(centerNode<T> *head);
        
        void week_report();
        void month_report();
        void print(centerNode<T> *node, centerNode<T> *prev, int direction);  // Print "Fibonacci heap"
        void delete_head(centerNode<T> *N,centerNode<T> *H);
        void print();
        void iteregister(centerNode<T> *node, centerNode<T> *prev, int direction);
        int go(int waiting,centerNode<T> *node, centerNode<T> *prev, int direction);
    private:
        
        void removeNode(centerNode<T> *node);  // Remove node from the double-linked list (not a complete delete)
        
        void addNode(centerNode<T> *node, centerNode<T> *root);  // Add a node to the heap before adding it to the root node.
        
        void catList(centerNode<T> *a, centerNode<T> *b);  // Link bidirectional list B to the end of bidirectional list A
        
        void insert(centerNode<T> *node);  // Insert node into the Fibonacci heap
        
        centerNode<T>* extractMin();  // Insert node into the Fibonacci heap，
        
        void link(centerNode<T>* node, centerNode<T>* root);  // Link node to root
        
        void makeCons();  // Space required for consolidating
        
        void consolidate();  // Merge the Fibonacci heap root list of trees with the same degree
        
        void renewDegree(centerNode<T> *parent, int degree);  // change the degree
        
        void cut(centerNode<T> *node, centerNode<T> *parent);  // Remove node from the child of parent and make node a member of the "root list of the heap".
        
        void cascadingCut(centerNode<T> *node) ;  // Perform "cascading clipping" on nodes.
        
        void decrease(centerNode<T> *node, T key);  // Reduce the Fibonacci heap node value to key
        
        void increase(centerNode<T> *node, T key);  // Add the Fibonacci heap node to key
        
        void update(centerNode<T> *node, T key);  // Update the Fibonacci heap node with key
        
        centerNode<T>* search(centerNode<T> *root, T key);  // Find the node with the key value in the minimum heap root
        
        centerNode<T>* search(T key);  // Find the key node in the Fibonacci heap
        
        void remove(centerNode<T> *node);  // Delete node
        
        void destroyNode(centerNode<T> *node);  // Destroy the Fibonacci heap
        
       
        
        bool contains(T key); // Whether there is a key node in Fibonacci heap.Returns true if it exists, false otherwise.


};
 #endif