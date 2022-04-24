#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

class HuffmanTree {
	class HuffmanNode {
	public:
		char ch_;
		int freq_;
		HuffmanNode* left;
		HuffmanNode* right;
		HuffmanNode(char ch, int freq) : ch_(ch), freq_(freq), left(nullptr), right(nullptr) {}
	};
	std::unordered_map<char, int> freq;
public:

	void countFrequences(std::string str) {
		for (char ch : str) {
			freq[ch]++;
		}
	}

	class compare {
	public:
		bool operator()(HuffmanNode* left, HuffmanNode* right) {
			return left->freq_ > right->freq_;
		}
	};

	void print(HuffmanNode* root_, std::string str){
		if (!root_) { return; }
		if (root_->ch_ != CHAR_MAX) {
			std::cout << "'" << root_->ch_ << "' " << str << std::endl;
		}
		print(root_->left, str + "0");
		print(root_->right, str + "1");
	}

	void encode(std::string str) {
		countFrequences(str);

		HuffmanNode* l = nullptr;
		HuffmanNode* r = nullptr;
		HuffmanNode* top = nullptr;

		std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, compare> minHeap;
		for (std::unordered_map<char, int>::iterator f = freq.begin(); f != freq.end(); ++f) {
			minHeap.push(new HuffmanNode(f->first, f->second));
		}

		while (minHeap.size() != 1) {
			l = minHeap.top();
			minHeap.pop();
			r = minHeap.top();
			minHeap.pop();
			top = new HuffmanNode(CHAR_MAX, l->freq_ + r->freq_);
			minHeap.push(top);
			top->left = l;
			top->right = r;
		}
		HuffmanNode* root_ = minHeap.top();
		print(root_, "");
	}
};