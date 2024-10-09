#include <iostream>
using namespace std;

// Estrutura do nó da árvore AVL
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Função para obter a altura do nó
int height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// Função para criar um novo nó
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // Novo nó tem altura 1
    return node;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Rotação simples à direita
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Rotação
    x->right = y;
    y->left = T2;

    // Atualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna nova raiz
    return x;
}

// Rotação simples à esquerda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Rotação
    y->left = x;
    x->right = T2;

    // Atualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna nova raiz
    return y;
}

// Função para inserir um nó na árvore AVL
Node* insert(Node* node, int key) {
    // Passo 1: Inserção normal de árvore binária
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Valores duplicados não são permitidos

    // Passo 2: Atualizar a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Passo 3: Obter o fator de balanceamento do nó ancestral
    int balance = getBalance(node);

    // Se o nó estiver desbalanceado, existem 4 casos

    // Caso Esquerda-Esquerda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Direita-Direita
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Esquerda-Direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retornar o ponteiro do nó (nenhuma rotação)
    return node;
}

// Função para imprimir a árvore AVL (em ordem)
void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Árvore AVL preOrder:\n";
    preOrder(root);

    return 0;
}
