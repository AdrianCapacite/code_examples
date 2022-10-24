/*
  Stack Example - Stack
    - A stack is a data structure that is made up of nodes
      - Each node contains a value and a pointer to the next node
    - The first node is called the top
      - This node is accessed via the head pointer called p_top
    - Push: Add new node on top of the stack
    - Pop: Removes node from the top of the stack

  Node structure:
    - next - pointer to next node
    - value - value of node

  *p_top
   ⬇️
  [top] -> [node] -> [node] -> [node] -> [node] -> NULL

  The queue is implemented as a linked list

  This examples shows the creation of a queue and how to push and pop

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
void printStack(Node *p_currNode);
void push(Node **p2_top, int value);
int pop(Node **p2_top);
void freeStack(Node **p2_top);

int main()
{
  // Create pointer to head node
  // It is NULL because there is no head node to point to yet
  Node *p_top, = NULL;

  // Create an inital stack
  push(&p_top, 120);
  push(&p_top, 100);
  push(&p_top, 135);
  push(&p_top, 10);
  push(&p_top, 50);

  // Program loop
  int usrSelect = 0;
  int usrIn;
  do
  {
    printf("\n");
    printf("================================================================\n");
    printf("\n");
    printf("[1] Push node\n[2] Pop node\n[3] Print stack\n[4] Exit\n");
    scanf("%d", &usrSelect);


    switch (usrSelect)
    {
      // Enqueue node
      case 1:
      {
        // Ask user for number to push to queue
        printf("Add number: ");
        scanf("%d", &usrIn);

        // Add number to the queue then print the queue
        push(&p_top, usrIn);
        printStack(p_top);
        break;
      }
      // Remove node
      case 2:
      {
        // Remove number from the list
        int value = pop(&p_top);

        // Print the number fetched and print the list
        printf("Fetched value: %d\n", value);
        printStack(p_top);
        break;
      }
      // Print list
      case 3:
      {
        printf("Printing list...\n");
        printStack(p_top);
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
  freeStack(&p_top);
  return 0;
}

/**
 * @brief Prints the stack
 *
 * @param p_currNode
 */
void printStack(Node *p_node)
{
  printf("*p_top: ");

  // Print value of current node then move to next node until current node is null
  while (p_node != NULL)
  {
    printf("%d -> ", p_node->value);
    p_node = p_node->next;
  }

  printf("NULL\n");
}

/**
 * @brief Adds a node to the top of the stack
 *
 * @param p2_head Double pointer to head node
 * @param value value to be stored in node
 */
void push(Node **p2_top, int value)
{
  // Create new node then check if allocation is successful
  Node *p_newNode = (Node *) malloc(sizeof(Node));
  if (p_newNode == NULL)
  {
    printf("Error: failed to allocate memory to push node");
    return;
  }

  // Assign values to new node
  p_newNode->next = NULL;
  p_newNode->value = value;

}

/**
 * @brief Removes a node from the top of the stack
 *
 * @param p2_top
 * @return int value of popped node
 */
int pop(Node **p2_head)
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
void freeStack(Node **p2_head, Node **p2_tail)
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