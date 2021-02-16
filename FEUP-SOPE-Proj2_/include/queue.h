#pragma once

#include <stdbool.h>

/** @file */

/** @defgroup queue Queue */
/** @addtogroup queue
  *
  * @details Code blatantly stolen from Tiago Silva's LCOM project
  * 
  * @brief	Handles a Queue of char pointers
  */

/**
 * @brief Queue data structure (FIFO)
 * @details Implemented using a linked list
 * @warning Has a maxsize defined on the macro QUEUE_MAX_CAPACITY
 * 
 */
typedef struct Queue Queue_t;

/**
 * @brief Called to create a new Queue
 * 
 * @param max_size Maximum size for this Queue
 * 
 * @return Queue_t* Pointer to the Queue upon success\n
 * NULL otherwise
 */
Queue_t* new_queue(unsigned int max_size);
/**
 * @brief Frees an entire Queue
 * 
 * @param q Pointer to the Queue to be freed
 */
void free_queue(Queue_t *q);

/**
 * @brief Frees and entire Queue and it's contents
 * 
 * @param q Pointer to the Queue to be freed
 */
void free_queue_and_data(Queue_t* q);

/**
 * @brief Clears all the elements from the Queue
 * 
 * @param q The Queue to clear
 */
void queue_clear(Queue_t* q);

/**
 * @brief Pushes an element onto the back of the Queue
 * 
 * @param q Pointer to the Queue to operate over
 * @param data The data to be pushed back
 * @return bool false on success\n
 * true otherwise
 */
bool queue_push_back(Queue_t *q, void* data);
/**
 * @brief Removes an element from the front of the Queue, returning it in the process
 * 
 * @param q Pointer to the Queue to operate over
 * @return void* The data of the element popped on success\n
 * NULL otherwise
 */
void* queue_pop(Queue_t *q);
/**
 * @brief Peeks and returns the element on the back of the Queue
 * 
 * @param q Pointer to the Queue to operate over
 * @return void* The data of the element on the back of the Queue on success\n
 * NULL otherwise
 */
void* queue_back(Queue_t *q);
/**
 * @brief Peeks and returns the element on the front of the Queue
 * 
 * @param q Pointer to the Queue to operate over
 * 
 * @return void* Pointer to the data of the element on the front of the Queue on success\n
 * NULL otherwise
 */
void* queue_front(Queue_t *q);
/**
 * @brief Returns true when the Queue is empty
 * 
 * @param q Pointer to the Queue to operate over
 * @return True when the Queue is empty\n
 * False otherwise
 */
bool queue_is_empty(Queue_t *q);
/**
 * @brief Returns true when the Queue is at its max capacity
 * 
 * @param q Pointer to the Queue to operate over
 * @return True when the number of elements of the Queue is at/over the QUEUE_MAX_CAPACITY
 * False otherwise
 */
bool queue_is_full(Queue_t *q);
/**
 * @brief Returns the current size of the Queue (the number of elements stored)
 * 
 * @param q Pointer to the Queue to operate over
 * @return unsigned int The number of elements in the Queue
 */
unsigned int queue_size(Queue_t *q);
/**
 * @brief Returns the max size for the Queue
 * 
 * @param q Pointer to the Queue to operate over
 * @return unsigned int The maximum number of elements in the Queue
 */
unsigned int queue_max_size(Queue_t *q);

/** @} */
