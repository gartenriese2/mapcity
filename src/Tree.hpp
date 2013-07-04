#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <iostream>
#include <array>

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
		Node(const float v) {
			value = v;
			for (int i = 0; i < 7; i++) {
				amount[i] = 0;
			}
		}
		
		// Blattknoten
		Node(const float v, const std::array<int, 7> a) {
			value = v;

			for (int i = 0; i < 7; i++) {
				amount[i] = a[i];
			}
		}

		float getValue() const { return value; }
		void setValue(const float v) { value = v; }
		const std::vector<Node> & getChildren() const { return children; }
		bool hasChildren() const { return children.size() > 0; }
		const std::array<int, 7> & getAmount() const { return amount; }

		void clear() {
			for (int i = 0; i < children.size(); i++) {
				children[i].clear();
			}
			children.clear();
		}
		const Node & addChild(const float v) {
			children.push_back(Node(v));
			return children[children.size() - 1];
		}
		const Node & addChild(const float v, const std::array<int, 7> a) {
			children.push_back(Node(v,a));
			return children[children.size() - 1];
		}

		float getSumOfValues(int num) const {
			
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
		std::array<int, 7> amount;
};

class Tree {
	public:
		
		Tree() {
			root = Node();
		}
		~Tree() {
			root.clear();
		}

		const Node & getRoot() { return root; }

	private:
		
		Node root;
		
};



#endif