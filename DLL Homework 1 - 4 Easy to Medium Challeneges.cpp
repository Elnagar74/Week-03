#include <iostream>
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
			/*
			// If tail is not exist.
			node* cur = head;
			while (cur->next != NULL) {
				cur = cur->next;
			}
			cur->next = newNode;
			newNode->prev = cur;
			newNode->next = NULL;
			tail = newNode;
			*/

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

	void dispaly() {
		node* cur = head;
		while (cur != NULL) {
			cout << cur->data << ' ';
			cur = cur->next;
		}
		cout << endl;
	}

	~dll() {
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

	// #1 --> Delete all nodes with key.

	void delete_all_nodes_with_key(int value) {
		if (head == NULL)
			return;
		add_from_start(-value);

		for (node* cur = head; cur; cur = cur->next) {
			if (cur->data == value) {
				if (cur->next == NULL) {
					rm_from_end();
					break;
				}	
				else
					cur = delete_link(cur);
			}
		}

		rm_from_start();
	}

	//-----------------------------------------------------------------------------------

	// #2 --> Delete even positions.

	void delete_even_positions() {
		if (len < 2)
			return;

		int cnt = 1;
		for (node* cur = head; cur; cur = cur->next, cnt++) {
			if (cnt % 2 == 0) {
				if (cur->next == NULL) {
					rm_from_end();
					break;
				}
				else
					cur = delete_link(cur);
			}
		}
	}

	//-----------------------------------------------------------------------------------

	// #3 --> Delete odd positions.

	// 1st way.
	void delete_odd_positions() {
		if (len == 0)
			return;

		rm_from_start();
		int cnt = 2;
		for (node* cur = head; cur; cur = cur->next, cnt++) {
			if (cnt % 2 != 0) {
				if (cur->next == NULL) {
					rm_from_end();
					break;
				}
				else
					cur = delete_link(cur);
			}
		}
	}

	// 2nd way --> reuse old functions.
	void delete_odd_positions1() {
		add_from_start(0);
		delete_even_positions();
		rm_from_start();
	}

	//-----------------------------------------------------------------------------------

	// #4 --> Is Palindrome.

	bool is_palindrome() {
		if (len < 2)
			return true;

		for (node* right = head, *left = tail; right || left; right = right->next, left = left->prev)
			if (right->data != left->data)
				return false;
		return true;
	}

	//-----------------------------------------------------------------------------------
};

int main()
{
	
	return 0;
}