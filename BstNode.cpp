#ifndef BST_NODE_CPP
#define BST_NODE_CPP

#include "./BstNode.h"

template<class T> // պարամետրիզացված կոնստրուկտորներ
BstNode<T>::BstNode(T& data) {
	// ինիցիալիզացնում ենք տվյալ տարրի մեջ գտնվող տվյալը
	// ճյուղերը դնում ենք nullptr տվյալների բացակայության համար
	this->set(data, nullptr, nullptr);
}

template<class T> // պարամետրիզացված կոնստրուկտորներ
BstNode<T>::BstNode(T&& data) {
	// ինիցիալիզացնում ենք տվյալ տարրի մեջ գտնվող տվյալը
	// ճյուղերը դնում ենք nullptr տվյալների բացակայության համար
	this->set(data, nullptr, nullptr);
}

template<class T> // պարամետրիզացված կոնստրուկտորներ
BstNode<T>::BstNode(T data, BstNode<T>* left, BstNode<T>* right) {
	// ինիցիալիզացնում ենք տվյալ տարրի մեջ գտնվող տվյալը
	// ճյուղերը դնում ենք այս կոնստրուկտորին տրված աջ և ձախ ենթատարրերը
	this->set(data, left, right);
}

template<class T> // պարամետրիզացված կոնստրուկտորներ
BstNode<T>::BstNode(T& data, BstNode<T>* left, BstNode<T>* right) {
	this->set(data, left, right);
}

template<class T> // պարամետրիզացված կոնստրուկտորներ
BstNode<T>::BstNode(T&& data, BstNode<T>* left, BstNode<T>* right) {
	this->set(data, left, right);
}

template<class T> // պատճենման կոնստրուկտոր
BstNode<T>::BstNode(BstNode<T>& node) {
	BstNode<T>* left = nullptr;
	BstNode<T>* right = nullptr;
	// եթե ձախ ենթատարրը գոյություն ունի
	if (node.left != nullptr) {
		// պատճենում ենք ձախ ենթատարրը
		left = new BstNode<T>(*(node.left));
	}
	// եթե աջ ենթատարրը գոյություն ունի
	if (node.right != nullptr) {
		// պատճենում ենք աջ ենթատարրը
		right = new BstNode<T>(*(node.right));
	}
	// վերագրում ենք տվյալները
	this->set(node.data, left, right);
}

template<class T> // տեղափոխման կոնստրուկտոր
BstNode<T>::BstNode(BstNode<T>&& node) {
	this->swap(node);
}

template<class T> // դեստրուկտոր
BstNode<T>::~BstNode() {
	// ջնջում ենք ձախ և աջ տարրերը եթե նրանք կան
	if (this->left != nullptr) {
		delete this->left;
	}
	if (this->right != nullptr) {
		delete this->right;
	}
}

template<class T> // ֆունկցիա տարրի տվյալների վերագրման համար
void BstNode<T>::set(T& data, BstNode<T>* left, BstNode<T>* right) {
	this->data = data; // վերագրում ենք տվյալ տարրի մեջ գտնվող տվյալը
	this->left = left; // և աջ և ձախ ենթատարրերը
	this->right = right;
}

template<class T> // ֆունկցիա մի տարրի տվյալը մյուսի հետ փոխանակելու համար
void BstNode<T>::swapData(BstNode<T>& node) { // ստանում ենք lvalue reference որպես պարամետր
	// տվյալը պահում ենք ժամանակավոր փոփոխականում
	T temp = this->data;
	// փոխում ենք ներկայիս օբյեկտի տվյալը
	this->set(node.data, this->left, this->right);
	// փոխում ենք որպես պարամետր փոխանցված օբյեկտի տվյալը
	node.set(temp, node.left, node.right);
}

template<class T> // ֆունկցիա մի տարրի տվյալը մյուսի հետ փոխանակելու համար
void BstNode<T>::swapData(BstNode<T>&& node) { // ստանում ենք rvalue reference որպես պարամետր
	// վերագրում ենք ներկայիս օբյեկտի տվյալները
	this->set(node.data, this->left, this->right);
	// փոխանակումը կարելի է չանել, քանի որ օբյեկտը շուտով ջնջվելու է
	// չեզոքացնում ենք այլ տարրի տվյալները տրված ժամանակավոր օբյեկտից
	// դեստրուկտորի ճիշտ աշխատանքի համար
	node.set(node.data, nullptr, nullptr);
}

template<class T> // ֆունկցիա տարրերի փոխանակման համաև
void BstNode<T>::swap(BstNode<T>& node) { // ստանում ենք lvalue reference որպես պարամետր
	// ժամանակավոր փոփոխականների մեջ պահում ենք տվյալները
	T tempData = node.data;
	BstNode<T>* tempLeft = node.left;
	BstNode<T>* tempRight = node.right;
	// փոխում ենք որպես պարամետր փոխանցված օբյեկտի տվյալները
	node.set(this->data, this->left, this->right);
	// փոխում ենք ներկայիս օբյեկտի տվյալները
	this->set(tempData, tempLeft, tempRight);
}

template<class T> // ֆունկցիա տարրերի փոխանակման համաև
void BstNode<T>::swap(BstNode<T>&& node) { // ստանում ենք rvalue reference որպես պարամետր
	// տեղափոխում ենք տվյալները
	this->set(node.data, node.left, node.right);
	// չեզոքացնում ենք այլ տարրի տվյալները տրված ժամանակավոր օբյեկտից
	// դեստրուկտորի ճիշտ աշխատանքի համար
	node.set(node.data, nullptr, nullptr);
}

template<class T> // ֆունկցիա տարրի ցուցիչը ստանալու համար
const BstNode<T>* BstNode<T>::get(NodeType type) const {
	switch (type) {
	case NodeType::LEFT:
		return this->left;
	case NodeType::RIGHT:
		return this->right;
	case NodeType::CURRENT:
	default:
		return this;
	}
}

template<class T> // ֆունկցիա տարրի տվյալը ստանալու համար
const T& BstNode<T>::getValue() const {
	return this->data;
}

#endif