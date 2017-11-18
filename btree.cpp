#include "btree.h"
#include <iostream>
#include <cassert>
#include <iomanip>
#include <cmath>

template <class T>
TreeNode<T>::TreeNode (const T& _data,
                       TreeNode<T> *_left,
                       TreeNode<T> *_right):data(_data),
                                            left(_left),
                                            right(_right)
{
  id = maxid;
  maxid++;
}

template <class T>
int TreeNode<T>::getId ()
{
  return id;
}

template <class T>
int TreeNode<T>::maxid = 0;


template <class T>
BTree<T>::BTree():root(NULL)
{

}

template <class T>
BTree<T>::BTree(const T data, const BTree<T> &lt, const BTree<T> &rt)
{
  //TODO: НЕ ТАКА!!!
  root = new TreeNode<T> (data,lt.root,rt.root);

}

template <class T>
void printNodesLISP (std::ostream& out, TreeNode<T> *root)
{
  if (root == NULL)
  {
    out << "()";
    return;
  }

  out << "(" << root->data << ",";
  printNodes (out, root->left);
  out << ",";
  printNodes (out, root->right);
  out << ")";
}

template <class T>
void printNodesDotty (std::ostream& out, TreeNode<T> *root)
{
  if (root == NULL)
  {
    return;
  }

  out << root->getId()
      << "[label=\""
      << root->data
      << "\"];"
      << std::endl;

  if (root->left != NULL)
  {
    out << root->getId()
        << "->"
        << root->left->getId()
        << "[color = \"red\"]"
        << ";"
        << std::endl;
  }

  if (root->right != NULL)
  {
    out << root->getId()
        << "->"
        << root->right->getId()
        << ";"
        << std::endl;
  }
  printNodesDotty (out, root->left);
  printNodesDotty (out, root->right);
}



std::ostream& operator << (std::ostream &out,const BTree<int> &t)
{
  out << "digraph G {" << std::endl;
  printNodesDotty (out, t.root);
  out << "}" << std::endl;
  return out;
}

template <class T>
bool BTree<T>::insertElement (std::string trace, const T& x, TreeNode<T> *&crr)
{
  if (trace == "" && crr == NULL)
  {
    crr = new TreeNode<T> (x,NULL,NULL);
    return true;
  }
  if (trace != "" && crr == NULL)
  {
    return false;
  }
  //=> trace != "" && current != NULL
  if (trace[0] == 'L')
  {
    trace.erase (0);
    return insertElement (trace,x,crr->left);
  }
  if (trace[0] == 'R')
  {
    trace.erase (0);
    return insertElement (trace,x,crr->right);
  }
  return false;
}


template <class T>
bool BTree<T>::insertElement (std::string trace, const T& x)
{
  return insertElement (trace, x, root);
}

template <class T>
void BTree<T>::insertBOT (const T &x, TreeNode<T> *&crr)
{
  if (crr == NULL)
  {
    crr = new TreeNode<T> (x,NULL,NULL);
    return;
  }

  if (x <= crr->data){
    insertBOT (x,crr->left);
    return;
  }

  insertBOT (x,crr->right);


}

template <class T>
void BTree<T>::insertBOT (const T& x)
{
  insertBOT (x, root);
}

template<class T>
int helpCount(TreeNode<T>* root, int counter = 0){
  if(root){
    counter += helpCount(root->left, counter) + helpCount(root->right, counter);
    counter++;
    return counter;
  }
  return 0;
}
template <class T>
int BTree<T>::count(){
  return helpCount(root);
}

template<class T>
int helpCountParam(TreeNode<T>* root, int counter, const T& value){
   if(root){
    counter += helpCountParam(root->left, counter, value) + helpCountParam(root->right, counter, value);
    if(root->data == value){
      counter++;
    }
    return counter;
  }
  return 0;
}

template<class T>
int BTree<T>::count(const T& value){
  return helpCountParam(root, 0, value);
}



template<class T>
bool isOdd(const T& value){
  return value % 2;
}

template<class T>
int helpCountFunc(TreeNode<T>* root, int counter, bool (*pred) (const T&)){
   if(root){
    counter += helpCountFunc(root->left, counter, pred) + helpCountFunc(root->right, counter, pred);
    if(pred(root->data)){
      counter++;
    }
    return counter;
  }
  return 0;
}

template<class T>
int BTree<T>::count(bool (pred) (const T&)){
  return helpCountFunc(root, 0, pred);
}

template<class T>
T leafHelper(TreeNode<T>* root, T max){
  if(root){
     if(!root->left && !root->right){
      if(root->data > max){
        max = root->data;
      }
    }
    T left = leafHelper(root->left, max);
    T right = leafHelper(root->right, max);
    if( left > right){
      return left;
    } else {
      return right;
    }

  }
  return max;

}

template<class T>
T BTree<T>::maxLeaf(){
  return leafHelper(root, 0);
}

template<class T>
void BTree<T>::leavesHelper(std::vector<T>& leaves, TreeNode<T>* root){
  if(!root){
    return;
  }
  if(root && !root->left && !root->right){
    leaves.push_back(root->data);
    return;
  }
  leavesHelper(leaves, root->left);
  leavesHelper(leaves, root->right);

}

template<class T>
std::vector<T> BTree<T>::listLeaves(){
  std::vector<T>* leaves = new std::vector<T>;
  leavesHelper(*leaves, root);
  return *leaves;
}




//TODO:: figure out how to do this !....
template<class T>
std::string BTree<T>::traceHelper (const T& el, TreeNode<T>* root){
  TreeNode<T>* curr = root;
  if(curr){
    //std::cout << curr->data;
    if(curr->data == el){
      return "";
    }
    std::string left = traceHelper(el, curr->left);
    std::string right = traceHelper(el, curr->right);

    if(left != "_" ){
      return "L" + left;
    }
    if(right != "_"){
      return "R" + right;
    }
  }
  return "_";
}

template<class T>
std::string BTree<T>::findTrace(const T& el){
  return traceHelper(el, root);
}

template<class T>
void BTree<T>::printHelper(TreeNode<T>* root, int numSpaces){
  if(root){
    //int change = numSpaces +=log2(root->data);//+=log(root->data);
    printHelper(root->left, numSpaces+1);
    std::cout << std::setw(4*numSpaces) << root->data << "\n";
    printHelper(root->right, numSpaces+1);
  }


}

template<class T>
void BTree<T>::prettyPrint(){
  printHelper(root, 0);
}

//
// static BTree<char> parseExpression(std::string& str){
//   BTree<char>* result;
//   parseHelper(str, result);
//   //if(str[0] >= '0' && str[0] <= '9')
// }
//
// void parseHelper(std::string& str, TreeNode<char>* root){
//   if(str[0] >= '0' && str[0] <= '9'){
//     if(!root){
//       root = new TreeNode<char>;
//     }
//     root->value = str[0];
//   }
// }
// template<class T>
// int BTree<T>::height(){
//   return heightHelper(root, 0);
// }
//
// template<class T>
// int BTree<T>::heightHelper(TreeNode<T>* root, int height){
//   if(root){
//     height++;
//
//   }
// }
template<class T>
void BTree<T>::fillLevels(TreeNode<T>* root, int numLevel, std::vector<std::vector<T> >& levels){
//
  //int height = height();
  if(root){
    if(numLevel >= levels.size()){
      levels.push_back(std::vector<T>());
    }
    levels[numLevel].push_back(root->data);
    //numLevel++;
    fillLevels(root->left, numLevel+1, levels);
    fillLevels(root->right, numLevel+1, levels);
  }
  return;

}

template <class T>
bool BTree<T>::hasTwoEqualLevels(){
  std::vector<std::vector<T> > levels;

  fillLevels(root, 0, levels);
  int size = levels.size();
  for (int i  = 0 ; i < size; ++i){
    for (int j = i + 1 ; j < size; ++j){
      if(levels[i] == levels[j]){
        return true;
      }
    }
  }
  return false;
}

template<class T>
bool BTree<T>::isBOTHelper(TreeNode<T>* root, T lowerRange, T upperRange){
  if(!root){
    return true;
  }
  int newLowerRange = lowerRange;
  int newUpperRange = upperRange;
  if(root->data > lowerRange){
    newLowerRange = root->data;
  }
  if(root->data < upperRange){
    newUpperRange = root->data;
  }
  return root->data >= lowerRange && root->data < upperRange
          && isBOTHelper(root->left, lowerRange, newUpperRange)
          && isBOTHelper(root->right, newLowerRange, upperRange);
}

template<class T>
bool BTree<T>::isBOT(){
  if(root)
  return isBOTHelper(root, -4000, 4000);
  return true;
}


template<class T>
int BTree<T>::convertHelper(TreeNode<T>* root){
  if(!root){
    return 0;
  }
  return root->data = convertHelper(root->left) + convertHelper(root->right) + 1;
  //return root->data + 1;
}

template<class T>
void BTree<T>::convertTree(){
  if(root){
    root->data = convertHelper(root);
  }
}


//TODO: figure out a way to make this work.. currently doesn't!
//template<class T>
// void BTree<T>::makeTree(TreeNode<int**>* root, int **matrix, int x, int y){
//   root = new TreeNode<int**>(matrix, nullptr, nullptr);
//   std::vector<int> leftContainer;
//   std::vector<int> rightContainer;
//   int **leftArr;
//   for(int i = 0; i < x; ++i){
//     for(int j = 0; j < y; ++j){
//       //**(root->data + i*x +j) = **(matrix + i*x + j);
//       if(**(matrix + i*y + j) < **matrix){
//         leftContainer.push_back(**(matrix + i*y + j));
//       } else {
//         rightContainer.push_back(**(matrix + i*y + j));
//       }
//     }
//   }
//   int leftSize = leftContainer.size();
//   if(leftContainer.size() >= 4){
//     int** leftMatrix = new int*[gdthfyjgukhilj]
//     makeTree(root->left, new )
//   }
// }

//from kalin!**********************************************
//TreeIterator
template <class T>
TreeIterator<T>::TreeIterator (TreeNode<T> *root, void(* _winder) (std::stack<task<T> >&))
{
    winderMethod = _winder;
    if (root != nullptr)
    {
      s.push (task<T> (root,false));
      winderMethod(s); //!!!
    }
}

// void windStackLRoR ();
//static void windStackRRightL();
//static void windStackLRightR();
template <class T>
void windStackLRoR (std::stack<task<T> >& s)
{
  //!!! s.top().toPrintNow == false
  while (!s.empty() && s.top().toPrintNow == false)
  {

    task<T> currentTask = s.top(); s.pop();

    if (currentTask.node->right != nullptr)
      s.push (task<T> (currentTask.node->right,false));

    s.push (task<T> (currentTask.node,true));

    if (currentTask.node->left != nullptr)
      s.push (task<T> (currentTask.node->left,false));

  }
}
template <class T>
void windStackLRightR (std::stack<task<T> >& s)
{
  //!!! s.top().toPrintNow == false
  while (!s.empty() && s.top().toPrintNow == false)
  {

    task<T> currentTask = s.top(); s.pop();

    s.push (task<T> (currentTask.node,true));

    if (currentTask.node->right != nullptr)
      s.push (task<T> (currentTask.node->right,false));

    if (currentTask.node->left != nullptr)
      s.push (task<T> (currentTask.node->left,false));

  }
}


template <class T>
void windStackRRightL (std::stack<task<T> >& s)
{
  //!!! s.top().toPrintNow == false
  while (!s.empty() && s.top().toPrintNow == false)
  {


    task<T> currentTask = s.top(); s.pop();

    s.push (task<T> (currentTask.node,true));

    if (currentTask.node->left != nullptr)
      s.push (task<T> (currentTask.node->left,false));

    if (currentTask.node->right != nullptr)
      s.push (task<T> (currentTask.node->right,false));


  }
}

template <class T>
T TreeIterator<T>::operator * ()
{
  assert (!s.empty());

  task<T> topTask = s.top();
  return topTask.node->data;
}

template <class T>
bool TreeIterator<T>::operator != (const TreeIterator<T> &other)
{
  return !(*this == other);
}


template <class T>
bool TreeIterator<T>::operator== (const TreeIterator<T> &other)
{
  //!!***!!!***!!
  //s == other.s следва от това нещо:

    return (s.empty() && other.s.empty()) ||
            (!s.empty () && !other.s.empty() &&
               (s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));

}

template <class T>
TreeIterator<T>& TreeIterator<T>::operator ++ (int)
{
  assert (!s.empty());
  s.pop();
  winderMethod(); //!!!

  return *this;
}



template <class T>
TreeIterator<T> BTree<T>::beginLRoR()
{

  return TreeIterator<T> (root, windStackLRoR);
}

template <class T>
TreeIterator<T> BTree<T>::beginLRightR()
{
  return TreeIterator<T> (root, windStackLRightR);
}

template <class T>
TreeIterator<T> BTree<T>::beginRRightL()
{
  return TreeIterator<T> (root, windStackRRightL);
}
template <class T>
TreeIterator<T> BTree<T>::end()
{
  return TreeIterator<T> (nullptr);
}

//not from iterator
template <class T>
void BTree<T>::levelsPrint (std::ostream &out)
{
  std::queue<TreeNode<T>*> q;

  if (root == nullptr)
    return;

  q.push (root);
  q.push (nullptr);

  while (q.size() > 1)
  {
    TreeNode<T>* currentNode = q.front();
    q.pop();

    if (currentNode != nullptr)
    {
      out << currentNode->data << " ";

      if (currentNode->left != nullptr)
        q.push (currentNode->left);
      if (currentNode->right != nullptr)
        q.push (currentNode->right);
    }else{
      out << std::endl;
      q.push (nullptr);
    }
  }
}

//RRightLTreeIterator

// template <class T>
// void RRightLTreeIterator<T>::windStack ()
// {
//   //!!! s.top().toPrintNow == false
//   while (!s.empty() && s.top().toPrintNow == false)
//   {
//
//     task<T> currentTask = s.top(); s.pop();
//
//     if (currentTask.node->left != nullptr)
//       s.push (task<T> (currentTask.node->left,false));
//
//     if (currentTask.node->right != nullptr)
//       s.push (task<T> (currentTask.node->right,false));
//
//     s.push (task<T> (currentTask.node,true));
//
//   }
// }

/*
template <class T>
RRigthLTreeIterator<T>::RRightLTreeIterator(TreeNode<T> *root){
  if (root != nullptr)
  {
    s.push (task<T> (root,false));
    windStack(); //!!!
  }
}

template <class T>
T RRightLTreeIterator<T>::operator *(){
  assert (!s.empty());

  task<T> topTask = s.top();
  return topTask.node->data;
}

template <class T>
bool RRightLTreeIterator<T>::= (const RRightLTreeIterator<T>& other) {
  return (s.empty() && other.s.empty()) ||
          (!s.empty () && !other.s.empty() &&
             (s.top().node == other.s.top().node) && (s.top().toPrintNow == other.s.top().toPrintNow));
}

template <class T>
bool RRightLTreeIterator<T>::operator != (const RRightLTreeIterator<T>& other){
  return !operator==(other);
}

template<class T>
RRightLTreeIterator<T>& RRightLTreeIterator<T>::operator++ (int _){
  assert (!s.empty());
  s.pop();
  windStack(); //!!!

  return *this;
}
*/
