/*
  Queue Example - Queue
    - A queue is a data structure that is made up of nodes
      - Each node contains a value and a pointer to the next node
    - The first node is called the head
      - This node is accessed via the head pointer called p_head
    - The last node is called the tail
      - This node is accessed via the tail pointer called p_tail
    - Enqueue: Put new node as new tail
    - Dequeue: Remove head node and sets next node as new head

  Node structure:
    - next - pointer to next node
    - value - value of node

  *p_head                                *p_tail
    ⬇️                                     ⬇️
  [head] -> [node] -> [node] -> [node] -> [tail] -> NULL

  The queue is implemented as a linked list

  This examples shows the creation of a queue and how to enqueue and dequeue

  Prefixes:
    p_ is a pointer
    p2_ is a double pointer

  Author: Adrian Thomas Capacite
  Date: 24 / 10 / 2022
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

// Function prototypes
void printQueue(Node *p_currNode);
void enqueue(Node **p2_head, Node **p2_tail, int value);
int dequeue(Node **p2_head, Node **p2_tail);
void freeQueue(Node **p2_head, Node **p2_tail);

int main()
{
  // Create pointer to head node
  // It is NULL because there is no head node to point to yet
  Node *p_head = NULL;
  Node *p_tail = NULL;

  // Create an inital queue
  enqueue(&p_head, &p_tail, 120);
  enqueue(&p_head, &p_tail, 100);
  enqueue(&p_head, &p_tail, 135);
  enqueue(&p_head, &p_tail, 10);
  enqueue(&p_head, &p_tail, 50);

  // Program loop
  int usrSelect = 0;
  int usrIn;
  do
  {
    printf("\n");
    printf("================================================================\n");
    printf("\n");
    printf("[1] Enqueue node\n[2] Dequeue node\n[3] Print queue\n[4] Exit\n");
    scanf("%d", &usrSelect);


    switch (usrSelect)
    {
      // Enqueue node
      case 1:
      {
        // Ask user for number to enqueue to queue
        printf("Add number: ");
        scanf("%d", &usrIn);

        // Add number to the queue then print the queue
        enqueue(&p_head, &p_tail, usrIn);
        printQueue(p_head);
        break;
      }
      // Remove node
      case 2:
      {
        // Remove number from the list
        int value = dequeue(&p_head, &p_tail);

        // Print the number fetched and print the list
        printf("Fetched value: %d\n", value);
        printQueue(p_head);
        break;
      }
      // Print list
      case 3:
      {
        printf("Printing list...\n");
        printQueue(p_head);
        break;
      }
      // Exit program
      case 4:
      {
        printf("Exiting...\n");
        break;
      }
      // Invalid option
      default:
      {
        printf("Warning: %d is not an option\n", usrSelect);
        break;
      }
    }
  } while (usrSelect != 4);
  freeQueue(&p_head, &p_tail);
  return 0;
}

/**
 * @brief Prints the queue
 *
 * @param p_currNode
 */
void printQueue(Node *p_node)
{
  printf("*p_head: ");

  // Print value of current node then move to next node until current node is null
  while (p_node != NULL)
  {
    if (p_node->next == NULL) printf("*p_tail: ");
    printf("%d -> ", p_node->value);
    p_node = p_node->next;
  }

  printf("NULL\n");
}

/**
 * @brief Adds a node to the start (tail) of the queue
 *
 * @param p2_head Double pointer to head node
 * @param p2_tail Double pointer to tail node
 * @param value value to be stored in node
 */
void enqueue(Node **p2_head, Node **p2_tail, int value)
{
  // Create new node then check if allocation is successful
  Node *p_newNode = (Node *) malloc(sizeof(Node));
  if (p_newNode == NULL)
  {
    printf("Error: failed to allocate memory to enqueue node");
    return;
  }

  // Assign values to new node
  p_newNode->next = NULL;
  p_newNode->value = value;

  // Check if queue is empty then
  if (*p2_head == NULL)
  {
    // Point p_head to point to new tail node
    *p2_head = p_newNode;
  }
  else
  {
    // Set current tail node to point to new tail node
    (*p2_tail)->next = p_newNode;
  }

  // Set p_tail to point to new tail node
  *p2_tail = p_newNode;
}

/**
 * @brief Removes a node from the end (head) of the queue
 *
 * @param p2_head
 * @param p2_tail
 * @return int
 */
int dequeue(Node **p2_head, Node **p2_tail)
{
  // Fetch value from head node
  int value = (*p2_head)->value;
  // Store address of old head into temp pointer
  Node *p_temp = *p2_head;

  // Set p_head to the address of the next node
  // This removes the node from the queue
  *p2_head = (*p2_head)->next;

  // Check if list is empty then set tail to NULL
  if (*p2_head == NULL)
  {
    *p2_tail = NULL;
  }

  // Free memory location of dequeued node
  free(p_temp);
  // Return value fetched from dequeued node
  return value;
}

/**
 * @brief Frees memory allocated to queue
 *
 * @param p2_head
 */
void freeQueue(Node **p2_head, Node **p2_tail)
{
  // Set current node to head node
  Node *p_currNode = *p2_head;
  // Loop through each node and free them
  while (p_currNode != NULL)
  {
    Node *p_temp = p_currNode;
    p_currNode = p_currNode->next;
    free(p_temp);
  }

  // Set p_head and p_tail to null
  *p2_head = NULL;
  *p2_tail = NULL;

  printf("List sucessfully freed\n");
}