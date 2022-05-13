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
#include "build.cpp"
#include "../database/database.h"
#include "../database/relationType.h"
using namespace std;

int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};// the exact days of every month
int month = 1; // global variables, record the time of the date in the program
int day = 1;
int am = 0;
int week = 0;
int date_treat;
int week_counter = 1;
int month_counter = 1;
Maindata<int> center;
BTree 1_btree_delaytreated;
BTree 1_btree_treated;
BTree 1_btree_appointment;
BTree 1_btree_registered;
BTree 2_btree_delaytreated;
BTree 2_btree_treated;
BTree 2_btree_appointment;
BTree 2_btree_registered;
BTree 3_btree_delaytreated;
BTree 3_btree_treated;
BTree 3_btree_appointment;
BTree 3_btree_registered;
void choice_0(); // the interactive interface of different choice entered by the user
void choice_1();
void choice_2();
void choice_3();

void half_day_process(){ // when time flows a day, it needs the following steps
    if(am != 0){
        return;
    }
    daily_hosp_setZero();  // clear the content patient of each hospital
    extern int date_treat;
    date_treat = month*1000 + day*10 + am; // the converted time
    center.build(); // insert the csv daily data;
    center.center1.mediumRisk_process(date_treat, 1_btree_delaytreated, 1_btree_treated, 1_btree_appointment, 1_btree_registered,center);
    center.center1.treatment_process(date_treat, 1_btree_delaytreated, 1_btree_treated, 1_btree_appointment, 1_btree_registered, center); // treat queue generated
    center.center1.appointment_process(date_treat, 1_btree_delaytreated, 1_btree_treated, 1_btree_appointment, 1_btree_registered, center);  // appointment queue generated
    center.center2.mediumRisk_process(date_treat, 2_btree_delaytreated, 2_btree_treated, 2_btree_appointment, 2_btree_registered, center);
    center.center2.treatment_process(date_treat, 2_btree_delaytreated, 2_btree_treated, 2_btree_appointment, 2_btree_registered, center); // treat queue generated
    center.center2.appointment_process(date_treat, 2_btree_delaytreated, 2_btree_treated, 2_btree_appointment, 2_btree_registered, center);  // appointment queue generated
    center.center3.mediumRisk_process(date_treat, 3_btree_delaytreated, 3_btree_treated, 3_btree_appointment, 3_btree_registered, center);
    center.center3.treatment_process(date_treat, 3_btree_delaytreated, 3_btree_treated, 3_btree_appointment, 3_btree_registered, center); // treat queue generated
    center.center3.appointment_process(date_treat, 3_btree_delaytreated, 3_btree_treated, 3_btree_appointment, 3_btree_registered, center); // appointment queue generated
}


void choice_1(){
    for(int i=1;i<=14;i++){
        choice_0();
    }
    return;
}

void choice_3(){
    printf("Today is Month/Day: %d/%d ",month,day);
    if(am == 0){
        printf("morning\n");
    }
    else{
        printf("evening\n");
    }
}

void choice_2(){
    int days=months[month];
    int remain_days = days-day; // the rest day of this month;
    for(int i=1;i<=2*remain_days;i++){
        choice_0();
    }
	return;
}

void choice_0(){
	half_day_process();// Begin appoint
	if(am == 0){
        am=5;
        return;
    }
    
	if(day==28){
		if(month==2){
			center1.month_report(1_btree_treated,1_btree_appointment,1_btree_registered,center1->withdraw_number);
            center2.month_report(2_btree_treated,2_btree_appointment,2_btree_registered,center2->withdraw_number);
            center3.month_report(3_btree_treated,3_btree_appointment,3_btree_registered,center3->withdraw_number); // if the month is ended, begin the month report
			month++;
            day=0;
		}
	}
	else if(day==31){
		if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
			
            center1.month_report(1_btree_treated,1_btree_appointment,1_btree_registered,center1->withdraw_number);
            center2.month_report(2_btree_treated,2_btree_appointment,2_btree_registered,center2->withdraw_number);
            center3.month_report(3_btree_treated,3_btree_appointment,3_btree_registered,center3->withdraw_number);
			month++;
            day=0;
		}
	}
	else if(day==30){
        if(month==4||month==6||month==9||month==11){
            center1.month_report(1_btree_treated,1_btree_appointment,1_btree_registered,center1->withdraw_number);
            center2.month_report(2_btree_treated,2_btree_appointment,2_btree_registered,center2->withdraw_number);
            center3.month_report(3_btree_treated,3_btree_appointment,3_btree_registered,center3->withdraw_number);
		    month++;
            day=0;
        }	
	}

	day++;am=0;
	week++;
	if(week==7){
		//center.print();
        center1.week_report(1_btree_treated,1_btree_appointment,1_btree_registered);
        center2.week_report(2_btree_treated,2_btree_appointment,2_btree_registered);
        center3.week_report(3_btree_treated,3_btree_appointment,3_btree_registered);
		week=0;
	}
}


int main()
{   
    capacity_total = 0;
    int choice_user;
    for(int i = 0; i < 3;i++){
        hospital* hop = new hospital(); // initialize the hospital information
        hop->hosp_id = i;
        hop->capacity = 1+i;
        hop->content = 0;
        hop->loc = 2+i;
        H[i] = hop;
        capacity_total += hop->capacity;
    } 

    while(month<=12&&day<=31){
		printf("what do you want to do for the medical treatment\n");
		printf("Enter the number from 0-3:\n");
		printf("0. waiting for the time to flow half day\n");
		printf("1. Skip a week.\n");
		printf("2. Skip this month.\n");
        printf("3. Show the time.\n");
        printf("4. End the program.\n");
		scanf("%d",&choice_user);
		if(choice_user<0||choice_user>4){
            printf("Wrong input please try again.\n");
            continue;
        }
        else if(choice_user == 0){
            choice_0();
            continue;
        }
        else if(choice_user == 1){
            choice_1();
            continue;
        }
        else if(choice_user == 2){
            choice_2();
            continue;
        }
        else if(choice_user == 3){
            choice_3();
            continue;
        }
        else if(choice_user == 4){
            cout << endl << "Thank you for using our program, goodbye!" << endl;
            return 0;
        }
    
    
    cout << endl << "we have ended a year, thank you" << endl;
	return 0;
    }
}