#include <iostream>

#include "btree.cpp"


void testBuild ()
{
  BTree<int> empty;
  BTree<int> t90 (90,empty,empty),
             t12 (12,t90,empty),
             t30 (30,empty,t12),
             t50 (50,empty,empty),
             t5  (5,t50, empty),
             t7  (7,t30,t5);


  t7.insertElement ("LL",100);
  std::cout << t7;

}

void testTrace ()
{
  BTree<int> t;

  t.insertElement ("",10);
  t.insertElement ("L",20);

  std::cout << t;
}

void testBOT ()
{
  BTree<int> t;

  t.insertBOT (10);
  t.insertBOT (20);
  t.insertBOT (30);
  t.insertBOT (11);
  t.insertBOT (13);
  t.insertBOT(5);
  t.insertBOT(28);
  t.insertBOT(69);
  t.prettyPrint();
  std::cout << "\n\n";

  BTree<int> empty;
  BTree<int> left_right(9, BTree<int>(5, empty, empty), BTree<int>(7, empty, empty));
  BTree<int> left(5, BTree<int>(8, empty, empty), left_right);
  BTree<int> tree(10, left, BTree<int>(7, empty, empty));
  tree.prettyPrint();

  // std::cout << t.count(isOdd);
  std::cout << t.isBOT() << " " << tree.isBOT();
   // std::cout << t << "\n";
  // std::cout<<t.maxLeaf();
}
void testListLeaves(){
  BTree<int> t;

  t.insertBOT (10);
  t.insertBOT (20);
  t.insertBOT (30);
  t.insertBOT (11);
  t.insertBOT (13);
  t.insertBOT(5);
  t.insertBOT(28);
  t.insertBOT(69);
  std::vector<int> leaves = t.listLeaves();
  std::vector<int>::iterator it;
  for(it = leaves.begin(); it < leaves.end(); ++it){
    std::cout << *it << "\n";
  }
}

void testConvert(){
  BTree<int> t;

  t.insertBOT (10);
  t.insertBOT (20);
  t.insertBOT (30);
  t.insertBOT (11);
  t.insertBOT (13);
  t.insertBOT(5);
  t.insertBOT(28);
  t.insertBOT(69);

  t.prettyPrint();
  t.convertTree();

  std::cout << "\n\n";
  t.prettyPrint();
  std::cout<<"\n\n";

  BTree<int> empty;
  BTree<int> left_right(9, BTree<int>(5, empty, empty), BTree<int>(7, empty, empty));
  BTree<int> left(5, BTree<int>(8, empty, empty), left_right);
  BTree<int> tree(10, left, BTree<int>(7, empty, empty));
  tree.prettyPrint();
  tree.convertTree();
  std::cout<<"\n\n";
  tree.prettyPrint();
}

void testTrace1(){
  BTree<int> t;
    t.insertBOT (10);
    t.insertBOT (20);
    t.insertBOT (30);
    t.insertBOT (11);
    t.insertBOT(9);
    t.insertBOT (13);
    t.insertBOT(5);
    t.insertBOT(28);
    t.insertBOT(69);
    std::string trace = t.findTrace(0);
  //  t.findTrace
    std::cout<< trace << "\n\n";
    t.prettyPrint();
}

void testEquality(){
  BTree<int> empty;
  BTree<int> left_right(9, BTree<int>(5, empty, empty), BTree<int>(7, empty, empty));
  BTree<int> left(5, BTree<int>(8, empty, empty), left_right);
  BTree<int> tree(10, left, BTree<int>(7, empty, empty));
  tree.prettyPrint();
  std::cout<<tree.hasTwoEqualLevels() << "\n";

}

// void testTreeMaker(){
//   //int a[4][4];
//   int **a;
//   a = new int *[10];
//   BTree<int>::makeTree(nullptr, a, 10);
// }

void testIterator ()
{
  BTree<int> empty;
  BTree<int> t90 (90,empty,empty),
             t12 (12,t90,empty),
             t30 (30,empty,t12),
             t50 (50,empty,empty),
             t5  (5,t50, empty),
             t7  (7,t30,t5);

  TreeIterator<int> it = t7.beginLRightR ();

  while (it != t7.end())
  {
    std::cout << *it << " ";
    it++;
  }
}


int main ()
{
  //testConvert();
  //testBuild ();
  //testTrace();
  // testBOT();
  //testListLeaves();
  //testTrace1();
  // testEquality();
//  testTreeMaker();
  testIterator();

}
