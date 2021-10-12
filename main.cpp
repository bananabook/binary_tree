// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// This is an imprementation of a binary tree.
//  You create a variable of type bin_tree and then you can access any element
//  by providing the address of the element to the get() member function. The
//  address is provided as an int array and an int indicating the size of the
//  int array.
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#include<iostream>
#include<string>

class bin_tree{
	// split is a subclass of bin_tree and models the point where two branches
	// split from a node. A split has a right and a left branch and a value of
	// type int. The constructor initializes the member values to default values.
	class split{
		public:
		split* left;
		split* right;
		int value;
		split(){
			value=0;
			left=nullptr;
			right=nullptr;
		}
		~split(){
			if (left!=nullptr)
				delete left;
			if (right!=nullptr)
				delete right;
		}
		// the get function returns the adress to the element described by the
		// adress i describes the adress and size indicates the length of the
		// adress
		int* get(int* i, int size){
			// size==0 means, that whe have reached the end of the adress. We only
			// return the value's adress of the current node.
			if (size==0){
				return &value;
			// an address entry of 0 indicates we take a turn to the left
			}else if (i[0]==0){
				// if the tree at this point does not have a branch to the described
				// side we create a split. This way the tree grows the same way we
				// acess an element
				if (left==nullptr)
					left=new split;
				return left->get(&i[1], size-1);
			// if the address entry is anything else but 0 we take a right turn. The
			// same happens as in the left case
			}else{
				if (right==nullptr)
					right=new split;
				return right->get(&i[1], size-1);
			}
		}
		// print gives an ascii representation of the current state of the binary
		// tree. Because we run the function recursively, we take as an input a
		// string which creates the beginning of a new line.
		void print(std::string buffer){
			// first we print out the value of the current node
			if (buffer.size()==1) std::cout<<"└";
			std::cout<<value<<std::endl;;
			// if both pointers are nullptr we have reached the bottom of the tree at
			// this point and we do nothing
			if (not (left==nullptr && right==nullptr)){
				// before we print out values we need to print out the buffer so our
				// output lines up correctly, then we append the branching point, so we
				// can append the possible output of out lower level output.
				std::cout<<buffer;
				std::cout<<"├";
				if (left!=nullptr){
					// we now call the print function of our lower level node. To have
					// the output line up the way we want, we append the appropriate
					// character "│"
					buffer.append("│");
					left->print(buffer);
					// we want to use "buffer.pop_back();" but because the character "│"
					// causes problems in this approach we instead use this workaround.
					// All we do in the end is remove the last character which in this
					// case is always "│"
					buffer=buffer.substr(0,buffer.size()-3);
				}else{
					// if "left" is a nullptr we give that out.
					std::cout<<"nullptr"<<std::endl;;
				}
				// we now do the same for "right", we have curve (└) instead of a
				// branching symbol (├) and we append a space instead of a "│". Because
				// we appended a space we can call the usual pop_back function to
				// remove it.
				std::cout<<buffer;
				std::cout<<"└";
				if (right!=nullptr){
					buffer.append(" ");
					right->print(buffer);
					buffer.pop_back();
				}else{
					std::cout<<"nullptr"<<std::endl;;
				}
			}
		}
	};
	public:
	// the print function of the bin_tree serves as an entry point to the
	// recursive print function of the lover level splits.
	void print(){
		//std::cout<<"┌root"<<std::endl;
		root.print("");
		std::cout<<std::endl;
	}
	// bin_tree contains a split, which is the root of the entire tree.
	split root;
	// similar to print the get function of bin_tree serves as an entry point for
	// the recursive get function of the lover level splits.
	int* get(int* i, int size){
		return root.get(i, size);
	}
};

// this example main shows how the bin_tree class can be used
int main(){
	// first we create an instance of out class
	bin_tree tree;
	
	// We now create two addresses to access in the later part of the main. These are lists of integers, where 0 indicates a left turn and 1 indicates a right turn in out binary tree.
	int address_a[6]{0, 0, 0, 1, 0, 0};
	int address_b[3]{0, 1, 1};

	// We can now access the entries, that correspond to the before defined addresses.
	*tree.get(&address_a[0], 6)=1;
	*tree.get(&address_b[0], 3)=2;

	// With the print function we can show the final state of the binary tree in
	// an ascii representation.
	tree.print();

	return 0;
}
