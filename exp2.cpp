#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
	char data;
	struct Node *left;
	struct Node *right;
} Node;

static const char *position;
static int parse_error;

static Node *make_node(char value, Node *left, Node *right) {
	Node *node = (Node *)malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	node->data = value;
	node->left = left;
	node->right = right;
	return node;
}

static void skip_spaces(void) {
	while (isspace((unsigned char)*position)) ++position;
}

static Node *parse_assignment(void);

static Node *parse_primary(void) {
	skip_spaces();
	if (*position == '(') {
		++position;
		Node *node = parse_assignment();
		skip_spaces();
		if (*position != ')') parse_error = 1;
		else ++position;
		return node;
	}
	if (isalnum((unsigned char)*position))
		return make_node(*position++, NULL, NULL);
	parse_error = 1;
	return NULL;
}

static Node *parse_product(void) {
	Node *left = parse_primary();
	while (!parse_error) {
		skip_spaces();
		if (*position != '*' && *position != '/') break;
		char op = *position++;
		Node *right = parse_primary();
		left = make_node(op, left, right);
	}
	return left;
}

static Node *parse_sum(void) {
	Node *left = parse_product();
	while (!parse_error) {
		skip_spaces();
		if (*position != '+' && *position != '-') break;
		char op = *position++;
		Node *right = parse_product();
		left = make_node(op, left, right);
	}
	return left;
}

static Node *parse_assignment(void) {
	Node *left = parse_sum();
	skip_spaces();
	if (!parse_error && *position == '=') {
		++position;
		Node *right = parse_assignment();
		left = make_node('=', left, right);
	}
	return left;
}

static void inorder(const Node *root) {
	if (root == NULL) return;
	if (root->left != NULL || root->right != NULL) putchar('(');
	inorder(root->left);
	putchar(root->data);
	inorder(root->right);
	if (root->left != NULL || root->right != NULL) putchar(')');
}

static void preorder(const Node *root) {
	if (root == NULL) return;
	putchar(root->data);
	preorder(root->left);
	preorder(root->right);
}

static void postorder(const Node *root) {
	if (root == NULL) return;
	postorder(root->left);
	postorder(root->right);
	putchar(root->data);
}

static void free_tree(Node *root) {
	if (root == NULL) return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

int main(void) {
	char expression[256];
	printf("Enter an expression (example: a=b+c): ");
	if (fgets(expression, sizeof(expression), stdin) == NULL) return 1;

	position = expression;
	parse_error = 0;
	Node *root = parse_assignment();
	skip_spaces();
	if (parse_error || root == NULL || (*position != '\0' && *position != '\n')) {
		printf("Invalid expression. Use single-character operands and +, -, *, /, =, or parentheses.\n");
		free_tree(root);
		return 1;
	}

	printf("Inorder:   ");
	inorder(root);
	printf("\nPreorder:  ");
	preorder(root);
	printf("\nPostorder: ");
	postorder(root);
	putchar('\n');

	free_tree(root);
	return 0;
}
