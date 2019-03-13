#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;
enum class NodeType { ROOT, LEFT_SPLIT, RIGHT_SPLIT, UNDEFINED };

struct DataPoint {

	vector<double> attributes;
	string target;

	DataPoint(vector<double> attributes, string target) {
		this->attributes = attributes;
		this->target = target;
	}

};

struct node
{
	int key;
	int value;
	NodeType type;
	NodeType parentSplit;
	string attribute;
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
	void insert(int key, int value, string attribute, string compare, string classification, NodeType type);
	void printTree();
	node *search(int key);
	void destroyTree();
	void populateTree();

	vector<string> classes;
	vector<string> attributes;
	vector<node> nodes;
	vector<DataPoint> data;

private:
	void parseData();
	void GetData(string fileName);
	void destroyTree(node *leaf);
	void insert(int key, int value, string attribute, string compare, string classification, NodeType type, node *leaf);
	void printTree(node *leaf);
	node *search(int key, node *leaf);

	node *root;
};