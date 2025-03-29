#pragma once

#include <functional>
#include <initializer_list>
#include <stack>
#include <string>
#include <iostream>

template<class T, class CMP = std::less<T>>
class RedBlackTree
{
	static_assert( !std::is_same_v<T, bool> && (std::is_integral_v<T> || std::is_same_v<T, std::string>), 
                   "Incorrect Node Type. Expected integral or string type");
private:

	enum class Color : int8_t 
	{
		BLACK = 0, 
		RED = 1
	};

	enum class Type : int8_t 
	{
		LOWER = 0, 
		UPPER = 1
	};

	struct Node
	{
		T data;
	
		Node* parent;
		Node* left;
		Node* right; 
		Color color; 
		int64_t cnt; 

		Node(T data_ = T(),
			 Node* parent_ = nullptr,
			 Node* left_ = nullptr,
			 Node* right_ = nullptr, 
			 Color color_ = 0,
			 int64_t cnt_ = 0);

		Node(Node* node_);

		void set (Node* node_);
	};

	class ConstRedBlackIterator : public std::iterator<std::bidirectional_iterator_tag, T>
	{
	private:

	    Node* TNULL_; 
		Node* ptr_;
		Node* root_;

		friend RedBlackTree;

		void find_min();
	
		void find_max();
	
		void find_next();
	
		void find_prev();
	
	public:

		ConstRedBlackIterator(Node* ptr = 0, Node* TNULL = 0, Node* root = 0);

		ConstRedBlackIterator(const std::initializer_list<T> init_list);
	
		bool operator== (const ConstRedBlackIterator rhs) const;
	
		bool operator!= (const ConstRedBlackIterator rhs) const;

		const T& operator* () const;
	
		ConstRedBlackIterator& operator++ ();
		const ConstRedBlackIterator operator++ (int);
	
		ConstRedBlackIterator& operator-- ();
		const ConstRedBlackIterator operator-- (int);
	
		int64_t order();
	};

	Node* TNULL;
	Node* root;
	int64_t elements;

	void left_rotate(Node* node_);

	void right_rotate(Node* node_);

	void balance_delete(Node* node_);

	void swap(Node* src, Node* dst);

	void balance_insert(Node* node_);

	void free_node(Node* ptr);

	void copy_tree(Node* dst, Node* src, Node* otherTNULL, Node* parent);

	void erase_helper(Node* helper);

	void set_color(Node* node_, Color color_);

	bool equel_color(Node* node_, Color color_);

	//int64_t range_queries_2_search(const T& key1);

public:

	using ConstIterator = ConstRedBlackIterator;

	RedBlackTree();

	RedBlackTree(const std::initializer_list<T> init_list);

	RedBlackTree(const RedBlackTree<T, CMP>& rhs);

	RedBlackTree(RedBlackTree<T, CMP>&& rhs) noexcept;

	RedBlackTree<T, CMP>& operator=(const RedBlackTree<T, CMP>& rhs);

	RedBlackTree<T, CMP>& operator=(RedBlackTree<T, CMP>&& rhs) noexcept;

	void insert(const T& key);

	void erase(const T& key);

	void erase(ConstIterator it);

	ConstIterator begin() const;

	ConstIterator end() const;

	int64_t size() const;

	void set(Node* TNULL, Node* root, int64_t elements);

	ConstIterator find(const T& key) const;

	ConstIterator lower_bound(const T& key) const;

	ConstIterator upper_bound(const T& key) const;

	ConstIterator find_by_order(int64_t i) const;

	int64_t order_of_key(const T& x) const;

	int64_t order_of_key(const ConstIterator key) const;

	int64_t range_queries(const T& key1, const T& key2);

	int64_t range_queries_2_search(const T& key1, const T& key2);

	int64_t range_queries_2(const T& key1, const T& key2);

	void dump2(Node* node, std::string const & rpref = "", std::string const & cpref = "", std::string const & lpref = "");

	Node* get_root(){return root;};

	bool operator==(const RedBlackTree<T, CMP>& rhs) const;

	bool operator!=(const RedBlackTree<T, CMP>& rhs) const;

	~RedBlackTree();
};

#include "RedBlackTreeImplementation.h"
#include "ConstRedBlackIterator.h"