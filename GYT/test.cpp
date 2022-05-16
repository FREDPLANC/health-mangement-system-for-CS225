#include "database.h"
#include "database.cpp"
#include "relationType.h"
#include "BPlus_node.cpp"
#include "BPlustree.cpp"
#include "BPlustree.h"
#include <iostream>
using namespace std;

int main(){
    CBPlusTree test_tree;
    test_tree.insert(1,2);
    Maindata<int> test_main_data;
    patient_f test_p1;
    test_p1.id = 1;
    patient_f test_p2;
    test_p2.id = 2;
    patient_f test_p3;
    test_p3.id = 3;
    patient_f modify_p4;
    modify_p4.id = 99;
    int idx_1 = test_main_data.insert(&test_p1);
    int idx_2 = test_main_data.insert(&test_p2);
    int idx_3 = test_main_data.insert(&test_p3);
    cout << test_main_data.search(1)<< endl;
    cout << idx_1 <<endl;
    cout << test_main_data.search(2)<< endl;
    cout << idx_2 <<endl;
    cout << test_main_data.search(3)<< endl;
    cout << idx_3 <<endl;
    test_main_data.modify(1, &modify_p4);
    cout << test_main_data.search(99) << endl;
    cout << test_main_data.indx_to_id(idx_1)<< endl;
    return 0;


}