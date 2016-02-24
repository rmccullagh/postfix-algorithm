#ifndef AST_H
#define AST_H

typedef struct ASTNode {
	char value;
	struct ASTNode *left;
	struct ASTNode *right;
} ASTNode;

ASTNode* newASTNode(char value, ASTNode* left, ASTNode *right);

#endif
