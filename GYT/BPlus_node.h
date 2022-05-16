#ifndef BPLUS_NODE
#define BPLUS_NODE
 
enum NODE_TYPE{INTERNAL, LEAF};        // 结点类型：内结点、叶子结点
enum SIBLING_DIRECTION{LEFT, RIGHT};   // 兄弟结点方向：左兄弟结点、右兄弟结点
typedef int KeyType;                   // 键类型
typedef int DataType;                  // 值类型
const int ORDER = 3;                   // B+树的阶（非根内结点的最小子树个数）
const int MINNUM_KEY = ORDER-1;        // 最小键值个数
const int MAXNUM_KEY = 2*ORDER-1;      // 最大键值个数
const int MINNUM_CHILD = MINNUM_KEY+1; // 最小子树个数
const int MAXNUM_CHILD = MAXNUM_KEY+1; // 最大子树个数
const int MINNUM_LEAF = MINNUM_KEY;    // 最小叶子结点键值个数
const int MAXNUM_LEAF = MAXNUM_KEY;    // 最大叶子结点键值个数
 
// 结点基类
class CNode{
public:
	CNode();
	virtual ~CNode();
 
	NODE_TYPE getType() const {return m_Type;}
	void setType(NODE_TYPE type){m_Type = type;}
	int getKeyNum() const {return m_KeyNum;}
	void setKeyNum(int n){m_KeyNum = n;}
	KeyType getKeyValue(int i) const {return m_KeyValues[i];}
	void setKeyValue(int i, KeyType key){m_KeyValues[i] = key;}
	int getKeyIndex(KeyType key)const;  // 找到键值在结点中存储的下标
	// 纯虚函数，定义接口
	virtual void removeKey(int keyIndex, int childIndex)=0;  // 从结点中移除键值
	virtual void split(CNode* parentNode, int childIndex)=0; // 分裂结点
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex)=0;  // 合并结点
	virtual void clear()=0; // 清空结点，同时会清空结点所包含的子树结点
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d)=0; // 从兄弟结点中借一个键值
	virtual int getChildIndex(KeyType key, int keyIndex)const=0;  // 根据键值获取孩子结点指针下标
protected:
	NODE_TYPE m_Type;
	int m_KeyNum;
	KeyType m_KeyValues[MAXNUM_KEY];
};
 
// 内结点
class CInternalNode : public CNode{
public:
	CInternalNode();
	virtual ~CInternalNode();
 
	CNode* getChild(int i) const {return m_Childs[i];}
	void setChild(int i, CNode* child){m_Childs[i] = child;}
	void insert(int keyIndex, int childIndex, KeyType key, CNode* childNode);
	virtual void split(CNode* parentNode, int childIndex);
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex)const;
private:
	CNode* m_Childs[MAXNUM_CHILD];
};
 
// 叶子结点
class CLeafNode : public CNode{
public:
	CLeafNode();
	virtual ~CLeafNode();
 
	CLeafNode* getLeftSibling() const {return m_LeftSibling;}
	void setLeftSibling(CLeafNode* node){m_LeftSibling = node;}
	CLeafNode* getRightSibling() const {return m_RightSibling;}
	void setRightSibling(CLeafNode* node){m_RightSibling = node;}
	DataType getData(int i) const {return m_Datas[i];}
	void setData(int i, const DataType& data){m_Datas[i] = data;}
	void insert(KeyType key, const DataType& data);
	virtual void split(CNode* parentNode, int childIndex);
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex)const;
private:
	CLeafNode* m_LeftSibling;
	CLeafNode* m_RightSibling;
	DataType m_Datas[MAXNUM_LEAF];
};
#endif

