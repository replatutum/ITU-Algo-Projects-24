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
		Node *parent, *left, *right;

		Node(publisher);
		~Node();
};

/////////////////// BST-Tree ///////////////////
class BST_tree{
	private:
		Node* root;

		void update_best_seller(Node* node);
		void traverse_publisher_names(Node* node, vector<string>& publisher_names);
		void destructor_traverse(Node* node);
	public:	
    publisher* best_seller[3];
		stack<string> tree_deep_stack;

    Node* get_root();

		Node* BST_insert(Node* root, Node* ptr);
		void insertValue(vector<string>);
		void find_best_seller();
		Node* search_publisher(const string publisher_name);
		vector<string> get_publishers();

		BST_tree();
		~BST_tree();
};

void print_best_sellers(int year, publisher* temp_publisher[3]){
	cout.precision(5);
	cout<< "End of the "+to_string(year)+" Year"<<endl;
	cout<< "Best seller in North America: "+temp_publisher[0]->name+" - "<<temp_publisher[0]->na_sales<<" million"<<endl;
	cout<< "Best seller in Europe: "+temp_publisher[1]->name+" - "<<temp_publisher[1]->eu_sales<<" million"<<endl;
	cout<< "Best seller rest of the World: "+temp_publisher[2]->name+" - "<<temp_publisher[2]->others_sales<<" million"<<endl;
}

BST_tree generate_BST_tree_from_csv(string file_name){
    
	BST_tree temp_BSTtree;
	ifstream file(file_name);

  if(!file.is_open()){
    cerr << "File could not be opened" << std::endl;
		return temp_BSTtree;
  }

  string line;
  getline(file, line);     // Ignore header

	if (file.eof()) {
		cerr << "Empty csv" << endl;
		return temp_BSTtree;
  }

	int decade = 1980;			// Starting decade
	int year;

	auto total_insertion_duration = 0;
	while (getline(file, line)){
		int pos = 0;
		vector<string> input_line;

		for (size_t i = 0; i < 6; i++){
			pos = line.find(',');
			input_line.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		input_line.push_back(line);

		year = stoi(input_line[2]);
		// if year exceeds the decade, print best sellers and update decade
		if (year > decade+10){
			decade += 10;

			temp_BSTtree.find_best_seller();
			print_best_sellers(decade, temp_BSTtree.best_seller);
		}
		
		auto start_insertion = chrono::high_resolution_clock::now();
		temp_BSTtree.insertValue(input_line);
		auto end_insertion = chrono::high_resolution_clock::now();

		auto duration_insertion = chrono::duration_cast<chrono::microseconds>(end_insertion - start_insertion);
		total_insertion_duration += duration_insertion.count();
	}

	// print best sellers after the last decade
	temp_BSTtree.find_best_seller();
	print_best_sellers(year, temp_BSTtree.best_seller);

	cout << "Time taken to insert all data into BST: " << total_insertion_duration << " µs" << endl;

	file.close();
	return temp_BSTtree;
}

////////////////////////////////////////////
//----------------- MAIN -----------------//
////////////////////////////////////////////
int main(int argc, char* argv[]){
	if (argc < 2){
		cerr << "File name not given" << endl;
		return EXIT_FAILURE;
	}
	
	string fname = argv[1];	
	// string output_file = "New.csv";

	// vector<vector<string>> file_data = read_file(fname);
	// sort_csv_vector_by_publisher(file_data);
	// write_file(file_data, output_file);

	// insertion and finding best seller
	BST_tree BSTtree = generate_BST_tree_from_csv(fname);

	vector<string> publisher_names = BSTtree.get_publishers();
	// 50 random searches
	random_device rand_dev;
	mt19937 gen(rand_dev());
  uniform_int_distribution<> dis(0, publisher_names.size() - 1);
	
	auto total_search_duration = 0.0;

	for (size_t i = 0; i < 50; i++){
		int index = dis(gen);
		string publisher = publisher_names[index];

		auto start_search = chrono::high_resolution_clock::now();
		Node* found = BSTtree.search_publisher(publisher);
		if (found == NULL){
			cerr << "Search error" << endl;
		}
		auto end_search = chrono::high_resolution_clock::now();

		auto duration_search = chrono::duration_cast<chrono::nanoseconds>(end_search - start_search);
    total_search_duration += duration_search.count();
	}

	double avg_search_duration = total_search_duration/50.0;
	cout << "Average time for 50 random searches : " << avg_search_duration << " ns" << endl;

	return EXIT_SUCCESS;
}


/////////////////// Node ///////////////////

Node::Node(publisher key){
	this->key = key;
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

Node::~Node(){
	if (this->parent != NULL){
		if (parent->left == this) {
      parent->left = NULL;
    } else if (parent->right == this) {
      parent->right = NULL;
    }
	}
	
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
}

/////////////////// BST-Tree ///////////////////

Node* BST_tree::get_root(){
	return this->root;
}

Node* BST_tree::BST_insert(Node* root, Node* ptr){

  if (root == NULL){
		return ptr;
	}
	
	// check if publisher already exists, if so add the sales
	if (ptr->key.name == root->key.name){
		root->key.na_sales += ptr->key.na_sales;
		root->key.eu_sales += ptr->key.eu_sales;
		root->key.others_sales += ptr->key.others_sales;

		delete ptr;
		return root;
	}

	if (ptr->key.name < root->key.name){
		if (root->left == NULL){
			root->left = ptr;
			ptr->parent = root;
		} else{
			BST_insert(root->left, ptr);
		}
	} else{
		if (root->right == NULL){
			root->right = ptr;
			ptr->parent = root;
		} else{
			BST_insert(root->right, ptr);
		}
	}

	return root;
}

void BST_tree::insertValue(vector<string> n) {
	if (n.size() != 7) {
		cerr << "Invalid vector size" << endl;
		return;
	}

	publisher new_publisher;
	
	new_publisher.name = n[3];
	new_publisher.na_sales = stof(n[4]);
	new_publisher.eu_sales = stof(n[5]);
	new_publisher.others_sales = stof(n[6]);

	Node* node = new Node(new_publisher);

	this->root = BST_insert(this->root, node);
}

void BST_tree::find_best_seller(){
	if (root == NULL){
		cerr << "Tree is empty" << endl;
		return;
	}

	update_best_seller(root);
}

// helper function for finding best seller
void BST_tree::update_best_seller(Node* node){
	if (node == NULL){		// base case
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
Node* BST_tree::search_publisher(const string publisher_name){
	Node* node = this->root;

	while (node != NULL){
		if (publisher_name == node->key.name){
			return node;
		}
		
		if (publisher_name < node->key.name){
			node = node->left;
		} else{
			node = node->right;
		}
	}
	
	return node;
}

// helper function to gather all publisher names in one vector
vector<string> BST_tree::get_publishers(){
	vector<string> publisher_names;
	traverse_publisher_names(root, publisher_names);

	return publisher_names;
}

void BST_tree::traverse_publisher_names(Node* node, vector<string>& publisher_names){
	if (node == NULL){
		return;
	}
	
	// in-order traversal so that the publishers are in sorted order
	traverse_publisher_names(node->left, publisher_names);
	publisher_names.push_back(node->key.name);
	traverse_publisher_names(node->right, publisher_names);
}

BST_tree::BST_tree(){
	this->root = NULL;
	this->best_seller[0] = NULL;
	this->best_seller[1] = NULL;
	this->best_seller[2] = NULL;
}

BST_tree::~BST_tree(){
	destructor_traverse(root);
}

// helper function for destructor
void BST_tree::destructor_traverse(Node* node){
	if (node == NULL){
		return;
	}

	// first delete children, then delete node (postorder)
	destructor_traverse(node->left);
	destructor_traverse(node->right);

	delete node;
}

// For part F uncomment these functions above main and uncomment their calls in main
// pass the sorted csv "New.csv" into generate_BST_tree_from_csv()
// comment find_best_seller and print_best_sellers calls
// then run to observe insertion and search times
// I used the same methods in RBT solution for measurements but deleted them to keep the code short

/*
// helper function for reading the csv
vector<vector<string>> read_file(const string file_name){
	vector<vector<string>> file_data;
	ifstream file(file_name);

	if(!file.is_open()){
    cerr << "File could not be opened" << std::endl;
		return file_data;
  }

  string line;
  getline(file, line);     // Ignore header

	if (file.eof()) {
		cerr << "Empty csv" << endl;
		return file_data;
  }
	
	while (getline(file, line)){
		int pos = 0;
		vector<string> input_line;

		for (size_t i = 0; i < 6; i++){
			pos = line.find(',');
			input_line.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		input_line.push_back(line);

		file_data.push_back(input_line);
	}
	
	file.close();
	return file_data;
}

// helper function to sort csv data based on publisher
void sort_csv_vector_by_publisher(vector<vector<string>>& csv_vector){
	sort(csv_vector.begin(), csv_vector.end(), [](const vector<string>& a, const vector<string>& b) { 
    return a[3] < b[3];
	});
}

// helper function to write the sorted vector to a new file
void write_file(const vector<vector<string>>& csv_vector, const string file_name){
	ofstream file(file_name);

	if(!file.is_open()){
    cerr << "File could not be opened" << std::endl;
		return;
  }

	// write header
	file << "Name,Platform,Year_of_Release,Publisher,NA_Sales,EU_Sales,Other_Sales\n";

	for (const auto& line : csv_vector){
		for (size_t i = 0; i < 7; i++){
			file << line[i];
			if (i < 6){
				file << ",";
			}
		}
		
		file << "\n";
	}
	
	file.close();
}
*/
