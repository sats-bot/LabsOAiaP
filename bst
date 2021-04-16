#include <iostream>
#include <cstdio>

using namespace std;

struct Tree {
    int info;
    int height;
    Tree* left;
    Tree* right;
};

Tree* createRoot(int);
Tree* addNode(Tree*, int);
Tree* createTree(Tree*, int);
void PrintPreOrder(Tree*);
void PrintPostOrder(Tree*);
void PrintInOrder(Tree*);
Tree* balanceTree(Tree**);
unsigned char height(Tree*);
int bfactor(Tree*);
void fixheight(Tree*);
Tree* rotateright(Tree*);
Tree* rotateleft(Tree*);
Tree* balance(Tree*);
Tree* insert(Tree*, int);
Tree* findmin(Tree*);
void deleteTree(Tree*);
void printTree(Tree*, int);
Tree* removemin(Tree*);
Tree* remove(Tree*, int);
Tree* median(Tree*, int);

int main()
{
    setlocale(LC_ALL, "ru");
    Tree* root = nullptr;
    cout << "Введите количество элементов: ";
    int n;
    cin >> n;
    cout << "\nВведите элементы дерева: " << endl;
    int* mas = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> mas[i];
        root = addNode(root, mas[i]);
    }
  //  balance(root);
    cout << "Вывод дерева (1. прямой обход; 2. обратный обход; 3. симметричный обход):\n1. ";
    PrintPreOrder(root);
    cout << "\n2. ";
    PrintPostOrder(root);
    cout << "\n3. ";
    PrintInOrder(root);
    root = balance(median(root, n/2));
    cout << "\nВывод дерева (1. прямой обход; 2. обратный обход; 3. симметричный обход):\n1. ";
    PrintPreOrder(root);
    cout << "\n2. ";
    PrintPostOrder(root);
    cout << "\n3. ";
    PrintInOrder(root);
    cout << endl;
    return 0;
}

Tree* createRoot(int info) {
    Tree* root = new Tree;
    root->info = info;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

Tree* addNode(Tree* temp, int info) {
    if (temp == nullptr) {
        return createRoot(info);
    }
    if (info < temp->info) {
        temp->left = addNode(temp->left, info);
    }
    else {
        temp->right = addNode(temp->right, info);
    }
    return temp;
}

void PrintPreOrder(Tree* temp) {
    if (temp != nullptr) {
        cout << temp->info << " ";
        PrintPreOrder(temp->left);
        PrintPreOrder(temp->right);
    }
}

void PrintPostOrder(Tree* temp) {
    if (temp != nullptr) {
        PrintPostOrder(temp->left);
        PrintPostOrder(temp->right);
        cout << temp->info << " ";
    }
}

void PrintInOrder(Tree* temp) {
    if (temp != nullptr) {
        PrintInOrder(temp->left);
        cout << temp->info << " ";
        PrintInOrder(temp->right);
    }
}

void deleteTree(Tree* temp) {
    if (temp == nullptr) return;
    deleteTree(temp->left);
    cout << "Удаление элемента " << temp->info << endl;
    deleteTree(temp->right);
    delete temp;
}

void printTree(Tree* p, int level)
{
    if (p)
    {
        printTree(p->left, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->info << endl;
        printTree(p->right, level + 1);
    }
}

unsigned char height(Tree* p)
{
    return p ? p->height : 0;
}

int bfactor(Tree* p)
{
    return height(p->right) - height(p->left);
}

void fixheight(Tree* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

Tree* rotateright(Tree* p) // правый поворот вокруг p
{
    Tree* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Tree* rotateleft(Tree* q) // левый поворот вокруг q
{
    Tree* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

Tree* median(Tree* temp, int n) {
    int i = 0;
    while (i < n) {
        median(temp->left, n);
        i++;
        median(temp->right, n);
    }
    return temp;
}

Tree* balance(Tree* p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

Tree* insert(Tree* p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) {
        Tree* temp = new Tree;
        temp->info = k;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
    }
    if (k < p->info)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
    return balance(p);
}

Tree* findmin(Tree* p) // поиск узла с минимальным ключом в дереве p 
{
    return p->left ? findmin(p->left) : p;
}

Tree* removemin(Tree* p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

Tree* remove(Tree* p, int k) // удаление ключа k из дерева p
{
    if (!p) return 0;
    if (k < p->info)
        p->left = remove(p->left, k);
    else if (k > p->info)
        p->right = remove(p->right, k);
    else //  k == p->key 
    {
        Tree* q = p->left;
        Tree* r = p->right;
        delete p;
        if (!r) return q;
        Tree* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}
