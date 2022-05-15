# SHIT_ASS  
![ABB9527C720B7AD6B5503D6BB994453C](https://user-images.githubusercontent.com/102898205/168458983-0a424c34-ea2e-43bf-a48a-773ca6a02729.jpg)
lyx is our son!!!  
基拉基拉  
k-fucking-d  
有关 new CA1 文件夹：暂时包括修改后的centerheap.h 以及build.cpp  
  修改内容：将centernode中其他部分删除，仅留下id部分，同时将build函数改为maindata的类成员函数，在从本地队列调出来以后先存入maindata再加入到centerheap中  
有关database.h :在maindata中新增了centerheap类型的变量，用于遍历和排序。   
b_tree 文件夹：包括b树和b+树的基本代码以及操作  
database文件夹： 包括数据库的基本构建操作  
三种priority type遵循的rules：
  0：之前定义的basic rule
  1：年长先治
  2：先到先治
treated  appointment  registered
有关内部代码：
  1. 总内存：maindata 内部有四个relation 每个relation的存储方式是由list类型的block实现的，block存的类型包括person,medical_status,registration,treatment四个类型。  
  2. maindata 内部存有一个b树，一个b+树以及三个斐波那契堆，其中，b+树用于根据id索引该病人在数据库的地址(即 block ID)，b树用于根据时间索引id，三个斐波那契堆用于排序。  
  3. 在maindata之外还有一个叫做paitient_f的类，这个类具有存每一个人全部个人信息的功能，用于数据在各个类以及文件输入输出的转换。
  4.  我们建立四个B树，registeration树，treat树，delaytreat树 与 appointment 树。 每个树储存不同status的病人，用于report时分类打印病人信息。其中regi，treat，appointment树病人互不相同，delaytreat是中风险或者之前withdraw过的病人暂时存放的树，可能与登记树重合。我们的B树是通过时间range去索引在此区间内所有病人的ID
  5.  我们的B+树通过输入的ID去返回block ID，然后通过BLOCK ID 和 ID 去database寻找病人的全部信息。用于之后的打印
b树的使用方法：基础的函数有BTree_insert（），
  6. 
