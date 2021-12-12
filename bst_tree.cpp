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

	// 层序遍历删除节点
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
		// 树为空，生成根结点
		if (root_ == nullptr) {
			root_ = new Node(val);
			return;
		}
		Node* cur = root_;
		Node* parent = nullptr;
		while (nullptr != cur) {
			if (cur->data_ == val) {
				// 不插入已存在的元素，结束
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
		// 没找到val节点
		if (cur == nullptr) {
			return;
		}
		// 此时cur指向待删除节点
		// 若有两个孩子，则寻找前驱节点，用前驱节点的值替换待删除节点的值
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
		cout << "递归前序遍历：";
		cur_pre_order(root_);
		cout << endl;
	}

	void cur_in_order() const {
		cout << "递归中序遍历：";
		cur_in_order(root_);
		cout << endl;
	}

	void cur_post_order() const {
		cout << "递归后序遍历：";
		cur_post_order(root_);
		cout << endl;
	}

	int high() const {
		return high(root_);
	}

	void cur_level_order() const {
		cout << "递归层序遍历：";
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

	// 先序遍历：根左右，先入右孩子，后入左孩子
	void non_cur_pre_order() const {
		cout << "非递归前序遍历：";
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
		cout << "非递归中序遍历：";
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
		cout << "非递归后序遍历：";
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
		cout << "非递归层序遍历：";
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

	// 找到区间[low, high]内的值存入vec
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
			// 没找到子树的根结点
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
		bool flag = true; // 假定当前树为平衡树
		is_balance(root_, level, flag);
		return flag;
	}
	

	// 返回中序遍历LVR倒数第k个节点，也即RVL正数第k个节点
	T get_k_node(const int k) {
		int cnt = 0;
		Node* node = get_k_node(root_, cnt, k);
		if (nullptr != node) {
			return node->data_;
		}
		try {
			string error = "不存在中序遍历倒数第";
			error += to_string(k);
			error += "个节点";
			throw error;
		}
		catch(string error){
			cout << error<<endl;
			exit(1);
		}
		
	}

	T getLCA(const T& val1, const T& val2) {
		if (nullptr == root_) {
			throw "root nullptr";
		}
		Node* lca = getLCA(root_, val1, val2);
		if (nullptr == lca) {
			throw "no LCA";
		}
		return lca->data_;
	}

private:
	// 这是类型定义，不是生成变量
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
	
	// 可输出以node为根节点的第i层的节点
	void cur_level_order(Node* node, int i) const {
		// 当树的某个分支比其他的分支都要长，就可能出现在某个第i层i不为0，node为nullptr的情况
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

	
	// 在以node为根结点的树中插入val，并返回插入节点后的树的根结点
	Node* cur_insert(Node* node, const T& val) {
		// 找到合适的位置，生成新节点，并返回节点地址
		if (nullptr == node) {
			return new Node(val);
		}
		if (val == node->data_) {
			// 不插入相同数据
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

	// 在以node为根结点的树中寻找值为val的节点删除
	// 删除指定节点后，需要把删除节点的孩子节点的地址返回给对应父节点
	Node* cur_del(Node* node, const T& val) {
		if (nullptr == node) {
			return nullptr;
		}
		if (node->data_ == val) {
			// 找到后，情况3
			if (nullptr != node->left_ && nullptr != node->right_) {
				// 找前驱节点，替换当前节点的值后，删除前驱节点
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
				// 情况1、2
				if (nullptr != node->left_) {
					// 左孩子不空，删除当前节点后返回左孩子的地址
					Node* left = node->left_;
					delete node;
					return left;
				}
				else if (nullptr != node->right_){
					// 右孩子不空，删除当前节点后返回右孩子的地址
					Node* right = node->right_;
					delete node;
					return right;
				}
				else {
					// 删除叶子节点
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
		// 每次调用函数，都是进入了一个节点，回溯的时候将当前节点的地址返回给对应父节点
		return node;
	}

	// 返回以node为根结点的树的节点数
	int get_tree_num(Node* node) {
		if (nullptr == node) {
			return 0;
		}
		int left = get_tree_num(node->left_);
		int right = get_tree_num(node->right_);
		return left + right + 1;
	}

	// 找到以node为根结点的树中，值介于[low, high]之间的元素
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
		// 父亲为空，孩子不空
		if (nullptr == father) {
			return false;
		}
		// 孩子为空，父亲不空
		if (nullptr == child) {
			return true;
		}
		// 孩子父亲都不空
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
			// 两个节点都不空
			if (l->data_ != r->data_) {
				return false;
			}
			return is_mirror_symmetry(l->left_, r->right_) && is_mirror_symmetry(l->right_, r->left_);
		}
		return false;
	}

	// 利用序列pre区间[i, j]元素和序列in区间[m, n]元素重建二叉树
	Node* cur_rebuild(int pre[], int i, int j, int in[], int m, int n) {
		if (i > j || m > n) {
			return nullptr;
		}
		Node* node = new Node(pre[i]);
		for (int k = m; k <= n; k++) {
			if (pre[i] == in[k]) {
				// 在中序遍历序列中找到当前的结点
				node->left_ = cur_rebuild(pre, i + 1, i + ( k - m ), in, m, k - 1);
				node->right_ = cur_rebuild(pre, i + (k - m) + 1, j, in, k + 1, n);
				return node;
			}
		}
		// 若在中序遍历序列中找到当前的结点，则说明先序和中序不匹配
		return nullptr;
	}

	int is_balance(Node* node, int level, bool& flag) {
		if (nullptr == node) {
			return level;
		}

		int left = is_balance(node->left_, level + 1, flag);
		if (!flag) {
			// 执行到这里，返回值是多少不重要，返回是为了提前结束函数，不再继续递归
			// flag已经被值为false，就可以判定当前树不平衡
			return -1;
		}

		int right = is_balance(node->right_, level + 1, flag);
		if (!flag) {
			return -1;
		}

		// 判断当前节点是否失衡
		if (abs(left - right) > 1) {
			flag = false;
		}
		// 返回子树level的大值，也即返回了当前节点的子树中最大的深度
		return max(left, right);
	}

	// 返回中序遍历LVR倒数第k个节点，也即RVL正数第k个节点
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

	Node* getLCA(Node* node, const T& val1, const T& val2) {
		if (nullptr == node) {
			return nullptr;
		}
		if (comp_(node->data_, val1) && comp_(node->data_, val2)) {
			return getLCA(node->right_, val1, val2);
		}else if(comp_(val1, node->data_) && comp_(val2, node->data_)){
			return getLCA(node->left_, val1, val2);
		}
		else {
			return node;
		}
	}
	// 指向BST树的根结点
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
	int pre[] = { 50,20,80,10,40,60,90 };
	int in[] = { 0, 5, 24,34,41,58,62, 64,67,69,78 };
	BSTree<int> tree;
	tree.rebuild(pre, 0, 10, in, 0, 10);
	tree.cur_pre_order();
	tree.cur_in_order();
}

int main() {
	/*using Element = pair<int, string>;
	using Functor = function<bool(Element, Element)>;

	BSTree<Element, Functor> tree(
		[](Element e1, Element e2)->bool {
		return e1.first > e2.first;
	});*/

	int arr[] = { 50,20,80,10,40,60,90 };
	BSTree<int> tree;
	for (int val : arr) {
		tree.cur_insert(val);
	}
	cout << tree.getLCA(20, 90);
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
