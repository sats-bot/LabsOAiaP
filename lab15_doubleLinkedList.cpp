#include <iostream>
#include <cstdio>

using namespace std;

struct dl_List { //  структура doubleLinkedList хранит информационную часть и указатели на след и пред элемент
    char info;
    dl_List* right;
    dl_List* left;
};

void NewList(dl_List**, dl_List**); // создание новой очереди
void PushBefore(dl_List*, char); // добавление перед заданным элементом
void PushAfter(dl_List*, char); // добавление после заданного элемента
void PrintList(dl_List*, dl_List*); // печать списка
char ReadElement(dl_List*); // чтение элемента
char DeleteElment(dl_List*); // удаление элемента
void SplitIntoTwo(dl_List*, dl_List*, dl_List**, dl_List**, dl_List**, dl_List**); // разделить список на два по условию
void delAllList(dl_List **, dl_List **); // удаление всего списка

int main()
{
    setlocale(LC_ALL, "ru");
    dl_List* qLeft, * qRight;
    NewList(&qLeft, &qRight);
    int n;
    char inf;
    cout << "Введите количество элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> inf;
        PushBefore(qRight, inf);
    }
    PrintList(qLeft, qRight);
    dl_List* qLL, * qLR, * qRL, * qRR;
    SplitIntoTwo(qLeft, qRight,&qLL, &qLR, &qRL, &qRR);
    cout << "Список 1:\n";
    PrintList(qLL, qRL);
    cout << "Список 2:\n";
    PrintList(qLR, qRR);
    delAllList(&qLL, &qRL);
    delAllList(&qLR, &qRR);
    return 0;
}

void NewList(dl_List** tempLeft, dl_List** tempRight) {
    *tempLeft = new dl_List;
    *tempRight = new dl_List;
    (*tempLeft)->left = NULL;
    (*tempLeft)->right = *tempRight;
    (*tempRight)->left = *tempLeft;
    (*tempRight)->right = NULL;
}

void PushBefore(dl_List* tempRight, char info) {
    dl_List* temp = new dl_List;
    temp->info = info;
    temp->right = tempRight;
    temp->left = tempRight->left;
    tempRight->left = temp;
    temp->left->right = temp;
}

void PrintList(dl_List* tempLeft, dl_List* tempRight) {
    dl_List* temp = tempLeft->right;
    while (temp != tempRight) {
        cout << temp->info << " ";
        temp = temp->right;
    }
    cout << endl;
}

char ReadElement(dl_List* temp) {
    char info = temp->info;
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    delete temp;
    return info;
}

void SplitIntoTwo(dl_List* tempLeft, dl_List* tempRight, dl_List** tempLeftL, dl_List** tempLeftR, dl_List** tempRightL, dl_List** tempRightR) {
    NewList(tempLeftL, tempRightL);
    NewList(tempLeftR, tempRightR);
    dl_List* temp = tempLeft->right;
    while (temp != tempRight) {
        if ((temp->info >= 'A' && temp->info <= 'Z') || (temp->info >= 'a' && temp->info <= 'z')) {
            cout << "Элемент " << temp ->info << " перенесен в 1 список" << endl;
            PushBefore(*tempRightL, ReadElement(temp));
            temp = tempLeft->right;
        }
        else if (temp != tempRight) {
            cout << "Элемент " << temp ->info << " перенесен во 2 список" << endl;
            PushBefore(*tempRightR, ReadElement(temp));
            temp = tempLeft->right;
        }
    }
    delete tempLeft;
    delete tempRight;
}

void delAllList(dl_List** tempLeft, dl_List** tempRight) {
    dl_List *temp = (*tempLeft)->right;
    while (temp != *tempRight) {
        cout << "Удаление элемента " << ReadElement(temp) << endl;
        temp = (*tempLeft)->right;
    }
    delete* tempLeft; tempLeft = NULL;
    delete* tempRight; tempRight = NULL;
}
