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
using namespace std;
#include "database.h"
#include "btree.h"
#include "BPlustree.h"
#include "BPlustree.cpp"




/*已经治疗人员周报告*/
template<class T> void Maindata<T>:: report_treated(BTree<T>* btree_treated)
{
    extern int week_counter;
    string tempstr = to_string(week_counter);
    tempstr = "treated" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);
    extern date;
    int tmp_date = date - 7;
    /*把时间扔进b树输出这部分人的id*/
    vector<op> b_treated = NULL;
    if (btree_treated == NULL)
    {
        return;
    }
    for (i=tmp_date, i<=date, i++)
    {
        op op1(tmp_date,0);
        btree_treated->find(op1,b_treated);
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_treated = NULL;
    for (vector<op>::iterator iter = b_treated.begin(); iter != b_treated.end(); iter++)
    {
        bp_treated.push_back(mainBP_Tree.select(int iter->id, EQ));
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_treated = NULL;
    for (vector<int>::iterator iter = bp_treated.begin(); iter != bp_treated.end(); iter++)
    {
        relate_treated.push_back(indx_to_id(iter));
    }
    /*年龄排序模板*/
    bool cmp(int x,int y)
    {
        return this->retrieveperson(x)->birthday > this->retrieveperson(y)->birthday;
    }
    /*用年龄进行排序*/
    sort(relate_treated.begin(),relate_treated.end(),cmp);
    /*打印*/
    for (vector<int>::iterator iter = relate_treated.begin(); iter != relate_treated.end(); iter++)
    {
        fout<<iter<<",";
        fout<<this->retrieveperson(iter)->name<<",";
        fout<<this->retrieveperson(iter)->prof<<",";
        fout<<this->retrieveperson(iter)->birthday<<",";
        fout<<this->retrievestatus(iter)->risk<<",";
        fout<<date_treat-this->retrievepatient_f(iter)->treat_time<<","<<endl;
    }
    fout.close();
}

/*已经预约人员周报告*/
template<class T> void Maindata<T>:: report_appointment(BTree<T>* btree_appointment)
{
    extern int week_counter;
    string tempstr = to_string(week_counter);
    tempstr = "appointment" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);
    extern date;
    int tmp_date = date - 7;
    /*把时间扔进b树输出这部分人的id*/
    vector<op> b_appointment = NULL;
    if (btree_appointment == NULL)
    {
        return;
    }
    for (i=tmp_date, i<=date, i++)
    {
        op op1(tmp_date,0);
        btree_appointment.find(op1,b_appointment);
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_appointment = NULL;
    for (vector<op>::iterator iter = b_appointment.begin(); iter != b_appointment.end(); iter++)
    {
        bp_appointment.push_back(mainBP_Tree.select(int iter->id, EQ));
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_appointment = NULL;
    for (vector<int>::iterator iter = bp_appointment.begin(); iter != bp_appointment.end(); iter++)
    {
        relate_appointment.push_back(indx_to_id(iter));
    }
    /*年龄排序模板*/
    bool cmp(int x,int y)
    {
        return this->retrieveperson(x)->birthday > this->retrieveperson(y)->birthday;
    }
    /*用年龄进行排序*/
    sort(relate_appointment.begin(),relate_appointment.end(),cmp);
    /*打印*/
    for (vector<int>::iterator iter = relate_appointment.begin(); iter != relate_appointment.end(); iter++)
    {
        fout<<iter<<",";
        fout<<this->retrieveperson(iter)->name<<",";
        fout<<this->retrieveperson(iter)->prof<<",";
        fout<<this->retrieveperson(iter)->birthday<<",";
        fout<<this->retrievestatus(iter)->risk<<",";
        fout<<this->retrievepatient_f(iter)->time<<","<<endl;
    }
    fout.close();
}

/*已经注册人员周报告*/
template<class T> void Maindata<T>:: report_registered(BTree<T>* btree_registered)
{
    extern int week_counter;
    string tempstr = to_string(week_counter);
    tempstr = "registered" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);
    extern date;
    int tmp_date = date - 7;
    /*把时间扔进b树输出这部分人的id*/
    vector<op> b_registered = NULL;
    if (btree_registered == NULL)
    {
        return;
    }
    for (i=tmp_date, i<=date, i++)
    {
        op op1(tmp_date,0);
        btree_registered.find(op1,b_registered);
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_registered = NULL;
    for (vector<op>::iterator iter = b_registered.begin(); iter != b_registered.end(); iter++)
    {
        bp_registered.push_back(mainBP_Tree.select(int iter->id, EQ));
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_registered = NULL;
    for (vector<int>::iterator iter = bp_registered.begin(); iter != bp_registered.end(); iter++)
    {
        relate_registered.push_back(indx_to_id(iter));
    }
    /*年龄排序模板*/
    bool cmp(int x,int y)
    {
        return this->retrieveperson(x)->birthday > this->retrieveperson(y)->birthday;
    }
    /*用年龄进行排序*/
    sort(relate_registered.begin(),relate_registered.end(),cmp);
    /*打印*/
    for (vector<int>::iterator iter = relate_registered.begin(); iter != relate_registered.end(); iter++)
    {
        fout<<iter<<",";
        fout<<this->retrieveperson(iter)->name<<",";
        fout<<this->retrieveperson(iter)->prof<<",";
        fout<<this->retrieveperson(iter)->birthday<<",";
        fout<<this->retrievestatus(iter)->risk<<",";
        fout<<this->retrievepatient_f(iter)->treat_time-this->retrievepatient_f(iter)->time<<","<<endl;
    }
    fout.close();
}

template<class T> void Maindata<T>:: week_report(BTree<T>* btree_treated,BTree<T>* btree_appointment,BTree<T>* btree_registered)
{
    report_treated(btree_treated);
    report_appointment(btree_appointment);
    report_registered(btree_registered);
    extern int week_counter;
    week_counter++;
}

template<class T> void Maindata<T>:: month_report(BTree<T>* btree_treated,BTree<T>* btree_appointment,BTree<T>* btree_registered,int withdraw)
{
    extern int month;
    extern int month_counter;
    string tempstr = to_string(month_counter);
    tempstr = "month_report" + tempstr;
    tempstr = tempstr + ".txt";
    ofstream fout(tempstr);
    extern date;
    int tmp_date = date;
    if (month==1||month==3||month==5||month==7||month==8||month==10||month==12)
    {
        tmp_date = tmp_date - 31;
    }
    if (month==4||month==6||month==9||month==11)
    {
        tmp_date = tmp_date - 30;
    }
    if (month==2)
    {
        tmp_date = tmp_date - 28;
    }
    /**********************************************************treated********************************************************************/
    vector<op> month_treated = NULL;
    int treated = 0;
    for (i=tmp_date, i<=date, i++)
    {
        op op1(tmp_date,0);
        btree_treated.find(op1,month_treated);
        treated++;
    }
    /*把这部分人id扔进b+树输出block的index*/
    vector<int> bp_treated = NULL;
    for (vector<op>::iterator iter = b_treated.begin(); iter != b_treated.end(); iter++)
    {
        bp_treated.push_back(select(int iter->id, EQ));
    }
    /*把block的index输入relation里面得到id*/
    vector<int> relate_treated = NULL;
    for (vector<int>::iterator iter = bp_treated.begin(); iter != bp_treated.end(); iter++)
    {
        relate_treated.push_back(indx_to_id(iter));
    }
    int waiting_time = 0;
    for (vector<int>::iterator iter = relate_treated.begin(); iter != relate_treated.end(); iter++)
    {
        waiting_time = waiting_time + date_treat-this->retrievepatient_f(iter)->treat_time;
    }
    waiting_time = waiting_time / treated;
    /**************************************************************registered*******************************************************/
    vector<op> month_registered = NULL;
    int registered = 0;
    for (i=tmp_date, i<=date, i++)
    {
        op op1(tmp_date,0);
        btree_registered.find(op1,month_registered);
        register++;
    }
    /**************************************************************appointment******************************************************/
    vector<op> month_appointment = NULL;
    int appointment = 0;
    for (i=tmp_date, i<=date, i++)
    {
        op op1(tmp_date,0);
        btree_appointment.find(op1,month_appointment);
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


