#pragma once

#ifndef BST_NODE_H
#define BST_NODE_H

#include "./Bst.h"
#include "./NodeType.h"

template<class T>
class BstNode {
public:
	void swapData(BstNode<T>&); // տվյալների փոխանակում
	void swapData(BstNode<T>&&);
	void swap(BstNode<T>&); // տվյալ տարրի և այլ տարրի փոխանակում
	void swap(BstNode<T>&&);
	const BstNode<T>* get(NodeType type = NodeType::CURRENT) const; // ծառի տարրի ստացում
	const T& getValue() const; // տվյալների ստացում համապատասխան տարրից

protected:
	T data;
	BstNode<T>* left = nullptr; // ձախ ենթատարր
	BstNode<T>* right = nullptr; // աջ ենթատարր

	BstNode(T&); // պարամետրիզացված կոնստրուկտորներ
	BstNode(T&&);
	BstNode(T, BstNode<T>*, BstNode<T>*);
	BstNode(T&, BstNode<T>*, BstNode<T>*);
	BstNode(T&&, BstNode<T>*, BstNode<T>*);
	BstNode(BstNode<T>&); // պատճենման կոնստրուկտոր
	BstNode(BstNode<T>&&); // տեղափոխման կոնստրուկտոր
	~BstNode(); // դեստրուկտոր

	void set(T& data, BstNode<T>* = nullptr, BstNode<T>* = nullptr);

	template <class T>
	friend class Bst; // ընկեր կլաս

};

#endif