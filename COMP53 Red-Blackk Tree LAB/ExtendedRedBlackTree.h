#ifndef EXTENDEDREDBLACKTREE_H
#define EXTENDEDREDBLACKTREE_H

#include "RedBlackTree.h"
#include "ExtendedRBTNode.h"

class ExtendedRedBlackTree : public RedBlackTree {
protected:
   // Each node in an ExtendedRedBlackTree is an ExtendedRBTNode
   virtual BSTNode* MakeNewNode(int key) override {
      return new ExtendedRBTNode(key);
   }

   virtual void InsertNode(BSTNode* node) override {
	   RedBlackTree::InsertNode(node);

       BSTNode* parent = node->GetParent();

       while (parent) {
           static_cast<ExtendedRBTNode*>(parent)->UpdateSubtreeKeyCount();
           parent = parent->GetParent();
       }
   }

   virtual bool RemoveNode(BSTNode* nodeToRemove) override {
       BSTNode* parent = nodeToRemove->GetParent();
	   bool result = RedBlackTree::RemoveNode(nodeToRemove);

       while (parent) {
           static_cast<ExtendedRBTNode*>(parent)->UpdateSubtreeKeyCount();
           parent = parent->GetParent();
       }

	   return result;
   }

   virtual BSTNode* RotateLeft(BSTNode* node) override {
       BSTNode* parent = node->GetParent();
	   BSTNode* resultnode = RedBlackTree::RotateLeft(node);

       while (parent) {
           static_cast<ExtendedRBTNode*>(parent)->UpdateSubtreeKeyCount();
           parent = parent->GetParent();
       }

	   return resultnode;
   }

   virtual BSTNode* RotateRight(BSTNode* node) override {
       BSTNode* parent = node->GetParent();
       BSTNode* resultnode = RedBlackTree::RotateRight(node);

       while (parent) {
           static_cast<ExtendedRBTNode*>(parent)->UpdateSubtreeKeyCount();
           parent = parent->GetParent();
       }

	   return resultnode;
   }

   int NthKey(BSTNode* curnode, int n) {

       if (curnode == nullptr) {
           return -1;
       }
       int leftCount = 0;

       if (curnode->GetLeft() != nullptr)
       {
           leftCount = curnode->GetLeft()->GetSubtreeKeyCount();
       }

       if (n < leftCount) {
           return NthKey(curnode->GetLeft(), n);
       }
       else if (n > leftCount) {
           return NthKey(curnode->GetRight(), n - leftCount - 1);
       }
       else {
           return curnode->GetKey();
       }
   }

public:
   virtual int GetNthKey(int n) override {
       return NthKey(root, n);
      return 0;
   }
};

#endif