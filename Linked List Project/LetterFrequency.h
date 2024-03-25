#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

// Defined according to UML diagram
class LetterNode {
    public:
        LetterNode(char chr) { // Construct a LetterNode containing the given character
            letter = chr;
            frequency = 1; // If previously unknown, this letter now has a frequency of 1!
            next = nullptr; // Initializes the "next" pointer
        }

        ~LetterNode() {
            cout << "Destroying " << letter << " ...\n"; // Destructor message
        }

        void increaseFrequency() {frequency++;}

        char getLetter() {return letter;}

        int getFrequency() {return frequency;}

        LetterNode *getNext() {return next;}

        void setNext(LetterNode *next) {this->next = next;}

    private:
        int frequency; // The number of times that the letter has been read in
        char letter; // The alphabetic letter that this node represents (node identifier)
        LetterNode *next; // The pointer to the next node in the list
};

class LetterFrequencyList {
    public:
        LetterFrequencyList() {
            head = nullptr; // Initializes the list
        }

        ~LetterFrequencyList() {
            // Add a recursive function that deletes from the END of the list to the FRONT
            delist(head);

            cout << "List is destroyed.\n";
            head = nullptr;
        }

        bool append(char letter) { // Optimized.
            LetterNode *foundNode = find(letter); // A "getter" traversal of the list (traverses to get, not set)
            // If the node ISN'T in the list
            if (nullptr == foundNode) {
                head = new LetterNode(letter); // Appends the first node
                return true; // Indicates that a new node was added
            }
            else if (foundNode->getLetter() != letter) {
                foundNode->setNext(new LetterNode(letter)); // Appends to derived insertion point
                return true;
            }
            // If the node IS on the list
            else {
                foundNode->increaseFrequency();
                return false; // Indicates that a new node wasn't added
            }
        }

        bool insertInOrder(char letter) {
            LetterNode *foundNode = find(letter);
            LetterNode *amazon = nullptr; // Keeps it A to Z, like Amazon
            // If the node ISN'T in the list
            // Add the node to the list so that the list is maintained in alphabetical order
            if (nullptr == foundNode) {
                head = new LetterNode(letter); // Inserts the first node of the sorted list
                return true; // Indicates that a new node was added
            }
            // If the node IS on the list
            else if (foundNode->getLetter() == letter) {
                foundNode->increaseFrequency();
                return false; // Indicates that a new node wasn't added
            }
            else if (foundNode->getLetter() != letter) {
                if (letter > foundNode->getLetter()) {
                    if (foundNode->getNext() == nullptr) { // Worst-case scenario, the last node is returned to foundNode
                        foundNode->setNext(new LetterNode(letter));
                        return true;
                    }
                    amazon = foundNode->getNext();
                    foundNode->setNext(new LetterNode(letter));
                    foundNode->getNext()->setNext(amazon);
                    return true;
                }
                else {
                    LetterNode *orderHere = alphabetize(letter);
                    if (nullptr == orderHere) { // New head
                        return true;
                    }
                    else if (orderHere->getNext() == nullptr) {
                        orderHere->setNext(new LetterNode(letter)); // New top letter
                        return true;
                    }
                    else {
                        amazon = orderHere->getNext();
                        orderHere->setNext(new LetterNode(letter));
                        orderHere->getNext()->setNext(amazon); // Insertion in the middle
                        return true;
                    }
                }
            }
        }

        int getFrequency(char letter) {
            // Given a capitalized letter
            LetterNode *foundNode = find(letter);
            // If the letter ISN'T in the list
            if (nullptr == foundNode || foundNode->getLetter() != letter) {
                return 0;
            } 
            return foundNode->getFrequency();
        }

        bool remove(char letter) { // Complete
            LetterNode *removeHere = head;
            LetterNode *tmp = nullptr;
            // If the letter is found
            if (nullptr == head->getLetter()) {
                cout << "Empty list." << endl;
                return false; // Empty list
            } else if (letter == head->getLetter()) {
                tmp = head;
                head = head->getNext(); // Reassigns head
                delete tmp;
                tmp = nullptr;
                return true; // The letter was found and removed
            }
            
            while (removeHere->getNext() != nullptr) {
                if (removeHere->getNext()->getLetter() == letter) {
                    tmp = removeHere->getNext();
                    removeHere->setNext(removeHere->getNext()->getNext()); // Fills the gap
                    delete tmp;
                    tmp = nullptr;
                    return true;
                }
                removeHere = removeHere->getNext();
            }
            // If the letter ISN'T in the list
            return false;
        }

        void print() {
            if (nullptr == head) {
                cout << "Empty list." << endl;
            }
            else {
                LetterNode *printHere = head;
                while (printHere != nullptr) {
                    cout << "| " << printHere->getLetter() << ":" << printHere->getFrequency() << " ";
                    printHere = printHere->getNext();
                }
                cout << "| " << endl;
            }
        }

        LetterNode *find(char letter) const { // Completed
            // Given a capitalized letter
            if (nullptr == head) {
                return nullptr; // Empty list
            }
            else if (head->getLetter() == letter) {
                return head;
            }
            else {
                LetterNode *lookHere = head;
                while (lookHere->getNext() != nullptr) {
                    if (lookHere->getLetter() == letter) {
                        return lookHere; // Returns match
                    }
                    lookHere = lookHere->getNext();
                }
                return lookHere; // Letter not found; returns insertion point (may conflict w/ sorted list)
            }
        }

    private:
        LetterNode *head; // The initial node
        // LetterNode *foundNode; // Saves a found letter node [one call to find() per class instance]

        void delist(LetterNode *node) { // Helper function, deletes nodes from END to FRONT recursively
            if (nullptr == node) {
                return;
            }
            delist(node->getNext());
            delete node;
            node = nullptr;
            return;
        }

        LetterNode *alphabetize(char letter) {
            LetterNode *alphaBet = head; // Saves the current node
            LetterNode *preNode = nullptr; // Saves the previous node
            LetterNode *amazon = nullptr;
            while (alphaBet != nullptr) {
                if (letter > alphaBet->getLetter()) {
                    preNode = alphaBet;
                    alphaBet = alphaBet->getNext();
                }
                else if (letter < head->getLetter()) {
                    amazon = new LetterNode(letter);
                    amazon->setNext(head);
                    head = amazon;
                    return nullptr; // The helper function helped, so there's nothing to return
                }
                else { // letter < alphaBet
                    return preNode;
                }
            }
            return preNode; // New top letter
        }
};
