#pragma once

#include "RedBlackTree.h"
#include <cstdint>
#include <iostream>
#include <iterator>


#define Black RedBlackTree<T>::Color::BLACK
#define Red RedBlackTree<T>::Color::RED
#define Upper_bound RedBlackTree::Type::UPPER
#define Lower_bound RedBlackTree::Type::LOWER

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::left_rotate(Node* node)
{
    Node* buff{node->right};
    node->right = buff->left;

    if (buff->left != TNULL) buff->left->parent = node;

    buff->parent = node->parent;

    if (node->parent == nullptr) root = buff;
    else if (node == node->parent->left) node->parent->left = buff;
    else node->parent->right = buff;

    buff->left = node;
    node->parent = buff;
    buff->cnt += node->cnt + 1;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::right_rotate(Node* node)
{
    Node* buff{node->left};
    node->left = buff->right;

    if (buff->right != TNULL) buff->right->parent = node;

    buff->parent = node->parent;

    if (node->parent == nullptr) root = buff;
    else if (node == node->parent->right) node->parent->right = buff;
    else node->parent->left = buff;

    buff->right = node;
    node->parent = buff;
    node->cnt -= buff->cnt + 1;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::set_color(Node* node_, Color color_)
{
    node_->color = color_;
}


template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::equel_color(Node* node_, Color color_)
{
    return (node_->color == color_);
}

template<class T, class CMP>
inline void  RedBlackTree<T, CMP>::Node::set(Node* node_)
{
    this = node_;
}

template<class T, class CMP>
void RedBlackTree<T, CMP>::balance_delete(Node* node)
{
    Node* brother;

    while (node != root && node->color == Black)
    {
        if (node == node->parent->left)
        {
            brother = node->parent->right;

            if (equel_color(brother, Red))
            {
                set_color(brother, Black);
                set_color(node->parent, Red);
                left_rotate(node->parent);

                brother = node->parent->right;
            }

            if (equel_color(brother->left, Black) && equel_color(brother->right, Black))
            {
                set_color(brother, Red);
                node = node->parent;
            }
            else
            {
                if (equel_color(brother->right, Black))
                {
                    set_color( brother->left, Black);
                    set_color(brother, Red);

                    right_rotate(brother);

                    brother = node->parent->right;
                }

                set_color(brother, node->parent->color);
                set_color(node->parent, Black);
                set_color(brother->right, Black);

                left_rotate(node->parent);

                node = root;
            }
        }
        else
        {
            brother = node->parent->left;

            if (equel_color(brother, Red)) 
            {
                set_color(brother, Black);
                set_color(node->parent, Red);

                right_rotate(node->parent);

                brother = node->parent->left;
            }

            if (equel_color(brother->left, Black) && equel_color(brother->right, Black))
            {
                set_color(brother, Red);
                node = node->parent;
            }

            else
            {
                if (equel_color(brother->left, Black))
                {
                    set_color(brother->right, Black);
                    set_color(brother, Red);

                    left_rotate(brother);
    
                    brother = node->parent->left;
                }

                set_color(brother, node->parent->color);
                set_color(node->parent, Black);
                set_color(brother->left, Black);

                right_rotate(node->parent);

                node = root;
            }
        }
    }

    set_color(node, Black);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::swap(Node* src, Node* dst)
{
    if (src->parent == nullptr) root = dst;
    else if (src == src->parent->left) src->parent->left = dst;
    else src->parent->right = dst;

    dst->parent = src->parent;
}

template<class T, class CMP>
void RedBlackTree<T, CMP>::balance_insert(Node* node)
{
    Node* uncle;

    while (equel_color(node->parent, Red))
    {
        if (node->parent == node->parent->parent->right)
        {
            uncle = node->parent->parent->left;

            if (equel_color(uncle, Red))
            {
                set_color(uncle, Black);
                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                node = node->parent->parent;
            }

            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    right_rotate(node);
                }
                
                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                left_rotate(node->parent->parent);
            }
        }
        else
        {
            uncle = node->parent->parent->right;

            if (equel_color(uncle, Red))
            {
                set_color(uncle, Black);
                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->right)
                {
                    node = node->parent;
                    left_rotate(node);
                }

                set_color(node->parent, Black);
                set_color(node->parent->parent, Red);

                right_rotate(node->parent->parent);
            }
        }

        if (node == root) break;
    }

    set_color(root, Black);
}

template<class T, class CMP>
void RedBlackTree<T, CMP>::free_node(Node* ptr)
{
    std::stack<Node*> stack_node;
    stack_node.push(root);

    while (stack_node.size())
    {
        ptr = stack_node.top();
        stack_node.pop();

        if (ptr == TNULL) continue;

        stack_node.push(ptr->left);
        stack_node.push(ptr->right);

        delete ptr;
    }
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::copy_tree(Node* dst, Node* src, Node* otherTNULL, Node* parent)
{
    std::stack<std::pair<Node*, Node*>> stack_node;
    std::stack<Node*> stack_parent;
    
    stack_node.push_back({src, dst});
    stack_parent.push_back(parent);

    while(stack_node.size())
    {
        auto [cur_node, dst_node] = stack_node.top();
        Node* cur_parent = stack_parent.top();

        stack_node.pop();
        stack_parent.pop();

        if(cur_node == otherTNULL) dst_node = otherTNULL;
        else
        {
            dst_node->data = cur_node->data;
            dst_node->color = cur_node->color;
            dst_node->cnt = cur_node->cnt;
            dst_node->parent = cur_parent;

            dst_node->right = new Node{};
            dst_node->left = new Node{};

            stack_node.push({cur_node->right, dst_node->right});
            stack_parent.push(dst_node);

            stack_node.push({cur_node->left, dst_node->left});
            stack_parent.push(dst_node);
        }
    }
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase_helper(Node* node)
{
    Node* buff_1;
    Node* buff_2 = node;

    Color y_original_color = buff_2->color;

    if (node->left == TNULL)
    {
        buff_1 = node->right;
        swap(node, node->right);
    }
    else if (node->right == TNULL)
    {
        buff_1 = node->left;
        swap(node, node->left);
    }
    else
    {
        buff_2 = node->right;

        while (buff_2->left != TNULL)
        {
            buff_2->cnt--;
            buff_2 = buff_2->left;
        }

        y_original_color = buff_2->color;
        buff_1 = buff_2->right;

        if (buff_2->parent == node) buff_1->parent = buff_2;
        else
        {
            swap(buff_2, buff_2->right);

            buff_2->right = node->right;
            buff_2->right->parent = buff_2;
        }

        swap(node, buff_2);

        buff_2->left = node->left;
        buff_2->left->parent = buff_2;

        set_color(buff_2, node->color);
        buff_2->cnt = node->cnt + 1;
    }

    delete node;

    if (y_original_color == Black) balance_delete(buff_1);
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::range_queries(const T& key1, const T& key2)
{
    if (key2 <= key1) return 0;

    Node* cur_node = root;
    int64_t num_elems = 0;

    std::stack<Node*> stack_node;
    stack_node.push(root);

    while (stack_node.size())
    {
        cur_node = stack_node.top();
        stack_node.pop();

        if (CMP{}(key1, cur_node->data) && 
            CMP{}(cur_node->data, key2)) num_elems ++;

        if (cur_node->right != TNULL) stack_node.push(cur_node->right);
        
        if (cur_node->left != TNULL) stack_node.push(cur_node->left);
    }

    return num_elems;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree::Node::Node(T data_,
                                                      Node* parent_,
                                                      Node* left_,
                                                      Node* right_, 
                                                      Color color_,
                                                      int64_t cnt_) :
    data(data_),
    parent(parent_),
    left(left_),
    right(right_),
    color(color_),
    cnt(cnt_)
{}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree::Node::Node(Node* node_) :
    data(node_->data),
    parent(node_->parent),
    left(node_->left),
    right(node_->right),
    color(node_->color),
    cnt(node_->cnt)
{}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree() :
    TNULL(new Node{T(0), nullptr, nullptr, nullptr, Black, -1 }),
    root(TNULL),
    elements(0)
{}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(const std::initializer_list<T> list) : RedBlackTree()
{
    for (auto& now : list) insert(now);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(const RedBlackTree<T, CMP>& rhs) : RedBlackTree()
{
    elements = rhs.elements;
    if (rhs.root != rhs.TNULL)
    {
        root = new Node;
        copy_tree(root, rhs.root, rhs.TNULL, nullptr);
    }
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::RedBlackTree(RedBlackTree<T, CMP>&& rhs) noexcept
{
    set(rhs.TNULL, rhs.root, rhs.elements);
    rhs.set(nullptr, nullptr, 0);
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>& RedBlackTree<T, CMP>::operator=(const RedBlackTree<T, CMP>& rhs)
{
    if (this == &rhs) return *this;
    if (root != TNULL) free_node(root);

    elements = rhs.elements;

    if (rhs.root != rhs.TNULL)
    {
        root = new Node;
        copy_tree(root, rhs.root, rhs.TNULL, nullptr);
    }
    else root = TNULL;

    return *this;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>& RedBlackTree<T, CMP>::operator=(RedBlackTree<T, CMP>&& rhs) noexcept
{
    if (this == &rhs) return *this;

    if (root != TNULL) free_node(root);

    delete TNULL;

    set(rhs.TNULL, rhs.root, rhs.elements);
    rhs.set(nullptr, nullptr, 0);

    return *this;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::insert(const T& key)
{ 
    elements++;

    Node* node = new Node{key, nullptr, TNULL, TNULL, Red, 0};

    set_color(node, Red);

    Node* parent = nullptr;
    Node* curr = root;

    while (curr != TNULL)
    {
        parent = curr;

        if (CMP{}(node->data, curr->data))
        {
            curr->cnt++;
            curr = curr->left;
        }
        else if (node->data == curr->data)
        {
            delete node;
            elements--;

            while (curr->parent != nullptr)
            {
                if (curr == curr->parent->left) curr->parent->cnt--;
                curr = curr->parent;
            }

            return;
        }
        else curr = curr->right;
    }

    node->parent = parent;
    node->cnt = node->left->cnt + 1;

    if (parent == nullptr) root = node;
    else if (CMP{}(node->data, parent->data)) parent->left = node;
    else parent->right = node;

    if (node->parent == nullptr)
    {
        set_color(node, Black);
        return;
    }

    if (node->parent->parent == nullptr) return;

    balance_insert(node);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase(const T& key)
{
	if (elements == 0) return;

	elements--;

	Node* node = root;
	Node* helper = TNULL;
	Node* buff = nullptr;

	while (node != TNULL)
    {
		buff = node;

		if (node->data == key) helper = node;

		if (CMP{}(node->data, key)) 
		{
			node = node->right;
		}
		else 
		{
			node->cnt--;
			node = node->left;
		}
	}

	if (helper == TNULL)
    {
		elements++;

		if (CMP{}(key, buff->data)) buff->cnt++;

		while (buff->parent != nullptr)
        {
			if (buff == buff->parent->left) buff->parent->cnt++;

			buff = buff->parent;
		};
    
		return;
	}

	erase_helper(helper);
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::erase(ConstIterator it)
{
    if (it.ptr == nullptr || it.ptr == TNULL) return;

    elements--;

    Node* curr = it.ptr;

    curr->cnt--;

    while (curr->parent != nullptr)
    {
        if (curr == curr->parent->left) curr->parent->cnt--;
        curr = curr->parent;
    }

    erase_helper(it.ptr);
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::size() const
{
    return elements;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::find(const T& key) const
{
    Node* node = root;
    Node* res_n = TNULL;

    while (node != TNULL)
    {
        if (node->data == key) res_n = node;

        if (CMP{}(node->data, key)) node = node->right;
        else node = node->left;
    }

    if (res_n == TNULL) return end();

    return ConstIterator{res_n, TNULL, root};
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::order_of_key(const T& key) const
{
    Node* curr = root;
    int64_t key_order = 0;

    while (curr != TNULL && curr->data != key) 
    {
        if (CMP{}(key, curr->data)) curr  = curr->left;
        else 
        {
            key_order += curr->cnt + 1;
            curr  = curr->right;
        }
    }

    if (curr  == TNULL) return elements;

    key_order += curr->cnt;

    return key_order;
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::order_of_key(const ConstIterator it) const
{
    return it.order();
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::operator==(const RedBlackTree<T, CMP>& rhs) const
{
    if (elements != rhs.elements) return false;

    auto it1 = begin(), it2 = rhs.begin();

    while (it1 != end())
    {
        if (*it1 != *it2) return true;
        it1++;
        it2++;
    }

    return true;
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::operator!=(const RedBlackTree<T, CMP>& rhs) const
{
    if (elements != rhs.elements) return true;

    auto it1 = begin(), it2 = rhs.begin();

    while (it1 != end())
    {
        if (*it1 != *it2) return true;

        it1++;
        it2++;
    }

    return false;
}

template<class T, class CMP>
inline RedBlackTree<T, CMP>::~RedBlackTree()
{
    if (root != TNULL) free_node(root);
    delete TNULL;
}
