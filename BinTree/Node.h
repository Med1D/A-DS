//
//  Node.h
//  Searching
//
//  Created by Иван Медведев on 09/03/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#ifndef Node_h
#define Node_h


template <typename NodeType>
class TreeNode {
    friend class Tree<NodeType>;
public:
    TreeNode(const NodeType &);
    NodeType get_data();
protected:
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    NodeType data;
};

template <typename NodeType>
TreeNode<NodeType>::TreeNode(const NodeType &a) {
    data = a;
    left = right = 0;
}

template <typename NodeType>
NodeType TreeNode<NodeType>::get_data() {
    return data;
}



#endif /* Node_h */
