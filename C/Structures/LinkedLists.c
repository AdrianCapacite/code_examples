/*
  Linked List Example - LinkedLists
    - A linked lists is a data structure that is made up of nodes.
    - Each node contains a value and a pointer to the next node.
    - The first node is called the head
    - The head node is the first node in the list
      - The list is accessed via a pointer variable pointing to the head,
        in this example program it is called p_head
    - The last node points to NULL

  Node structure:
    - next - pointer to next node
    - value - value of node

  *p_head
    ⬇️
  [head] -> [node] -> [node] -> [node] -> [node] -> NULL

  A linked list can grow and shrink dynamically and is stoted non-contigously
  in heap memory.

  Adding a node will insert it to a location where the value of the new node is
  lesser than previous node or at the end of the list

  Removing a node will remove the node that matches the value specified

  This examples shows the creation of a linked list and how to add and remove

  Prefixes:
    p_ is a pointer
    p2_ is a double pointer

  Author: Adrian Thomas Capacite
  Date: 11 / 10 / 2022
*/
#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
  int value;
  struct Node *next;
} Node;

// Function prototypes
void printList(Node *p_currNode);
void addNode(Node **p2_head, int value);
int removeNode(Node **p2_head, int value);
void freeList(Node **p2_node);

int main()
{
  // Create pointer to head node
  // It is NULL because there is no head node to point to yet
  Node *p_head = NULL;

  // Create an inital list
  addNode(&p_head, 120);
  addNode(&p_head, 100);
  addNode(&p_head, 135);
  addNode(&p_head, 10);
  addNode(&p_head, 50);

  // Program loop
  int usrSelect = 0;  // Store user menu selection
  int usrIn;          // Store user value entry

  do
  {
    // Menu user prompt
    printf("\n");
    printf("================================================================\n");
    printf("\n");
    printf("[1] Add node \n[2] Remove node \n[3] Print list \n[4] Exit\n");
    scanf("%d", &usrSelect);

    // Execute selection
    switch (usrSelect)
    {
      // Add node to linked list
      case 1:
      {
        // Ask user for number to add to list
        printf("Add number: ");
        scanf("%d", &usrIn);

        // Add number to the list then print the list
        addNode(&p_head, usrIn);
        printList(p_head);
        break;
      }
      // Remove node from linked list
      case 2:
      {
        // Ask user for number to remove from list
        printf("Remove number: ");
        scanf("%d", &usrIn);

        // Remove number from the list
        int value = removeNode(&p_head, usrIn);

        // Print the number fetched and print the list
        printf("Fetched value: %d\n", value);
        printList(p_head);
        break;
      }
      // Print list
      case 3:
      {
        printf("Printing list...\n");
        printList(p_head);
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

  freeList(&p_head);
  return 0;
}

/**
 * @brief Prints the list
 *
 * @param p_currNode Pointer to head node
 */
void printList(Node *p_currNode)
{
  printf("HEAD -> ");

  // Print value of current node then move to next node until current node is null
  while (p_currNode != NULL)
  {
    printf("%d -> ", p_currNode->value);
    p_currNode = p_currNode->next;
  }

  printf("NULL\n");
}

/**
 * @brief Adds a new node to the list
 *
 * @param p2_head double pointer to head node
 * @param value value stored in new node
 */
void addNode(Node **p2_head, int value)
{
  // Allocate memory to new node
  Node *p_newNode = (Node *)malloc(sizeof(Node));
  // Check if node has not been allocated memory
  if (p_newNode == NULL)
  {
    printf("Error: Unable to allocate memory to new node");
    return;
  }
  // Assign values to new node
  p_newNode->next = NULL;
  p_newNode->value = value;

  // Set location to head node
  Node *p_prevNode = NULL;
  Node *p_currNode = *p2_head;

  // Find a location where value is less than current node
  // or if we are at the end of the list
  while (p_currNode != NULL && value > p_currNode->value)
  {
    p_prevNode = p_currNode;
    p_currNode = p_currNode->next;
  }

  // If we are at the start of the list
  // Else insert between previous and current node
  if (p_prevNode == NULL)
  {
    // Set new node to point to head node
    p_newNode->next = *p2_head;
    // Set head node to point to new node
    *p2_head = p_newNode;
  }
  else
  {
    // Set previous node to point to new node
    p_prevNode->next = p_newNode;
    // Set new node to point to current node
    p_newNode->next = p_currNode;
  }

  printf("Node inserted sucessfully!\n");
  return;
}

/**
 * @brief Removes a node from the list
 *
 * @param p2_head double pointer to head of node
 * @param key value to remove from list
 */
int removeNode(Node **p2_head, int key)
{
  // Check if list is empty
  if (*p2_head == NULL)
  {
    printf("List is empty\n");
    return 0;
  }
  // If value of head node matches key value
  // Else look through the list
  if (key == (*p2_head)->value)
  {
    Node *p_temp = *p2_head;      // Store address of old head node into a temp pointer
    *p2_head = (*p2_head)->next;  // Set head pointer to the new head node
    free(p_temp);

    return key;
  }
  else
  {
    // Set location to after the head node
    Node *p_prevNode = *p2_head;
    Node *p_currNode = (*p2_head)->next;

    // Find a location where value is less than current node
    // Find node containing the key
    while (p_currNode != NULL && p_currNode->value != key)
    {
      p_prevNode = p_currNode;
      p_currNode = p_currNode->next;
    }

    // If a node node has been found then delete the node
    if (p_currNode != NULL)
    {
      // Store address of current node into a temp pointer
      Node *p_temp = p_currNode;
      // Set previous node to point to node next after current node
      p_prevNode->next = p_currNode->next;
      free(p_temp);

      return key;
    }
  }
  // If there are no nodes to be deleted, return 0
  printf("No value found");
  return 0;
}

/**
 * @brief Frees memory allocated to linked list
 *
 * @param p_currNode pointer to head node
 */
void freeList(Node **p2_head)
{
  Node *p_currNode = *p2_head;
  // Free each node
  while (p_currNode != NULL)
  {
    Node *p_temp = p_currNode;
    p_currNode = p_currNode->next;
    free(p_temp);
  }

  // Set p_head to null
  *p2_head = NULL;

  printf("List sucessfully freed\n");
}
