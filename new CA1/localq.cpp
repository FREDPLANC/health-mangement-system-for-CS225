#ifndef _localq_
#define _localq_
#include <cstdio>
#include "stdlib.h"
#include <fstream>
#include <iostream>
#include <vector>
#include<string>
#include "localq.h"
#include "centerheap.h"
#include <relationType.h>
#include <sstream>
#include <database.h>

using namespace std;

void daily_hosp_setZero(void){
    for(int i = 0; i < 3;i++){
        H[i]->content = 0;
    }
    content_total = 0;
    return;
}

template <class T>
int centerHeap<T>::check_nearest(int loc_pat)
{   
    
    int result = 0;
    int best = 100;
    int choice = 0;
    for(int i = 0; i < 3; i++){
        if(H[i]->content >= H[i]->capacity){
            continue;
        }
        result = loc_pat - H[i]->loc;
        if(result < 0){
            result = -result;
        } 
        result = result % 10;
        if(result < best){
            best = result;
            choice = i;
        }

    }
    H[choice]->content++;
    content_total++;
    return choice;
    
}

extern int file_counter;
extern int day;

localQueue<patient_f*>  build_queue (BTree<T>* btree_registered){
    
    file_counter ++;
    localQueue<patient_f*> palist;
    char filename[256];
    string tmpered = to_string(file_counter) + to_string(day)+".csv";
    int i;
    for( i=0;i<tmpered.length();i++)
        filename[i] = tmpered[i];
    filename[i] = '\0';//注意，一定要手动加上 '\0'
    /*
    cout<<"请输入文件名"<<endl;
    cin>>filename;
    */
    int omitline = 0; // the line to be neglected

    if(file_counter == 3){
        file_counter = 0;
    }

    ifstream infile(filename);
    
    while(infile.good()){
        
        //.csv files use commas (,) as delimiters
        if(omitline == 0){
            char omitting[256];
            infile.getline(omitting,256);
            omitline++;
            continue;
        }
        //patient_f* ill = new patient_f();
        int item;
        item = 0;
        extern int month;
        extern int day;
        extern int am;
        string line;
        while (getline(infile, line)){
            // Prints a full line of strings
            //cout << "each line : " << line << endl;
            patient_f* pat = new patient_f();
            // Parse the data for each row
            stringstream ss(line);
            string _sub;
            vector<string> subArray;
    
            // Separate them by commas
            while (getline(ss, _sub, ','))
                subArray.push_back(_sub);
            
    
            // Outputs each parsed line of data
            for (size_t i=0; i<subArray.size(); ++i)
            {
                
                switch (i+1) {  // You can refer to the order in the sample csv.
					case 1:
                        pat->id = atoi(subArray[i].c_str());
                        //cout << pat->id<<endl;
						break;
					case 2:
                        subArray[i].copy(pat->name, subArray[i].length(), 0);
                        *(pat->name+subArray[i].length())='\0';
                        //cout << pat->name<<endl;
						break;
					case 3:
                        pat->prof = atoi(subArray[i].c_str());
                        //cout << pat->prof<<endl;
						break;
					case 4:
						pat->time=atoi(subArray[i].c_str());
                        pat->time=month*1000+day*10+am;
                        //cout << pat->time<<endl;
						break; 
                    case 5:
                        pat->risk=atoi(subArray[i].c_str());
                        
                        //cout << pat->risk<<endl;
                        break;
                    case 6:
                        subArray[i].copy(pat->contact, subArray[i].length(), 0);
                        *(pat->contact+subArray[i].length())='\0';
                        //cout << pat->contact<<endl;
                        break;
                    case 7:
                        pat->treat_ddl=10*atoi(subArray[i].c_str());
                        
                        //cout << pat->treat_ddl<<endl;
                        break;
                    case 8:
                        pat->loc=atoi(subArray[i].c_str());
                        
                        //cout << pat->loc<<endl;
						break;
                    case 9:
                        pat->birth=atoi(subArray[i].c_str());
                        
                        //cout << pat->birth<<endl;
                        (*pat).age_rank();
                        break;
                    case 10:
                        pat->status=atoi(subArray[i].c_str());
                        
                        //cout << pat->status<<endl;
                        break;
                    case 11:
                        pat->treatment_type=atoi(subArray[i].c_str());
                        //cout << pat->status<<endl;
                        switch(pat->treatment_type){
                            case 0:
                                if(pat->risk == 0 || 1){
                                    pat->priority = pat->prof * 100000 + pat->aging * 10000 + pat->time;
                                }
                                else{
                                    pat->priority = pat->prof * 100000 + pat->aging * 10000 + pat->time + pat->risk *1000000;
                                }
                                break;
                            case 1:
                                pat->priority = 10-(pat->aging);
                                break;
                            case 2:
                                pat->priority = pat->time;
                                break;
                        }
                        item = -2;
                        break;             
            }

            }
            palist.En_queue(pat);
            op tmp = op(date_treat,pat->id);
            btree_registered->BTree_insert(tmp);
            cout << endl;
        }
        /*
        patient_f* pat = new patient_f();
        while(item >= 0){
            char buffer[128]; // the size of each item;
            infile.getline(buffer,128,',');
            while(buffer[0] == '\n'){
                strcpy(buffer,buffer + 1);
            }
            item++;
            
            switch (item) {  // You can refer to the order in the sample csv.
					case 1:
						
						if (buffer[0]=='\0') {
							delete pat;
							pat = nullptr; 
							item=-1;
							break;
						}
						//pat->id=len_N;  // Set the id as the index of the array N.
                        pat->id = (int)strtol(buffer,NULL,10);
                        cout << pat->id<<endl;
                        
						break;
					case 2:
						strcpy(pat->name,buffer);
                        cout << pat->name<<endl;
						break;
					case 3:
						pat->prof=(int)strtol(buffer,NULL,10);
                        cout << pat->prof<<endl;
						break;
					case 4:
						pat->time=(int)strtol(buffer,NULL,10);
                        pat->time=month*1000+day*10+am;
                        cout << pat->time<<endl;
						break; 
                    case 5:
                        pat->risk=(int)strtol(buffer,NULL,10);
                        cout << pat->risk<<endl;
                        break;
                    case 6:
                        strcpy(pat->contact,buffer);
                        cout << pat->contact<<endl;
                        break;
                    case 7:
                        pat->treat_ddl=10*(int)strtol(buffer,NULL,10);
                        cout << pat->treat_ddl<<endl;
                        break;
                    case 8:
                        pat->loc=(int)strtol(buffer,NULL,10);
                        cout << pat->loc<<endl;
						break;
                    case 9:
                        
                        pat->birth=(int)strtol(buffer,NULL,10);
                        cout << pat->birth<<endl;
                        (*pat).age_rank();
                        break;
                    case 10:
                        pat->status=(int)strtol(buffer,NULL,10);
                        cout << pat->status<<endl;
                        item = -2;
                        break;
                        
                    default:
                        cout << "exit with case in reading the file\n";      
            }
            if(item == -2){
                N[len_N++]=pat; 
                
                palist.En_queue(pat);  
                 
            }

        } 
        */  
    }
    
    infile.close();
	return palist;
}
template<class T> localQueue<T>::localQueue(int size)
{
    maxsize = size;
    if (size < 20){
        minsize = size;
        maxsize = 20;
    }
    else
        minsize = 20;
    numitems = 0;
    first = 1;
    last = 0;
    reprarray = new T[maxsize];
}

template<class T>bool localQueue<T>::isNull(void)
{
    if (numitems == 0)
	{
		return true;  //队头等于队尾，为空
	}
	return false;
}

template<class T> T &localQueue<T>::operator[](int index)
{
    if ((0 <= index) && (index <= numitems))
    {
        int dirindex = (index + first -1) % maxsize;
        return reprarray[dirindex];
    }
    else
    {
        cout << "Error: index out of range.\n";
        exit(EXIT_FAILURE);
    }
}   

template<class T> int localQueue<T>::getlength(void)
{
    return numitems;
}

template<class T> T localQueue<T>::front(void)
{
    if (isNull())
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
    else{
        return reprarray[first];
    }
}

template<class T> T localQueue<T>::rear(void)
{
    if (isNull())
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        int dirindex = (first + numitems - 1) % maxsize;
        return reprarray[dirindex];
    }
}

template<class T> patient_f localQueue<T>::De_queue(void){ // let a element go out a queue
    if (isNull())
	{
		cout<<"The queue is empty~";
		exit(EXIT_FAILURE);
	}
    if(((numitems -1) <= maxsize * 0.25) && (2*minsize < maxsize)){
        deallocate();
    }
    //cout << (reprarray[first])->id << endl;
    patient_f ele_out = *(reprarray[first]);  // the element to be out;
	first += 1;
	first = first % maxsize;
    numitems--;
    return ele_out;
}

template<class T> void localQueue<T>::En_queue(T element){ // let a element go into a queue
    if ( numitems >= maxsize * 0.75)
        allocate();
	last += 1;
    last = last % maxsize;
    
	reprarray[last] = element;
    //cout << (reprarray[last])->prof<<endl;
    numitems++;
    return;
}

template<class T> void localQueue<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
        newarray[i] = reprarray[(i + first) % maxsize];
    first = 1;
    last = numitems -1;
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    
    return;
}

template<class T> void localQueue<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[(i + first) % maxsize];
    }
    first = 1;
    last = numitems -1;
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

void patient_f::age_rank() {  // for aged < 12, we use 1 to represent the age group;And the same for others
	int age_diff = 2022 - this->birth;
	if (age_diff <= 12) {
        this->aging = 1;
    }
	else if (age_diff <= 18) {
        this->aging = 2;
    }
	else if (age_diff <= 35) {
        this->aging = 3;
    }
	else if (age_diff <= 50) {
        this->aging = 4;
    }
	else if (age_diff <= 65) {
        this->aging = 5;
    }
	else if (age_diff <= 75) {
        this->aging = 6;
    }
	else{
        this->aging = 7;
    }  
}
#endif