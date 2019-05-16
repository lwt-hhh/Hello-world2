
//���ѭ�����ã���Դ���ܼ�ʱ�ͷŵ�����

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

/*1. node1��node2��������ָ�����ָ�������ڵ㣬���ü������1�����ǲ���Ҫ�ֶ�delete��
2. node1��_nextָ��node2��node2��_prevָ��node1�����ü������2��
3. node1��node2���������ü�������1������_next��ָ����һ���ڵ㡣����_prev��ָ����һ���ڵ㡣
4. Ҳ����˵_next�����ˣ�node2���ͷ��ˡ�
5. Ҳ����˵_prev�����ˣ�node1���ͷ��ˡ� 
6. ����_next����node�ĳ�Ա��node1�ͷ��ˣ�_next�Ż���������node1��_prev����
_prev����node2 ��Ա��������ͽ�ѭ�����ã�˭Ҳ�����ͷš�
*/

// ��������������ü����ĳ����£��ѽڵ��е�_prev��_next�ĳ�weak_ptr�Ϳ����� 
// ԭ����ǣ�node1->_next = node2;��node2->_prev = node1;
//weak_ptr��_next��_prev�������� node1��node2�����ü����� 