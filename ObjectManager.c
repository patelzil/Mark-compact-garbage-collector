//-----------------------------------------
// NAME: Patel Zil
// STUDENT NUMBER: 7876456
// COURSE: COMP 2160, SECTION: A02
// INSTRUCTOR: Franklin Bristow
// ASSIGNMENT: 1, QUESTION: 1
//
// REMARKS:
//
//-----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ObjectManager.h"

static int memID = 0;

typedef struct CONTENT
{
    int start;
    int size;
    int reference;
    int id;
} Content;

typedef struct NODE Node;
struct NODE
{
    Content content;
    Node *next;
};

Node *top;

uchar *buffer;

/*
 * Note that we provide our entire interface via this object module
 * and completely hide our index (see course notes). This allows us to
 * change indexing strategies without affecting the interface to
 * everyone else.

 * This function trys to allocate a block of given size from our buffer.
 * It will fire the garbage collector as required.
 * We always assume that an insert always creates a new object...
 * On success it returns the reference number for the block of memory
 * allocated for the object.
 * On failure it returns NULL_REF (0)
 */
Ref insertObject( ulong size )
{
    assert(size > 0);

    Node *current = top;
    Node *newNode;
    int result;

    while (current->next != NULL)
    {
        current = current->next;
    }

    if(current->content.start + size > MEMORY_SIZE)
    {
        result = 0;
    }
    else
    {
        newNode = (Node *) malloc(sizeof(Node));
        if (top->next == NULL)
        {
            newNode->content.start = 0;
        }
        else
        {
            newNode->content.start = current->content.start + current->content.size;
        }

        newNode->content.size = size;
        newNode->content.reference = 1;
        newNode->content.id = memID++;
        newNode->next = NULL;
        current->next = newNode;
        result = newNode->content.id;
    }

    return result;
}// end insertObject

// returns a pointer to the object being requested given by the reference id
void *retrieveObject( Ref ref )
{
    Node *current = top;

    while (current->content.id != ref)
    {
        current = current->next;
    }

}// end retrieveObject

// update our index to indicate that we have another reference to the given object
void addReference( Ref ref )
{
    Node *current = top;

    while (current->content.id != ref)
    {
        current = current->next;
    }

    current->content.reference++;
}// end addReference

// update our index to indicate that a reference is gone
void dropReference( Ref ref )
{
    Node *current = top;

    while (current->content.id != ref)
    {
        current = current->next;
    }

    current->content.reference--;
}// end dropReference

// initialize the object manager
void initPool()
{
    buffer = malloc(MEMORY_SIZE);
    top = NULL;
}// initPool

// clean up the object manager (before exiting)
void destroyPool()
{

}// end destroyPool

/*
 * This function traverses the index and prints the info in each entry
 * corresponding to a block of allocated memory. You should print the
 * block's reference id, its starting address, and its size (in
 * bytes).
 */
void dumpPool()
{

}// end dumpPool

/*
 * This function traverses the index as it calculates the total
 * number of objects that exist
 */
int totalObjects()
{

}