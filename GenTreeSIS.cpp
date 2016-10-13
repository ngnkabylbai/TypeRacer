/**
* Program of a geneological tree
*
* @author Nurbek Kabylbay
* @version 1.0.0
*/
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

/**
* This struct represents nodes
*/
struct Node {
public:
	/* Name of a node*/
	string name; 
	/* Name of the node's father */
	Node *father; 
	/* Vector that contains the node's children*/
	vector<Node*> children; 

	/**
	* Constructor with one param
	*
	* @param name Name of the node
	*/
	Node(string name){
		this->name = name;
	}

	/**
	* Default constructor
	*/
	Node(){

	}
};

/** 
* This struct is the geneological tree
*/
struct GenTree {
public:
	/*the global vector of fathers thoose dont have relation*/
	vector<Node*> fathers; 

	
	/**
	* Finds the node from the geneological tree
	* 
	* @param grandNode the root of the tree
	* @param parentName name of the node that needs to be found
	*
	* @return return the found node or NULL if node doesn exist
	*/
	Node *find(Node *grandNode, string parentName){
		if(grandNode->name == parentName){
			return grandNode;
		}

		if(grandNode->children.size() != 0){
			for(int i = 0; i < grandNode->children.size(); i++){
				if(grandNode->children[i]->children.size() != 0){
					find(grandNode->children[i], parentName);
				}

				if(find(grandNode->children[i], parentName) == NULL)
					continue;
				else
					return find(grandNode->children[i], parentName);
			}
		} 

		return NULL;
	}

	/**
	* Adds a node to the tree
	* 
	* @param grand root or certain node that is father of the adding node
	* @param parentName name of the node that is the father of the adding node
	* param childName name of the node that is going to be added to the tree
	*/
	void add(Node *grand,string parentName, string childName){

		Node *child = new Node(childName);

		if(grand == NULL){ // if the tree is empty
			Node *node = new Node(parentName);
			child->father = node;
			node->children.push_back(child);
			fathers.push_back(node); //adding node to the global vector of fathers
		} else {
			Node *node = find(grand, parentName);
			node->children.push_back(child);
			child->father = node;
		}
	}

	/**
	* Checks if an input father exists in the global vector of fathers(GVOF)
	*	to decide to create a new global father in the GVOF !OR!
	*		creates a relation between global fathers and deletes child
	*			from GVOF 		 
	*
	* @param parentName name of the father
	* @param childName name of the child
	*/
	void insert(string parentName, string childName){
		if(fathers.size() == 0){ // if GVOF is empty
			add(NULL, parentName, childName);
		} else {

			bool fFound = false; //checks if father exits in the GVOF
			bool cFound = false; //checks if child exits in the GVOF

			Node *fnode = new Node(); //node of the father
			Node *cnode = new Node(); //node of the child

			for(int i = 0; i < fathers.size(); i++){
				if(fFound == false)
					fnode = find(fathers[i], parentName);
				
				if(cFound == false)
					cnode = find(fathers[i], childName);

					if(fnode != NULL) // faher is found!
						fFound = true;

					if(cnode != NULL) // child is found!
						cFound = true;
				
					if(fFound == true && cFound == true) // ending the search
						break;	
			}

			if(fnode == NULL){ // if father doesn't exist
				Node *node = new Node(parentName);
				Node *childNode = new Node(childName);
				node->children.push_back(childNode);
				childNode->father = node;
				fathers.push_back(node); // creating a new GLOBAL FATHER in GVOF	
			} else {
				if(cnode == NULL){ // if there is no child with the name childName 
					Node *childNode = new Node(childName);
					childNode->father = fnode;
					fnode->children.push_back(childNode); // just add to its vector of children
				} else { // There is a global relationship
					fnode->children.push_back(cnode); // adding child to father's children
					cnode->father = fnode; 

					for(int i = 0; i < fathers.size(); i++){
						if(fathers[i] == cnode){
							fathers.erase(fathers.begin() + i); // deleting node from GVOF
						}
					}
				}
			} 
		}
	}

	/**
	* Does oredered walk from global fathers
	*/
	void ordered_walk(){
		if(fathers.size() != 0){
			for(int i = 0; i < fathers.size(); i ++){
				printf("THE GRANDFATHER IS ") ;
				ordered_walk_out(fathers[i]);
			}
		} else {
			printf("\n THE GENELOGICAL TREE IS EMPTY \n \n");
		}

	}

	/**
	* Outputs all children of the fathers
	*
	* @param root a node that has children
	*/
	void ordered_walk_out(Node *root){
		cout << root->name << " : " << endl;

		for(int i = 0; i < root->children.size(); i ++){
			if(root->children[i]->father != NULL)
			cout << "   " << root->children[i]->name << endl;
		}

		cout << endl;

		for(int i = 0; i < root->children.size(); i ++){
			if(root->children[i]->children.size() != 0){
				ordered_walk_out(root->children[i]);
			}
		}
	}

	/**
	* Identifies the relationship between two nodes
	*
	* @param grand the common ancestor
	* @param child1 name the first child
	* @param ind1 identifies which on account of the father of the child1
	* @param child2 name the first child
	* @param ind2 identifies which on account of the father of the child2
	*/
	void checkRelation(string grand, string child1, int ind1,
						string child2, int ind2){
		
		if(ind1 == ind2){
			cout << child1 <<" and " << child2 <<" are children of "
					<< grand << endl;
		} else {
			if(grand == child1){
				cout << grand << "is father of" << child2 << endl;
			} else {
				if(grand == child2){
					cout << grand << " is father of " << child1 << endl;
				} else {
					cout << "The common ancestor is "<< grand << endl;
					switch(ind1){
						case 0:
							cout << grand <<" is father of" << child1 << endl;
							break;
						case 1:
							cout << grand <<" is grandfather of " << child1 << endl;
							break;
						default:
							cout << grand <<" is great-grandfather of " << child1 << endl;
							break;
					}

					switch(ind2){
						case 0:
							cout << grand <<" is father of " << child2 << endl;
							break;
						case 1:
							cout << grand <<" is grandfather of " << child2 << endl;
							break;
						default:
							cout << grand <<" is great-grandfather of " << child2 << endl;
							break;
					}
				}
			}
		}
	}

	/**
	* Finds the common ancestor of two children
	*
	* @param child1 the first child
	* @param child2 the second child
	*
	* @return return -1 if there is no common ancestor
	*/
	int findRelation(string child1, string child2){

		cout << "Finding the relationship between " << child1 
			<<" and " << child2 << endl;

		vector<Node*> fathers1;
		vector<Node*> fathers2;

		Node *node1 = find(fathers[0], child1);
		Node *node2 = find(fathers[0], child2);

		fathers1.push_back(node1);
		fathers2.push_back(node2);

		while(node1->father != NULL){
			fathers1.push_back(node1->father);
			node1 = node1 -> father;
		}
		while(node2->father != NULL){
			fathers2.push_back(node2->father);
			node2 = node2 -> father;
		}
		
		for(int i = 0; i < fathers1.size(); i ++){
			for(int j = 0; j < fathers2.size(); j++){
				if(fathers1[i] == fathers2[j]){
					checkRelation(fathers1[i]->name, child1, i, child2, j);
					return 0;
				}
			}
		}

		return -1;
	}

	void outAllSons(string parentName){

		Node *parent = find(fathers[0], parentName);
		cout << "Sons of "<< parent->name <<" :" << endl;

		for(int i = 0; i < parent->children.size(); i ++){
			cout<<"   "<< parent->children[i]->name << endl;
		}
	}

	void outAllGrandsons(string parentName){
		
		Node *parent = find(fathers[0], parentName);
		cout << "Grandsons of " << parent->name <<" :" << endl;

		for(int i = 0; i < parent->children.size(); i ++){
			for(int j = 0; j < parent->children[i]->children.size(); j++){
				cout<<"   "<< parent->children[i]->children[j]->name << endl;
			}
		}

	}
};

int main () {

	GenTree *gt = new GenTree();
	string pName, cName, findSons, findGrandSons;
	int n;

	int curOperation;

	while(7){
		printf("[0] Father-son relation\n");
		printf("[1] Find Realationship between two persons\n");
		printf("[2] List all children of a person\n");
		printf("[3] List all grandsons of a person\n");
		printf("[4] List the Genelogical Tree\n");
		printf("[5] Clear the Genelogical Tree\n");
		printf("[6] Quit\n");
		printf("Please, enter your choice: ");
		
		cin >> curOperation;

		switch(curOperation){
			case 0:
				//freopen("InputGenTree","r",stdin);
				cin >> n;
				for(int i = 0; i < n; i++){
					cin >> pName >> cName;
					gt->insert(pName, cName);
				}
				//fclose(stdin);
				break;
			case 1:
				cin >> pName >> cName;
				gt->findRelation(pName, cName);
				break;
			case 2:
				cin >> findSons;
				gt->outAllSons(findSons);
				break;
			case 3:
				cin >> findGrandSons;
				gt->outAllGrandsons(findGrandSons);
				break;
			case 4:
				gt->ordered_walk();
				break;
			case 5:
				gt->fathers.clear();
				break;
			case 6:
				return 0;
				break;
		}
	
	}


return 0;
}
