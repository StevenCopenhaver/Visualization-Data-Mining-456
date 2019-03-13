#include "decisionTree.h"

// constructor
decisionTree::decisionTree()
{
	root = NULL;
	parseData();
	populateTree();
}

// creates a dummy tree for implementing graphics DEPRECATED
decisionTree::decisionTree(int n)
{
	cout << "Creating Dummy Tree" << "\n";
	root = NULL;
	insert(0, 2.5, "", "root", "N/A", NodeType::SPLIT);
	insert(1, 2.5, "", "ucellsize<2.5", "N/A", NodeType::SPLIT);
	insert(2, 4.5, "", "ucellsize>=2.5", "N/A", NodeType::SPLIT);
	insert(3, 0, "", "bnuclei<2.5", "benign", NodeType::CLASSIFICATION);
	insert(4, 0, "", "bnuclei>=2.5", "malignant", NodeType::CLASSIFICATION);
	insert(5, 2.5, "", "ucellsize<=4.5", "N/A", NodeType::SPLIT);
	insert(6, 0, "", "ucellsize>=4.5", "malignant", NodeType::CLASSIFICATION);
	insert(7, 0, "", "clump<6.5", "benign", NodeType::CLASSIFICATION);
	insert(8, 0, "", "clump>=6.5", "malignant", NodeType::CLASSIFICATION);
}

// destructor
decisionTree::~decisionTree()
{
	destroyTree();
}

// A decision tree is a binary tree whose nodes have information about branches of decisionmaking
void decisionTree::parseData()
{
	ifstream myFile("tree.txt");
	string curLine;
	int numLines = 0;

	while (getline(myFile, curLine))
		numLines++;
	// debugging purposes; prints number of lines in file
	cout << "Num lines in file: " << numLines << endl << endl;

	ifstream file("tree.txt");
	string line;


	node r;
	r.key = 0;
	r.attribute = "N/A";
	r.value = 0;
	r.comparison = "ROOT";
	r.classification = "ROOT";
	r.type = NodeType::SPLIT;
	nodes.push_back(r);

	for (int i = 1; i <= numLines; i++)
	{
		// get the attribute name from the line
		getline(file, line, '{');
		getline(file, line, '}');

		// if the attribute isn't already present in the vector of possible attributes, add it
		if (!(find(attributes.begin(), attributes.end(), line) != attributes.end()))
			attributes.push_back(line);
		// to temporarily hold the class name of node
		string attribute = line;

		// get the comparison operator (</<=/>/>=) from the line
		getline(file, line, '{');
		getline(file, line, '}');

		// to temporarily hold the comparison operator
		string comparator = line;

		// get the numerical information (e.g. 2.5) from the line
		getline(file, line, '{');
		getline(file, line, '}');

		// to temporarily hold the numerical information
		string num = line;
		string comparison = comparator + line;

		// get the decision from the line
		getline(file, line, '{');
		getline(file, line, '}');

		// to temporarily hold the classifier
		string decision = line;

		// if the attribute isn't already present in the vector of possible attributes, add it (unless it's empty)
		if (!(find(classes.begin(), classes.end(), decision) != classes.end()))
			classes.push_back(decision);

		// create a node to store in vector
		node n;
		n.key = i;
		n.attribute = attribute;
		n.value = stoi(num);
		n.comparison = comparison;
		n.classification = decision;
		
		if (decision == "N/A")
			n.type = NodeType::SPLIT;
		else
			n.type = NodeType::CLASSIFICATION;

		// put node in vector
		nodes.push_back(n);
	}
}

void decisionTree::populateTree()
{
	int keyCount = 0;
	// first node will be root
	insert(keyCount, nodes[0].value, "N/A", "root", "N/A", NodeType::SPLIT);
	keyCount++;

	// for every following node, check to see if it matches another. If it does, modify it and continue
	for (int i = 1; i < nodes.size(); i++)
	{
		for (int j = i+1; j < nodes.size(); j++)
		{
			if ((nodes[i].attribute + to_string(nodes[i].value)) == (nodes[j].attribute + to_string(nodes[j].value)))
			{
				insert(keyCount, nodes[i].value, nodes[i].attribute, nodes[i].comparison, nodes[i].classification, nodes[i].type);
				keyCount++;
				insert(keyCount, nodes[j].value, nodes[j].attribute, nodes[j].comparison, nodes[j].classification, nodes[j].type);
				keyCount++;
				nodes[i].attribute = "";
				nodes[j].attribute = to_string(j+10);
				continue;
			}
		}
		
	}
}

void decisionTree::insert(int key, int value, string attribute, string compare, string classification, NodeType type, node *parent)
{
	if (key < parent->key)
	{
		if (parent->left != NULL)
			insert(key, value, attribute, compare, classification, type, parent->left);
		else
		{
			parent->left = new node;
			parent->left->key = key;
			parent->left->value = value;
			parent->left->attribute = attribute;
			parent->left->comparison = compare;
			parent->left->classification = classification;
			parent->left->type = type;
			parent->left->left = NULL;
			parent->left->right = NULL;
		}
	}
	else if (key >= parent->key)
	{
		if (parent->right != NULL)
			insert(key, value, attribute, compare, classification, type, parent->right);
		else
		{
			parent->right = new node;
			parent->right->key = key;
			parent->right->value = value;
			parent->right->attribute = attribute;
			parent->right->comparison = compare;
			parent->right->classification = classification;
			parent->right->type = type;
			parent->right->left = NULL;
			parent->right->right = NULL;
		}
	}
}

void decisionTree::insert(int key, int value, string attribute, string compare, string classification, NodeType type)
{
	if (root != NULL)
		insert(key, value, attribute, compare, classification, type, root);
	else
	{
		root = new node;
		root->key = key;
		root->value = value;
		root->attribute = attribute;
		root->comparison = compare;
		root->classification = classification;
		root->type = type;
		root->left = NULL;
		root->right = NULL;
	}
}

// BFS from given leaf; mostly used in the public search function
node* decisionTree::search(int key, node *leaf)
{
	if (leaf != NULL)
	{
		if (key == leaf->key)
			return leaf;
		if (key < leaf->key)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else return NULL;
}

// searches from root down
node* decisionTree::search(int key)
{
	return search(key, root);
}

// prints contents of tree from root down
void decisionTree::printTree()
{
	cout << "Printing tree info: " << endl << endl;
	cout << "Key: " << root->key << "\tCondition: " << (root->comparison)
		<< "\tClass: " << root->classification << endl;
	printTree(root->left);
	printTree(root->right);
}

// prints the contents of tree from given leaf
void decisionTree::printTree(node *leaf)
{
	if (leaf != NULL)
	{
		cout << "Key: " << leaf->key << "\tCondition: " << leaf->attribute + leaf->comparison
			<< "\tClass: " << leaf->classification << endl;
		printTree(leaf->left);
		printTree(leaf->right);
	}
}

// calls delete function on every leaf, from given leaf; mostly used in the public destroy function
void decisionTree::destroyTree(node *leaf)
{
	if (leaf != NULL)
	{
		destroyTree(leaf->left);
		destroyTree(leaf->right);
		delete leaf;
	}
}

// destroys all leaves from root down
void decisionTree::destroyTree()
{
	destroyTree(root);
}