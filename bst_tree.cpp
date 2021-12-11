#include <iostream>
#include <functional>
#include <stack>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

template<typename T, typename Comp = less<T>>
class BSTree {
public:
	BSTree(Comp comp = Comp())
		: root_(nullptr)
		, comp_(comp)
	{}

	// �������ɾ���ڵ�
	~BSTree() {
		if (nullptr != root_) {
			queue<Node*> q;
			q.push(root_);
			while (!q.empty()) {
				Node* cur = q.front();
				q.pop();
				if (nullptr != cur->left_) {
					q.push(cur->left_);
				}
				if (nullptr != cur->right_) {
					q.push(cur->right_);
				}
				delete cur;
			}
		}
	}

	void non_cur_insert(const T& val) {
		// ��Ϊ�գ����ɸ����
		if (root_ == nullptr) {
			root_ = new Node(val);
			return;
		}
		Node* cur = root_;
		Node* parent = nullptr;
		while (nullptr != cur) {
			if (cur->data_ == val) {
				// �������Ѵ��ڵ�Ԫ�أ�����
				return;
			}
			else if (comp_(val, cur->data_)) {
				parent = cur;
				cur = cur->left_;
			}
			else {
				parent = cur;
				cur = cur->right_;
			}
		}
		cur = new Node(val);
		if (comp_(val, parent->data_)) {
			parent->left_ = cur;
		}
		else {
			parent->right_ = cur;
		}
	}

	void non_cur_del(const T& val) {
		if (root_ == nullptr) {
			return;
		}
		Node* parent = nullptr;
		Node* cur = root_;
		while (cur != nullptr) {
			if (cur->data_ == val) {
				break;
			}
			else if (comp_(val, cur->data_)) {
				parent = cur;
				cur = cur->left_;
			}
			else {
				parent = cur;
				cur = cur->right_;
			}
		}
		// û�ҵ�val�ڵ�
		if (cur == nullptr) {
			return;
		}
		// ��ʱcurָ���ɾ���ڵ�
		// �����������ӣ���Ѱ��ǰ���ڵ㣬��ǰ���ڵ��ֵ�滻��ɾ���ڵ��ֵ
		if (cur->left_ != nullptr && cur->right_ != nullptr) {
			parent = cur;
			Node* pre = cur->left_;
			while (pre->right_ != nullptr) {
				parent = pre;
				pre = pre->right_;
			}
			cur->data_ = pre->data_;
			cur = pre;
		}
		
		Node* child = cur->left_ == nullptr ? cur->right_ : cur->left_;
		if (parent == nullptr) {
			delete root_;
			root_ = child;
		}
		else {
			if (parent->left_ == cur) {
				parent->left_ = child;
			}
			else {
				parent->right_ = child;
			}
		}
		delete cur;
	}

	bool non_cur_search(const T& val) const{
		if (root_ == nullptr) {
			return false;
		}
		Node* cur = root_;
		while (cur != nullptr) {
			if (val == cur->data_) {
				return true;
			}
			else if (comp_(val, cur->data_)) {
				cur = cur->left_;
			}
			else {
				cur = cur->right_;
			}
		}
		return false;
	}

	void cur_pre_order() const {
		cout << "�ݹ�ǰ�������";
		cur_pre_order(root_);
		cout << endl;
	}

	void cur_in_order() const {
		cout << "�ݹ����������";
		cur_in_order(root_);
		cout << endl;
	}

	void cur_post_order() const {
		cout << "�ݹ���������";
		cur_post_order(root_);
		cout << endl;
	}

	int high() const {
		return high(root_);
	}

	void cur_level_order() const {
		cout << "�ݹ���������";
		int tree_high = high();
		for (int i = 0; i < tree_high; i++) {
			cur_level_order(root_, i);
		}
		cout << endl;
	}

	void cur_insert(const T& val) {
		root_ = cur_insert(root_, val);
	}
	
	bool cur_search(const T& val) const {
		return cur_search(root_, val);
	}

	void cur_del(const T& val) {
		root_ = cur_del(root_, val);
	}

	// ��������������ң������Һ��ӣ���������
	void non_cur_pre_order() const {
		cout << "�ǵݹ�ǰ�������";
		stack<Node*> st;
		if (nullptr == root_) {
			return;
		}
		st.push(root_);
		while (!st.empty()) {
			Node* cur = st.top();
			cout << cur->data_ << " ";
			st.pop();
			if(nullptr != cur->right_){
				st.push(cur->right_);
			}
			if (nullptr != cur->left_) {
				st.push(cur->left_);
			}
		}
		cout << endl;
	}

	void non_cur_in_order() const {
		cout << "�ǵݹ����������";
		if (nullptr == root_) {
			return ;
		}
		stack<Node*> st;
		Node* cur = root_;
		while (!st.empty() || nullptr != cur) {
			if (nullptr != cur) {
				st.push(cur);
				cur = cur->left_;
			}
			else {
				cur = st.top();
				st.pop();
				cout << cur->data_ << " ";
				cur = cur->right_;
			}
		}
	}

	void non_cur_post_order() const {
		cout << "�ǵݹ���������";
		if (nullptr == root_) {
			return;
		}

		// LRV -> VRL
		stack<Node*> st;
		stack<Node*> res_st;

		st.push(root_);
		while (!st.empty()) {
			Node* cur = st.top();
			res_st.push(cur);
			st.pop();
			if (nullptr != cur->left_) {
				st.push(cur->left_);
			}
			if (nullptr != cur->right_) {
				st.push(cur->right_);
			}
		}
		while (!res_st.empty()) {
			cout << res_st.top()->data_ << " ";
			res_st.pop();
		}
		cout << endl;
	}

	void non_cur_level_order() const {
		cout << "�ǵݹ���������";
		if (nullptr == root_) {
			return;
		}
		queue<Node*> q;
		q.push(root_);
		while (!q.empty()) {
			Node* cur = q.front();
			q.pop();
			cout << cur->data_ << " ";
			if (nullptr != cur->left_) {
				q.push(cur->left_);
			}
			if (nullptr != cur->right_) {
				q.push(cur->right_);
			}
		}
		cout << endl;
	}

	int get_tree_num() {
		return get_tree_num(root_);
	}

	// �ҵ�����[low, high]�ڵ�ֵ����vec
	void find_values(vector<T>& vec, int low, int high) {
		find_values(root_, vec, low, high);
	}

	bool isBST() {
		Node* pre = nullptr;
		return isBST(root_, pre);
	}

	bool is_child_tree(const BSTree<T, Comp>& tree) const {
		if (nullptr == tree.root_) {
			return true;
		}
		Node* cur = root_;
		while (nullptr != cur) {
			if (cur->data_ == tree.root_->data_) {
				break;
			}
			else if (comp_(tree.root_->data_, cur->data_)) {
				cur = cur->left_;
			}
			else {
				cur = cur->right_;
			}
		}
		if (nullptr == cur) {
			// û�ҵ������ĸ����
			return false;
		}
		return is_child_tree(cur, tree.root_);
	}
	
	void mirror_reverse() {
		mirror_reverse(root_);
	}

	bool is_mirror_symmetry() {
		if (nullptr == root_) {
			return true;
		}
		return is_mirror_symmetry(root_->left_, root_->right_);
	}

	void rebuild(int pre[], int i, int j, int in[], int m, int n) {
		root_ = cur_rebuild(pre, i, j, in, m, n);
	}

	bool is_balance() {
		int level = 0;
		bool flag = true; // �ٶ���ǰ��Ϊƽ����
		is_balance(root_, level, flag);
		return flag;
	}

	// �����������LVR������k���ڵ㣬Ҳ��RVL������k���ڵ�
	T get_k_node(const int k) {
		int cnt = 0;
		Node* node = get_k_node(root_, cnt, k);
		if (nullptr != node) {
			return node->data_;
		}
		try {
			string error = "�������������������";
			error += to_string(k);
			error += "���ڵ�";
			throw error;
		}
		catch(string error){
			cout << error<<endl;
			exit(1);
		}
		
	}

private:
	// �������Ͷ��壬�������ɱ���
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		Node(T data = T())
			: data_(data)
			, left_(nullptr)
			, right_(nullptr)
		{}
	};

	void cur_pre_order(Node* node) const {
		if (nullptr != node) {
			cout << node->data_ << " ";
			cur_pre_order(node->left_);
			cur_pre_order(node->right_);
		}
	}

	void cur_in_order(Node* node) const {
		if (nullptr != node) {
			cur_in_order(node->left_);
			cout << node->data_ << " ";
			cur_in_order(node->right_);
		}
	}

	void cur_post_order(Node* node) const {
		if (nullptr != node) {
			cur_post_order(node->left_);
			cur_post_order(node->right_);
			cout << node->data_ << " ";
		}
	}

	int high(Node* node) const {
		if (nullptr == node) {
			return 0;
		}
		int left = high(node->left_);
		int right = high(node->right_);
		return left > right ? left + 1 : right + 1;
	}
	
	// �������nodeΪ���ڵ�ĵ�i��Ľڵ�
	void cur_level_order(Node* node, int i) const {
		// ������ĳ����֧�������ķ�֧��Ҫ�����Ϳ��ܳ�����ĳ����i��i��Ϊ0��nodeΪnullptr�����
		if (nullptr == node) {
			return;
		}
		if (i == 0) {
			cout << node->data_ << " ";
			return;
		}
		cur_level_order(node->left_, i - 1);
		cur_level_order(node->right_, i - 1);
	}

	
	// ����nodeΪ���������в���val�������ز���ڵ������ĸ����
	Node* cur_insert(Node* node, const T& val) {
		// �ҵ����ʵ�λ�ã������½ڵ㣬�����ؽڵ��ַ
		if (nullptr == node) {
			return new Node(val);
		}
		if (val == node->data_) {
			// ��������ͬ����
			return node;
		}
		else if (comp_(val, node->data_)) {
			node->left_ = cur_insert(node->left_, val);
		}
		else {
			node->right_ = cur_insert(node->right_, val);
		}
		return node;
	}

	bool cur_search(Node* node, const T& val) const {
		if (nullptr == node) {
			return false;
		}
		if (val == node->data_) {
			return true;
		}
		else if (comp_(val, node->data_)) {
			return cur_search(node->left_, val);
		}
		else {
			return cur_search(node->right_, val);
		}
	}

	// ����nodeΪ����������Ѱ��ֵΪval�Ľڵ�ɾ��
	// ɾ��ָ���ڵ����Ҫ��ɾ���ڵ�ĺ��ӽڵ�ĵ�ַ���ظ���Ӧ���ڵ�
	Node* cur_del(Node* node, const T& val) {
		if (nullptr == node) {
			return nullptr;
		}
		if (node->data_ == val) {
			// �ҵ������3
			if (nullptr != node->left_ && nullptr != node->right_) {
				// ��ǰ���ڵ㣬�滻��ǰ�ڵ��ֵ��ɾ��ǰ���ڵ�
				Node* parent = node;
				Node* pre = node->left_;
				while (nullptr != pre->right_) {
					parent = pre;
					pre = pre->right_;
				}
				node->data_ = pre->data_;
				
				// node->left_ = cur_del(node->left_, pre->data_);
				Node* child = (nullptr == pre->left_) ? pre->right_ : pre->left_;

				if (parent == nullptr) {
					delete root_;
					root_ = child;
				}
				else {
					if (parent->left_ == pre) {
						parent->left_ = child;
					}
					else {
						parent->right_ = child;
					}
				}
				delete pre;
			}
			else {
				// ���1��2
				if (nullptr != node->left_) {
					// ���Ӳ��գ�ɾ����ǰ�ڵ�󷵻����ӵĵ�ַ
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (nullptr != node->right_){
					// �Һ��Ӳ��գ�ɾ����ǰ�ڵ�󷵻��Һ��ӵĵ�ַ
					Node* right = node->right_;
					delete node;
					return right;
				}
				else {
					// ɾ��Ҷ�ӽڵ�
					delete node;
					return nullptr;
				}
			}
		}
		else if (comp_(val, node->data_)) {
			node->left_ = cur_del(node->left_, val);
		}
		else {
			node->right_ = cur_del(node->right_, val);
		}
		// ÿ�ε��ú��������ǽ�����һ���ڵ㣬���ݵ�ʱ�򽫵�ǰ�ڵ�ĵ�ַ���ظ���Ӧ���ڵ�
		return node;
	}

	// ������nodeΪ���������Ľڵ���
	int get_tree_num(Node* node) {
		if (nullptr == node) {
			return 0;
		}
		int left = get_tree_num(node->left_);
		int right = get_tree_num(node->right_);
		return left + right + 1;
	}

	// �ҵ���nodeΪ���������У�ֵ����[low, high]֮���Ԫ��
	void find_values(Node* node, vector<T>& vec, int low, int high) {
		if (nullptr == node) {
			return;
		}

		if (node->data_ > low) {
			find_values(node->left_, vec, low, high);
		}
		
		if (node->data_ >= low && node->data_ <= high) {
			vec.push_back(node->data_);
		}

		if (node->data_ < high) {
			find_values(node->right_, vec, low, high);
		}
		
	}

	bool isBST(Node* node, Node* &pre) {
		if (nullptr == node) {
			return true;
		}
		if (!isBST(node->left_, pre)) {
			return false;
		}
		if (nullptr != pre) {
			if (comp_(node->data_, pre->data_)) {
				return false;
			}
		}
		pre = node;
		return isBST(node->right_, pre);
	}

	bool is_child_tree(Node* father, Node* child) const{
		if (nullptr == father && nullptr == child) {
			return true;
		}
		// ����Ϊ�գ����Ӳ���
		if (nullptr == father) {
			return false;
		}
		// ����Ϊ�գ����ײ���
		if (nullptr == child) {
			return true;
		}
		// ���Ӹ��׶�����
		if (father->data_ != child->data_) {
			return false;
		}
		return is_child_tree(father->left_, child->left_) && is_child_tree(father->right_, child->right_);
	}

	void mirror_reverse(Node* node) {
		if (nullptr == node) {
			return;
		}
		Node* tmp = node->left_;
		node->left_ = node->right_;
		node->right_ = tmp;
		mirror_reverse(node->left_);
		mirror_reverse(node->right_);
	}

	bool is_mirror_symmetry(Node* l , Node* r) {
		if (nullptr == l && nullptr == r) {
			return true;
		}
		if (nullptr != l && nullptr != r) {
			// �����ڵ㶼����
			if (l->data_ != r->data_) {
				return false;
			}
			return is_mirror_symmetry(l->left_, r->right_) && is_mirror_symmetry(l->right_, r->left_);
		}
		return false;
	}

	// ��������pre����[i, j]Ԫ�غ�����in����[m, n]Ԫ���ؽ�������
	Node* cur_rebuild(int pre[], int i, int j, int in[], int m, int n) {
		if (i > j || m > n) {
			return nullptr;
		}
		Node* node = new Node(pre[i]);
		for (int k = m; k <= n; k++) {
			if (pre[i] == in[k]) {
				// ����������������ҵ���ǰ�Ľ��
				node->left_ = cur_rebuild(pre, i + 1, i + ( k - m ), in, m, k - 1);
				node->right_ = cur_rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);
				return node;
			}
		}
		// ������������������ҵ���ǰ�Ľ�㣬��˵�����������ƥ��
		return nullptr;
	}

	int is_balance(Node* node, int level, bool& flag) {
		if (nullptr == node) {
			return level;
		}

		int left = is_balance(node->left_, level + 1, flag);
		if (!flag) {
			// ִ�е��������ֵ�Ƕ��ٲ���Ҫ��������Ϊ����ǰ�������������ټ����ݹ�
			// flag�Ѿ���ֵΪfalse���Ϳ����ж���ǰ����ƽ��
			return -1;
		}

		int right = is_balance(node->right_, level + 1, flag);
		if (!flag) {
			return -1;
		}

		// �жϵ�ǰ�ڵ��Ƿ�ʧ��
		if (abs(left - right) > 1) {
			flag = false;
		}
		// ��������level�Ĵ�ֵ��Ҳ�������˵�ǰ�ڵ���������������
		return max(left, right);
	}

	// �����������LVR������k���ڵ㣬Ҳ��RVL������k���ڵ�
	Node* get_k_node(Node* node, int& cnt, const int k) {
		if (nullptr == node) {
			return nullptr;
		}
		Node* right = get_k_node(node->right_, cnt, k);

		if (right != nullptr) {
			return right;
		}

		if (++cnt == k) {
			return node;
		}
		if (cnt > k) {
			return nullptr;
		}

		return get_k_node(node->left_, cnt, k);
	}

	// ָ��BST���ĸ����
	Node* root_;
	Comp comp_;
};

#if 0
void test() {
	using Node = BSTree<int>::Node;
	BSTree<int> tree;
	tree.root_ = new Node(10);
	Node* node1 = new Node(5);
	Node* node2 = new Node(20);
	Node* node3 = new Node(8);
	Node* node4 = new Node(30);
	tree.root_->left_ = node1;
	tree.root_->right_ = node2;
	node2->left_ = node3;
	node2->right_ = node4;
	cout << tree.isBST() << endl;
}


void test1() {
	int arr[] = { 57,38,61,30,45,59,68,41,40,48 };
	BSTree<int> tree;
	for (int val : arr) {
		tree.cur_insert(val);
	}

	using Node = BSTree<int>::Node;
	BSTree<int> tree1;
	tree1.root_ = new Node(45);
	Node* node1 = new Node(1);
	Node* node2 = new Node(1);
	Node* node3 = new Node(2);
	Node* node4 = new Node(2);

	tree1.root_->left_ = node1;
	tree1.root_->right_ = node2;
	node1->left_ = node3;
	node2->right_ = node4;
	cout<<tree1.is_mirror_symmetry();
}
#endif

void test() {
	int pre[] = { 58, 24, 0, 5, 34, 41, 67, 62, 64,69,78 };
	int in[] = { 0, 5, 24,34,41,58,62, 64,67,69,78 };
	BSTree<int> tree;
	tree.rebuild(pre, 0, 10, in, 0, 10);
	tree.cur_pre_order();
	tree.cur_in_order();
}

int main() {
	using Element = pair<int, string>;
	using Functor = function<bool(Element, Element)>;

	BSTree<Element, Functor> tree(
		[](Element e1, Element e2)->bool {
		return e1.first > e2.first;
	});

	/*int arr[] = { 57,24,67,0,34,62,69,5,41,64,78};
	BSTree<int> tree;
	for (int val : arr) {
		tree.cur_insert(val);
	}*/

	// cout<<tree.get_k_node(-1);
	// tree.non_cur_level_order();
	// cout << tree.isBST() << endl;

	//cout << tree.cur_search(55) << endl;
	//cout << tree.cur_search(0) << endl;
	//cout << tree.cur_search(38) << endl;
	//cout << tree.cur_search(57) << endl;

	//tree.cur_in_order();
	//tree.non_cur_del(45);
	//tree.cur_in_order();
	//tree.non_cur_in_order();
	//tree.non_cur_del(57);
	//tree.cur_in_order();
	//tree.non_cur_del(30);
	//tree.cur_in_order();
	//tree.non_cur_post_order();
	//tree.cur_post_order();

	//BSTree<int> tree;
	//BSTree<int>* p = &tree;
	//BSTree<int>& q = tree;

	//cout << sizeof(tree) << endl;
	//cout << sizeof(q) << endl;
	//cout << sizeof(p) << endl;



	//char arr[5] = {1};
	//char(&q)[5] = arr;  // q
	//char(*p)[5] = &arr;
	//
	//cout << sizeof(arr) << endl;
	//cout << sizeof(q) << endl;
	//cout << sizeof(p) << endl;
	

	//cout << &tree << endl;
	//cout << &q << endl;
	//cout << p << endl;
	return 0;
}
