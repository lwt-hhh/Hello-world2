
//解决循环引用，资源不能及时释放的问题

#include<iostream>
#include<memory>
#include<thread>
#include<mutex>
using namespace std;

struct listnode
{
	int date;
	weak_ptr<listnode> _prev;
	weak_ptr<listnode> _next;
	~listnode()
	{
		cout << "~listnode()" << endl;
	}
};

int main()
{
	shared_ptr<listnode> node1(new listnode);
	shared_ptr<listnode> node2(new listnode);
	cout << node1.use_count() << endl;
	cout << node2.use_count()<< endl;
	node1->_next = node2;  
	node2->_prev = node1;

	cout << node1.use_count() << endl; 
	cout << node2.use_count() << endl;
	system("pause");
	return 0;
}

/*1. node1和node2两个智能指针对象指向两个节点，引用计数变成1，我们不需要手动delete。
2. node1的_next指向node2，node2的_prev指向node1，引用计数变成2。
3. node1和node2析构，引用计数减到1，但是_next还指向下一个节点。但是_prev还指向上一个节点。
4. 也就是说_next析构了，node2就释放了。
5. 也就是说_prev析构了，node1就释放了。 
6. 但是_next属于node的成员，node1释放了，_next才会析构，而node1由_prev管理，
_prev属于node2 成员，所以这就叫循环引用，谁也不会释放。
*/

// 解决方案：在引用计数的场景下，把节点中的_prev和_next改成weak_ptr就可以了 
// 原理就是，node1->_next = node2;和node2->_prev = node1;
//weak_ptr的_next和_prev不会增加 node1和node2的引用计数。 