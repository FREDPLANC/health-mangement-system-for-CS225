#ifndef _report_
#define _report_
#include <list>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
#include "database.cpp"
//#include "BPlustree.h"
//#include "BPlustree.cpp"
using namespace std;
extern int date_treat;

/*年龄排序模板*/
template<class T> bool Maindata<T>::cmp(int x,int y)
{
    return this->retrieveperson(x)->birthday > this->retrieveperson(y)->birthday;
}
/*已经治疗人员周报告*/
template<class T> void Maindata<T>:: report_treated(BTree<op>* btree_treated)
{
    extern int week_counter;
    string tempstr = to_string(week_counter);
    tempstr = "treated" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);

    int tmp_date = date_treat - 70;
    /*把时间扔进b树输出这部分人的id*/
    vector<op> b_treated;
    if (btree_treated == NULL)
    {
        return;
    }
    for (int i=tmp_date; i<=date_treat; i+=10)
    {
        op op1(i,0);
        btree_treated->find(op1,b_treated);
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_treated;
    vector<int> temp;
    for (vector<op>::iterator iter = b_treated.begin(); iter != b_treated.end(); iter++)
    {   
        temp = mainBP_Tree.select(iter->ID, EQ);
        int temp_2 = temp.back();
        bp_treated.push_back(temp_2);
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_treated;
    for ( vector<int>::iterator iter = bp_treated.begin(); iter != bp_treated.end(); iter++)
    {
        relate_treated.push_back(indx_to_id(*iter));
    }
    
    /*用年龄进行排序*/
    std::sort(relate_treated.begin(),relate_treated.end(),[this](auto x, auto y){ return this->cmp(x,y);});
    //std::sort(v.begin(), v.end(), [this](auto a, auto b){ return this->cmp(a, b);});
    /*打印*/
 
    for (vector<int>::iterator iter = relate_treated.begin(); iter != relate_treated.end(); iter++)
    {
        fout<<*iter<<",";
        fout<<this->retrieveperson(*iter)->name<<",";
        fout<<this->retrieveperson(*iter)->prof<<",";
        fout<<this->retrieveperson(*iter)->birthday<<",";
        fout<<this->retrievestatus(*iter)->risk<<",";
        fout<<date_treat - (this->retrievepatient_f(*iter).treat_time) <<","<<endl;
    }
    fout.close();
}

/*已经预约人员周报告*/
template<class T> void Maindata<T>:: report_appointment(BTree<op>* btree_appointment)
{
    extern int week_counter;
    string tempstr = to_string(week_counter);
    tempstr = "appointment" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);
    
    int tmp_date = date_treat - 70;
    /*把时间扔进b树输出这部分人的id*/
    vector<op> b_appointment ;
    if (btree_appointment == NULL)
    {
        return;
    }
    for (int i=tmp_date; i<=date_treat; i++)
    {
        op op1(i,0);
        btree_appointment->find(op1,b_appointment);
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_appointment ;
    vector<int> temp_8;
    for (vector<op>::iterator iter = b_appointment.begin(); iter != b_appointment.end(); iter++)
    {
        temp_8 = mainBP_Tree.select(iter->ID, EQ);
        int temper = temp_8.back();
        bp_appointment.push_back(temper);
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_appointment;
    for (vector<int>::iterator iter = bp_appointment.begin(); iter != bp_appointment.end(); iter++)
    {
        relate_appointment.push_back(indx_to_id(*iter));
    }
    /*年龄排序模板*/
    
    /*用年龄进行排序*/
    
    std::sort(relate_appointment.begin(),relate_appointment.end(),[this](auto x, auto y){ return this->cmp(x,y);});
    /*打印*/
    for (vector<int>::iterator iter = relate_appointment.begin(); iter != relate_appointment.end(); iter++)
    {
        fout<<*iter<<",";
        fout<<this->retrieveperson(*iter)->name<<",";
        fout<<this->retrieveperson(*iter)->prof<<",";
        fout<<this->retrieveperson(*iter)->birthday<<",";
        fout<<this->retrievestatus(*iter)->risk<<",";
        fout<<this->retrievepatient_f(*iter).time<<","<<endl;
    }
    fout.close();
}

/*已经注册人员周报告*/
template<class T> void Maindata<T>:: report_registered(BTree<op>* btree_registered)
{
    extern int week_counter;
    string tempstr = to_string(week_counter);
    tempstr = "registered" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);

    int tmp_date = date_treat - 70;
    /*把时间扔进b树输出这部分人的id*/
    vector<op> b_registered ;
    if (btree_registered == NULL)
    {
        return;
    }
    for (int i=tmp_date; i<=date_treat; i++)
    {
        op op1(i,0);
        btree_registered->find(op1,b_registered);
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_registered ;
    vector<int> temp_7;
    for (vector<op>::iterator iter = b_registered.begin(); iter != b_registered.end(); iter++)
    {   
        temp_7 = mainBP_Tree.select(iter->ID, EQ);
        int temper = temp_7.back();
        bp_registered.push_back(temper);
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_registered ;
    for (vector<int>::iterator iter = bp_registered.begin(); iter != bp_registered.end(); iter++)
    {
        relate_registered.push_back(indx_to_id(*iter));
    }
    /*年龄排序模板*/
    
    /*用年龄进行排序*/
    std::sort(relate_registered.begin(),relate_registered.end(),[this](auto x, auto y){ return this->cmp(x,y);});
    /*打印*/
    for (vector<int>::iterator iter = relate_registered.begin(); iter != relate_registered.end(); iter++)
    {
        fout<<*iter<<",";
        fout<<this->retrieveperson(*iter)->name<<",";
        fout<<this->retrieveperson(*iter)->prof<<",";
        fout<<this->retrieveperson(*iter)->birthday<<",";
        fout<<this->retrievestatus(*iter)->risk<<",";
        fout<<this->retrievepatient_f(*iter).treat_time- this->retrievepatient_f(*iter).time<<","<<endl;
    }
    fout.close();
}

template<class T> void Maindata<T>:: week_report(BTree<op>* btree_treated,BTree<op>* btree_appointment,BTree<op>* btree_registered)
{
    report_treated(btree_treated);
    report_appointment(btree_appointment);
    report_registered(btree_registered);
    extern int week_counter;
    week_counter++;
}

template<class T> void Maindata<T>:: month_report(BTree<op>* btree_treated,BTree<op>* btree_appointment,BTree<op>* btree_registered,int withdraw)
{
    extern int month;
    extern int month_counter;
    string tempstr = to_string(month_counter);
    tempstr = "month_report" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);
    extern int date_treat;
    int tmp_date = date_treat;
    if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
        tmp_date = tmp_date - 310;
    }
    if (month==4||month==6||month==9||month==11)
    {
        tmp_date = tmp_date - 300;
    }
    if (month==2)
    {
        tmp_date = tmp_date - 280;
    }
    /**********************************************************treated********************************************************************/
    vector<op> month_treated ;
    int treated = 0;
    for (int i=tmp_date; i<=date_treat; i++)
    {
        op op1(i,0);
        btree_treated->find(op1,month_treated);
        treated++;
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_treated;
    vector<int> temp;  
    for (vector<op>::iterator iter = month_treated.begin(); iter != month_treated.end(); iter++)
    {   
        
        temp = mainBP_Tree.select(iter->ID, EQ);
        int temp_2 = temp.back();
        bp_treated.push_back(temp_2);
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_treated ;

    for (vector<int>::iterator iter = bp_treated.begin(); iter != bp_treated.end(); iter++)
    {
        relate_treated.push_back(indx_to_id(*iter));
    }
    int waiting_time = 0;
    for (vector<int>::iterator iter = relate_treated.begin(); iter != relate_treated.end(); iter++)
    {
        waiting_time = waiting_time + date_treat-this->retrievepatient_f(*iter).treat_time;
    }
    waiting_time = waiting_time / treated;
    /**************************************************************registered*******************************************************/
    vector<op> month_registered;
    int registered = 0;
    for (int i=tmp_date; i<=date_treat; i++)
    {
        op op1(i,0);
        btree_registered->find(op1,month_registered);
        registered++;
    }
    /**************************************************************appointment******************************************************/
    vector<op> month_appointment ;
    int appointment = 0;
    for (int i=tmp_date; i<=date_treat; i++)
    {
        op op1(i,0);
        btree_appointment->find(op1,month_appointment);
        appointment++;
    }
    
    fout<<"The number of people who have registered is "<<registered+treated+appointment<<endl;
    fout<<"The number of people who are waiting is "<<appointment<<endl;
    fout<<"The number of people who are waiting in total is "<<registered-treated<<endl;
    fout<<"The number of treatment appointment which have been made is "<<treated+appointment<<endl;
    fout<<"The average waiting time is "<<waiting_time<<endl;
    fout<<"The number of people who withdrew is "<<withdraw<<endl;

    fout.close();
    extern int month_counter;
    month_counter++;
}

#endif
