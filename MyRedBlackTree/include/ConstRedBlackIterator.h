#pragma once

#include "RedBlackTree.h"

template<class T, class CMP>
inline RedBlackTree<T, CMP>::ConstRedBlackIterator::ConstRedBlackIterator(Node* ptr, Node* TNULL, Node* root) :
    TNULL_(TNULL),
	ptr_(ptr),
	root_ (root)
{}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::ConstRedBlackIterator::operator==(const ConstRedBlackIterator rhs) const
{
	return ptr_ == rhs.ptr;
}

template<class T, class CMP>
inline bool RedBlackTree<T, CMP>::ConstRedBlackIterator::operator!=(const ConstRedBlackIterator rhs) const
{
	return ptr_ != rhs.ptr_;
}

template<class T, class CMP>
inline const T& RedBlackTree<T, CMP>::ConstRedBlackIterator::operator*() const
{
	return ptr_->data;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator& RedBlackTree<T, CMP>::ConstRedBlackIterator::operator++()
{
	if (ptr_ == nullptr || ptr_ == TNULL_) return *this;
	find_next();
	return *this;
}

template<class T, class CMP>
inline const class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::ConstRedBlackIterator::operator++(int)
{
	ConstRedBlackIterator res(*this);
	find_next();
	return res;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator& RedBlackTree<T, CMP>::ConstRedBlackIterator::operator--()
{
	Node* prev_ptr = ptr_;
	if (ptr_ == nullptr)
	{
		ptr_ = root;
		find_max();
		return *this;
	}

	find_prev();
	if (!ptr_) ptr_ = prev_ptr;

	return *this;
}

template<class T, class CMP>
inline const class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::ConstRedBlackIterator::operator--(int)
{
	ConstRedBlackIterator res(*this);
	if (ptr_ == nullptr)
	{
		ptr_ = root;
		find_max();
		return res;
	}

	find_prev();
	if (!ptr_) ptr_ = res.ptr;

	return res;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_min()
{
	while (ptr_->left != TNULL_) ptr_ = ptr_->left;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_max()
{
	while (ptr_->right != TNULL) ptr_ = ptr_->right;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_next()
{
	if (ptr_ == nullptr || ptr_ == TNULL_) return;

	if (ptr_->right != TNULL_)
	{
		ptr_ = ptr_->right;
		find_min();
		return;
	}

	Node* y = ptr_->parent;
	while (y != nullptr && ptr_ == y->right)
	{
		ptr_ = y;
		y = y->parent;
	}
	ptr_ = y;
}

template<class T, class CMP>
inline void RedBlackTree<T, CMP>::ConstRedBlackIterator::find_prev()
{
	if (ptr_->left != TNULL_)
	{
		ptr_ = ptr_->left;
		find_max();
		return;
	}

	Node* y = ptr_->parent;
	while (y != nullptr && ptr_ == y->left)
	{
		ptr_ = y;
		y = y->parent;
	}
	ptr_ = y;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::end() const
{
    return ConstIterator{nullptr, TNULL, root};
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::begin() const
{
    if (root == TNULL) return end();

    ConstIterator it{root, TNULL, root};
    it.find_min();

    return it;
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::lower_bound(const T& key) const
{
    Node* curr = root;
    Node* result = nullptr;

	bool less_than_min = true;

    while (curr != TNULL)
    {
        if (CMP{}(curr->data, key)) 
		{
			curr = curr->right;
			less_than_min = false;
		}
        else
        {
			if (result == nullptr) result = curr;

            result = CMP{}(curr->data, result->data) ? curr : result;

			if (!CMP{}(key, curr->data)) less_than_min = false;

            curr = curr->left;
        }
    }

    if(result == nullptr || less_than_min) return end();

    return ConstIterator{result, TNULL, root};
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::upper_bound(const T& key) const
{
    Node* curr = root;
    Node* result = nullptr;

	bool less_than_min = true;

    while (curr != TNULL)
    {
        if (!CMP{}(key, curr->data) && key != curr->data) 
		{
			curr = curr->right;
			less_than_min = false;
		}
        else
        {
			if (result == nullptr) result = curr;

            result = !CMP{}(result->data, curr->data) ? curr : result;

			if (!CMP{}(key, curr->data)) less_than_min = false;

            curr = curr->left;
        }
    }

    if(result == nullptr || less_than_min) return end();

    return ConstIterator {result, TNULL, root};
}

template<class T, class CMP>
inline class RedBlackTree<T, CMP>::ConstRedBlackIterator RedBlackTree<T, CMP>::find_by_order(int64_t index) const
{
    if (index >= size()) return end();

    Node* curr = root;
    
    while (curr != TNULL && curr->cnt != index)
    {
        if (curr->cnt < index)
        {
            index -= curr->cnt + 1;
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }

    return ConstIterator{curr, TNULL, root};
}

template<class T, class CMP>
inline int64_t RedBlackTree<T, CMP>::ConstRedBlackIterator::order()
{
	Node* curr = ptr_;
	int64_t index = 0;

	if (!curr)
	{
		curr = root;
		while (curr != TNULL)
		{
			index += curr->cnt + 1;
			curr = curr->right;
		}
	}
	else
	{
		index = curr->cnt;
		while (curr != root)
		{
			if (curr->parent->right == curr) index += curr->parent->cnt + 1;
			curr = curr->parent;
		}
	}

	return index;
}
