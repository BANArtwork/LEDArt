#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * @brief A basic linked list implementation.
 * 
 * @tparam T Data type to be held in the list.
 */
template <typename T>
class LinkedList {

    public:
        
        /**
         * @brief List node class.
         */
        class ListNode {

            public: 

                T data;
                ListNode* next;
        };

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
            return get(index);
        }

        /**
         * @brief Get an item in the list by index.
         * 
         * @param index 
         * @return T 
         */
        T get(int index) {
            ListNode* result = _start;
            int i = index;
            while (i > 0 && result != NULL) {
                result = result->next;
                i--;
            }
            if (result == NULL) return NULL;
            return result->data;
        }

        /**
         * @brief Execute the given action on every list item.
         * 
         * @param loopAction 
         */
        void forEach(std::function<void(T item)> loopAction) {
            ListNode* it = _start;
            while (it != NULL) {
                loopAction(it->data);
                it = it->next;
            }
        }

        /**
         * @brief Return the first item in the list that matches the
         * given predicate.
         * 
         * @param searchAction 
         * @return T 
         */
        T findFirst(std::function<bool(T item)> searchAction) {
            ListNode* it = _start;
            while (it != NULL) {
                if (searchAction(it)) return it;
                it = it->next;
            }
            return NULL;
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
            ListNode* newNode = new ListNode();
            newNode->data = insert;

            // Insert before first item.
            if (index == 0 || _start == NULL) {
                newNode->next = _start;
                _start = newNode;
                return;
            }
            
            // Cast to unsigned and decrement to 
            // get the item to insert after.
            unsigned int i = index;
            i--;

            // Get the item to insert after.
            ListNode* item = _start;
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
            
            // List is empty.
            if (_start == NULL) return;

            // Delete first item.
            if (index == 0) {
                ListNode* d = _start;
                _start = _start->next;
                delete d;
                return;
            }

            // Advance to indexed item.
            ListNode* a;
            ListNode* b;
            a = _start;
            b = a->next;
            int i = index - 1;
            while(i > 0 && b->next != NULL) {
                a = b;
                b = b->next;
                i--;
            }
            
            // If we found the indexed item (or index was -1)...
            if (i == 0 || index == -1) {
            
                // Then delete the item.
                a->next = NULL;
                delete b;
            }
        }

    private:
    
        // Start of list.
        ListNode* _start;

        // Current item in list.
        ListNode* _current;
};

#endif
