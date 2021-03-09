// FILE: table2.h
// TEMPLATE CLASS PROVIDED: Table<RecordType>
//   This class is a container template class for a Table of records.
//   The template parameter, RecordType, is the data type of the records in the
//   Table. It may any type with a default constructor, a copy constructor,
//   an assignment operator, and an integer member variable called key.
//
// CONSTRUCTOR for the Table<RecordType> template class:
//   Table( )
//     Postcondition: The Table has been initialized as an empty Table.
//
// MODIFICATION MEMBER FUNCTIONS for the Table<RecordType> class:
//   void insert(const RecordType& entry)
//     Precondition: entry.key >= 0. Also if entry.key is not already a key in
//     the table, then the Table has space for another record
//     (i.e., size( ) < CAPACITY).
//     Postcondition: If the table already had a record with a key equal to
//     entry.key, then that record is replaced by entry. Otherwise, entry has
//     been added as a new record of the Table.
//
//   void remove(int key)
//     Postcondition: If a record was in the Table with the specified key, then
//     that record has been removed; otherwise the table is unchanged.
//
// CONSTANT MEMBER FUNCTIONS for the Table<RecordType> class:
//   bool is_present(const Item& target) const
//     Postcondition: The return value is true if there is a record in the
//     Table with the specified key. Otherwise, the return value is false.
//
//   void find(int key, bool& found, RecordType& result) const
//     Postcondition: If a record is in the Table with the specified key, then
//     found is true and result is set to a copy of the record with that key.
//     Otherwise found is false and the result contains garbage.
//
//   size_t size( ) const
//     Postcondition: Return value is the total number of records in the
//     Table.
//
// VALUE SEMANTICS for the Table<RecordType> template class:
//   Assignments and the copy constructor may be used with Table objects.
//
// DYNAMIC MEMORY USAGE by the Table<RecordType> template class:
//   If there is insufficient dynamic memory, then the following functions
//   can call new_handler: the copy constructor, insert, the assignment
//   operator.

#ifndef TABLE2_H
#define TABLE2_H
#include <cstdlib>    // Provides size_t
#include "node2.h"    // Provides the node type, from Figure 6.5 on page 306



namespace main_savitch_12B
{
    template <class RecordType>
    class table
    {
    public:
        // MEMBER CONSTANT -- See Appendix E if this fails to compile.
        static const std::size_t TABLE_SIZE = 811;
        // CONSTRUCTORS AND DESTRUCTOR
        table( )
        {
          total_records = 0;
          for(int i = 0; i < TABLE_SIZE; i++) { //initialize linked lists as null head ptr
		           data[i] = NULL;
	        }
        }

        table(const table& source)
        {
          node<RecordType> *tempTail;
          for(int i = 0; i < TABLE_SIZE; i++) {
        		list_copy(source.data[i], data[i], tempTail);
        	}
          this->total_records = source.total_records;
        }

        ~table( )
        {
          for (int i = 0; i < TABLE_SIZE; i++)
          {
            list_clear(data[i]);
          }
        }

        // MODIFICATION MEMBER FUNCTIONS
        void insert(const RecordType& entry)
        {
        	if(is_present(entry.key) == false)
        	{
        		node<RecordType> *cursor = data[hash(entry.key)];

        		if(cursor == NULL) //unfilled
        		{
        			cursor = data[hash(entry.key)] = new node<RecordType>;
        			cursor->data = entry;
        			cursor->link = NULL;
        		}
        		else //filled
        		{
        			while(cursor->link != NULL && cursor->data.key != entry.key)
        			{
        				cursor = cursor->link;
        			}

        			cursor->link = new node<RecordType>;
        			cursor = cursor->link;
        			cursor->link = NULL;
        			cursor->data = entry;
        		}

        		++total_records;
        	}
        }


void remove(int key)
{
  node<RecordType> *cursor = data[hash(key)],
 *precursor = NULL;

bool found = false;
while(cursor != NULL)
{
  if(cursor->data.key == key)
  {
    found = true;
    break;
  }
  precursor = cursor;
  cursor = cursor->link;
}
if(found == true)
{
  list_remove(precursor);
  total_records--;
}
}




        void operator =(const table& source)
        {
          if (this == &source)
            return;
          clear();
          node<RecordType> *tempTail;
          for(int i = 0; i < TABLE_SIZE; i++)
          {
            list_copy(source.data[i], data[i], tempTail);
          }
          this->total_records = source.total_records;
        }







        // CONSTANT MEMBER FUNCTIONS
        void find(int key, bool& found, RecordType& result) const
        {
          Node<RecordType> *cursor = data[hash(key)];

          bool found = false;
          while (cursor->link() != NULL && curosr->data.key != key)
          {
            if (key == cursor->data.key)
            {
              result = cursor->data;
              found = true;
              break;
            }
            cursor = cursor->link();
          }
        }



        bool is_present(int key) const
        {
          Node<RecordType> *cursor = data[hash(key)];
        	bool found = false;
        	while(cursor != NULL)
        	{
        		if(cursor->data.key == key)
        		{
        			found = true;
        			break;
        		}
        		cursor = cursor->link;
        	}
        	return found;
        }

        std::size_t size( ) const { return total_records; }
    private:
        main_savitch_6B::node<RecordType> *data[TABLE_SIZE];
        std::size_t total_records;
        // HELPER MEMBER FUNCTION
        std::size_t hash(int key) const { return key % TABLE_SIZE; }
    };
}



#endif
