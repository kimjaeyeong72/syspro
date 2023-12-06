#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data);
int delete(struct node **head, struct node **tail);
void printQueue(struct node *head);

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int data;

    while (1) {
        if (scanf("%d", &data) == 1) {
            addq(&head, &tail, data);
        } else {
            if (feof(stdin) || ferror(stdin)) {
                break; 
            } else {
                printQueue(head);
                break;
            }
        }
    }

    return 0;
}

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {

        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("Print queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node *temp = *head;
    int deletedValue = temp->data;

    *head = temp->next;
    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
    return deletedValue;
}

void printQueue(struct node *head) {
    if (head == NULL) {
        printf("Print queue is empty.\n");
        return;
    }

    printf("Print queue\n");
    while (head != NULL) {
        printf("%d\n", head->data);
        head = head->next;
    }
    printf("\n");
}
