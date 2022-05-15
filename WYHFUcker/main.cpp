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
#include "database.h"
#include "relationType.h"
using namespace std;

int months[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};// the exact days of every month
int month = 1; // global variables, record the time of the date in the program
int day = 1;
int am = 0;
int week = 0;
int date_treat;
int week_counter = 1;
int month_counter = 1;
int file_counter = 0;
Maindata<int> center;
BTree<op> hhhh;
BTree<op> btree_delaytreated_1;
BTree<op> btree_treated_1;
BTree<op> btree_appointment_1;
BTree<op> btree_registered_1;
BTree<op> btree_delaytreated_2;
BTree<op> btree_treated_2;
BTree<op> btree_appointment_2;
BTree<op> btree_registered_2;
BTree<op> btree_delaytreated_3;
BTree<op> btree_treated_3;
BTree<op> btree_appointment_3;
BTree<op> btree_registered_3;

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
    center.build(&btree_registered_1,&btree_registered_2,&btree_registered_3); // insert the csv daily data;
    center.mediumRisk_process(date_treat, &btree_delaytreated_1, &btree_treated_1, &btree_appointment_1, &btree_registered_1,center.center1);
    center.treatment_process(date_treat, &btree_delaytreated_1, &btree_treated_1, &btree_appointment_1, &btree_registered_1, center.center1); // treat queue generated
    center.appointment_process(date_treat, &btree_delaytreated_1, &btree_treated_1, &btree_appointment_1, &btree_registered_1, center.center1);  // appointment queue generated
    center.mediumRisk_process(date_treat, &btree_delaytreated_2, &btree_treated_2, &btree_appointment_2, &btree_registered_2, center.center2);
    center.treatment_process(date_treat, &btree_delaytreated_2, &btree_treated_2, &btree_appointment_2, &btree_registered_2, center.center2); // treat queue generated
    center.appointment_process(date_treat, &btree_delaytreated_2, &btree_treated_2, &btree_appointment_2, &btree_registered_2, center.center2);  // appointment queue generated
    center.mediumRisk_process(date_treat, &btree_delaytreated_3, &btree_treated_3, &btree_appointment_3, &btree_registered_3, center.center3);
    center.treatment_process(date_treat, &btree_delaytreated_3, &btree_treated_3, &btree_appointment_3, &btree_registered_3, center.center3); // treat queue generated
    center.appointment_process(date_treat, &btree_delaytreated_3, &btree_treated_3, &btree_appointment_3, &btree_registered_3, center.center3); // appointment queue generated
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
			center.month_report(&btree_treated_1,&btree_appointment_1,&btree_registered_1,center.center1->withdraw_number);
            center.month_report(&btree_treated_2,&btree_appointment_2,&btree_registered_2,center.center2->withdraw_number);
            center.month_report(&btree_treated_3,&btree_appointment_3,&btree_registered_3,center.center3->withdraw_number); // if the month is ended, begin the month report
			month++;
            day=0;
		}
	}
	else if(day==31){
		if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
			
            center.month_report(&btree_treated_1,&btree_appointment_1,&btree_registered_1,center.center1->withdraw_number);
            center.month_report(&btree_treated_2,&btree_appointment_2,&btree_registered_2,center.center2->withdraw_number);
            center.month_report(&btree_treated_3,&btree_appointment_3,&btree_registered_3,center.center3->withdraw_number); // if the month is ended, begin the month report
			month++;
            day=0;
		}
	}
	else if(day==30){
        if(month==4||month==6||month==9||month==11){
            center.month_report(&btree_treated_1,&btree_appointment_1,&btree_registered_1,center.center1->withdraw_number);
            center.month_report(&btree_treated_2,&btree_appointment_2,&btree_registered_2,center.center2->withdraw_number);
            center.month_report(&btree_treated_3,&btree_appointment_3,&btree_registered_3,center.center3->withdraw_number); // if the month is ended, begin the month report
		    month++;
            day=0;
        }	
	}

	day++;am=0;
	week++;
	if(week==7){
		//center.print();
        center.week_report(&btree_treated_1,&btree_appointment_1,&btree_registered_1);
        center.week_report(&btree_treated_2,&btree_appointment_2,&btree_registered_2);
        center.week_report(&btree_treated_3,&btree_appointment_3,&btree_registered_3);
		week=0;
	}
}


int main()
{   
    capacity_total = 0;
    int choice_user;
    int mode_choice;
    for(int i = 0; i < 3;i++){
        hospital* hop = new hospital(); // initialize the hospital information
        hop->hosp_id = i;
        hop->capacity = 1+i;
        hop->content = 0;
        hop->loc = 2+i;
        H[i] = hop;
        capacity_total += hop->capacity;
    }
    /*
    printf("Select mode: auto( enter: 54188 ) or manual(else)! \n");
    scanf("%d",&mode_choice);
    if(mode_choice == 54188){
        while(month<=12&&day<=31){
		printf("what do you want to do for the medical treatment(auto mode)\n");
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
        }
    }
    */
    

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
    }
    
    cout << endl << "we have ended a year, thank you" << endl;
    return 0;
}