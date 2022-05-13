#ifndef _process_
#define _process_
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "localq.h"
#include "../database/database.h"
#include "../database/relationType.h"
#include "../btree.h"
#include "centerheap.h"
using namespace std;
#include <vector>
// Handle reservation and cancellation operations
// We will first process the treatment list on that day, that is, we will call the withdraw function to withdraw the patients in the reservation list (at this point, the reservation list is equivalent to today's treatment list) and those waiting in the central queue to be withdrawn
// After that, all the patients in the appointment list before the update were put into the treatment list of the same day, and the appointment list was cleared
// We will update today's appointment list later
// Patients with DDL (date +1) on the next day will be prioritized in the appointment list, and then the remaining capacity will be displayed as the main queue of priority patients
// Capacity_total should be a const global variable that records the total daily capacity of all hospitals added up
//content_total Records how many appointments are made today
/*******************************************************************************************************************/
template<class T> void  centerHeap<T>::appointment_process(int date, BTree btree_delaytreated, BTree btree_treated, BTree btree_appointment, BTree btree_registered, Maindata<int> center )
{   extern int capacity_total;
    extern int content_total;
    pop_patient_wrtddl(min,date+10,btree_registered,btree_appointment,date,center);  // The treatment is scheduled one day before DDL, so an appointment is required the day before
    int rest_capacity = capacity_total - content_total;
   
       for (int i = 0; i < rest_capacity && min != NULL;i++){ // To prevent exceeding the daily capacity of all hospitals combined on that day
        patient_f temper =  center.retrievepatient_f(min->id);
        patient_f* temp = &temper;
        if((temp->risk == 2)||(withdraw_list[temp->id] == 1)){
            if(temp->risk == 2){
                if(temp->treat_ddl < 0){
                    temp->treat_ddl = date + 3000;
                }
                temp->treat_time = date + 3010; 
                //op temp_op = op(temp->treated_time,temp->id);
                //btree_treated.insert(temp_op);
            }
            else{
                if(temp->treat_ddl < 0){
                    temp->treat_ddl = date + 1400;
                }
                temp->treat_time = date + 1410; 
                //op temp_op = op(temp->treated_time,temp->id);
                //btree_treated.insert(temp_op);
            }
            op temp_op = op(temp->treat_ddl,temp->id);
            btree_delaytreated.BTree_insert(temp_op);
            center.modify(min->id,temp);
            removeMin();

            /*
            if(last_mediumRisk == NULL) {
                last_mediumRisk = min;
                center.modify(min->id,temp);
                removeMin();
                last_mediumRisk->child = NULL;
                curnode_mediumRisk = last_mediumRisk;
                
            }
            else{
                curnode_mediumRisk->parent = min;
                center.modify(min->id,temp);
                removeMin();
                curnode_mediumRisk->parent->child = curnode_mediumRisk; // the headnode points at the end of the list;
                curnode_mediumRisk = curnode_mediumRisk->parent;
                curnode_mediumRisk->parent = NULL;
                
            }
            */
            
        }
        patient_f tmper =  center.retrievepatient_f(min->id);
        patient_f *tmp = &tmper;
        tmp->treat_ddl  = date;
        tmp->treat_time = date + 10;
        op tmp_op = op(date,tmp->id);
        op tmp_opre = op(tmp->time,tmp->id);
        btree_registered.BTree_delete(tmp_opre);
        btree_appointment.BTree_insert(tmp_op);
        tmp->treat_hospital = check_nearest(tmp->loc);
        center.modify(min->id,tmp);
        //total_appointment_num++;
        
        removeMin();
        
        
    }
    
    return;
}

template<class T> void centerHeap<T>::mediumRisk_process(int date, BTree btree_delaytreated, BTree btree_treated, BTree btree_appointment, BTree btree_registered, Maindata<int> center)  // Deal with the treatment, add all the patients in the appointment list of the day before yesterday into the treatment list, and clear the appointment list
{  
    op tmp = op(date,0);
    vector <op> list;
    btree_delaytreated.find(tmp,list);
    for(int i = 0; i < list.size(); i++){
        patient_f tmper =  center.retrievepatient_f(list[i].ID);
        patient_f *tmp = &tmper;
        tmp->treat_hospital = check_nearest(tmp->loc);
        center.modify(list[i].id,tmp);
        op temper = op(tmp->time,tmp->id);
        btree_registered.BTree_delete(temper);
        btree_delaytreated.BTree_delete(list[i]);
        btree_appointment.BTree_insert(list[i]);
    }
    return;
    
    /*
    centerNode<T> *temp;
    temp = last_mediumRisk;
    if(temp == NULL){
        return;
    }
    else{
        while(temp->parent!=NULL){
            if(temp->treat_ddl == date){
                last_treatment->child = temp;
                centerNode<T> *last;
                centerNode<T> *next;
                last = temp->child;
                next = temp->parent;
                last->parent = next;
                next->child = last;
                temp->treated_location = check_nearest(temp);
                temp = next;
                last_treatment->child->parent = last_treatment;
                last_treatment = last_treatment->child;
            }
            else{
                temp = temp->parent;
            }
        }
        if(temp->treat_ddl == date){
                last_treatment->child = temp;
                centerNode<T> *last;
                last = temp->child;
                last->parent = NULL;
                last_treatment->child->parent = last_treatment;
                last_treatment = last_treatment->child;
        }
        temp = NULL;
    }
    */

    

}  


template<class T> void centerHeap<T>::treatment_process(int date, BTree btree_delaytreated, BTree btree_treated, BTree btree_appointment,  BTree btree_registered,Maindata<int> center)  // Deal with the treatment, add all the patients in the appointment list of the day before yesterday into the treatment list, and clear the appointment list
{  
    op tmp = op(date-10,0); // yesterday's appointed people
    vector <op> list;
    btree_appointment.find(tmp,list);
    for(int i = 0; i < list.size(); i++){
        btree_appointment.BTree_delete(list[i]);
        list[i].time = date;
        btree_treated.BTree_insert(list[i]);
    }
    return;
    /*
    centerNode<T> *temp;
    
    if(last_treatment == NULL){
        last_treatment = last_appointment;
        last_appointment = NULL;
    }else{
        while(last_appointment!=NULL){
            last_treatment->child = last_appointment;
            last_appointment = last_appointment->parent;
            last_treatment->child->parent = last_treatment;
            last_treatment = last_treatment->child;
        }
            last_appointment = NULL;
    }
    */
    return;

}  
template<class T> void  centerHeap<T>::withdraw(int id, BTree btree_delaytreated,  BTree btree_appointment, BTree btree_registered, Maindata<int> center) // Cancel designated patients from the appointment list and center queue
{
    patient_f tmper =  center.retrievepatient_f(id);
    patient_f *tmp = &tmper;

    if(centerNode<T>* p = search_id(min,id)) {
        remove(p);  
        if(withdraw_list[id] == 0) withdraw_number++; // If this person has not revoked, the number of revoked is increased by one
        withdraw_list[id] = 1; 
    }
    
    if(contain_pat(btree_registered,tmp)){
        op withdraw_pat = op(tmp->time,id);
        btree_registered.BTree_delete(withdraw_pat);
        if(withdraw_list[id] == 0) withdraw_number++; // If this person has not revoked, the number of revoked is increased by one
        withdraw_list[id] = 1;
    }
    else if(contain_pat(btree_appointment,tmp)){
        op withdraw_pat = op(tmp->treat_ddl,id);
        btree_appointment.BTree_delete(withdraw_pat);
        if(withdraw_list[id] == 0) withdraw_number++; // If this person has not revoked, the number of revoked is increased by one
        withdraw_list[id] = 1;
    }
    else if(contain_pat(btree_delaytreated,tmp)){
        op withdraw_pat = op(tmp->treat_ddl,id);
        btree_delaytreated.BTree_delete(withdraw_pat);
        if(withdraw_list[id] == 0) withdraw_number++; // If this person has not revoked, the number of revoked is increased by one
        withdraw_list[id] = 1;
    } 
    
}
template<class T> bool centerHeap<T>::contain_pat(BTree tree, patient_f *pat){
    op op1(pat->time,pat->id);
    vector<op> contain_list = NULL;
    tree.find(op1,contain_list);
    for (vector<op>::iterator iter = contain_list.begin(); iter != contain_list.end(); iter++)
    {
        if (iter->ID == pat->id)
        {
            return true;
        }
    }
    return false;
}

#endif
