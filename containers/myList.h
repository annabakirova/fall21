//TODO: erase, constructors, operators=
#pragma once
#include <utility>

template <typename T>
class MyList {
private:
	struct Node {
		Node* prev_;
		Node* next_;
		T data_;
		Node(const T& x) : prev_(nullptr), next_(nullptr), data_(x) {}
		Node(T&& x) : prev_(nullptr), next_(nullptr), data_(std::move(x)) {}
	};

	Node* head_;
	Node* tail_;
	unsigned size_;    //number of nodes

public:
	MyList() : head_(nullptr), tail_(nullptr), size_(0) {}

	MyList(const MyList& other);    //outer implementation

	MyList(MyList&& other);    //outer implementation

	~MyList() {
		clear();
	}

	MyList& operator=(const MyList& other);    //outer implementation

	MyList& operator=(MyList&& other);    //outer implementation

	void clear() {
		Node* tmp = nullptr;
		while (head_) {
			tmp = head_;
			head_ = head_->next_;
			delete tmp;
		}
		tail_ = nullptr;
		size_ = 0;
	}

	void push_back(const T& data) {
		if (!head_) {
			head_ = tail_ = new Node(data);
		}
		else {
			tail_->next_ = new Node(data);

			tail_->next_->prev_ = tail_;
			tail_ = tail_->next_;
		}
		++size_;
	}

	void push_front(const T& data) {
		if (!head_) {
			head_ = tail_ = new Node(data);
		}
		else {
			head_->prev_ = new Node(data);
			head_->prev_->next_ = head_;
			head_ = head_->prev_;
		}
		++size_;
	}

	unsigned getSize() {
		return size_;
	}

	class iterator {
		Node* curr_;
	public:
		iterator(Node* pos = nullptr) : curr_(pos) { ; }
		T& operator*() const {
			return curr_->data_;
		}
		T& operator*() {
			return curr_->data_;
		}
		bool operator==(const iterator& pos) {
			return curr_ == pos.curr_;
		}
		bool operator!=(const iterator& pos) {
			return curr_ != pos.curr_;
		}
		//infix
		iterator& operator++() {
			if (curr_) {
				curr_ = curr_->next_;
			}
			else {
				throw "iterator is out of list boundaries";
			}
			return *this;
		}
		iterator operator++(int) {
			Node* tmp = curr_;
			if (curr_) {
				curr_ = curr_->next_;
			}
			else {
				throw "iterator is out of list boundaries";
			}
			return iterator(tmp);
		}
		friend class MyList;
	};

	class reverse_iterator {
		Node* curr_;
	public:
		reverse_iterator(Node* pos = nullptr) : curr_(pos) { ; }
		T& operator*() const {
			return curr_->data_;
		}
		T& operator*() {
			return curr_->data_;
		}
		//указывают ли два итератора на один и тот же узел
		bool operator==(const reverse_iterator& pos) {
			return curr_ == pos.curr_;
		}
		bool operator!=(const reverse_iterator& pos) {
			return curr_ != pos.curr_;
		}
		//infix
		reverse_iterator& operator++() {
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				throw "iterator is out of list boundaries";
			}
			return *this;
		}
		reverse_iterator operator++(int) {
			Node* tmp = curr_;
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				throw "iterator is out of list boundaries";
			}
			return reverse_iterator(tmp);
		}
		friend class MyList;
	};

	iterator begin() const {
		return iterator(head_);
	}
	//iterator poining next to the last element
	iterator end() const {
		return iterator(nullptr);
	}
	reverse_iterator rbegin() const {
		return reverse_iterator(tail_);
	}
	//iterator poining next to the last element
	reverse_iterator rend() const {
		return reverse_iterator(nullptr);
	}

	iterator find(const T&) const;
	void erase(const iterator&);
	iterator insert(iterator, const T&);

};

template <typename T>
typename MyList<T>::iterator MyList<T>::find(const T& X) const {
	Node* now = head_;
	while (now) {
		if (now->data_ == X)
			return iterator(now);
		now = now->next_;
	}
	return end();
}

template <typename T>
typename MyList<T>::iterator MyList<T>::insert(MyList<T>::iterator pos, const T& x) {
	Node* tmp = new Node(x);
	tmp->next_ = pos.curr_;
	tmp->prev_ = (pos.curr_)->prev_;
	//if curr_ is not head_
	if ((pos.curr_)->prev_) {
		(pos.curr_)->prev_->next_ = tmp;
	}
	else {
		head_ = tmp;
	}
	(pos.curr_)->prev_ = tmp;
	++size_;
	return iterator(tmp);
}