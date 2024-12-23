// Alper Tutum 150210088

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

/////////////////// Player ///////////////////
class publisher{
public:
	string name;
	float na_sales;
	float eu_sales;
	float others_sales;
};

/////////////////// Node ///////////////////
class Node{
public:
	publisher key;
	int color; // "Red"=1 or "Black"=0
	Node *parent, *left, *right;

	Node(publisher);
	~Node();
	int get_color();
	void set_color(int);
};

/////////////////// RB-Tree ///////////////////
class RB_tree{
private:
	Node *root;

	void update_best_seller(Node *node);
	void traverse_publisher_names(Node *node, vector<string> &publisher_names);
	void preorder_print(Node *node, int depth);
	void destructor_traverse(Node *node);

public:
	publisher *best_seller[3];
	stack<string> tree_deep_stack;

	Node *get_root();

	Node *RB_insert(Node *root, Node *ptr);
	void insertValue(vector<string>);
	void RB_left_rotate(Node *);
	void RB_right_rotate(Node *);
	void RB_insert_fixup(Node *);
	void preorder();
	void find_best_seller();
	Node *search_publisher(const string publisher_name);
	vector<string> get_publishers();

	RB_tree();
	~RB_tree();
};

void print_best_sellers(int year, publisher *temp_publisher[3]){
	cout.precision(5);
	cout << "End of the " + to_string(year) + " Year" << endl;
	cout << "Best seller in North America: " + temp_publisher[0]->name + " - " << temp_publisher[0]->na_sales << " million" << endl;
	cout << "Best seller in Europe: " + temp_publisher[1]->name + " - " << temp_publisher[1]->eu_sales << " million" << endl;
	cout << "Best seller rest of the World: " + temp_publisher[2]->name + " - " << temp_publisher[2]->others_sales << " million" << endl;
}

RB_tree generate_RBT_tree_from_csv(string file_name){
	RB_tree temp_RBtree;
	ifstream file(file_name);

	if (!file.is_open())
	{
		cerr << "File could not be opened" << std::endl;
		return temp_RBtree;
	}

	string line;
	getline(file, line); // Ignore header

	if (file.eof())
	{
		cerr << "Empty csv" << endl;
		return temp_RBtree;
	}

	int decade = 1980; // Starting decade
	int year;

	auto total_insertion_duration = 0;
	while (getline(file, line))
	{
		int pos = 0;
		vector<string> input_line;

		for (size_t i = 0; i < 6; i++)
		{
			pos = line.find(',');
			input_line.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		input_line.push_back(line);

		year = stoi(input_line[2]);
		// if year exceeds the decade, print best sellers and update decade
		if (year > decade + 10)
		{
			decade += 10;

			temp_RBtree.find_best_seller();
			print_best_sellers(decade, temp_RBtree.best_seller);
		}

		auto start_insertion = chrono::high_resolution_clock::now();
		temp_RBtree.insertValue(input_line);
		auto end_insertion = chrono::high_resolution_clock::now();

		auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insertion - start_insertion);
		total_insertion_duration += duration_insertion.count();
	}

	// print best sellers after the last decade
	temp_RBtree.find_best_seller();
	print_best_sellers(year, temp_RBtree.best_seller);

	cout << "Time taken to insert all data into RBT: " << total_insertion_duration << " µs" << endl;

	file.close();
	return temp_RBtree;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char *argv[]){

	string fname = argv[1];
	RB_tree RBtree = generate_RBT_tree_from_csv(fname);

	vector<string> publisher_names = RBtree.get_publishers();
	// 50 random searches
	random_device rand_dev;
	mt19937 gen(rand_dev());
	uniform_int_distribution<> dis(0, publisher_names.size() - 1);

	auto total_search_duration = 0.0;

	for (size_t i = 0; i < 50; i++){
		int index = dis(gen);
		string publisher = publisher_names[index];

		auto start_search = chrono::high_resolution_clock::now();
		Node *found = RBtree.search_publisher(publisher);
		if (found == NULL)
		{
			cerr << "Search error" << endl;
		}
		auto end_search = chrono::high_resolution_clock::now();

		auto duration_search = chrono::duration_cast<chrono::nanoseconds>(end_search - start_search);
		total_search_duration += duration_search.count();
	}

	double avg_search_duration = total_search_duration / 50.0;
	cout << "Average time for 50 random searches : " << avg_search_duration << " ns" << endl;

	RBtree.preorder();

	return EXIT_SUCCESS;
}

/////////////////// Node ///////////////////

Node::Node(publisher key){
	this->key = key;
	this->color = 1; // "RED";
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

Node::~Node(){
	if (this->parent != NULL){
		if (parent->left == this){
			parent->left = NULL;
		} else if (parent->right == this){
			parent->right = NULL;
		}
	}

	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

int Node::get_color(){
	return this->color;
}

void Node::set_color(int c){
	this->color = c;
}

/////////////////// RB-Tree ///////////////////
Node *RB_tree::get_root(){
	return this->root;
}

Node *RB_tree::RB_insert(Node *root, Node *ptr){

	if (root == NULL){
		return ptr;
	}

	// check if publisher already exists, if so add the sales
	if (ptr->key.name == root->key.name){
		root->key.na_sales += ptr->key.na_sales;
		root->key.eu_sales += ptr->key.eu_sales;
		root->key.others_sales += ptr->key.others_sales;

		return root;
	}

	if (ptr->key.name < root->key.name){
		if (root->left == NULL){
			root->left = ptr;
			ptr->parent = root;
		}
		else{
			root->left = RB_insert(root->left, ptr);
		}
	}
	else{
		if (root->right == NULL){
			root->right = ptr;
			ptr->parent = root;
		}
		else{
			root->right = RB_insert(root->right, ptr);
		}
	}

	return root;
}

void RB_tree::insertValue(vector<string> n)
{
	if (n.size() != 7)
	{
		cerr << "Invalid vector size" << endl;
		return;
	}

	publisher new_publisher;

	new_publisher.name = n[3];
	new_publisher.na_sales = stof(n[4]);
	new_publisher.eu_sales = stof(n[5]);
	new_publisher.others_sales = stof(n[6]);

	Node *node = new Node(new_publisher);

	this->root = RB_insert(this->root, node);
	RB_insert_fixup(node);
}

void RB_tree::RB_left_rotate(Node *ptr)
{
	Node *right_child = ptr->right;
	ptr->right = right_child->left;

	if (right_child->left != NULL)
	{
		right_child->left->parent = ptr;
	}
	right_child->parent = ptr->parent;

	if (ptr->parent == NULL)
	{ // update root if necessary
		this->root = right_child;
	}
	else if (ptr == ptr->parent->left)
	{
		ptr->parent->left = right_child;
	}
	else
	{
		ptr->parent->right = right_child;
	}

	right_child->left = ptr;
	ptr->parent = right_child;
}

void RB_tree::RB_right_rotate(Node *ptr)
{
	Node *left_child = ptr->left;
	ptr->left = left_child->right;

	if (left_child->right != NULL)
	{
		left_child->right->parent = ptr;
	}
	left_child->parent = ptr->parent;

	if (ptr->parent == NULL)
	{ // update root if necessary
		this->root = left_child;
	}
	else if (ptr == ptr->parent->right)
	{
		ptr->parent->right = left_child;
	}
	else
	{
		ptr->parent->left = left_child;
	}

	left_child->right = ptr;
	ptr->parent = left_child;
}

void RB_tree::RB_insert_fixup(Node *ptr)
{
	while (ptr != root && ptr->parent != NULL && ptr->parent->get_color() == 1)
	{
		Node *grandparent = ptr->parent->parent;

		if (ptr->parent == grandparent->left)
		{ // parent is left child
			Node *uncle = grandparent->right;

			if (uncle != NULL && uncle->get_color() == 1)
			{ // uncle is red
				ptr->parent->set_color(0);
				uncle->set_color(0);
				grandparent->set_color(1);

				ptr = grandparent;
			}
			else
			{ // uncle is black
				if (ptr == ptr->parent->right)
				{ // if ptr is right child
					ptr = ptr->parent;
					RB_left_rotate(ptr);
				}
				else
				{
					ptr->parent->set_color(0);
					grandparent->set_color(1);
					RB_right_rotate(grandparent);
				}
			}
		}
		else
		{ // parent is right child
			Node *uncle = grandparent->left;

			if (uncle != NULL && uncle->get_color() == 1)
			{ // uncle is red
				ptr->parent->set_color(0);
				uncle->set_color(0);
				grandparent->set_color(1);

				ptr = grandparent;
			}
			else
			{ // uncle is black
				if (ptr == ptr->parent->left)
				{ // if ptr is left child
					ptr = ptr->parent;
					RB_right_rotate(ptr);
				}
				else
				{
					ptr->parent->set_color(0);
					grandparent->set_color(1);
					RB_left_rotate(grandparent);
				}
			}
		}
	}

	this->root->set_color(0);
}

void RB_tree::preorder(){
	preorder_print(root, 0);
}

// helper function to print nodes in preorder
void RB_tree::preorder_print(Node *node, int depth){
	if (node == NULL){
		return;
	}

	for (int i = 0; i < depth; ++i) {
    cout << "-";
  }
	
	string color;
	if (node->get_color() == 0){
		color = "(BLACK)";
	}else{
		color = "(RED)";
	}
	
	cout << color << " " << node->key.name << endl;

	preorder_print(node->left, depth+1);
	preorder_print(node->right, depth+1);
}

void RB_tree::find_best_seller(){
	if (root == NULL){
		cerr << "Tree is empty" << endl;
		return;
	}

	update_best_seller(root);
}

// helper function for finding best seller
void RB_tree::update_best_seller(Node *node)
{
	if (node == NULL){ // base case
		return;
	}

	// NA sales
	if (best_seller[0] == NULL || node->key.na_sales > best_seller[0]->na_sales){
		best_seller[0] = &node->key;
	}
	// EU sales
	if (best_seller[1] == NULL || node->key.eu_sales > best_seller[1]->eu_sales){
		best_seller[1] = &node->key;
	}
	// other sales
	if (best_seller[2] == NULL || node->key.others_sales > best_seller[2]->others_sales){
		best_seller[2] = &node->key;
	}

	update_best_seller(node->left);
	update_best_seller(node->right);
}

// search function
Node *RB_tree::search_publisher(const string publisher_name){
	Node *node = this->root;

	while (node != NULL){
		if (publisher_name == node->key.name){
			return node;
		}

		if (publisher_name < node->key.name){
			node = node->left;
		}
		else{
			node = node->right;
		}
	}

	return node;
}

// helper function to gather all publisher names in one vector
vector<string> RB_tree::get_publishers(){
	vector<string> publisher_names;
	traverse_publisher_names(root, publisher_names);

	return publisher_names;
}

void RB_tree::traverse_publisher_names(Node *node, vector<string> &publisher_names){
	if (node == NULL){
		return;
	}

	// in-order traversal so that the publishers are in sorted order
	traverse_publisher_names(node->left, publisher_names);
	publisher_names.push_back(node->key.name);
	traverse_publisher_names(node->right, publisher_names);
}

RB_tree::RB_tree(){
	this->root = NULL;
	this->best_seller[0] = NULL;
	this->best_seller[1] = NULL;
	this->best_seller[2] = NULL;
}

RB_tree::~RB_tree(){
	destructor_traverse(root);
}

// helper function for destructor
void RB_tree::destructor_traverse(Node *node){
	if (node == NULL){
		return;
	}

	// first delete children, then delete node (postorder)
	destructor_traverse(node->left);
	destructor_traverse(node->right);

	delete node;
}
