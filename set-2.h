//consulted sources such as implementbalancedset.h
//consulted geeksforgeeks
//consulted https://www.cpp.edu/~ftang/courses/CS241/notes/b-tree.htm
//consulted many youtube videos
//consulted navid's ppts


#ifndef MAIN_SAVITCH_SET_H
#define MAIN_SAVITCH_SET_H
#include <cstdlib>   // Provides size_t
#include <array>

namespace main_savitch_11
{
        template <class Item>
        class set
        {
public:
                // TYPEDEFS
                typedef Item value_type;
                // CONSTRUCTORS and DESTRUCTOR
                set( );
                set(const set& source) {
                }
                ~set( ) {
                        clear( );
                }
                // MODIFICATION MEMBER FUNCTIONS
                void operator =(const set& source);
                void clear();
                bool insert(const Item& entry);
                std::size_t erase(const Item& target);
                // CONSTANT MEMBER FUNCTIONS
                std::size_t count(const Item& target) const;
                bool empty() const {
                        clear();
                        data[MAXIMUM+1];

                        this->set();
                        return (data_count == 0);
                }
                // SUGGESTED FUNCTION FOR DEBUGGING
                void print(int indent) const;
private:
                // MEMBER CONSTANTS
                static const std::size_t MINIMUM = 200;
                static const std::size_t MAXIMUM = 2 * MINIMUM;

                // MEMBER VARIABLES
                std::size_t data_count;
                Item data[MAXIMUM+1];
                std::size_t child_count;
                set *subset[MAXIMUM+2];

                // HELPER MEMBER FUNCTIONS
                bool is_leaf( ) const {
                        return (child_count == 0);
                }
                bool loose_insert(const Item& entry);
                bool loose_erase(const Item& target);
                void remove_biggest(Item& removed_entry);
                void fix_excess(std::size_t i);
                void fix_shortage(std::size_t i);
                // NOTE: The implementor may want to have additional helper functions
        };


        set::set( )
        {
                data_count = 0;
                child_count = 0;
                data = new int[MAXIMUM + 1];
                subset = new set[MAXIMUM + 2];
        }

        set::set(const set& source)
        {
                data_count = source;
                child_count = source;
                data = new int[MAXIMUM+1];
                subset = new set[MAXIMUM + 2];
        }

        set::~set( )
        {
                clear();
        }

        // MODIFICATION MEMBER FUNCTIONS
        void set::operator =(const set& source)
        {
                data_count = source.data_count;
                child_count = source.child_count;
                for (auto e : data)
                        e = Item();
                for (auto e : subset)
                        e = nullptr;
                for (std::size_t i = 0; i < data_count; i++)
                        data[i] = source.data[i];

                for (std::size_t i = 0; i < child_count; i++)
                        subset[i] = source.subset[i];
        }

        void set::clear()
        {
                delete [] data;
                delete [] subset;
        }

        bool set::insert(const Item& entry)
        {
                loose_insert(element);
                if (data_count > MAXIMUM) {
                        set child = new set();
                        for (int x=0; x<data_count; x++)
                                child.data[x] = data[x];
                        for (int y=0; y<child_count; y++)
                                child.subset[y] = subset[y];
                        child.child_count = child_count;
                        child.data_count = data_count;
                        data_count = 0;
                        child_count = 1;
                        subset[0] = child;
                        fix_excess(0);
                }
        }

        std::size_t set::erase(const Item& target)
        {
                size_t count = 0;
                for (int i = 0; i < data_count; i++) {
                        if (data[i] == target) {
                                loose_remove(data[i]);
                                count++;
                        }
                }
                --data_count;
                --child_count;
                return count;
        }

        // CONSTANT MEMBER FUNCTIONS
        std::size_t set::count(const Item& target) const
        {
                size_t count = 0
                               for (auto i : data)
                {
                        if ( target == i ) { count++; }
                }
                return data_count;
        }

        // SUGGESTED FUNCTION FOR DEBUGGING
        void set::print(int root) const
        {
                int i = 0;
                if (root != NULL)
                {
                        for (int i = 0; i < root.data_count; i++)
                        {
                                print(root->child[i]);
                                cout << root->data[i + 1] << "\t";
                        }
                        print(root->child[i]);
                }
        }

        // HELPER MEMBER FUNCTIONS
        bool set::is_leaf() const
        {
                return (child_count == 0);
        }

        bool set::loose_insert(const Item& entry)
        {
                int i;
                for (i = 0; i < data_count && data[i] < entry; i++); //reach index with data[i] < entry
                if (i<data.length && data[i] == entry)
                        return;
                if (child_count == 0)
                {
                        for(int x = data.length-1; x > i; x--)
                                data[x] = data[x-1];
                        data[i] = entry;
                        data_count++;
                }
                else
                {
                        subset[i].looseAdd(entry);
                        if(subset[i].data_count > MAXIMUM)
                                fix_excess(i);
                }
        }

        bool set::loose_erase(const Item& target)
        {
                int i;
                for (i = 0; i<data_count && data[i] < target; i++);
                if (child_count == 0 && i == data_count)
                {
                        return false;
                } else if ((child_count == 0) && (data[i] == target)  )
                {
                        // remove the target from the data array and return true
                        return true;
                }
                if ((child_count > 0 ) && (data[i] == target))
                {
                        bool answer = subset[i].loose_remove(target);
                        if ((answer) && (subset[i].data_count < MINIMUM))
                        {
                                fix_shortage(i);
                        }
                        return answer;
                }
                if ( (child_count > 0) && ( data[i] == target))
                {
                        data[i] = subset[i].remove_biggest(i);
                        if (subset[i].data_count < MINIMUM)
                        {
                                fix_shortage(i);
                        }
                        return true;
                }
                return false;
        }

        void set::remove_biggest(Item& removed_entry) //IS THIS ASSUMING DUPLICATES? isn't that super hard to implement?
        {
                if (data_count <= 0) {
                        cout<< "fail" << endl;
                }
                if (child_count == 0) {
                        return data[--data_count];
                }
                if (child_count > 0 )
                {
                        int answer = subset[child_count-1].remove_biggest(removed_entry);
                        if (subset[child_count-1].data_count < MINIMUM) {
                                fix_shortage(child_count-1);
                        }
                        return answer;
                }
                return 0;
        }


        void set::fix_excess(std::size_t i)
        {
                int ct;
                for(ct = data_count; ct > i; ct--)
                        data[ct] = data[ct-1];
                data[i] = subset[i].data[MINIMUM];
                data_count++;
                set leftChild = new set(),
                    rightChild = new set();
                leftChild.data_count = MINIMUM;
                rightChild.data_count = MINIMUM;
                for (ct = 0; ct < MINIMUM; ct++) {
                        leftChild.data[ct] = subset[i].data[ct];
                        rightChild.data[ct] = subset[i].data[ct+MINIMUM+1];
                }
                int subChCt = (subset[i].child_count)/2;
                for (ct = 0; ct < subChCt; ct++) {
                        leftChild.subset[ct] = subset[i].subset[ct];
                        rightChild.subset[ct] = subset[i].subset[ct+subChCt];
                }
                if(subChCt > 0) {
                        leftChild.child_count = MINIMUM + 1;
                        rightChild.child_count = MINIMUM + 1;
                }
                subset[child_count] = new set();
                for (ct = child_count; ct > i; ct--)
                        subset[ct] = subset[ct-1];
                child_count++;
                subset[i] = leftChild;
                subset[i+1] = rightChild;
        }


        void set::fix_shortage(std::size_t i)
        {

                assert(i > 0);

                if (subset[i - 1]->data_count > MINIMUM)
                //Suppose subset[i-1] has more than the MINIMUM number of elements.
                {
                        //Transfer an extra element from subset[i-1].
                        for (std::size_t m = child_count; m > 0; m--)
                                subset[i]->data[m] = subset[i]->data[m - 1];

                        subset[i]->data[0] = data[i - 1];
                        subset[i]->data_count++;

                        data[i - 1] = subset[i - 1]->data[data_count - 1];
                        subset[i - 1]->data_count--;
                        subset[i - 1]->data[data_count - 1] = Item();

                        if (!subset[i - 1]->is_leaf())
                        {
                                for (std::size_t m = subset[i]->child_count; m > 0; m--)
                                        subset[i]->subset[m] = subset[i]->subset[m - 1];

                                subset[i]->subset[0] = subset[i - 1]->subset[child_count - 1];
                                subset[i]->child_count++;
                                subset[i - 1]->child_count--;
                        }
                }
                else if (subset[i + 1]->data_count > MINIMUM)
                // Transfer an extra element from subset[i+1].
                {
                        //Suppose subset[i+1] has more than the MINIMUM number of elements.
                        subset[i]->data[data_count] = data[i];
                        subset[i]->data_count++;
                        data[i] = subset[i + 1]->data[0];

                        for (std::size_t m = 0; m < subset[i + 1]->data_count - 1; m++)
                                subset[i + 1]->data[m] = subset[i + 1]->data[m + 1];

                        subset[i + 1]->data[data_count - 1] = Item();
                        subset[i + 1]->data_count--;

                        if (!subset[i + 1]->is_leaf())
                        {
                                subset[i]->subset[subset[i]->child_count] = subset[i + 1]->subset[0];

                                for (std::size_t m = 0; m < subset[i + 1]->child_count - 1; m++)
                                        subset[i + 1]->subset[m] = subset[i + 1]->subset[m + 1];

                                subset[i]->child_count++;
                        }
                }
                else if (subset[i - 1]->data_count == MINIMUM)
                // Combine subset[i] with subset[i-1].
                {
                        //Suppose subset[i-1] has only MINIMUM elements.
                        subset[i - 1]->data[subset[i - 1]->data_count] = data[i - 1];

                        for (std::size_t m = i - 1; m < data_count - 1; m++)
                                data[m] = data[m + 1];

                        --data_count;
                        subset[i - 1]->data_count++;

                        for (std::size_t m = 0; m < subset[i]->data_count; m++, subset[i - 1]->data_count++)
                                subset[i - 1]->data[subset[i - 1]->data_count + m] = subset[i]->data[m];

                        subset[i]->data_count = 0;

                        for (std::size_t m = 0; m < subset[i]->child_count; m++, subset[i - 1]->child_count++)
                                subset[i - 1]->subset[subset[i - 1]->child_count + m] = subset[i]->subset[m];

                        subset[i]->child_count = 0;

                        for (std::size_t m = i; m < child_count; m++)
                                subset[m] = subset[m + 1];

                        --child_count;
                }
                else if (subset[i + 1]->data_count == MINIMUM)
                // Combine subset[i] with subset[i+1].
                {
                        //Suppose subset[i+1] has only MINIMUM elements.
                        for (std::size_t m = subset[i + 1]->data_count; m > 0; m--)
                                subset[i + 1]->data[m] = subset[i + 1]->data[m - 1];

                        subset[i + 1]->data[0] = data[i];

                        data_count--;
                        subset[i]->data_count++;

                        for (std::size_t m = subset[i]->data_count; m > 0; m--, subset[i + 1]->data_count++)
                        {
                                for (std::size_t j = 0; j < subset[i + 1]->data_count; j++)
                                        subset[i + 1]->data[j] = subset[i + 1]->data[j - 1];

                                subset[i + 1]->data[0] = subset[i]->data[m];
                        }

                        for (std::size_t m = subset[i]->child_count; m > 0; m--, subset[i + 1]->child_count++)
                        {
                                for (std::size_t j = 0; j < subset[i + 1]->child_count; j++)
                                        subset[i + 1]->subset[j] = subset[i + 1]->subset[j - 1];

                                subset[i + 1]->subset[0] = subset[i]->subset[m];
                        }

                        for (std::size_t m = i; m < child_count; m++)
                                subset[m] = subset[m + 1];

                        child_count--;
                }

                fix_shortage(i);
        }

#include "set.template" // Include the implementation.

#endif
