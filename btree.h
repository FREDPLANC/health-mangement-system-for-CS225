#include <iostream>
using namespace std;
#include <vector>
static const int m = 3;  //定义最小度为3
static const int key_max = 2*m-1;//关键字最大个数
static const int key_min = m - 1;//关键字最小个数
static const int child_max = key_max + 1;//子节点最大个数(这里可以看出子节点数与关键字数有关)
static const int child_min = key_min + 1;//子节点最小个数
 
template <class T>
class BTree;//前置声明
/*
类名:BTnode
*/
template <class T>
class BTnode
{
  friend class BTree<T>;//友元函数
public:
	BTnode()
	{
		keyNum = 0;
		parent = NULL;//父节点初始化
        isleaf = true;
		int i ;
		for (i = 0;i < child_max;i++)//子树指针数组初始化
		{
			pchild[i] = NULL;
		}
		for (i = 0;i < key_max;i++)//关键字数组初始化
		{
			keyvalue[i] =-1;
		}
	}
 private:
 bool isleaf;//判断节点是否是叶子节点
 int keyNum;//关键字个数
 BTnode<T>* parent;//指向父节点
 BTnode<T>* pchild[child_max];//子树指针数组
 T   keyvalue[key_max];//关键字数组
};
 
/*
类名:BTree
*/
template <class T>
class BTree
{
public:
	  /*
     函数名:BTree
     函数作用:无参构造函数
     函数参数:无
     函数返回值: 无
     */
  
    BTree()
    {
       root = NULL;
    }
      /*
     函数名:BTree_insert
     函数作用:插入关键字
     函数参数:T value
     函数返回值: bool类型判断插入是否成功
     */
 
    bool BTree_insert(T value)
    {
      if (contain(value))//看树中是否有相同的关键字
      {
         return false;
      }
      else
      {
      	  if (root == NULL)
      	  {
      	  	 root = new BTnode<T>();
      	  }
      	  if (root->keyNum == key_max)
      	  {
             BTnode<T>* newnode = new BTnode<T>();
             newnode->pchild[0] = root;
             newnode->isleaf = false;//由上步操作可知newnode已经有子节点
             SplitBlock(newnode,0,root);//分块操作
             root = newnode;//更新根节点
      	  }
      	  Notfull_insert(root,value);//插入块未满的操作
      	  return true;
      }
    }
 
    /*
     函数名:SplitBlock
     函数作用:把节点分裂
     函数参数:BTnode<T>* node_parent,int child_index,BTnode<T>* node_child
     函数返回值: 无
     */
    
    void SplitBlock(BTnode<T>* node_parent,int child_index,BTnode<T>* node_child)
    {
       BTnode<T>* node_right = new BTnode<T>();
       node_right->isleaf = node_child->isleaf;
       node_right->keyNum = key_min;
       int i;
       //node_right拷贝关键字
       for (i = 0;i < key_min;i++)
       {
         node_right->keyvalue[i] = node_child->keyvalue[i+child_min];
       }
       //判断分裂的节点是否是叶子节点,如果不是的话就要把它的孩子赋值过去
       if (!node_child->isleaf)
       {
          for (i = 0;i < child_min;i++)
          {
             node_right->pchild[i] = node_child->pchild[i+child_min];
             node_child->pchild[i+child_min]->parent = node_right->pchild[i];
          }
       }
       node_child->keyNum = key_min;//更新子节点的关键字数
       //把父节点关键字和子指针往后移 倒序赋值
       for (i = node_parent->keyNum;i > child_index;i--)
       {
          node_parent->keyvalue[i] = node_parent->keyvalue[i-1];
          node_parent->pchild[i+1] = node_parent->pchild[i];
          node_child->pchild[i]->parent = node_parent->pchild[i+1];
       }
       node_parent->keyNum++;//更新父节点关键字数
       node_parent->pchild[child_index+1] = node_right;
       node_right->parent = node_parent->pchild[child_index+1];
       //把中间的那个关键字上移到父节点
       node_parent->keyvalue[child_index] = node_child->keyvalue[key_min];
    }
 
   
    /*
    函数名:Notfull_insert
    函数作用:往没有满的节点中增加关键字
    函数参数:BTnode<T>* node,T value
    函数返回值:无
    */
    void Notfull_insert(BTnode<T>* node,T value)
    {
 
      int node_keynum = node->keyNum;//获取节点关键字数
      if (node->isleaf)//node是叶子节点
      {
      	 while (node_keynum > 0 && value < node->keyvalue[node_keynum-1])
      	 {
      	 	node->keyvalue[node_keynum] = node->keyvalue[node_keynum-1];//把关键字往后移动
      	 	--node_keynum;
      	 }
      	 node->keyvalue[node_keynum] = value;
      	 node->keyNum++;
      }
      else//node是内部节点
      {
      	  while (node_keynum > 0 && value < node->keyvalue[node_keynum-1])
      	  {
      	  	 --node_keynum;
      	  }
      	  //在比它小和比它大中间那个子节点中找合适位置,
      	  //如果它比所有的都小则在第一个子节点中寻找
      	  BTnode<T>* node_child = node->pchild[node_keynum];
      	  if (node_child->keyNum == key_max)
      	  {
      	  	 SplitBlock(node,node_keynum,node_child);
      	  	 if (value > node->keyvalue[node_keynum])//插入值和子节点中间的值比较
      	  	 {
      	  	 	 node_child = node->pchild[node_keynum+1];
      	  	 }
      	  }
      	  Notfull_insert(node_child,value);//继续往下寻找合适的位置
      }
    }
    
    /*
    函数名:contain
    函数作用:查找是否有相同元素在数中
    函数参数:T value
    函数返回值:bool类型
    */
   bool contain(T value)
   {
        if (BTree_find(root,value) != NULL){
			return true;
		}
   	  
    return false;
   }
   
   
    /*
    函数名:BTree_find
    函数作用:查找是否有相同元素在数中
    函数参数:BTnode<T>* node,T value
    函数返回值: BTnode<T>*
    */
   BTnode<T>* BTree_find(BTnode<T>* node,T value)
   {
   	   if (node == NULL)//当前节点为空的时候
   	   {
   	   	  return NULL;
   	   }
   	   else//当前节点不为空
   	   {
   	   	 int i;
		 int mark=0;
         //在比它小和比它大的中间子节点中寻找相等的
   	   	 for (i = 0; i < node->keyNum ;i++)
   	   	 {
   	   	 	  if (value <= node->keyvalue[i])
            {
               mark=1;
			   break; 
            }
   	   	 }
		/*if (mark==0){
			i++;
		}*/
   	   	 //校验当前的关键字是否等于查找的关键字
         if (i < node->keyNum && value != node->keyvalue[i])//i是下标最大值keyNum-1 != 已经被重载
         {
            return node;
         }
         else
         {
         	//如果之前比查找关键没有相等的关键字并且当前节点是叶子节点的话
         	//那么在B树中没有一样的关键字(因为后面比关键字更大)
         	 if (node->isleaf)
         	 {
         	 	return NULL;
         	 }
         	 else//如果不是叶子节点则在下面的子节点中寻找
         	 {
             return BTree_find(node->pchild[i],value);//这里的return别忘了
         	 }
         }
   	   }
   }
   void find(T value,vector<T> &vec)
   {
	   B_find(root,value,vec);
   }
   void B_find(BTnode<T>* node,T value,vector<T> &vec)
   {
   	   if (node == NULL)//当前节点为空的时候
   	   {
   	   	  return ;
   	   }
   	   else//当前节点不为空
   	   {
   	   	 int i;
         //在比它小和比它大的中间子节点中寻找相等的
   	   	 for (i = 0; i < node->keyNum ;i++)
   	   	 {
               if (i < node->keyNum && value == node->keyvalue[i])//i是下标最大值keyNum-1
				{
					vec.push_back(node->keyvalue[i]);
				} 
				if (!(node->isleaf))//如果不是叶子节点则在下面的子节点中寻找
				{
				for(int j=i;j<=node->keyNum;j++){
					B_find(node->pchild[j],value,vec);//这里的return别忘了
				}
				
				}
   	   	 }
 
   	   	 
         
   	   }
   }


  
  
    /*
    函数名:printpoint
    函数作用:打印元素
    函数参数:BTnode<T>* node,int count
    函数返回值:无
    */
   void printpoint(BTnode<T>* node,int count)
   {
   	  if (node != NULL)//判断元素是否为空
   	  {
   	  	  int i,j;
          //每个节点从小到大打印
   	     for (i = 0;i < node->keyNum; i++)
   	     {
          //判断是否叶节点,不是的话则要往子节点中寻找打印
   	   	   if (!node->isleaf)//判断是否是叶子节点
   	   	   {
             printpoint(node->pchild[i],count-3);
   	   	   }
   	   	   for (j = count;j >= 0; j--)
   	   	   {
   	   	   	 cout<<"-";
   	   	   }
   	   	   cout<<"|"<<node->keyvalue[i].ID<<","<<node->keyvalue[i].time<<"|"<<endl;//1111111111111234
   	    }
   	    if (!node->isleaf)//子节点数比关键字数多一个
   	   	{
             printpoint(node->pchild[i],count-3);
   	   	}
   	  }
   }
    /*
    函数名:printpoint
    函数作用:printpoint无参函数传递值过去
    函数参数:无
    函数返回值:无
    */
   void printpoint()
   {
   	 printpoint(root,key_max*5);
   }
    /*
    函数名:BTree_delete
    函数作用:删除函数
    函数参数:T value
    函数返回值:bool类型
    */
   bool BTree_delete(T value)
   {
      if (!contain(value))
      {
          return false;
      }
      if (root->keyNum == 1)
      {
             if (root->isleaf)
             {
                delete root;
                root = NULL;
                return true;
             }
             else//当根节点只有一个关键字时且不为叶子节点
             {
                BTnode<T>* node_child1 = root->pchild[0];
                BTnode<T>* node_child2 = root->pchild[1];
                //减少一层树的高度
                if (node_child1->keyNum == key_min && node_child2->keyNum == key_min)
                {
                    MergeBlock(root,0);
                    delete root;
                    root = node_child1;
                }
             }
      }
      BTree_deletebalance(root,value);
	  return true;
   }
     /*
    函数名:MergeBlock
    函数作用:合并块
    函数参数:BTnode<T>* node_parent,int child_index
    函数返回值:无
    */
   void MergeBlock(BTnode<T>* node_parent,int child_index)
   {
      BTnode<T>* node_child1 = node_parent->pchild[child_index];
      BTnode<T>* node_child2 = node_parent->pchild[child_index+1];
      //将父节点的节点对应的关键字下移
      node_child1->keyvalue[key_min] = node_parent->keyvalue[child_index];
      node_child1->keyNum = key_max;
      int i;
      for (i = 0;i < key_min;i++)
      {
        node_child1->keyvalue[child_min+i] = node_child2->keyvalue[i];
      }
      //判断node_child1是否是叶子节点,不是叶子节点则要将node_child2的子节点赋值给node_child1
      if (!node_child1->isleaf)
      {
        for (i = 0; i < child_min;i++)
        {
           node_child1->pchild[i+child_min] = node_child2->pchild[i];
        }
      }
      //因为父节点下移一个关键字,则关键字后的所有值要往前移动一个
      node_parent->keyNum--;
      for (i = child_index;i <  node_parent->keyNum;i++)
      {
         node_parent->keyvalue[i] = node_parent->keyvalue[i+1];
         //子节点也要往前移动一位
         node_parent->pchild[i+1] = node_parent->pchild[i+2];
      }
      delete node_child2;
      node_child2 = NULL;
   }
      /*
    函数名:getprev
    函数作用:在左边的兄弟节点中找一个最大的
    函数参数:BTnode<T>* node
    函数返回值:左边兄弟的最大的关键字
    */
   T getprev(BTnode<T>* node)
   {
    //在比节点位置小的节点中找一个最大的值最为
      while (!node->isleaf)
      {
         node = node->pchild[node->keyNum];
      }
      node->keyNum--;
      return node->keyvalue[node->keyNum-1];
   }
      /*
    函数名:getnext
    函数作用:在右边的兄弟节点中找一个最小的
    函数参数:BTnode<T>* node
    函数返回值:右边兄弟的最小的关键字
    */
   T getnext(BTnode<T>* node)
   {
     //在比节点位置大的节点中找一个最小的
     while (!node->isleaf)
      {
         node = node->pchild[0];
      }
     return node->keyvalue[0];
   }
    /*
    函数名:BTree_deletebalance
    函数作用:用递归删除并做修复
    函数参数:BTnode<T>* node
    函数返回值:无
    */
   void BTree_deletebalance(BTnode<T>* node,T value)
   {
     int i;
     //在当前节点中找合适坐标使得value在这个区间内
     for(i = 0;i < node->keyNum && value > node->keyvalue[i];i++)
     {
 
     }
     //如果当前i的关键字等于value
     if (i < node->keyNum && value != node->keyvalue[i])//有重载运算符
     {
      //判断当前节点是否是叶子节点,如果是的话直接删除,下面的情况保证了如果value在叶子节点的话,叶子节点keyNum一定是>=child_min
        if (node->isleaf)
        {
           node->keyNum--;
           //把i后面的都往前移动一位
           for (;i < node->keyNum;i++)
           {
             node->keyvalue[i] = node->keyvalue[i+1];
           }
           return;
        }
        else//当前节点为内节点
        {
          //里面关键字都比value小的节点
          BTnode<T>* node_left = node->pchild[i];
          //里面关键字都比value大的节点
          BTnode<T>* node_right = node->pchild[i+1];
          if (node_left->keyNum >= child_min)//左子节点中的关键字数大于等于child_min
          {
             T prev_replace = getprev(node_left);
             //传递不平衡点让pre_replace
             BTree_deletebalance(node_left,prev_replace);
             //让前继的关键字替换当前删除的关键字
             node->keyvalue[i] = prev_replace;
             return;
          }
          else if (node_right->keyNum >= child_min)//右子节点中的关键字数大于等于child_min
          {
             T next_replace = getnext(node_right);
             //在左边中找到最大的那个递归替换
             BTree_deletebalance(node_right,next_replace);
             //让前继的关键字替换当前删除的关键字
             node->keyvalue[i] = next_replace;
             return;
          }
          else//左右子节点中的关键字数都等于key_min
          {
            //合并两个子节点
            MergeBlock(node,i);
            //在合并的节点中删除value值
            BTree_deletebalance(node_left,value);
          }
        }
     }
     else//关键字不在当前节点(下面步骤保证了遍历的所有节点关键字数都是大于等于child_min)
     {
       //在(<<value<<)的区间找
        BTnode<T>* node_child = node->pchild[i];//这里i = node->keyNum
        BTnode<T>*  node_left = NULL;
        BTnode<T>*  node_right = NULL;
        if (node_child->keyNum == key_min)//当前节点只有两个关键字,补给当前节点使之大于等于child_min
        {  
            //判断是否有左右兄弟节点
            if (i >0)
            {
                node_left = node->pchild[i-1];
            }
            if (i <= node->keyNum-1)
            {
               node_right = node->pchild[i+1];
            }
           int j;
           //当前左兄弟的关键字数大于等于child_min
           if (node_left && node_left->keyNum >= child_min)
           {   
                //把父节点的i-1对应的关键字下移
               for (j = node_child->keyNum;j > 0; j--)
               {
                 node_child->keyvalue[j] = node_child->keyvalue[j-1];
               }
               node_child->keyvalue[0] = node->keyvalue[i-1];
               //如果子节点的左兄弟节点不是叶子节点
               if (!node_left->isleaf)
               {
                //把左兄弟最右边的子节点指针赋值给node_child
                  for (j = node_child->keyNum+1;j > 0;j--)
                  {
                    node_child->pchild[j-1]->parent = node_child->pchild[j]->parent;
                    node_child->pchild[j] = node_child->pchild[j-1];
 
                  }
                  node_left->pchild[node_left->keyNum]->parent =  node_child->pchild[0];
                  node_child->pchild[0] = node_left->pchild[node_left->keyNum];
               }
               node_child->keyNum++;
               node->keyvalue[i-1] = node_left->keyvalue[node_left->keyNum-1];
               node_left->keyNum--;
           }
           else if (node_right && node_right->keyNum >= child_min)
           {
               //把父节点的i对应的关键字下移
               node_child->keyvalue[node_child->keyNum] = node->keyvalue[i];
               node_child->keyNum++;
               //把右兄弟节点最小的关键字赋值给父节点的i位置
               node->keyvalue[i] = node_right->keyvalue[0];
               node_right->keyNum--;
               //把右兄弟的关键字往前移动一位
               for (j = 0;j < node_right->keyNum;j++)
               {
                 node_right->keyvalue[j] = node_right->keyvalue[j+1];
               }
               //如果右兄弟不是叶子节点则需要把右兄弟最左边的子节点指针赋值给node_child
               if (!node_right->isleaf)
               {
                node_right->pchild[0]->parent = node_child->pchild[node_child->keyNum]->parent;
                 node_child->pchild[node_child->keyNum] = node_right->pchild[0];
                  for (j = 0;j < node_right->keyNum+1;j++)
                  {
                    node_right->pchild[j+1]->parent = node_right->pchild[j]->parent;
                    node_right->pchild[j] = node_right->pchild[j+1];
 
                  }
                 
               }
           }
           else if (node_left)//node_left只有child_min-1个关键字
           {
            //把左兄弟合并
             MergeBlock(node,i-1);
             //更新子节点
             node_child = node_left;
           }
           else if (node_right)
           {
            //把右兄弟合并,子节点无需更新
             MergeBlock(node,i);
           }
        }
        BTree_deletebalance(node_child,value);
     }
   }
private:
	BTnode<T>* root;//根节点
};

/*
//新加入的代码
template<class T> class nodes
{
	nodes(BTnode<T>* s)
	{
		content=s;
	}
	BTnode<T>* content;
	nodes<T>* next;
	nodes<T>* prev;
	
};
template<class T> class nodelist
{
	nodelist()
	{
		dummy=new node<T>();
		dummy->next=dummy;
		dummy->prev=dummy;
		now=dummy;
	}
	nodes<T>* now;
	nodes<T>* dummy;
	void insert(node<T>* node)
	{
		node->next=now->next;
		node->next->prev=node;
		now->next=node;
		node->prev=now;
		
		now=node;
	}
	void concat(nodelist<T>* new)
	{

	}
};
*/

class op
{
	public:
	op();
	op(int t,int i);
	int time;
	int ID;
	bool operator<(op op1);
	bool operator<=(op op1);
	bool operator>(op op1);
	bool operator>=(op op1);
	bool operator==(op op1);
	bool operator!=(op op1);
	void operator=(int i);
};
op::op()
{
	time=-1;
	ID=-1;
	
}
op::op(int t,int i)
{
	time=t;
	ID=i;
	
}
bool op::operator<(op op1)
{
	//op op1;
	//op op2;
	if (time<op1.time)
	{
		return true;
	}
	else if(time==op1.time&&ID<op1.ID)
	{
		return true;
	}
	return false;
}
bool op::operator<=(op op1)
{
	//op op1;
	//op op2;
	if (time<op1.time)
	{
		return true;
	}
	else if(time==op1.time&&ID<=op1.ID)
	{
		return true;
	}
	return false;
}
bool op::operator>(op op1)
{
	//op op1;
	//op op2;
	if (time>op1.time)
	{
		return true;
	}
	else if(time==op1.time&&ID>op1.ID)
	{
		return true;
	}
	return false;
}
bool op::operator>=(op op1)
{
	//op op1;
	//op op2;
	if (time>op1.time)
	{
		return true;
	}
	else if(time==op1.time&&ID>=op1.ID)
	{
		return true;
	}
	return false;
}
bool op::operator==(op op1)
{
	//op op1;
	//op op2;
	if (time==op1.time)
	{
		return true;
	}
	
	return false;
}
bool op::operator!=(op op1)
{
	//op op1;
	//op op2;
	if (time==op1.time&&ID==op1.ID)
	{
		return true;
	}
	return false;
}
void op::operator=(int i)
{
	//op op1;
	//op op2;
	time=i;

	
}
