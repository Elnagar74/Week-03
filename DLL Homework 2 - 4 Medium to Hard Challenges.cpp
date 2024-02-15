#include <iostream>
#include <cassert>
using namespace std;

struct node {
	int data;
	node* prev, * next;
	node(int data) : data(data) { }
};

class dll {
private:
	node* head;
	node* tail;
	int len = 0;

public:
	int get_length() {
		return len;
	}

	void link(node* n1, node* n2) {
		n2->prev = n1;
		n1->next = n2;
	}

	node* delete_link(node* cur) {
		node* ret = cur->prev;
		link(cur->prev, cur->next);
		delete cur;
		len--;
		return ret;
	}

	void add_from_start(int value) {
		node* newNode = new node(value);
		if (!head) {
			head = tail = newNode;
			newNode->next = newNode->prev = NULL;
		}
		else {
			newNode->next = head;
			newNode->prev = NULL;
			head->prev = newNode;
			head = newNode;
		}
		len++;
	}

	void add_from_end(int value) {
		node* newNode = new node(value);
		if (head == NULL) {
			head = tail = newNode;
			newNode->next = newNode->prev = NULL;
		}
		else {
			newNode->next = NULL;
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		len++;
	}

	void rm_from_start() {
		if (head == NULL) // Is empty.
			cout << "linked list is empty." << endl;
		else if (head->next == NULL) { // Only one node.
			delete head;
			head = tail = NULL;
			len--;
		}
		else {
			node* cur = head;
			head = head->next;
			head->prev = NULL;
			delete cur;
			len--;
		}

	}

	void rm_from_end() {
		if (head == NULL)
			cout << "linked list is empty." << endl;
		else if (head->next == NULL) {
			delete head;
			head = tail = NULL;
			len--;
		}
		else {
			node* cur = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete cur;
			len--;
		}
	}

	node* get_nth(int n) {
		int cnt = 0;
		for (node* cur = head; cur; cur = cur->next)
			if (++cnt == n)
				return cur;

		return NULL;
	}

	node* get_nth_back(int n) {
		int cnt = 0;
		for (node* cur = tail; cur; cur = cur->prev)
			if (++cnt == n)
				return cur;

		return NULL;
	}

	void display() {
		node* cur = head;
		while (cur != NULL) {
			cout << cur->data << ' ';
			cur = cur->next;
		}
		cout << endl;
	}

	void clear() {
		node* cur;
		while (head != NULL) {
			cur = head->next;
			delete head;
			head = cur;
		}
		tail = NULL;
		len = 0;
	}

	//-----------------------------------------------------------------------------------

	// #1 --> Find the middle.

	// 1st way.
	int find_middle1() {
		assert(head);
		node* right = head, *left = tail;
		while (right != left && right != left->prev) {
			right = right->next, left = left->prev;
		}
		return left->data;
	}

	// 2nd way.
	int find_middle2() {
		assert(head);

		node* h1 = head, *h2 = head;
		while (h2 && h2->next) {
			h1 = h1->next, h2 = h2->next->next;
		}
		return h1->data;
	}

	//-----------------------------------------------------------------------------------

	// #2 --> Swap forward with backward.

	// Idea: Pr --> L, L --> Nr  "--"  Pl --> R, R --> Nl.

	// With length.
	void swap_kth_node1(int k) {
		int kth_back = len - k + 1;

		if (len == 0 || k > len || k == kth_back) return;

		if (k > kth_back) swap(k, kth_back);

		if (k == 1) {
			swap(head->data, tail->data);
			return;
		}

		node* right = get_nth(k), * left = get_nth(kth_back);

		node* right_prev = right->prev, * right_next = right->next, * left_prev = left->prev, * left_next = left->next;

		if (right->next == left) {
			link(right_prev, left);
			link(left, right);
			link(right, left_next);
		}
		else {
			link(right_prev, left);
			link(left, right_next);
			link(left_prev, right);
			link(right, left_next);
		}
	}

	// Without length.
	void swap_kth_node2(int k) {
		node* right = get_nth(k), * left = get_nth_back(k);

		if (right == left) return;

		if (k == 1) {
			swap(head->data, tail->data);
			return;
		}

		node* right_prev = right->prev, * right_next = right->next, * left_prev = left->prev, * left_next = left->next;

		if (right->next == left) {
			link(right_prev, left);
			link(left, right);
			link(right, left_next);
		}
		else {
			link(right_prev, left);
			link(left, right_next);
			link(left_prev, right);
			link(right, left_next);
		}
	}

	//-----------------------------------------------------------------------------------

	// #3 --> Reverse list nodes.

	void reverse() {
		if (len <= 1)
			return;
		
		int times = len / 2;
		while (times) {
			swap_kth_node1(times);
			times--;
		}
	}
	
	//-----------------------------------------------------------------------------------

	// #4 --> Merge lists.

	void merge_2sorted_lists(dll& other) {
		// using 2 pointer technique.
		dll temp;
		node* h1 = head, *h2 = other.head;
		while (h1 && h2) {
			if (h1->data > h2->data) {
				temp.add_from_end(h2->data);
				h2 = h2->next;
			}
			else {
				temp.add_from_end(h1->data);
				h1 = h1->next;
			}
		}
		while (h1 != NULL) { temp.add_from_end(h1->data); h1 = h1->next; }

		while (h2 != NULL) { temp.add_from_end(h2->data); h2 = h2->next; }

		other.head = other.tail = NULL;

		head = temp.head;
	}


	//-----------------------------------------------------------------------------------

};

int main()
{

	return 0;
}
