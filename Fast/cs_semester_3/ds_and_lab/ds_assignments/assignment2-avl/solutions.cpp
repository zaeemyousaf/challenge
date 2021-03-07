// #include "containers.h" // linkList, BinaryTree,etc
// #include "containers.cpp"
// ====================== Q1 mirror tree
// T(n) : log2 (n+1) -1
// log(n)/log2 = O(log n)
// look workout.pdf
template <class TYPE>
BinaryTree<TYPE>* mirror_iterative(BinaryTree<TYPE>* root_ptr);

// ====================== Q2 spiral traversal
// T(n): n+n = 2*n
// O(n) = n
// look workout.pdf
template <class TYPE>
void spiral_print(BinaryTree<TYPE>* btree);
// ====================== Q3 diameterOfBinaryTree
// O(n)
template <class TYPE>
int diameterOfBinaryTree(TreeNode<TYPE> *root);

// ====================== Q4 flatten
// O(n)
template <class TYPE>
LinkList<TreeNode<TYPE>*>* flatten(BinaryTree<TYPE> *btree);
// ====================== Q5 join
//O(h1+h2)
template <class TYPE>
AVL<TYPE>* join(TreeNode<TYPE> *root1,TreeNode<TYPE> *root2);
//-------------------------- End of prototype

template <class TYPE>
BinaryTree<TYPE>* mirror_iterative(BinaryTree<TYPE>* btree){
  // visit node
  // swap their children
  // move left or right and repeat until you reach null
  if(btree != NULL){
    TreeNode<TYPE>* node_index = btree->getRoot();
    Stack<TreeNode<TYPE>*> right_childrens;
    while(true){
      if(node_index != NULL){
	swap_children(node_index);
	if(node_index->rChild != NULL){
	  right_childrens.push(node_index->rChild);
	}
	node_index = node_index->lChild;
      }
      else{
	if(right_childrens.isEmpty()) break;
	node_index = right_childrens.pop();
	swap_children(node_index);
	if(node_index->lChild != NULL){
	  right_childrens.push(node_index->lChild);
	}
	node_index = node_index->rChild;
      }
    }
  }
  return btree;
}
//------------------- part b spiral traversal
template <class TYPE>
void spiral_print(BinaryTree<TYPE>* btree){
  TreeNode<TYPE> *root_index = btree->getRoot();
  if(root_index != NULL){
    Stack<TreeNode<TYPE>*> left_to_right;
    Stack<TreeNode<TYPE>*> right_to_left;
    right_to_left.push(root_index);
    while(!left_to_right.isEmpty()\
	  || !right_to_left.isEmpty()){
      while(!left_to_right.isEmpty()){
	root_index = left_to_right.pop();
	cout << root_index->data << " ";
	if(root_index->lChild != NULL)
	  right_to_left.push(root_index->lChild);
	if(root_index->rChild != NULL)
	  right_to_left.push(root_index->rChild);
      }
      while(!right_to_left.isEmpty()){
	root_index = right_to_left.pop();
	cout << root_index->data << " ";
	if(root_index->rChild != NULL)
	  left_to_right.push(root_index->rChild);
	if(root_index->lChild != NULL)
	  left_to_right.push(root_index->lChild);
      }
    }
  }
}

//---------------------
template <class TYPE>
void insert_preorder(LinkList<TreeNode<TYPE>*>* flatten_list,
		     TreeNode<TYPE>* btree){
  if(btree == NULL){
    return;
  }
  else{
    insert_preorder(flatten_list,btree->lChild);
    flatten_list->insertAtEnd(btree);
    // cout << "inserting ..." << btree->data << endl;
    insert_preorder(flatten_list,btree->rChild);
    //cout <<  "going to traverse right " << btree << endl;
  }
}

//==================== Q4: flatten
template <class TYPE>
LinkList<TreeNode<TYPE>*>* flatten(BinaryTree<TYPE>* btree){
  LinkList<TreeNode<TYPE>*>* flatten_list =
    new LinkList<TreeNode<TYPE>*>();
  TreeNode<TYPE>* root = btree->getRoot();
  insert_preorder(flatten_list,root);
  return flatten_list;
}
//---------------------
template <class TYPE>
int diameterOfBinaryTree(BinaryTree<TYPE> *btree){
  int max=0;
  if(btree != NULL){
    // flatten list
    Node<TreeNode<TYPE>*> *all_nodes;
    all_nodes = (flatten(btree))->getHead();
    while(all_nodes != NULL){
      int lh =get_height(all_nodes->data->lChild);
      int rh = get_height(all_nodes->data->rChild);
      int sub_diameter = lh+rh; // 1: node itself
      if(sub_diameter > max){
	max = sub_diameter;
      }
      //cout << all_nodes->data->data << "->";
      all_nodes = all_nodes->next;
    }
    return max;
  }
  else{
    return 0;
  }
}

//----------------
//join two lists
template <class TYPE>
AVL<TYPE>* join(AVL<TYPE> *root1,AVL<TYPE> *root2){
  if(root1->getRoot() == NULL && root2->getRoot() == NULL){
    AVL<TYPE>* empty = new AVL<TYPE>();
    return empty;
  }
  else if(root1->getRoot() == NULL && root2->getRoot() != NULL){
    return root2;
  }
  else if(root1->getRoot() != NULL && root2->getRoot() == NULL){
    return root1;
  }
  else if(get_height(root2->lChild) <1) {
    cout << "T2 should contain at least one child\n";
  }
  int h2 = get_height(root2->getRoot());
  TreeNode<TYPE>* smallest_node_root2;
  TreeNode<TYPE>* prev_root2;
   TreeNode<TYPE>* root2_index=root2->getRoot();
  while (root2_index->lChild != NULL){
    prev_root2 = root2_index;
    root2_index = root2_index->lChild;
  }
  smallest_node_root2 = root2_index;
  if(prev_root2 != NULL){
    prev_root2->height = get_height(prev_root2->lChild)-
    get_height(prev_root2->rChild);
    prev_root2->lChild = NULL;
  }

  //cout << "hieght of h2: " << h2 << endl;
  root2->inorderPrint();
   TreeNode<TYPE>* root1_index = root1->getRoot();
   TreeNode<TYPE>* parent = root1_index;
   root1_index = root1_index->rChild;
  while(root1_index != NULL && (get_height(root1_index) > h2+1)){
    parent = root1_index;
    root1_index = root1_index->rChild;
    //cout << "height of index t1: " << get_height(root1_index) << endl;
  }
  //cout << root1_index->data << "---------\n";
  AVL<TYPE>* root3 = new AVL<TYPE>();
  root3->insert(smallest_node_root2->data);
  TreeNode<TYPE>* root3_node = root3->getRoot();
  TreeNode<TYPE>* root2_node = root2->getRoot();
  root3_node->lChild = root1_index;
  root3_node->rChild = root2_node;
  parent->rChild = NULL;
  root3_node->height = get_height(root3_node->lChild)-\
    get_height(root3_node->rChild);
  //cout << root3_node->height << endl;
  //root3->inorderPrint();
  parent->rChild = root3_node;
  parent->rChild->height = get_height(parent->rChild->lChild)-\
    get_height(parent->rChild->rChild);
  return root1;
}

