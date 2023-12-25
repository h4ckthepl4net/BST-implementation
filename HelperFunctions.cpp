#ifndef HELPERS_CPP
#define HELPERS_CPP

#include "./HelperFunctions.h"

Bst<char> helperFunctions::binarySearchTreeFromFile(std::ifstream& stream) { // բինար որոնման ծառի ստեղծում ֆայլից
	if (!stream.is_open()) throw std::invalid_argument("File is not open"); // եթե ֆայլը բաց չէ նետում ենք սխալ
	if (!stream.good()) throw std::invalid_argument("File is not good"); // եթե ֆայլի հետ խնդիր կա նետում ենք սխալ
	Bst<char> bst; // բինար որոնման ծառի ստեղծում
	char currentChar; // ընթացիկ սիմվոլ
	while (!stream.eof()) { // կարդում ենք հաջորդ սիմվոլը քանի դեռ չենք հասել վերջին
		currentChar = stream.get();
		bst.insert(currentChar); // սիմվոլը ավելացնում ենք ծառին
	}
	return bst; // վերադարձնում ենք ծառի օբյեկտը
}

Bst<char> helperFunctions::binarySearchTreeFromFile(std::string file) { // բինար որոնման ծառի ստեղծում ֆայլից
	std::ifstream stream(file, std::ios::in | std::ios::binary); // ստեղծում ենք ֆայլի օբյեկտ
	Bst<char> tmp = binarySearchTreeFromFile(stream);
	stream.close();
	return tmp; // ֆայլի օբյեկտը փոխանցում ենք գերբեռնված ֆունկցիայի համապատասխան ռեալիզացիային
}

#endif // !HELPERS_CPP