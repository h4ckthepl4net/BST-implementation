// BST implementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "./Bst.h"
#include "./BstNode.h"
#include "./Bst.cpp"
#include "./BstNode.cpp"
#include "./HelperFunctions.h"

int main()
{
	int arr[] = { 37,-15,23,8,-42,-42,19,-3,56,0,-7 };
	Bst<int> esiminch(arr, 10);

	auto& outStream = std::cout;
	std::function<void(const BstNode<int>*)> callback = [&outStream](const BstNode<int>* node) {
		outStream << node->getValue() << ", ";
	};

	std::cout << "Inorder traversal: ";
	esiminch.traverse(callback, TraverseType::INORDER); // տպում ենք հերթականությամբ (inorder)
	outStream << std::endl;

	std::cout << "Preorder traversal: ";
	esiminch.traverse(callback, TraverseType::PREORDER); // տպում ենք preorder
	outStream << std::endl;

	std::cout << "Postorder traversal: ";
	esiminch.traverse(callback, TraverseType::POSTORDER); // տպում ենք postorder
	outStream << std::endl;

	std::cout << "Level order traversal: ";
	esiminch.traverse(callback, TraverseType::LEVELORDER); // տպում ենք levelorder
	outStream << std::endl;

	std::cout << "Adding new value: 10\n";
	esiminch.insert(10); // ավելացնում ենք նոր արժեք

	std::cout << "Inorder traversal: ";
	esiminch.traverse(callback, TraverseType::INORDER); // տպում ենք հերթականությամբ (inorder), հերթականության պահպանումը ստուգելու համար
	outStream << std::endl;

	std::cout << "Removing value: 42\n";
	esiminch.remove(-42); // hեռացնում ենք կրկնվող արժեք

	std::cout << "Inorder traversal: ";
	esiminch.traverse(callback, TraverseType::INORDER); // համոզվում ենք որ բոլոր համապատասխան հանգույցները հեռացվել են
	outStream << std::endl;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
