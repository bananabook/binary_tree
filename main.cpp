#include<iostream>
#include<string>

class bin_tree{
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
		int* get(int* i, int size){
			if (size==0){
				return &value;
			}else if (i[0]==0){
				if (left==nullptr)
					left=new split;
				return left->get(&i[1], size-1);
			}else{
				if (right==nullptr)
					right=new split;
				return right->get(&i[1], size-1);
			}
		}
		void newline(std::string input){
			std::cout<<input;
		}
		void print(std::string buffer){
			//std::cout<<"printcalled"<<std::endl;
			if (buffer.size()==1) std::cout<<"└";
			std::cout<<value<<std::endl;;
			/**/
			if (not (left==nullptr && right==nullptr)){
				//newline(level);
				std::cout<<buffer;
				std::cout<<"├";
				if (left!=nullptr){
					buffer.append("│");
					left->print(buffer);
					buffer.pop_back();
				}else{
					std::cout<<"nullptr"<<std::endl;;
				}
				newline(buffer);
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
	void print(){
		std::cout<<"┌root"<<std::endl;
		root.print(" ");
		std::cout<<std::endl;
	}
	split root;
	int* get(int* i, int size){
		return root.get(i, size);
	}
};

int main(){
	bin_tree tree;
	int address_a[3]{0, 0, 0};
	int address_b[3]{0, 1, 1};

	*tree.get(&address_a[0], 3)=1;
	*tree.get(&address_b[0], 3)=2;
	//std::cout<<*tree.get(&address_a[0], 3)<<std::endl;
	//std::cout<<*tree.get(&address_b[0], 3)<<std::endl;
	//std::cout<<*tree.get(&address_c[0], 3)<<std::endl;

	tree.print();

	return 0;
}
