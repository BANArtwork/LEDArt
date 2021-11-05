#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class ListNode {

    public: 

        T data;
        ListNode* next;
};

template <typename T>
class LinkedList {

    public:
        
        /**
         * @brief Get the first item in the list.
         * 
         * @return T 
         */
        T start() {
            _current = _start;
            if (_current == NULL) return NULL;
            return _current->data;
        }
        
        /**
         * @brief Get the next item in the list.
         * 
         * @return T 
         */
        T next() {
            _current = _current->next;
            if (_current == NULL) return NULL;
            return _current->data;
        }

        /**
         * @brief Index list as an array.
         * 
         * @param index 
         * @return T 
         */
        T operator[](int index) {
            ListNode<T>* result = _start;
            int i = index;
            while (i > 0 && result != NULL) {
                result = result->next;
                i--;
            }
            if (result == NULL) return NULL;
            return result->data;
        }

        /**
         * @brief Insert the item at the given 
         * index. -1 inserts at the end of the list.
         * 
         * @param insert The item to insert.
         * @param index The index of the item to insert after.
         */
        void insert(T insert, int index = -1) {
            
            // Create new list node.
            ListNode<T>* newNode = new ListNode<T>();
            newNode->data = insert;

            // Insert before first item.
            if (index == 0 || _start == NULL) {
                newNode->next = _start;
                _start = newNode;
                return;
            }
            
            // Cast to unsigned and decrement to 
            // get the item to instert after.
            unsigned int i = index;
            i--;

            // Get the item to insert after.
            ListNode<T>* item = _start;
            while(i > 0 && item->next != NULL) {
                item = item->next;
                i--;
            }

            // Insert item.
            newNode->next = item->next;
            item->next = newNode;
        };

        /**
         * @brief Delete the item at the given 
         * index. -1 deletes the last item in the list.
         * 
         * @param index Index of the item to delete.
         */
        void remove(int index = -1) {
            
            // Var to hold deleted item.
            ListNode<T>* result;

            // Delete first item.
            if (index == 0) {
                result = _start;
                _start = _start->next;
                delete result;
                return;
            }
            
            // Cast to unsigned and decrement to get 
            // the item before the item to delete.
            unsigned int i = index;
            i--;
            
            // Get the item before the item to delete.
            ListNode<T>* item = _start;
            while(i > 0 && item->next->next != NULL) {
                item = item->next;
                i--;
            }

            // Delete the item.
            result = item->next;
            item->next = result->next;
            delete result;
        }

    private:
    
        // Start of list.
        ListNode<T>* _start;

        // Current item in list.
        ListNode<T>* _current;
};

#endif
