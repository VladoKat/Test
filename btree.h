#ifndef __BTREE_H
#define __BTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

template <class T>
struct TreeNode
{
  TreeNode (const T& data, TreeNode<T> *_left, TreeNode<T> *_right);
  TreeNode<T> *left, *right;
  T data;

  int getId ();

private:
  static int maxid;
  int id;
};

template <class T>
struct task
{
  task(){}
  task (TreeNode<T> *_n, bool _p): node(_n), toPrintNow (_p){}
  TreeNode<T> *node;
  bool toPrintNow;
};


template <class T>
class TreeIterator
{
public:
  TreeIterator (TreeNode<T> *, void(*_winder)(std::stack<task<T> >) );

  T operator * ();
  bool operator == (const TreeIterator<T>&);
  bool operator != (const TreeIterator<T>&);
  TreeIterator<T>& operator ++ (int);


private:
  std::stack<task<T> > s;
  void* winderMethod;

};
template <class T>
void windStackLRoR (std::stack<task<T> >&);
template <class T>
void windStackRRightL(std::stack<task<T> >&);
template <class T>
void windStackLRightR(std::stack<task<T> >&);

// template <class T>
// class RRightLTreeIterator{
// public:
//   RRigthLTreeIterator(TreeNode<T> *root, void* winderMethod);
//   T operator *();
//   bool operator == (const RRightLTreeIterator<T>&);
//   bool operator != (const RRightLTreeIterator<T>&);
//   RRightLTreeIterator<T>& operator++ (int);
// private:
//   std::stack<task<T>> s;
//
//   void windStack();
// }


template <class T>
class BTree
{
public:
  BTree();
  BTree(const T, const BTree<T>&, const BTree<T>&);
  //BTree(const T);
  //TODO: ГОЛЯМА ЧЕТВОРКА

  friend std::ostream& operator << (std::ostream&,const BTree<T>&);

  bool insertElement (std::string, const T&);
  void insertBOT (const T&);
  int count();
  int count(const T&);
  int count(bool (*pred) (const T&));
  T maxLeaf();
  std::string findTrace(const T&);
  std::vector<T> listLeaves();
  void prettyPrint();
  bool hasTwoEqualLevels();
  static BTree<char> parseExpression(const std::string&);
  //bool biggerThan(const T&);
  void convertTree();
  bool isBOT();
  //static void makeTree(TreeNode<int**>*, int**, int);
  void levelsPrint(std::ostream&);

  TreeIterator<T> beginLRoR();
  TreeIterator<T> beginLRightR();
  TreeIterator<T> beginRRightL();
  TreeIterator<T> end();


private:
  TreeNode<T> *root;
  bool insertElement (std::string, const T&, TreeNode<T>*&);
  void insertBOT (const T&, TreeNode<T>*&);
  void leavesHelper(std::vector<T>&, TreeNode<T>*);
  std::string traceHelper(const T&, TreeNode<T>*);
  void printHelper(TreeNode<T>*, int);
  bool isBOTHelper(TreeNode<T>*, T, T);
  int convertHelper(TreeNode<T>*);
  //static makeTreeHelper(int[][]);
  void fillLevels(TreeNode<T>*, int, std::vector<std::vector<T> >&);
  //std::string traceHelper(const T&, TreeNode<T>*);
};

template <class T>
std::ostream& operator << (std::ostream&,const BTree<T>&);



#endif
