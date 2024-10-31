#ifndef EXTENDEDRBTNODE_H
#define EXTENDEDRBTNODE_H

#include "RBTNode.h"

class ExtendedRBTNode : public RBTNode {
private:
   int subtreeKeyCount;

public:
   ExtendedRBTNode(int nodeKey) : RBTNode(nodeKey) {
      subtreeKeyCount = 1;
   }
   
   virtual int GetSubtreeKeyCount() override {
      return subtreeKeyCount;
   }

   virtual void UpdateSubtreeKeyCount() {
       subtreeKeyCount = 1;
       if (GetLeft()) {
           subtreeKeyCount += ((ExtendedRBTNode*)GetLeft())->GetSubtreeKeyCount();
       }
       if (GetRight()) {
           subtreeKeyCount += ((ExtendedRBTNode*)GetRight())->GetSubtreeKeyCount();
       }
   }

   virtual void SetLeft(BSTNode* newLeftChild) override {
       RBTNode::SetLeft(newLeftChild);
       UpdateSubtreeKeyCount();
   }

   virtual void SetRight(BSTNode* newRightChild) override {
       RBTNode::SetRight(newRightChild);
       UpdateSubtreeKeyCount();
   }

   virtual void SetParentToNull() override {
       BSTNode::SetParentToNull();

	   UpdateSubtreeKeyCount();
   }


   virtual bool ReplaceChild(BSTNode* currentChild, BSTNode* newChild) override {
	   bool result = RBTNode::ReplaceChild(currentChild, newChild);
       if (result) {
           UpdateSubtreeKeyCount();
       }
	   return result;
   }
   
   // Your code here
};

#endif