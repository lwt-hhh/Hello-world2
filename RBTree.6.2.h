#include <iostream>

using namespace std;
//pair
enum Color
{
	Red,
	Black
};

template <class T>
struct RBTreeNode
{
	T _data;
	Color _color = Red;

	RBTreeNode<T>* _pLeft = nullptr;
	RBTreeNode<T>* _pRight = nullptr;
	RBTreeNode<T>* _pParent = nullptr;
};

template <class T>
struct __TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __TreeIterator<T> Self;
	typedef Node* pNode;

	__TreeIterator(pNode node)
		:_node(node)
	{}

	T* operator->()
	{
		return &_node->_data;
	}
	T& operator*()
	{
		return _node->_data;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	Self& operator++()
	{
		//右子树是否存在
		//右子树存在， 访问最左节点
		if (_node->_pRight != nullptr)
		{
			_node = _node->_pRight;
			while (_node->_pLeft)
			{
				_node = _node->_pLeft;
			}
		}
		else
		{
			//叶子节点，向上回溯
			pNode parent = _node->_pParent;
			while (_node == parent->_pRight)
			{
				_node = parent;
				parent = parent->_pParent;
			}
			if (_node->_pRight != parent)
				_node = parent;
		}
		return *this;
	}

	pNode _node;
};

template <class K, class V, class KeyOfValue>
class RBTree
{
public:
	typedef RBTreeNode<V> Node;
	typedef __TreeIterator<V> iterator;
	typedef Node* pNode;

	RBTree()
		:_header(new Node)
	{
		_header->_pLeft = _header;
		_header->_pRight = _header;
	}

	iterator begin()
	{
		return iterator(_header->_pLeft);
	}

	iterator end()
	{
		return iterator(_header);
	}

	pair<iterator, bool> Insert(const V& data)
	{
		//二叉搜索树的插入

		if (_header->_pParent == nullptr)
		{
			//空树，插入根节点，颜色为黑
			pNode root = new Node;
			root->_data = data;
			root->_color = Black;
			_header->_pParent = root;
			root->_pParent = _header;
			_header->_pLeft = root;
			_header->_pRight = root;
			return make_pair(iterator(root), true);
		}
		KeyOfValue keyOfValue;
		pNode cur = _header->_pParent;
		pNode parent = nullptr;
		while (cur)
		{
			if (keyOfValue(cur->_data) > keyOfValue(data))
			{
				parent = cur;
				cur = cur->_pLeft;
			}
			else if (keyOfValue(cur->_data) < keyOfValue(data))
			{
				parent = cur;
				cur = cur->_pRight;
			}
			else
				return make_pair(iterator(cur), false);
		}

		cur = new Node;
		pNode newNode = cur;
		cur->_data = data;
		if (keyOfValue(parent->_data) > keyOfValue(cur->_data))
			parent->_pLeft = cur;
		else
			parent->_pRight = cur;

		cur->_pParent = parent;
		//调整，变色
		while (cur != _header->_pParent && cur->_pParent->_color == Red)
		{
			pNode parent = cur->_pParent;
			pNode gParent = parent->_pParent;
			if (gParent->_pLeft == parent)
			{
				pNode uncle = gParent->_pRight;
				//u存在且为红
				if (uncle && uncle->_color == Red)
				{
					parent->_color = uncle->_color = Black;
					gParent->_color = Red;
					cur = gParent;
				}
				else
				{
					// u不存在 / u存在且为黑
					//检查是否有双旋场景: 左右双旋
					//首先左单旋，swap, --> 右单旋
					if (parent->_pRight == cur)
					{
						RotateL(parent);
						swap(parent, cur);
					}

					RotateR(gParent);
					parent->_color = Black;
					gParent->_color = Red;
					break;
				}
			}
			else
			{
				pNode uncle = gParent->_pLeft;
				if (uncle && uncle->_color == Red)
				{
					parent->_color = uncle->_color = Black;
					gParent->_color = Red;
					cur = gParent;
				}
				else
				{
					// u存在且为黑 / u不存在
					if (parent->_pLeft == cur)
					{
						RotateR(parent);
						swap(cur, parent);
					}

					RotateL(gParent);
					gParent->_color = Red;
					parent->_color = Black;
					break;
				}
			}
		}

		//红黑树根始终是黑色的
		_header->_pParent->_color = Black;
		_header->_pParent->_pParent = _header;
		//为了实现后续的迭代器
		_header->_pLeft = leftMost();
		_header->_pRight = rightMost();
		return make_pair(iterator(newNode), true);
	}

	pNode leftMost()
	{
		pNode cur = _header->_pParent;
		while (cur && cur->_pLeft)
		{
			cur = cur->_pLeft;
		}
		return cur;
	}

	pNode rightMost()
	{
		pNode cur = _header->_pParent;
		while (cur && cur->_pRight)
		{
			cur = cur->_pRight;
		}
		return cur;
	}

	void RotateL(pNode parent)
	{
		pNode subR = parent->_pRight;
		pNode subRL = subR->_pLeft;
		//旋转
		subR->_pLeft = parent;
		parent->_pRight = subRL;

		//更新三叉链
		//链接subRL 和parent
		if (subRL)
			subRL->_pParent = parent;

		//链接subR 和 parent->_pParent
		if (parent != _header->_pParent)
		{
			pNode gParent = parent->_pParent;
			//判断parent之前是parent->_pParent的那一边的节点
			//把subR链接到对应的边

			if (gParent->_pLeft == parent)
				gParent->_pLeft = subR;
			else
				gParent->_pRight = subR;
			//更新subR的pParent
			subR->_pParent = gParent;
		}
		else
		{
			//如果parent是根，subR变成新的根
			subR->_pParent = nullptr;
			_header->_pParent = subR;
		}

		//链接subR 和 parent
		parent->_pParent = subR;

	}


	void RotateR(pNode parent)
	{
		pNode subL = parent->_pLeft;
		pNode subLR = subL->_pRight;
		// 1. 单向链接subL, subLR, parent
		subL->_pRight = parent;
		parent->_pLeft = subLR;
		//2 向上链接subLR, parent
		if (subLR)
			subLR->_pParent = parent;
		//3. 双向链接subL与pParent->_pParent
		if (parent != _header->_pParent)
		{
			pNode gParent = parent->_pParent;
			if (gParent->_pLeft == parent)
				gParent->_pLeft = subL;
			else
				gParent->_pRight = subL;
			subL->_pParent = gParent;
		}
		else
		{
			subL->_pParent = nullptr;
			_header->_pParent = subL;
		}
		//4. 向上链接parent, subL
		parent->_pParent = subL;

	}

	void Inorder()
	{
		_Inorder(_header->_pParent);
		cout << endl;
	}

	void _Inorder(pNode root)
	{
		if (root)
		{
			_Inorder(root->_pLeft);
			cout << root->_kv.first << " ";
			_Inorder(root->_pRight);
		}
	}

	bool IsValidRBTree()
	{
		pNode pRoot = _header->_pParent;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;
		// 检测根节点是否满足情况
		if (Black != pRoot->_color)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}
		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		pNode pCur = pRoot;
		while (pCur)
		{
			if (Black == pCur->_color)
				blackCount++;
			pCur = pCur->_pLeft;
		}
		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}
	bool _IsValidRBTree(pNode pRoot, size_t k, const size_t blackCount)
	{
		//走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}
		// 统计黑色节点的个数
		if (Black == pRoot->_color)
			k++;
		// 检测当前节点与其双亲是否都为红色
		pNode pParent = pRoot->_pParent;
		if (pParent && Red == pParent->_color && Red == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}
		return _IsValidRBTree(pRoot->_pLeft, k, blackCount) &&
			_IsValidRBTree(pRoot->_pRight, k, blackCount);
	}

private:
	//pNode _header->_pParent;
	pNode _header;
};




