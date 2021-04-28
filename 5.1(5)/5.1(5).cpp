#include <stdio.h>
#include <malloc.h>
#include <Windows.h>

typedef struct QueueNode {
    int data;
    QueueNode* next;
};
typedef struct Queue {
    QueueNode* head, * tail;
};
typedef struct StackNode {
    Queue* queue;
    StackNode* next;
}StackNode;

typedef struct Stack {
    StackNode* head;
}Stack;

Queue* createQueue();
void pushToQueue(Queue* q, int data);
size_t queueSize(Queue* q);
void enterQueue(Queue* q);
void showQueue(Queue* q);
int getQueueSum(Queue* q);
int getQueueMaxValue(Queue* q);
Stack* createStack();
void pushToStack(Stack* stack);
void enterStack(Stack* stack);
size_t stackSize(Stack* stack);
void showStack(Stack* stack);
StackNode* getNthStackNode(Stack* stack, int n);
void showQueueWithMaxParameter(Stack* stack, int (*function)(Queue* q));
void deleteNode(StackNode* node);
void deleteStack(Stack* stack);

int main() {
    Stack* stack = createStack();
    enterStack(stack);
    showStack(stack);
    putchar('\n');
    printf("Queue with max value: ");
    showQueueWithMaxParameter(stack, getQueueMaxValue);
    putchar('\n');
    printf("Queue with max sum: ");
    showQueueWithMaxParameter(stack, getQueueSum);
    deleteStack(stack);
}

Queue* createQueue() {
    Queue* tmp;
    if (!(tmp = (Queue*)malloc(sizeof(Queue)))) {
        return 0;
    }
    tmp->head = NULL;
    tmp->tail = NULL;
    return tmp;
}

void pushToQueue(Queue* q, int data) {
    QueueNode* tmp;
    tmp = (QueueNode*)malloc(sizeof(QueueNode*));
    tmp->next = NULL;
    tmp->data = data;
    if (q->head != NULL) {
        q->tail->next = tmp;
    }
    else {
        q->head = tmp;
    }
    q->tail = tmp;
}

size_t queueSize(Queue* q) {
    QueueNode* current = q->head;
    size_t qSize = 0;
    while (current) {
        qSize++;
        current = current->next;
    }
    return qSize;
}

void enterQueue(Queue* q) {
    int number, data;
    printf("How many values should be in queue?");
    scanf_s("%d", &number);
    for (int i = 0; i < number; i++) {
        printf("queue[%d] = ", i + 1);
        while (1) {
            if (scanf_s("%d", &data))
                break;
            else
                rewind(stdin);
        }
        pushToQueue(q, data);
    }
}

void showQueue(Queue* q) {
    QueueNode* current = q->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
}
int getQueueSum(Queue* q) {
    QueueNode* current = q->head;
    int sum = 0;
    while (current) {
        sum += current->data;
        current = current->next;
    }
    return sum;
}
int getQueueMaxValue(Queue* q) {
    QueueNode* current = q->head;
    int max = q->head->data;
    while (current) {
        if (current->data > max) {
            max = current->data;
        }
        current = current->next;
    }
    return max;
}

Stack* createStack() {
    Stack* tmp = (Stack*)malloc(sizeof(Stack));
    tmp->head = NULL;
    return tmp;
}

void pushToStack(Stack* stack) {
    StackNode* tmp = (StackNode*)malloc(sizeof(StackNode));
    tmp->next = stack->head;
    tmp->queue = createQueue();
    enterQueue(tmp->queue);
    stack->head = tmp;
}

void enterStack(Stack* stack) {
    int number;
    printf("How many queues you want to create?\n");
    while (1) {
        if (scanf_s("%d", &number))
            break;
        else
            rewind(stdin);
    }
    for (int i = 0; i < number; i++, system("cls")) {
        printf("Queue %d:\n", i + 1);
        pushToStack(stack);
    }
}
size_t stackSize(Stack* stack) {
    StackNode* current = stack->head;
    size_t size = 0;
    while (current) {
        size++;
        current = current->next;
    }
    return size;
}
void showStack(Stack* stack) {
    printf("\tStack:\n");
    StackNode* current = stack->head;
    int i = stackSize(stack);
    while (current) {
        printf("Queue %d: ", i);
        showQueue(current->queue);
        putchar('\n');
        current = current->next;
        i--;
    }
}
StackNode* getNthStackNode(Stack* stack, int n) {
    StackNode* current = stack->head;
    int count = 0;
    while (current) {
        count++;
        if (count == n)
            return current;
        current = current->next;
    }
}
void showQueueWithMaxParameter(Stack* stack, int (*function)(Queue* q)) {
    int queueWithMaxValueIndex = 0;
    int maxQueuesValue = 0;
    int maxValueOfCurrentQueue;
    StackNode* current = stack->head;
    int i = 0;
    while (current) {
        i++;
        maxValueOfCurrentQueue = function(current->queue);
        if (maxValueOfCurrentQueue > maxQueuesValue) {
            maxQueuesValue = maxValueOfCurrentQueue;
            queueWithMaxValueIndex = i;
        }
        current = current->next;
    }
    StackNode* nodeWithMaxQueue = getNthStackNode(stack, queueWithMaxValueIndex);
    showQueue(nodeWithMaxQueue->queue);
}
void deleteNode(StackNode* node) {
    if (node->next) {
        deleteNode(node->next);
    }
    free(node);
}
void deleteStack(Stack* stack) {
    StackNode* current = stack->head;
    if (!stack->head)
        return;
    if (current->next)
        deleteNode(current->next);
    free(stack);
    stack = NULL;
}