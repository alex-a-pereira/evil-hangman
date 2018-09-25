#include "status.h"
/*
struct MY_STRING declares an object that contains the following:
1. an integer 'size', which holds the number of characters contained
by the object
    int size;
2. an integer 'capacity', which holds the number of possible characters
that can currently be hold by the object
    int capacity;
3. a character array 'data', which holds the characters currently held
in the objects
    char* data;
*/
typedef void* MY_STRING;

/* POST:
Allocate space for a string object that represents the empty string.
String will have capacity of 7 and size 0 by default
A copy of the address of the opaque object will be returned
on success, and NULL will be returned on failure
*/
MY_STRING my_string_init_default(void);

/*
PRE:
phMy_string holds the address of a valid handle to a MY_STRING object
POST:
The memory used for the MY_STRING object has been reclaimed by the system
The handle referred to by the pointer phMy_string has bee set to NULL
*/
void my_string_destroy(MY_STRING* phMy_string);


/*
PRE:
c_string is a valid null terminated c-string
POST:
Allocate space ofr a string object that represents a string
with the same value as the given c string. The capacity of the string
object will be set to be one greater than is required to hold the string
RETURN:
on success: copy of the address of the opaque object
on failure: NULL
*/
MY_STRING my_string_init_c_string(const char* c_string);

/*
* PRE:
* hMy_string is the handle of a valid My_string object
* POST:
* Returns a copy of the integer value of the object's capacity
*/
int my_string_get_capacity(MY_STRING hMy_string);

/*
* PRE:
* hMy_string is the handle of a valid My_string object
* POST:
* Returns a copy of the integer value of the object's size
*/
int my_string_get_size(MY_STRING hMy_string);

/*
PRE:
hLeft_string and hRight_string are valid My_string objects
POST:
Consider than a string is considered "less than" if it is lexicographically
smaller than the string it's compared to. If one string is a prefix
of the other string then the shorter String is considered to be
the smaller one (e.g. app is less than apple).
RETURN:
Case 1. Returns an integer less than zero if the string represented by hLeft_string
is smaller than hRight_string.

Case 2. Returns 0 if the strings are the same

Case 3. Returns a integer greater than zero if the string represented by hLeft_string is
is greater than hRight_string
*/

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);


/*
PRE:
hMy_string is the handle to a valid My_string objects
POST:
hMy_string will be the handle of a string object that contains the
next string from the file stream according to the following conditions:
1. Leading whitespace will be ignored
2. All characters (after the first non-whitespace character is obtained
and included) will be added to the string until a stopping condition is met.
The capacity of the string will continue to grow as needed until all characters
are stored.
3. A stopping condition is met if we read a whitespace character after we
have read at least one non-whitespace character or if we reach the eof
RETURN:
Function will return SUCCESS if a non-empty string is read successfully,
otherwise is will return FAILURE.

the incoming string may already contain some data and the func should replace
the data, but not resize the array unless necessary.
*/
Status my_string_extraction(MY_STRING hMy_string, FILE* fp);



/*
PRE:
hMy_string is the handle to a valid My_string object
POST:
Writes the characters contained in the string object
indeicated by hMy_string to the file stream fp
RETURN:
Returns SUCCESS if write is successful, otherwise FAILURE
*/

Status my_string_insertion(MY_STRING hMy_string, FILE* fp);