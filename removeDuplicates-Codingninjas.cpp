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

	// Remove duplicates -- Codingninjas

	void removeDuplicates() {
		for (node* cur = head; cur->next;) {
			if (cur->data == cur->next->data) {
				if (cur->next->next == NULL) {
					cur->next = NULL;
					break;
				}
				cur = delete_link(cur->next);
			}
			else {
				cur = cur->next;
			}
		}
	}

	//-----------------------------------------------------------------------------------
};

int main()
{

	return 0;
}