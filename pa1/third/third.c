#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node 
{
    int data;
    struct Node *next;
} Node;
Node* createNode(int data) 
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node **head, int data) 
{
    Node *newNode = createNode(data);
    if (*head == NULL || (*head)->data >= data) 
    {
        newNode->next = *head;
        *head = newNode;
    } 
    else 
    {
        Node *current = *head;
        while (current->next != NULL && current->next->data < data) 
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void deleteNode(Node **head, int data) 
{
    if (*head == NULL) return;

    Node *temp = *head;
    if (temp->data == data) 
    {
        *head = temp->next;
        free(temp);
        return;
    }

    Node *prev = NULL;
    while (temp != NULL && temp->data != data) 
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return; 

    prev->next = temp->next;
    free(temp);
}

void printList(Node *head) 
{
    if (head == NULL) 
    {
        printf("EMPTY\n");
        
        return;
    }
    Node *current = head;
    while (current != NULL) 
    {
        printf("%d\t", current->data);
        
        current = current->next;
    }
    printf("\n");
}

void freeList(Node *head) 
{
    Node *temp;
    while (head != NULL) 
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) 
    {
        perror("Error opening file");
        return 1;
    }

    Node *head = NULL;
    char command[10];
    int data;

    while (fscanf(file, "%s %d", command, &data) != EOF) 
    {
        if (strcmp(command, "INSERT") == 0) 
        {
            insertNode(&head, data);
        } 
        else if (strcmp(command, "DELETE") == 0) 
        {
            deleteNode(&head, data);
        }
        printList(head);
    }

    fclose(file);
    freeList(head); 

    return 0;
}