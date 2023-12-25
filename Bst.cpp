#ifndef BST_CPP
#define BST_CPP

#include "Bst.h"

template<class T>
Bst<T>::Bst() {
	this->root = nullptr;
}

template<class T>
Bst<T>::Bst(std::vector<T> data) { // կոնստրուկտորը ստանում է զանգված
	this->root = nullptr;
	for (T& item : data) { // տարրերը հերթով ավելացնում ենք ծառին
		this->insert(item);
	}
}

template<class T>
Bst<T>::Bst(T* data, std::size_t size) { // կոնստրուկտորը ստանում է զանգված
	this->root = nullptr;
	for (std::size_t i = 0; i < size; i++) { // տարրերը հերթով ավելացնում ենք ծառին
		this->insert(data[i]);
	}
}

template<class T>
Bst<T>::Bst(Bst<T>& tree) { // պատճենման կոնստրուկտոր
	if (this->root != nullptr) { // եթե ծառը դատարկ չէ
		delete this->root; // ապա այն ջնջում ենք
	}
	tree.traverse([this](BstNode<T>& item) { // տվյալները հերթով պատճենում ենք ծառի մեջ
		this->insert(item.data);
	}, TraverseType::PREORDER);
}

template<class T>
Bst<T>::Bst(Bst<T>&& tree) noexcept { // տեխափոխման կոնստրուկտոր
	if (this->root != nullptr) { // եթե ծառը դատարկ չէ
		delete this->root; // ապա այն ջնջում ենք
	}
	this->nodeCount = tree.nodeCount; // տեղափոխում ենք տարրերի քանակը
	tree.nodeCount = 0;
	this->root = tree.root; // տեղափոխում ենք արմատը
	tree.root = nullptr;
}

template<class T>
Bst<T>::~Bst() { // դեստրուկտորով ջնջում ենք արմատի տարրը
	if (this->root != nullptr) {
		delete this->root;
	}
}

template<class T>
std::size_t Bst<T>::insert(BstNode<T>& node) {
	if (this->root == nullptr) { // եթե ծառը դատարկ է, ապա տարրը ավելացնում ենք արմատի տեղում
		this->root = &node;
		this->nodeCount++; // ավելացնում ենք տարրերի քանակը
		return 1;
	}
	BstNode<T>* temp = this->root; // սկսում ենք արմատից
	while (true) { // կրկնում ենք մինչև չգտնենք տարրի տեղը
		if (temp == &node) {
			return this->nodeCount; // եթե տարրը արդեն կա, ապա չենք ավելացնում այն
		}
		if (node.data <= temp->data) { // եթե տարրը փոքր կամ հավասար է տվյալ temp-ում գրված տվյալին
			if (temp->left == nullptr) { // և ձախ կողմում չկա տարր
				temp->left = &node; // ավելացնում ենք այն ձախ կողմում և դուրս գալիս ցիկլից
				this->nodeCount++; // ավելացնում ենք տարրերի քանակը
				break;
			}
			temp = temp->left; // հակառակ դեպքում շարունակում ենք ցիկլը դեպի ձախ ենթածառը
		}
		else if (node.data > temp->data) { // եթե տարրը մեծ է տվյալ temp-ում գրված տվյալից
			if (temp->right == nullptr) { // և աջ կողմում չկա տարր
				temp->right = &node; // ավելացնում ենք այն աջ կողմում և դուրս գալիս ցիկլից
				this->nodeCount++; // ավելացնում ենք տարրերի քանակը
				break;
			}
			temp = temp->right; // հակառակ դեպքում շարունակում ենք ցիկլը դեպի աջ ենթածառը
		}
	}
	return this->nodeCount; // վերադարձնում ենք ընդհանուր տարրերի քանակը
}

template<class T>
std::size_t Bst<T>::insert(BstNode<T>&& node) { // օգտագործում ենք վերը տրված գերբեռնված ֆունկցիան
	BstNode<T>* newNode = new BstNode<T>(node);
	return this->insert(*newNode);
}

template<class T>
std::size_t Bst<T>::insert(T& data) { // օգտագործում ենք վերը տրված գերբեռնված ֆունկցիան
	BstNode<T>* newNode = new BstNode<T>(data);
	return this->insert(*newNode);
}

template<class T>
std::size_t Bst<T>::insert(T&& data) { // օգտագործում ենք վերը տրված գերբեռնված ֆունկցիան
	BstNode<T>* newNode = new BstNode<T>(data);
	return this->insert(*newNode);
}

template<class T>
BstNode<T>* Bst<T>::getParent(BstNode<T>& node) {
	BstNode<T>* temp = this->root; // սկսում ենք արմատից
	while (temp != nullptr) { // ցիկլը կանգնում է եթե տարրը հավասար է nullptr
		if (temp->left == &node || temp->right == &node) { // եթե տվյալ հանգույցի ենթատարրերից մեկը հավասար է փնտրվող հանգույցին
			return temp; // ապա վերադարձնում ենք տվյալ տարրը
		}
		else if (node.data > temp->data) { // եթե տրված տարրի տվյալը մեծ է ներկայիս տարրի տվյալից
			temp = temp->right; // ապա շարժվում ենք դեպի աջ
		}
		else if (node.data <= temp->data) { // եթե տրված տարրի տվյալը փոքր կամ հավասար է ներկայիս տարրի տվյալից
			temp = temp->left; // ապա շարժվում ենք դեպի ձախ
		}
	}
	return nullptr;
}

template<class T>
BstNode<T>* Bst<T>::search(T data) { // ստանում ենք տվյալը որը պետք է գտնել
	BstNode<T>* temp = this->root; // սկսում ենք արմատից
	while (temp != nullptr) { // ցիկլը կանգնում է եթե տարրը հավասար է nullptr
		if (data == temp->data) { // եթե տարրը հավասար է որոշված տվյալին վերադարձնում ենք այն
			return temp;
		}
		else if (data <= temp->data) { // եթե որոնվող տվյալը փոքր կամ հավասար է տվյալ տարրի տվյալին
			temp = temp->left; // ապա շարժվում ենք դեպի ձախ
		}
		else if (data > temp->data) { // եթե որոնվող տվյալը մեծ է տվյալ տարրի տվյալից
			temp = temp->right; // ապա շարժվում ենք դեպի աջ
		}
	}
	return nullptr;
}

template<class T>
std::size_t Bst<T>::remove(BstNode<T>& node) { // ջնջում ենք տրված տարրը
	BstNode<T>* temp = &node;
	if (temp == nullptr) { // եթե տվյալ տարրը հավասար է nullptr վերադարձնում ենք տարրերի քանակը չանելով ոչինչ
		return this->nodeCount;
	}
	if (temp->left == nullptr && temp->right == nullptr) { // եթե տվյալ տարրը չունի child տարրեր
		BstNode<T>* parent = this->getParent(*temp);  // ուղղակի հեռացնում ենք ծառից
		if (parent->left == temp) { // եթե տվյալ տարրը ձախ տողի համար է
			parent->left = nullptr; // ապա այն դարձնում ենք nullptr
		}
		else if (parent->right == temp) { // եթե տվյալ տարրը աջ տողի համար է
			parent->right = nullptr; // ապա այն դարձնում ենք nullptr
		}
		delete temp;
		return --this->nodeCount; // վերադարձնում ենք տարրերի քանակը հանելով 1
	}
	else if (temp->left == nullptr || temp->right == nullptr) { // եթե տվյալ տարրը ունի միայն 1 child տարր
		BstNode<T>* temp2 = temp->left == nullptr ? temp->right : temp->left; // ստանում ենք գոյություն ունեցող child տարրը
		temp->swap(std::move(*temp2)); // տվյալ տարրի տվյալները փոխարինում ենք child տարրի տվյալներով
		// և child տարրի տվյալները անհետացնում ենք դեստրուկտորում խնդիրներից խուսափելու համար
		delete temp2; // child տարրը ջնջում ենք
		return --this->nodeCount; // վերադարձնում ենք տարրերի քանակը հանելով 1
	}
	else {
		BstNode<T>* temp2 = this->getMaximum(temp->left); // ստանում ենք ձախ ենթածառի մաքսիմումը
		temp->data = temp2->data;  // տվյալ տարրի տվյալները փոխարինում ենք ձախ ենթածառի մաքսիմումը տվյալներով
		this->remove(*temp2); // ջնջում ենք մաքսիմում տարրը ռեկուրսիվ կանչի օգնությամբ
		return --this->nodeCount; // վերադարձնում ենք տարրերի քանակը հանելով 1
		// այս կերպ մենք պահպանում ենք ծառի դասավորվածությունը,
		// քանի որ հեռացվող հանգույցից աջ մնում են նրանից մեծ տարրերը,
		// իսկ հանգույցից ձախ մնում են նրանից փոքր կամ հավասար տարրերը
	}
}

template<class T>
std::size_t Bst<T>::remove(T data) { // տարրի ջնջում ըստ տվյալի
	BstNode<T>* temp = this->search(data); // գտնում ենք առաջին տարրը որտեղ կա տրված տվյալը
	while (temp != nullptr) { // ցիկլը կատարում ենք բոլոր գտնված տարրերի համար
		// վերը նշված ֆունկցիայի ալգորիթմով հեռացնում ենք տարրերը
		if (temp->left == nullptr && temp->right == nullptr) {
			BstNode<T>* parent = this->getParent(*temp);  // ուղղակի հեռացնում ենք ծառից
			if (parent->left == temp) { // եթե տվյալ տարրը ձախ տողի համար է
				parent->left = nullptr; // ապա այն դարձնում ենք nullptr
			}
			else if (parent->right == temp) { // եթե տվյալ տարրը աջ տողի համար է
				parent->right = nullptr; // ապա այն դարձնում ենք nullptr
			}
			delete temp;
			return --this->nodeCount;
			break;
		}
		else if (temp->left == nullptr || temp->right == nullptr) {
			BstNode<T>* temp2 = temp->left == nullptr ? temp->right : temp->left;
			temp->swap(std::move(*temp2));
			delete temp2;
			--this->nodeCount;
			if (temp->right == nullptr) { // թե աջ կողմի տարրը դատարկ է, հետևաբար ձախ կողմի տարրը դատարկ չէ
				temp = this->search(data);  // և անհրաժեշտ է նորից փնտրել տարրը կրկնօրինակները գտնելու համար
			} else { // հակառակ դեպքում
				break; // դուրս ենք գալիս ցիկլից
			}
		}
		else {
			BstNode<T>* temp2 = this->getMinimum(temp->right);
			temp->data = temp2->data;
			this->remove(*temp2);
			--this->nodeCount;
			temp = this->search(data);
		}
	}
	return this->nodeCount;
}

template<class T>
std::size_t Bst<T>::remove(BstNode<T>&& node) { // օգտվում ենք վերը սահմնաված ֆունկցիայից
	return this->remove(node.data);
}

template<class T>
void Bst<T>::traverseInorder(typename Bst<T>::BstNodeCallback callback, BstNode<T>* node) { // անցում ծառի տարրերի վրայով
	if (node == nullptr) {
		return;
	}
	this->traverseInorder(callback, node->left); // ձախ ենթածառի վրայով անցում
	callback(node); // տվյալ տարրի վրայով անցում
	this->traverseInorder(callback, node->right); // աջ ենթածառի վրայով անցում
}

template<class T>
void Bst<T>::traversePreorder(typename Bst<T>::BstNodeCallback callback, BstNode<T>* node) {
	if (node == nullptr) {
		return;
	}
	callback(node); // տվյալ տարրի վրայով անցում
	this->traversePreorder(callback, node->left); // ձախ ենթածառի վրայով անցում
	this->traversePreorder(callback, node->right); // աջ ենթածառի վրայով անցում
}

template<class T>
void Bst<T>::traversePostorder(typename Bst<T>::BstNodeCallback callback, BstNode<T>* node) {
	if (node == nullptr) {
		return;
	}
	this->traversePreorder(callback, node->left); // ձախ ենթածառի վրայով անցում
	this->traversePreorder(callback, node->right); // աջ ենթածառի վրայով անցում
	callback(node); // տվյալ տարրի վրայով անցում
}

template<class T>
void Bst<T>::traverseLevelOrder(typename Bst<T>::BstNodeCallback callback, BstNode<T>* node) { // անցում ըստ մակարդակների
	if (node == nullptr) {
		return;
	}
	std::queue<BstNode<T>*> nodesQueue; // ստեղծում ենք հերթ
	callback(node); // տվյալ տարրի վրայով անցում
	nodesQueue.push(node); // ավելացնում ենք հերթին

	while (!nodesQueue.empty()) { // եթե հերթը դատարկ չէ
		BstNode<T>* current = nodesQueue.front(); // վերցնում ենք հերթի առաջին տարրը
		nodesQueue.pop(); // և այն հանում հերթից
		 
		if (current->left != nullptr) { // առաջին տարրի ձախ child-ին ավելացնում ենք հերթին
			callback(current->left); // կանչում ենք callback-ը ձախ տարրի համար
			nodesQueue.push(current->left);
		}
		if (current->right != nullptr) { // առաջին տարրի աջ child-ին ավելացնում ենք հերթին
			callback(current->right); // կանչում ենք callback-ը աջ տարրի համար
			nodesQueue.push(current->right);
		}
	}
}

template<class T>
void Bst<T>::traverse(typename Bst<T>::BstNodeCallback callback, TraverseType type, BstNode<T>* node) { // ընդհանուր ֆունկցիա անցումների համար
	if (node == nullptr) {
		node = this->root;
	}
	switch (type) { // կանչում ենք համապատասխան ֆունկցիան կախված պարամետրից
	case TraverseType::INORDER:
		return this->traverseInorder(callback, node);
	case TraverseType::PREORDER:
		return this->traversePreorder(callback, node);
	case TraverseType::POSTORDER:
		return this->traversePostorder(callback, node);
	case TraverseType::LEVELORDER:
		return this->traverseLevelOrder(callback, node);
	}
}

template<class T>
BstNode<T>* Bst<T>::getRoot() { // ստանում ենք ծառի արմատը, սկզբնակետը
	return this->root;
}

template<class T>
BstNode<T>* Bst<T>::getMinimum(BstNode<T>* findAfter) { // ստանում ենք ծառի/ենթածառի ամենափոքր տարրը
	BstNode<T>* temp = findAfter == nullptr ? this->root : findAfter;
	// եթե տրված է որևէ տարր ապա սկսում ենք նրանից 
	// հակառակ դեպքում արմատից
	while (temp->left != nullptr) { // մինչև վերջ շարժվում ենք ծախ ամենափոքր տարրը գտնելու համար
		temp = temp->left;
	}
	return temp;
}

template<class T>
BstNode<T>* Bst<T>::getMaximum(BstNode<T>* findAfter) { // ստանում ենք ծառի/ենթածառի ամենամեծ տարրը
	BstNode<T>* temp = findAfter == nullptr ? this->root : findAfter;
	// եթե տրված է որևէ տարր ապա սկսում ենք նրանից
	// հակառակ դեպքում արմատից
	while (temp->right != nullptr) { // մինչև վերջ շարժվում ենք աջ ամենամեծ տարրը գտնելու համար
		temp = temp->right;
	}
	return temp;
}

template<class T>
std::map<T, float> Bst<T>::getFrequencies(bool percentages) { // ստանում ենք բոլոր տարրերի հաճախությունները
	std::map<T, float> frequencies; // հաճախությունները պահելու համար
	this->traverse([&frequencies](const BstNode<T>* node) { // անցնում ենք բոլոր տարրերի վրա
		if (frequencies.find(node->data) == frequencies.end()) { // եթե տվյալ տարրը առաջին անգամ է հանդիպում
			frequencies[node->data] = 0; // ապա այն դարձնում ենք 0
		}
		frequencies[node->data]++; // այնուհետև տվյալ տարրի քանակը ավելացնում ենք մեկով
	});
	if (percentages) { // հաշվում ենք տարրերի հաճախությունները տոկոսային արժեքներով
		std::size_t total = this->nodeCount; // ընդհանուր քանակը
		for (auto& pair : frequencies) { // անցնում ենք բոլոր տարրերի վրա
			pair.second = (pair.second * 100) / total; // հաշվում ենք տոկոսային արժեքը
		}
	}
	return frequencies; // վերադարձնում ենք հաճախությունները
}

template <class T>
std::size_t Bst<T>::getSize() { // ստանում ենք պառի տարրերի քանակը
	return this->nodeCount;
}

#endif