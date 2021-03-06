// =========================================================
//HW#: HW4 BST
//Your name: Raul Perez
//Complier:  g++
//File type: cpp
//================================================================

using namespace std;

#include <iostream>
#include "binstree.h"

// constructor  initializes Root
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;
}


// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{
  if (V != NULL)
    {
      dtraverse(V->Left);         // visit left sub tree of V
      dtraverse(V->Right);       //  visit right sub tree of V
      delete V;                  //  deletes V
    }
}


// PURPOSE: Show elements in IN order traversal from the Root
void BST::ShowInOrder()
{
  cout << "Elements IN order: " << endl;
  INorderTraversal(Root);  // start in-order traversal from the root
}

// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
      // ** traverse left sub-tree of V recursively
      // ** display V's element and do endl;
      // ** traverse right sub-tree of V recursively
      INorderTraversal(V->Left);
      cout << V->Elem << " " << endl;
      
      INorderTraversal(V->Right);
    }
}

// PURPOSE:  Show elements in PRE order traversal from the Root
// This is the same as Depth First Traversal
void BST::ShowPreOrder()
{
  cout << "Elements PRE order:" << endl;
  PREorderTraversal(Root);  // start pre-order traversal from the root
}

// PURPOSE: Does PRE order traversal from V recursively
// PARAM: V is the pointer to the vertex to be visited now
void BST::PREorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
      // ** display V's element and do endl;
      // ** traverse left sub-tree of V recursively
      // ** traverse right sub-tree of V recursively
      cout << V->Elem << " " << endl;
      PREorderTraversal(V->Left);
      
      PREorderTraversal(V->Right);
      //cout << V->Elem << " " << endl;
    }
}

// PURPOSE: Adds a vertex to the binary search tree for a new element
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively) to demonstrate
// the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::Insertvertex(elem_t E)
{
  // Set up a new vertex first
  Vertex *N;         // N will point to the new vertex to be inserted
  N = new Vertex;    // a new vertex is created
  N->Left  = NULL;   // make sure it does not
  N->Right = NULL;   // point to anything
  N->Elem  = E;      // put element E in it
  
  //cout << "Trying to insert " << E << endl;
  
  if (Root == NULL)  // Special case: we have a brand new empty tree
    {
      Root = N;      // the new vertex is added as the root
      cout << "Added " << E << " as the root" << endl;
    }
  
  else  // the tree is not empty
    {
      Vertex *V;       // V will point to the current vertex
      Vertex *Parent;  // Parent will point to V's parent
      
      V = Root;        // start with the root as V
      
      while (V != NULL)  // go down the tree until you cannot go any further
	{
	  if (N->Elem == V->Elem) // the element already exists
	    {	 cout << "Error: the element already exists" << endl;
	      return;
	    }
	  
	  else if (N->Elem < V->Elem)  // what I have is smaller than V
	    {
	      //cout << "...going to the left" << endl;
	      // ** change Parent to be V to go down
	      // ** change V to be V's Left
	      Parent = V;
	      V = V->Left;
	    }
	  
	  else // what I have is bigger than V
	    {
	      //cout << "...going to the right" << endl;
	      // ** change Parent to be V to go down
	      // ** change V to be V's Right
	      Parent = V;
	      V = V->Right;
	    }
	  
	}//end of while
      
      // reached NULL -- Must add N as the Parent's child
      
      if (N->Elem < Parent->Elem)
	{
	  // ** Parent's Left should point to the same place as N
	  cout << "Added " << E << " as the left child of " << Parent->Elem << endl;
	  Parent->Left = N;
	  N->Left = V;
	}
      else
	{
	  // ** Parent's Right should point to the same place as N
	  cout << "Added " << E << " as the right child of " << Parent->Elem << endl;
	  Parent->Right = N;
	  N->Right = V;
	}
      
    }// end of normal case
}// end of InsertVertex


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove
void BST::DeleteVertex(elem_t E)
{
  cout << "Trying to delete " << E << endl;
  
  Vertex *V = Root;        // the current vertex, starting at Root
  Vertex *Parent = NULL;  // its parent
  
  // if the element that is to be deleted is the root, and isn't pointing to anything
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL))
    {
      cout << "deleting the lonely root" << endl;
      delete Root;
      Root = NULL;
      return;
    }
  
  
  // if what you want to delete is the root with one child, and it's the right one
  else if ((E == Root->Elem) && ((Root->Left == NULL) && (Root->Right != NULL)))
    {
      cout << "Deleting Root " << V->Elem << endl;
      //change the root to the leftchild and return
      Root = Root->Right;
      
      //deletes the previous root to avoid leaks
      delete V;
      return;
      
    }
  
  // if what you want to delete is the root with one child, and it's the left one
  else if((E == Root->Elem) && ((Root->Left != NULL) && (Root->Right == NULL)))
    {
      cout << "Deleting Root " << V->Elem << endl;
      //change the root to the child and return
      Root = Root->Left;
      
      //deletes the previous root to avoid leaks
      delete V;
      return;
    }
  
  //if want to delete the Root, but is has 2 children
  else if((E == Root->Elem) && (Root->Left != NULL) && (Root->Right != NULL))
    {
      cout << "Deleting Root with 2 children " << V->Elem << endl;
      //parent becomes the Root to bookmark
      Parent = Root;
      
      //move over one to the right
      V = V->Right;
      
      //goes to the leftmost node
      while(V->Left != NULL)
	{
	  V = V->Left;
	}
      
      //makes the left child of the Root the child of the leftmost node to the right of Root
      V->Left = Root->Left;
      
      //makes the root equal to the new V
      Root = V;
      
      //deletes the parent that is holding the previous root to avoid leaks
      delete Parent;
      
      return;
    }
  
  
  
  // Otherwise deleting something else
  
  
  while (V != NULL)
    {
      if ( E == V->Elem)   // found it
        {
	  cout << "Removing " << V->Elem << endl;
	  
	  remove(V, Parent);
	  // ** call remove here to remove V
	  return;
        }
      
      else if (E < V->Elem)
        {
	  //cout << "...going to the left" << endl;
	  //parent becomes the Node
	  Parent = V;
	  //V moves to the left
	  V = V->Left;
        }
      
      else
        {
	  //cout << "...going to the right" << endl;
	  
	  //parent becomes the Node
	  Parent = V;
	  //V moves to the left
	  V = V->Right;
        }
      
    }// end of while
  
  
  // reached NULL  -- did not find it
  cout << "Did not find " << E << " in the tree." << endl;
  
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  //if V is a leaf (case 1)
  if ((V->Left == NULL) && (V->Right == NULL))
    {
      cout << "removing a leaf" << endl;
      
      //if V is a left child of P
      if (P->Left == V)
        {
	  //removes V from parent
	  P->Left = NULL;
	  //deletes V
	  delete V;
	  return;
        }
      
      else // V is a right child of the Parent
        {
	  //removes V from parent
	  P->Right = NULL;
	  //deletes V
	  delete V;
	  return;
        }
      
    }
  
  // if V has just the left child (case 2)
  else if ((V->Left != NULL) && (V->Right == NULL))
    {
      cout << "removing a vertex with just the left child" << endl;
      
      if (P->Left == V)
	{
	  //replaces P's right with V's right
	  P->Left = V->Left;
	  delete V;
	  return;
        }
      
      //if its the parent's right node
      else
	{
	  //replaces P's right with V's right
	  P->Right = V->Left;
	  delete V;
	  return;
        }
    }
  
  
  
  //if V has just the right child
  else if ((V->Left == NULL) && (V->Right != NULL))
    {
      cout << "removing a vertex with just the right child" << endl;
      //Make Parent left or right point to the right child and delete V
      
      if (P->Left == V)
        {
	  //replaces P's right with V's right
	  P->Left = V->Right;
	  delete V;
	  return;
        }
      
      //if its the parent's right node
      else
        {
	  //replaces P's right with V's right
	  P->Right = V->Right;
	  delete V;
	  return;
        }
    }
  
  else // V has two children (case 3)
    {
      //extra pointer in case the tree is really big
      Vertex *E;
      
      cout << "removing an internal vertex with children" << endl;
      
      //if the left node is to be deleted
      if (P->Left == V)
	{
	  //if there is a node to the left of V's right side
	  //imagine as is there was a huge tree to the right of V, this will make sure it gets transplanted
	  
	  //extra node is placed at the right of node that is to be deleted
	  E = V->Right;
	  
	  //goes to the leftmost node of the deleted node
	  while (E->Left != NULL)
	    {
	      E = E->Left;
	    }
	  
	  //makes the left child of the deleted node the child of the leftmost node to the right of Root
	  E->Left = V->Left;
	  
	  //moves V->left it V's spot
	  P->Left = V->Right;
	  //deletes V
	  delete V;
	  return;
        }
      
      
      //is the right node is to be deleted (P->Right == V)
      else
        {
	  //if there is a node to the Right of V's left side
	  //imagine as is there was a huge tree to the left of V, this will make sure it gets transplanted
	  
	  //extra node is placed at the Left of node that is to be deleted
	  E = V->Left;
	  
	  //goes to the Rightmost node of the deleted node
	  while (E->Right != NULL)
	    {
	      E = E->Right;
	    }
	  
	  //makes the Right child of the deleted node the child of the Rightmost node to the right of Root
	  E->Right = V->Right;
	  
	  //moves V->Right it V's spot
	  P->Right = V->Left;
	  //deletes V
	  delete V;
	  return;
        }
      
      
      
    }//end of V with two children
  
}// end of remove


// PURPOSE: Finds the Maximum element in the left sub-tree of V
elem_t BST::findMax(Vertex *V)
{
  //*I* Never actually use this function, but it should work, so hopefully it will be useful for something
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  
  //RUNS the right child of V is still available
  while (V->Right != NULL)
    {
      // ** update Parent and V to go to the right
      Parent = V;
      V = V->Right;
    }
  
  // reached NULL Right  -- V now has the MAX element
  elem_t X = V->Elem;
  cout << ".....Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex
  return X;             // return the MAX element
  
}// end of FindMax
