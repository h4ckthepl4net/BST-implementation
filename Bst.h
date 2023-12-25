#pragma once

#ifndef BST_H
#define BST_H

#include <vector>
#include <queue>
#include <map>
#include <istream>
#include <functional>
#include "./TraverseType.h"

template<class T> // կլասի նախահայտարարություն
class BstNode;

template<class T> // կաղապարով կլասի հայտարարություն, որը աշխատում է յուրաքանչյուր տիպի հետ
class Bst {
public:
	using BstNodeCallback = std::function<void (const BstNode<T>*)>; // ֆունկցիայի ցուցիչի տիպի հայտարարում, որի օգնությամբ կարելի է անցնել ծառի տարրերի վրայով
	Bst(); // լռելյայն կոնստրուկտոր
	Bst(std::vector<T>); // պարամետրիզացված կոնստրուկտորներ
	Bst(T*, std::size_t);
	Bst(Bst& other); // պատճենման կոնստրուկտոր
	Bst(Bst&& other) noexcept; // տեղափոխման կոնստրուկտոր
	~Bst(); // դեստրուկտոր

	std::size_t insert(BstNode<T>&); // տարրի ավելացում ծառին
	std::size_t insert(BstNode<T>&&);
	std::size_t insert(T&);
	std::size_t insert(T&&);

	BstNode<T>* getParent(BstNode<T>&); // ստանում ենք տարրի ծնողին

	std::size_t remove(BstNode<T>&); // տարրի ջնջում ծառից
	std::size_t remove(BstNode<T>&&);
	std::size_t remove(T);

	BstNode<T>* search(T); // տարրի որոնում ծառի մեջ

	BstNode<T>* getRoot(); // ծառի արմատի վերադարձ

	std::size_t getSize(); // ծառի տարրերի քանակը

	BstNode<T>* getMinimum(BstNode<T>* = nullptr); // ծառի ամենափոքր տարրը
	BstNode<T>* getMaximum(BstNode<T>* = nullptr); // ծառի ամենամեծ տարրը

	std::map<T, float> getFrequencies(bool percentages = false); // տարրերի հաճախականությունը

	// ծառի տարրերի վրայով անցում
	void traverse(BstNodeCallback callback, TraverseType type = TraverseType::INORDER, BstNode<T>* node = nullptr);

protected:
	std::size_t nodeCount = 0; // տարրերի քանակը
	BstNode<T>* root = nullptr; // ծառի արմատը, այն կետը որտեղից սկսում է ծառը
	// ծառի տարրերի վրայով անցումներ ըստ տարբեր հերթականությունների
	void traverseInorder(BstNodeCallback, BstNode<T>* = this->root); // ձախ ենթածառ -> տվյալ տարրը -> աջ ենթածառ
	void traversePreorder(BstNodeCallback, BstNode<T>* = this->root);  // տվյալ տարրը -> ձախ ենթածառ -> աջ ենթածառ
	void traversePostorder(BstNodeCallback, BstNode<T>* = this->root); // ձախ ենթածառ -> աջ ենթածառ -> տվյալ տարրը
	void traverseLevelOrder(BstNodeCallback, BstNode<T>* = this->root); // ըստ մակարդակների (խորության)
};

#endif
