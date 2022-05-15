
#ifndef _FIBONACCI_TREE_HPP_
#define _FIBONACCI_TREE_HPP_

#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "localq.h"
#include "centerheap.h"
#include "../btree.h"
using namespace std;


/*
 Constructor
*/
template <class T>
centerHeap<T>::centerHeap()
{
    keyNum = 0;
    maxDegree = 0;
    min = NULL;
    cons = NULL;
    last_appointment = NULL;
    last_treatment = NULL;
    withdraw_number = 0;
    total_appointment_num = 0;
}

/*
Destructor
*/
template <class T>
centerHeap<T>::~centerHeap()
{
}

/*
 * remove the node from the doubly-linked list
 */
template <class T>
void centerHeap<T>::removeNode(centerNode<T> *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

/*
 * adding node heap in front of the root node(in linked list)
*/
template <class T>
void centerHeap<T>::addNode(centerNode<T> *node, centerNode<T> *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

/*
 * insert the node into the fibonacci heap
 */
template <class T>
void centerHeap<T>::insert(centerNode<T> *node)
{
    if (keyNum == 0)
        min = node;
    else
       {
        addNode(node, min);
        if (node->key < min->key)
            min = node;
    }
    keyNum++;
}

/*
 * create a new node with key value ad key, then insert it into the fibonacci heap
 */
template <class T>
void centerHeap<T>::insert(T key)
{
    centerNode<T> *node;

    node = new centerNode<T>(key);
    if (node == NULL)
        return ;

    insert(node);
}

/*
 * Link bidirectional linked list B to the end of bidirectional linked list A
 */
template <class T>
void centerHeap<T>::catList(centerNode<T> *a, centerNode<T> *b)
{
    centerNode<T> *tmp;

    tmp            = a->right;
    a->right       = b->right;
    b->right->left = a;
    b->right       = tmp;
    tmp->left      = b;
}


/*
 Merge Other into the current heap
 */
template <class T>
void centerHeap<T>::combine(centerHeap<T> *other)
{
    if (other==NULL)
        return ;

    if(other->maxDegree > this->maxDegree)
        swap(*this, *other);

    if((this->min) == NULL)                // this has no "minimum node"
    {
        this->min = other->min;
        this->keyNum = other->keyNum;
        free(other->cons);
        delete other;
    }
    else if((other->min) == NULL)           // this has the minimum node and the other has no min
    {
        free(other->cons);
        delete other;
    }                                       // this has the min and the other also have
    else
    {
        // Add "other root list "to "this"
        catList(this->min, other->min);

        if (this->min->key > other->min->key)
            this->min = other->min;
        this->keyNum += other->keyNum;
        free(other->cons);
        delete other;
    }
}

/*
Remove the "smallest node of the heap" from the root list
 */
template <class T>
centerNode<T>* centerHeap<T>::extractMin()
{
    centerNode<T> *p = min;

    if (p == p->right)
        min = NULL;
    else
    {
        removeNode(p);
        min = p->right;
    }
    p->left = p->right = p;

    return p;
}

/*
 * link node to the root node
 */
template <class T>
void centerHeap<T>::link(centerNode<T>* node, centerNode<T>* root)
{
    //remove node from the doubly-linked list
    removeNode(node);
    //set node as the child of the root
    if (root->child == NULL)
        root->child = node;
    else
        addNode(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = false;
}

/*
  make space for the operation "consolidate"
 */
template <class T>
void centerHeap<T>::makeCons()
{
    int old = maxDegree;

    // calculate the log2(keyNum)
    maxDegree = (log(keyNum)/log(2.0)) + 1;
    if (old >= maxDegree)
        return ;

     // Since degree maxDegree can be merged, maxDegree+1 is required
    cons = (centerNode<T> **)realloc(cons,
            sizeof(centerHeap<T> *) * (maxDegree + 1));
}

/*
 Merges the left and right trees of the same degree in the root list of the Fibonacci heap
 */
template <class T>
void centerHeap<T>::consolidate()
{
    int i, d, D;
    centerNode<T> *x, *y, *tmp;

    makeCons();// open up the space used for hashing
    D = maxDegree + 1;

    for (i = 0; i < D; i++)
        cons[i] = NULL;

    // Merge the root nodes of the same degree so that each degree of the tree is unique
    while (min != NULL)
    {
        x = extractMin();                // Select the smallest node in the heap.
        d = x->degree;                    // Get the degree of the minimum tree
        // cons[d] != NULL，
        while (cons[d] != NULL)
        {
            y = cons[d];                
            if (x->key > y->key)        
                swap(x, y);

            link(y, x);    
            cons[d] = NULL;
            d++;
        }
        cons[d] = x;
    }
    min = NULL;

    // add the nodes in cons back to the root table
    for (i=0; i<D; i++)
    {
        if (cons[i] != NULL)
        {
            if (min == NULL)
                min = cons[i];
            else
            {
                addNode(cons[i], min);
                if ((cons[i])->key < min->key)
                    min = cons[i];
            }
        }
    }
}

/*
 Remove the minimum node
 */
template <class T>
void centerHeap<T>::removeMin()
{
    if (min==NULL)
        return ;

    centerNode<T> *child = NULL;
    centerNode<T> *m = min;
    // Add each of Min's sons (son and son's brother) to the Fibonacci Heap root list
    while (m->child != NULL)
    {
        child = m->child;
        removeNode(child);
        if (child->right == child)
            m->child = NULL;
        else
            m->child = child->right;

        addNode(child, min);
        child->parent = NULL;
    }

    // Remove m from the root list
   // Remove m from the root list 
    removeNode(m);
    // If m is the only node in the heap, set the minimum node of the heap to NULL;
// Otherwise, set the minimum node of the heap to a non-empty node (m- >;Right), and then adjust.
    if (m->right == m)
        min = NULL;
    else
    {
        min = m->right;
        consolidate();
    }
    keyNum--;
}

/*
 Get the minimum key value in the Fibonacci heap and save it in pkey;Returns true on success, false otherwise.
 */
template <class T>
bool centerHeap<T>::minimum(T *pkey)
{
    if (min==NULL || pkey==NULL)
        return false;

    *pkey = min->key;
    return true;
}


template <class T>
void centerHeap<T>::renewDegree(centerNode<T> *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renewDegree(parent->parent, degree);
}

/*
* Remove node from child link of parent node,
* And make node a member of the root list of the heap.
 */
template <class T>
void centerHeap<T>::cut(centerNode<T> *node, centerNode<T> *parent)
{
    removeNode(node);
    renewDegree(parent, node->degree);
    
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = false;
    
    addNode(node, min);
}

/*
* Perform "cascading clipping" on nodes
*
* Cascading shear: If the reduced node breaks the minimum heap property,
* then cut it off (that is, delete it from the bidirectional list it is in, and change it to
* it inserts into the bidirectional linked list formed by the smallest root node),
* Then perform cascading pruning recursively from "the parent of the node being cut" to the root node
*/
template <class T>
void centerHeap<T>::cascadingCut(centerNode<T> *node)
{
    centerNode<T> *parent = node->parent;
    if (parent != NULL)
    {
        if (node->marked == false)
            node->marked = true;
        else
        {
            cut(node, parent);
            cascadingCut(parent);
        }
    }
}

/*
 * 将斐波那契堆中节点node的值减少为key
 */
template <class T>
void centerHeap<T>::decrease(centerNode<T> *node, T key)
{
    centerNode<T> *parent;

    if (min==NULL ||node==NULL)
        return ;

    if ( key>=node->key)
    {
        cout << "decrease failed: the new key(" << key <<") "
             << "is no smaller than current key(" << node->key <<")" << endl;
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        // Remove node from parent and add node to the root list
        cut(node, parent);
        cascadingCut(parent);
    }

    // Update the minimum node
    if (node->key < min->key)
        min = node;
}

/*
* Increase the Fibonacci heap node value to key
*/
template <class T>
void centerHeap<T>::increase(centerNode<T> *node, T key)
{
    centerNode<T> *child, *parent, *right;

    if (min==NULL ||node==NULL)
        return ;

    if (key <= node->key)
    {
        cout << "increase failed: the new key(" << key <<") "
             << "is no greater than current key(" << node->key <<")" << endl;
        return ;
    }

    // Will node every son (excluding grandchildren, great-grandchildren...)All added to the Fibonacci Heap root list
    while (node->child != NULL)
    {
        child = node->child;
        removeNode(child);               
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        addNode(child, min);       
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // If node is not in the root list,
// Remove node from child link of parent node.
// And make node a member of the root list of the heap,
// Then perform "cascading clipping"
// Otherwise, determine whether the smallest node of the heap needs to be updated
    parent = node->parent;
    if(parent != NULL)
    {
        cut(node, parent);
        cascadingCut(parent);
    }
    else if(min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(node->key > right->key)
                min = right;
            right = right->right;
        }
    }
}

/*
* Update Fibonacci heap node with key
*/
template <class T>
void centerHeap<T>::update(centerNode<T> *node, T key)
{
    if(key < node->key)
        decrease(node, key);
    else if(key > node->key)
        increase(node, key);
    else
        cout << "No need to update!!!" << endl;
}

template <class T>
void centerHeap<T>::update(T oldkey, T newkey)
{
    centerNode<T> *node;

    node = search(oldkey);
    if (node!=NULL)
        update(node, newkey);
}

/*
* Find the node with the key value in the minimum heap root
*/
template <class T>
centerNode<T>* centerHeap<T>::search(centerNode<T> *root, T key)
{
    centerNode<T> *t = root;    
    centerNode<T> *p = NULL;    

    if (root==NULL)
        return root;

    do
    {
        if (t->key == key)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = search(t->child, key)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}

/*
* Find the key node in the Fibonacci heap
*/
template <class T>
centerNode<T>* centerHeap<T>::search(T key)
{
    if (min==NULL)
        return NULL;

    return search(min, key);
}
template <class T>
centerNode<T>* centerHeap<T>::search_id(centerNode<T> *root, int id)
{
    centerNode<T> *t = root;    // temporary node
    centerNode<T> *p = NULL;    // node to search

    if (root==NULL)
        return root;

    do
    {
        if (t->id == id)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = search_id(t->child, id)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}
template <class T>
void centerHeap<T>::pop_patient_wrtddl(centerNode<T> *root, int ddl, BTree<T>* btree_registered, BTree<T>* btree_appointment,int date, Maindata<int>* center) //返回指向当天有ddl的病人的指针
{
    centerNode<T> *t = root;    // temporary node
    patient_f temper =  center->retrievepatient_f(t->id);
    patient_f *temp = &temper;

    if (root==NULL)
        return;

    do
    {
        if ( temp->treat_ddl == ddl){
            temp->treat_time = ddl + 10;
            temp->treat_hospital = check_nearest(temp->loc);
            op temper = op(temp->time,temp->id);
            btree_registered->BTree_delete(temper);
            op temper_appoint = op(date,temp->id);
            btree_appointment->BTree_insert(temper_appoint);
            center->modify(min->id,temp);
            remove(t);
        }else{
            pop_patient_wrtddl(t->child, ddl,&btree_registered,&btree_appointment,date,&center); 
        }
        t = t->right;
    } while (t != root);

    
}
/*
* Whether there are key nodes in the Fibonacci heap.
* Returns true if it exists, false otherwise.
*/
template <class T>
bool centerHeap<T>::contains(T key)
{
    return search(key)!=NULL ? true: false;
}


template <class T>
void centerHeap<T>::remove(centerNode<T> *node)
{
    T m = min->key-1;
    decrease(node, m-1);
    removeMin();
}

template <class T>
void centerHeap<T>::remove(T key)
{
    centerNode<T> *node;

    if (min==NULL)
        return ;

    node = search(key);
    if (node==NULL)
        return ;

    remove(node);
}


template <class T>
void centerHeap<T>::destroyNode(centerNode<T> *node)
{
    centerNode<T> *start = node;

    if(node == NULL)
        return;

    do {
        destroyNode(node->child);
        // Destroy the node and point it to the next one
        node = node->right;
        delete node->left;
    } while(node != start);
}

template <class T>
void centerHeap<T>::destroy()
{
    destroyNode(min);
    free(cons);
}

/*
* Print "Fibonacci heap"
*
* Parameter description:
* node -- the current node
* prev -- the previous node of the current node (parent or sibling)
* direction -- 1, indicating that the current node is a left child;
* 2: indicates that the current node is a sibling node.
*/
template <class T>
void centerHeap<T>::print(centerNode<T> *node, centerNode<T> *prev, int direction)
{
    centerNode<T> *start=node;

    if (node==NULL)
        return ;
    do
    {
        if (direction == 1)
            cout << setw(8) << node->key << "(" << node->degree << ") is "<< setw(2) << prev->key << "'s child" << endl;
        else
            cout << setw(8) << node->key << "(" << node->degree << ") is "<< setw(2) << prev->key << "'s next" << endl;

        if (node->child != NULL)
            print(node->child, node, 1);

        // brother node
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

template <class T>
void centerHeap<T>::print() // print the exact node in the fibonacci heap
{
    int i=0;
    centerNode<T> *p;

    if (min==NULL)
        return ;

    cout << "== 斐波那契堆的详细信息: ==" << endl;
    p = min;
    do {
        i++;
        cout << setw(2) << i << ". " << setw(4) << p->key << "(" << p->degree << ") is root" << endl;

        print(p->child, p, 1);
        p = p->right;
    } while (p != min);
    cout << endl;
}

#endif