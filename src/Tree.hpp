#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <iostream>

class Node {
	public:
		// Wurzel
		Node() {
			value = 100.0f;
			for (int i = 0; i < 7; i++) {
				amount[i] = 0;
			}
		}
		// Innenknoten
		Node(float v) {
			value = v;
			for (int i = 0; i < 7; i++) {
				amount[i] = 0;
			}
		}
		// Blattknoten
		Node(float v, int a[]) {
			value = v;
			for (int i = 0; i < 7; i++) {
				amount[i] = a[i];
			}
		}

		inline float getValue() { return value; }
		inline void setValue(float v) { value = v; }
		inline std::vector<Node> getChildren() { return children; }
		inline bool hasChildren() { return children.size() > 0; }
		inline int* getAmount() { return amount; }

		void clear() {
			for (int i = 0; i < children.size(); i++) {
				children[i].clear();
			}
			children.clear();
		}
		Node addChild(float v) {
			children.push_back(Node(v));
			return children[children.size() - 1];
		}
		Node addChild(float v, int* a) {
			children.push_back(Node(v,a));
			return children[children.size() - 1];
		}
		float getSumOfValues(int num) {
			float sum = 0;
			if (num > children.size()) num = children.size();
			for (int i = 0; i < num; i++) {
				sum += children[i].value;
			}
			return sum;
		}

	private:
		// Gewichtung
		float value;

		// Nachfolger
		std::vector<Node> children;

		// Anzahl
		int amount[7];
};

class Tree {
	public:
		Tree() {
			root = Node();
		}
		~Tree() {
			root.clear();
		}

		inline Node getRoot() { return root; }

	private:
		Node root;
		
};



#endif