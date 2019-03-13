#include "decisionTree.h"

// constructor
decisionTree::decisionTree()
{
	root = NULL;
	parseData();
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

	for (int i = 0; i < numLines; i++)
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

		// get the decision from the line
		getline(file, line, '{');
		getline(file, line, '}');

		// to temporarily hold the classifier
		string decision = line;

		// if the attribute isn't already present in the vector of possible attributes, add it (unless it's empty)
		if (!(find(classes.begin(), classes.end(), decision) != classes.end()))
			classes.push_back(decision);

		
		// debugging purposes: print the contents of the file
		//cout << attribute << ' ' << comparator << ' ' << num << ' ' << decision << endl;

		string comparison = attribute + ' ' + comparator + ' ' + num;

		if (decision == "N/A")
		{
			insert(i, comparison, "N/A", NodeType::SPLIT);
			cout << "Adding Split Node. " << endl;
		}
		else if (decision == classes[0])
		{
			insert(i, comparison, classes[0], NodeType::CLASSIFICATION);
			cout << "Adding Classification Node. " << endl;
		}
		else if (decision == classes[1])
		{
			insert(i, comparison, classes[1], NodeType::CLASSIFICATION);
			cout << "Adding Classification Node. " << endl;
		}
		else if (decision == classes[2])
		{
			insert(i, comparison, classes[2], NodeType::CLASSIFICATION);
			cout << "Adding Classification Node. " << endl;
		}
		else if (decision == classes[3])
		{
			insert(i, comparison, classes[3], NodeType::CLASSIFICATION);
			cout << "Adding Classification Node. " << endl;
		}
		else
		{
			cout << "Error: Invalid file format! " << endl;
			return;
		}
	}
	cout << endl << "Tree constructed successfully! " << endl;

	// debugging purposes: print the contents of the classes and attributes vectors
	for (int i = 0; i < classes.size(); i++)
		cout << classes[i] << ' ';
	
	cout << endl;

	//for (int i = 0; i < attributes.size(); i++)
	//	cout << attributes[i] << ' ';

	//cout << endl;

}

void decisionTree::insert(int key, string compare, string classification, NodeType type, node *parent)
{
	if (key < parent->key_value)
	{
		if (parent->left != NULL)
			insert(key, compare, classification, type, parent->left);
		else
		{
			parent->left = new node;
			parent->left->key_value = key;
			parent->left->comparison = compare;
			parent->left->classification = classification;
			parent->left->type = type;
			parent->left->left = NULL;
			parent->left->left = NULL;
		}
	}
	else if (key >= parent->key_value)
	{
		if (parent->right != NULL)
			insert(key, compare, classification, type, parent->right);
		else
		{
			parent->right = new node;
			parent->right->key_value = key;
			parent->right->comparison = compare;
			parent->right->classification = classification;
			parent->right->type = type;
			parent->right->left = NULL;
			parent->right->right = NULL;
		}
	}
}

void decisionTree::insert(int key, string compare, string classification, NodeType type)
{
	if (root != NULL)
		insert(key, compare, classification, type, root);
	else
	{
		root = new node;
		root->key_value = key;
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
		if (key == leaf->key_value)
			return leaf;
		if (key < leaf->key_value)
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
	cout << "Key: " << root->key_value << "\tCondition: " << root->comparison
		<< "\tClass: " << root->classification << endl;
	printTree(root->left);
	printTree(root->right);
}

// prints the contents of tree from given leaf
void decisionTree::printTree(node *leaf)
{
	if (leaf != NULL)
	{
		cout << "Key: " << leaf->key_value << "\tCondition: " << leaf->comparison
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