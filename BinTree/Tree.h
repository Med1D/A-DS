//
//  Tree.h
//  Searching
//
//  Created by Иван Медведев on 09/03/2019.
//  Copyright © 2019 Medvedev. All rights reserved.
//

#ifndef Tree_h
#define Tree_h

template <typename NodeType> class Tree;
#include "Node.h"
#include <stack>

template <typename NodeType>
class Tree {
public:
    Tree();
    int insert_node(const NodeType &);
    TreeNode<NodeType>* delete_node(TreeNode<NodeType>*);
    void inorder_walk(TreeNode<NodeType>*);
    void preorder_walk(TreeNode<NodeType>* n);
    void preorder_iter(TreeNode<NodeType>* n);
    
    TreeNode<NodeType>* find_node(TreeNode<NodeType>*, const NodeType &);
    TreeNode<NodeType> *get_root();
private:
    TreeNode<NodeType> *root;
};


template<typename NodeType>
Tree<NodeType>::Tree() {
    root=0;
}

template<typename NodeType>
int Tree<NodeType>::insert_node(const NodeType &x) { // Вставить узел в дерево
    TreeNode<NodeType> *node = new TreeNode<NodeType>(x);
    TreeNode<NodeType> *ptr;
    TreeNode<NodeType> *ptr1;
    
    node->parent=node->left=node->right=0;
    ptr = root;
    while(ptr!=0) {
        ptr1=ptr;
        
        if(x < ptr->get_data()) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }
    
    node->parent = ptr1;
    if(ptr1==0) {
        root = node;
    }
    else {
        if(x< ptr1->get_data()) {
            ptr1->left = node;
        }
        else {
            ptr1->right = node;
        }
    }
    return 0;
    
}

template<class NodeType>
TreeNode<NodeType>* Tree<NodeType>::delete_node(TreeNode<NodeType> *z) // Удалить узел дерева
{
    TreeNode<NodeType>* y;
    TreeNode<NodeType>* x;
    if(z->left == 0 || z->right == 0)               /* в этой и следующих двух строках ищем вершину y, которую мы потом вырежем из дерева. Это либо z, либо следующий за z */
        y=z;
    else
        y=find_succsessor(z->get_data());
    if(y->left!=0)                                  /* x - указатель на существующего ребенка y или 0 если таковых нет */
        x=y->left;
    else
        x=y->right;
    if(x!=0)                                        /* эта и следующие 9 строк - вырезание y */
        x->parent=y->parent;
    if(y->parent == 0)
        root=x;
    else
    {
        if (y== (y->parent)->left)
            (y->parent)->left=x;
        else
            (y->parent)->right=x;
    }
    if(y!=z)                                        /* если мы вырезали вершин, отличную от z, то ее данные перемещаем в z */
        z->data=y->get_data();
    return y;
}

template<class NodeType>
TreeNode<NodeType>* Tree<NodeType>::find_node(TreeNode<NodeType>* n,
                                              const NodeType & val) // Найти узел в дереве
{
    if(n==0 || val==n->get_data())
        return n;
    if(val > n->get_data() )
        return find_node(n->right,val);
    else
        return find_node(n->left,val);
}

template<class NodeType>
void Tree<NodeType>::inorder_walk(TreeNode<NodeType>* n)// Симметричный обход
{
    if(n!=0)
    {
        inorder_walk(n->left);
        std::cout<<n->get_data()<<std::endl;
        inorder_walk(n->right);
    }
}

template<typename NodeType>
void Tree<NodeType>::preorder_walk(TreeNode<NodeType>* n)// Функция рекурсивного прямого обхода дерева
{
    if(n!=0)
    {
        std::cout << n->get_data() << std::endl;
        preorder_walk(n->left);
        preorder_walk(n->right);
    }
}

template<typename NodeType>
void Tree<NodeType>::preorder_iter(TreeNode<NodeType>* n) { // Функция итеративного прямого обхода дерева
    std::stack<TreeNode<NodeType>> *ps = new std::stack<TreeNode<NodeType>>();//Создание STL стека
    while (ps->size() != 0 || n != NULL) {
        if (n != NULL) {
            printf("visited %d\n", n->get_data());
            if (n->right) {
                ps->push(*(n->right));
            }
            n = n->left;
        } else {
            n = &ps->top();
            ps->pop();
        }
    }
    free(ps);
}





template<class NODETYPE>
TreeNode<NODETYPE>* Tree<NODETYPE>::get_root() // Метод получения корня дерева
{
    return root;
}

#endif /* Tree_h */
