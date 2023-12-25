#pragma once

#ifndef TRAVERSE_TYPE_H
#define TRAVERSE_TYPE_H

enum class TraverseType { // Սահմանվում է տիպ ծառի տարրերով անցնելու հերթականության որոշման համար
	INORDER, // ձախ ենթածառ -> տվյալ տարրը -> աջ ենթածառ
	PREORDER, // տվյալ տարրը -> ձախ ենթածառ -> աջ ենթածառ
	POSTORDER, // ձախ ենթածառ -> աջ ենթածառ -> տվյալ տարրը
	LEVELORDER, // ըստ մակարդակների (խորության)
};

#endif