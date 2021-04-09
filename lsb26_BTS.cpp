#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

struct Tree {
	int info;
	Tree* left;
	Tree* right;
};

Tree* CreateTree(Tree*, int, int, int*);
Tree* AddNode(Tree*, int);
void PrintPreOrder(Tree*);
void PrintPostOrder(Tree*);
void PrintInOrder(Tree*);
void quickSort(int*, int, int);
int Closest(Tree*, double);
void deleteTree(Tree*);

int main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	int n;
	Tree* root = nullptr;
	cout << "Введите количество элементов: ";
	cin >> n;
	cout << "Введите данные: ";
	int* inf = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> inf[i];
	}
	quickSort(inf, 0, n - 1);
    double average = 0;
	for (int i = 0; i < n; i++) {
		average += inf[i];
	}
	average /= n;
	cout << "Добавляемые значения: ";
	root = CreateTree(root, 0, n - 1, inf);
	cout << "\nВывод дерева (1. прямой обход; 2. обратный обход; 3. симметричный обход):\n1. ";
	PrintPreOrder(root);
	cout << "\n2. ";
	PrintPostOrder(root);
	cout << "\n3. ";
	PrintInOrder(root);
	cout << "\nСреднее значение элементов дерева: " << average;
	cout << "\nБлижайший элемент к среднему: ";
	cout << Closest(root, average) << endl;
	deleteTree(root);
	cout << "\nДерево очищено";
	delete[] inf;
	return 0;
}

Tree* CreateTree(Tree* temp, int begin, int end, int *inf) {
	if (begin > end) return 0;
	int middle = (begin + end) / 2;
	cout << inf[middle] << " ";
	temp = AddNode(temp, inf[middle]);
	temp->left = CreateTree(temp->left, begin, middle - 1, inf); 
	temp->right = CreateTree(temp->right, middle + 1, end, inf);
	return temp;
}

Tree* CreateRoot(int info) {
	Tree* temp = new Tree;
	temp->info = info;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}

Tree* AddNode(Tree* temp, int info) {
	if (temp == nullptr) {
		return CreateRoot(info);
	}
	if (info < temp->info) {
		temp->left = AddNode(temp->left, info);
	}
	else {
		temp->right = AddNode(temp->right, info);
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

void quickSort(int* s, int left, int right) {
	if (left < right) {
		int i = left, j = right;
		int t, x;
		int mid;
		mid = s[(left + right) / 2];
		do {
			while (s[i] < mid) i++;
			while (s[j] > mid) j--;
			if (i <= j) {
				x = s[i];
				s[i] = s[j];
				s[j] = x;
				i++;
				j--;
			}
		} while (i <= j);
		if (left < j) quickSort(s, left, j);
		if (i < right) quickSort(s, i, right);
	}
}

int Closest(Tree* temp, double avg) {
	double difference, minDifference = fabs(temp->info - avg)+ 1;
	int ans = 0;
	while (temp) {
		if (temp->info == avg) return temp->info;
		if (temp->info > avg) {
			difference = fabs(temp->info - avg);
			if (minDifference > difference) {
				minDifference = difference;
				ans = temp->info;
			}
			temp = temp->left;
		}
		else if (temp->info < avg) {
			difference = fabs(temp->info - avg);
			if (minDifference > difference) {
				minDifference = difference;
				ans = temp->info;
			}
			temp = temp->right;
		}
	}
	return ans;
}

void deleteTree(Tree *temp) {
	if (temp == nullptr) return;
	deleteTree(temp->left);
	cout << "Удаление элемента " << temp->info << endl;
	deleteTree(temp->right);
	delete temp;
}
