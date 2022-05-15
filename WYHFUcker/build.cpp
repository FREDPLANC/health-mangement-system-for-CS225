#ifndef _BUILD_
#define _BUILD_
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "localq.h" 
#include "centerheap.h" 
#include "centerheap.cpp"
#include "localq.cpp"
#include "process.cpp"
#include "report.cpp"
#include "database.h"
using namespace std;



template <class T>
void Maindata<T>::build( BTree<op>* btree_registered_1 , BTree<op>* btree_registered_2,BTree<op>* btree_registered_3)
{//Add local queues to the central heap
    
    localQueue <patient_f*> Q1 = build_queue(btree_registered_1); //first build the local queue;
    localQueue<patient_f*> Q2 = build_queue(btree_registered_2);
    localQueue<patient_f*> Q3 = build_queue(btree_registered_3);
    int k=0;
    int l1 = Q1.getlength();
    int l2 = Q2.getlength();
    int l3 = Q3.getlength();
    for (int i=1;i<=l1;i++)
    {
        patient_f p1= Q1.De_queue() ;
        patient_f *p_temp = &p1; 
        if (p1.status==54188)
        {
            withdraw(p1.id);
            
        }
        else{
            int idx_block = this->insert(p_temp);
            if (idx_block == -1) cout << "wrong dequeue_1" << endl;
            if (this->mainBP_Tree.insert(p1.id, idx_block) == -1) cout<< "wrong insert B+tree" << endl;
            //add_patient(p1); //first pop the content of the queue one by one
            add_patient(p1);
        }
        
        

    }
    for (int i=1;i<=l2;i++)
    {   
        patient_f p2=Q2.De_queue() ;// same for other queues
        patient_f *p_temp = &p2; 
        if (p2.status==54188)
        {
            withdraw(p2.id);
        }
        else{
            int idx_block = this->insert(p_temp);
            if (idx_block == -1) cout << "wrong dequeue_2" << endl;
            if (this->mainBP_Tree.insert(p2.id, idx_block) == -1) cout<< "wrong insert B+tree" << endl;
            //add_patient(p2);
            add_patient(p2);
        }
        
    }
    for (int i=1;i<=l3;i++)
    {
        patient_f p3=Q3.De_queue() ;
        patient_f *p_temp = &p3;
        if (p3.status==54188)
        {
            withdraw(p3.id);
        }
        else{
            int idx_block = this->insert(p_temp);
            if (idx_block == -1) cout << "wrong dequeue_3" << endl;
            if (this->mainBP_Tree.insert(p3.id, idx_block) == -1) cout<< "wrong insert B+tree" << endl;
            //add_patient(p3);
            add_patient(p3);
        } 
        
    }

}
/*template <class T>
void centerHeap<T>::add_patient(patient_f p) //Eject the elements of the local queue and build them into centerHeap
{
    
    if (p.status==54188)
    {
        withdraw(p.id);
    }
    else{
        insert(p);
    }  
    
}*/
template <class T>
void centerHeap<T>::insert(patient_f p) // insert an element into the heap
{
    centerNode<T> *node;
    node = new centerNode<T>(p);
    if (node == NULL) return ;
    insert(node);
    list_numb--;
    
}
#endif