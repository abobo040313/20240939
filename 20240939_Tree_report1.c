#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void preorder(TreeNode* node) {
    if (node) {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(TreeNode* node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

void postorder(TreeNode* node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}

int getHeight(TreeNode* node) {
    if (node == NULL) return -1; // 높이는 엣지 기준일 경우 -1, 노드 기준이면 0
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(TreeNode* node) {
    if (node == NULL) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int countLeaves(TreeNode* node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}

int getSum(TreeNode* node) {
    if (node == NULL) return 0;
    return node->data + getSum(node->left) + getSum(node->right);
}

int getMax(TreeNode* node) {
    if (node == NULL) return -999999; // 매우 작은 수로 초기화
    int leftMax = getMax(node->left);
    int rightMax = getMax(node->right);
    int max = node->data;
    if (leftMax > max) max = leftMax;
    if (rightMax > max) max = rightMax;
    return max;
}

void searchRange(TreeNode* node, int min, int max) {
    if (node == NULL) return;
    if (node->data > min)
        searchRange(node->left, min, max);
    if (node->data > min && node->data < max)
        printf("%d ", node->data);
    if (node->data < max)
        searchRange(node->right, min, max);
}

void freeTree(TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
   
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    printf("전위 순회: ");
    preorder(root);
    printf("\n");

    printf("중위 순회: ");
    inorder(root);
    printf("\n");

    printf("후위 순회: ");
    postorder(root);
    printf("\n");

    printf("\n트리 높이: %d\n", getHeight(root));
    printf("전체 노드 수: %d\n", countNodes(root));
    printf("리프 노드 수: %d\n", countLeaves(root));

    printf("노드 값 총합: %d\n", getSum(root));
    printf("최댓값: %d\n", getMax(root));

    printf("\n값이 6 이상 20 이하인 노드: ");
    searchRange(root, 6, 20);
    printf("\n");

    freeTree(root);
    return 0;
}
