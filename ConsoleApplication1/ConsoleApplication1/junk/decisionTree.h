#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;
enum class NodeType { CLASSIFICATION, SPLIT };

struct node
{
	int key_value;
	NodeType type;
	string comparison;
	string classification;

	node *left;
	node *right;
};

class decisionTree

{
public:
	decisionTree();
	~decisionTree();
	void insert(int key, string compare, string classification, NodeType type);
	void printTree();
	node *search(int key);
	void destroyTree();

	vector<string> classes;
	vector<string> attributes;

private:
	void parseData();
	void destroyTree(node *leaf);
	void insert(int key, string compare, string classification, NodeType type, node *leaf);
	void printTree(node *leaf);
	node *search(int key, node *leaf);

	node *root;
};