#pragma once

#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <fstream>
#include "./BstNode.h"
#include "./BstNode.cpp"
#include "./Bst.h"
#include "./Bst.cpp"

namespace helperFunctions {
	Bst<char> binarySearchTreeFromFile(std::ifstream& stream); // բինար որոնման ծառի ստեղծում ֆայլից
	Bst<char> binarySearchTreeFromFile(std::string file); // բինար որոնման ծառի ստեղծում ֆայլից
}

#endif // !HELPERS_H
