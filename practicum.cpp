#include<iostream>

template<class T>
struct Node{
  T value;
  Node* left;
  Node* right;
};

template<class T>
class Tree{
  private:
    Node<T>* root;

    bool printLeaves;

    bool _find(T value, Node<T>* root){
      Node<T>* temp = root;
      if(temp){
        if(temp->value == value){
          std::cout << value << " ";
          return true;
        } else {
          bool left = _find(value, root->left) ;
          bool right = _find(value, root->right);
          if(left){
            std::cout << temp->value  <<  " ";
          }
          if(right){
            std::cout << temp->value << " ";
          }
          return left || right;
        }
      } else {
        return false;
      }
    }


    void _add(T value, Node<T>* root){
      Node<T>* temp = root;
      if(temp){
        if(value <= temp->value){
          if(!temp->left){
            temp->left = new Node<T>();
            temp->left->value = value;
            return;
          } else {
            _add(value, temp->left);
          }
        } else {
          if(!temp->right){
            temp->right = new Node<T>();
            temp->right->value = value;
            return;
          } else {
            _add(value, temp->right);
          }
        }
      }
   }

    int heightHelper(Node<T>* root, int height){
      Node<T>* temp = root;
      if(temp){
        int left = heightHelper(temp->left, height + 1);
        int right = heightHelper(temp->right, height + 1);
        //std::cout << left > right ? temp->left->value : temp->right->value << " ";
        if(left > right){
          if(temp->left){
            std::cout << temp->left->value << " ";
          }
        } else {
          if(temp->right){
            std::cout << temp->right->value << " ";
          }
        }
      //  std::cout << left << " " << right << "\n";
        return left > right ? left : right;
      } else {
        return height;
      }
    }

    void _print(Node<T>* root){
      Node<T>* temp = root;
      if(temp){
        std::cout<<root->value << "\n";
        _print(temp->left);
        _print(temp->right);
      }
    }
  public:


    Tree():root(nullptr){}

    bool find(T value){
      _find(value, root);
    }
    void add(T _value){
      if(root){
        _add(_value, root);
      } else {
        root = new Node<T>();
        root->value = _value;
      }
   }
    void print(){
      _print(root);
    }
    int height(){
      return heightHelper(root, 0);
    }

};


int main(){
  Tree<int> myTree;
  myTree.add(4);
  myTree.add(5);
  myTree.add(3);
  myTree.add(6);
  myTree.add(7);
  myTree.add(2);
  myTree.add(1);
  myTree.add(0);
  myTree.add(10);
  myTree.add(9);
  myTree.add(8);
  myTree.add(11);
//  std::cout << myTree.find(0) << " " << myTree.find(7) << " " << myTree.find(10) << "\n";
//  myTree.find(8);
  std::cout << "\n";
//  myTree.print();

  //std::cout<<myTree.height() << std::endl;
//myTree.height();
myTree.find(0);

  return 0;
}
