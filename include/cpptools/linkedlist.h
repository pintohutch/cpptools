/** \file linkedlist.h
 * Basic linked list class template and methods.
 * Implementation courtesy of "Data structures and algorithm analysis in C++",
 * Fourth edition by Mark Allen Weiss.
 *
 * Copyright 2017 Daniel Clark
 */

// Define guard
#ifndef CPPTOOLS_LINKEDLIST_H_
#define CPPTOOLS_LINKEDLIST_H_

#include <cstddef>
#include <algorithm>

namespace cpptools {

/**
 * An implementation of a doubly linked list using templates to handle
 * generic data types. This class also uses sentinel nodes as empty head
 * and tail markers to remove special case handling in the methods.
 *
 * ||--|------|-->|---|-->|---|-->|------|
 *     | head |   | a |   | b |   | tail |
 *     |------|<--|---|<--|---|<--|------|--||
 */
template <typename T>
class LinkedList {
  // Internal classes
  private:
    /**
     * The Node private nested class serves to store the previous and next nodes
     * it references to, as well as a data payload.
     */
    struct Node {
      T data;
      Node* prev;
      Node* next;

      // lvalue constructor.
      Node(const T& d = T(), Node* p = nullptr, Node* n = nullptr) :
          data(d), prev(p), next(n) {}
      // rvalue constructor.
      Node(T&& d, Node* p = nullptr, Node* n = nullptr) :
          data( std::move(d) ), prev(p), next(n) {}
  };

  public:
    /**
     * The cons_iterator public nested class serves as a way to track position
     * as one iterates through the nodes of the list, allowing it to be used in
     * range-based for loops. The const_iterator returns a constant reference
     * upon using the * operator, to prevent mutating of the underlying node.
     *
     * This is particularly important when the list is declared as a constant
     * reference prior to iterating through it (as objects declared `const` can
     * only call `const` member functions).
     */
    class const_iterator {
      public:
        const_iterator() :
          current_(nullptr) {};

        // Read-only data payload via dereference of iterator.
        const T& operator* () const {
          return retrieve();
        }
        // Prefix increment (++itr)
        const_iterator& operator++ () {
          current_ = current_->next;
          return *this;
        }
        // Postfix increment (itr++) - i.e. increment after use.
        // Note: `int` arg is never used.
        // `this` keyword is always a pointer to its own address.
        const_iterator& operator++ (int) {
          // Copy constructor returns the non-incremented version.
          // NOTE: the default copy constructor is fine here. The reason being,
          // that the pointer is copied (still pointing to the same object) in
          // `old`, so when the ++(*this) occurs, `old.current_` is still
          // pointing to the previous object, but *this is pointing to the next.
          const_iterator old = *this;
          // Increment underlying object, so when it's next accessed,
          // it's incremented.
          ++(*this);
          return old;
        }
        bool operator== (const const_iterator& rhs) const {
          // Iterators refer to the same position in the list.
          return current_ == rhs.current_;
        }
        bool operator!= (const const_iterator& rhs) const {
          // Invoke the overloaded == operator and return the NOT (!) of that.
          return !(*this == rhs);
        }

      protected:
        Node* current_;

        T& retrieve() const {
          return current_->data;
        }

        explicit const_iterator(Node* p) :
          current_(p) {}

        // Allow LinkedList member functions to access private and protected
        // members of const_iterator.
        friend class LinkedList<T>;
    };

    /**
     * The iterator public nested class serves the same functionality as its
     * super-class, the const_iterator, but allows for mutability of the
     * underlying node.a way to track position
     */
    class iterator : public const_iterator {
      public:
        iterator() {}

        // Mutator dereference of iterator (not `const`-ness).
        T& operator* () {
          return const_iterator::retrieve();
        }

        // Read-only data payload via dereference of iterator (just call
        // const_iterator's implementation).
        // We need to declare this because otherwise, the new accessor method
        // hides the const_iterator * method, and will be invoked when an
        // instance dereferences the iterator to a `const` data variable.
        const T& operator* () const {
          return const_iterator::operator*();
        }

        // Prefix (++itr) incrementer implementation again because of the different
        // return types (but does hide base class).
        // Derived classes of template base classes need to explicitly use
        // `this` to access member variables.
        // See: https://stackoverflow.com/a/4643295/8826268
        iterator& operator++ () {
          this->current_ = this->current_->next;
          return *this;
        }

        // Postfix (itr++) incrementer implementation again because of the different
        // return types (but does hide base class).
        iterator operator++ (int) {
          iterator old = *this;
          ++(*this);
          return old;
        }

      protected:
        // Use base class initializer for constructor.
        explicit iterator(Node* p) :
          const_iterator(p) {}

        // Allow LinkedList member functions to access private and protected
        // members of iterator.
        friend class LinkedList<T>;

    };

  public:
    LinkedList() {
      init();
    }
    // Explicit guards against implicit type conversions - lvalue.
    explicit LinkedList(const T& d) {
      init();
      // NOTE: since the list is empty, push_front or push_back works here.
      push_front(d);
    }
    // Explicit guards against implicit type conversions - rvalue.
    explicit LinkedList(T&& d) {
      init();
      // NOTE: since the list is empty, push_front or push_back works here.
      push_front(d);
    }
    // Big Five
    // Overwriting defaults is necessary when data types are pointers.
    // Destructor
    ~LinkedList() {
      clear();
      delete head_;
      delete tail_;
    }
    // Copy constructor (lvalue const reference)
    LinkedList(const LinkedList& rhs) : size_(rhs.size_) {
      // Invoke LinkedNode's copy constructor.
    }
    // Move constructor (rvalue reference)
    //LinkedList(LinkedList&& rhs);
    // Copy assignment (lvalue const reference)
    //LinkedList& operator= (const LinkedList& rhs);
    // Move assignment (rvalue reference)
    //LinkedList& operator= (LinkedList&& rhs);

    // const keyword specifies accessor method - non-mutating.
    int size() const {
      return size_;
    }

    // const keyword specifies accessor method - non-mutating.
    bool empty() const {
      return size() == 0;
    }

    const_iterator begin() const {
      // Use aggregate initializer to return type (inferred from method
      // declaration). same as: return const_iterator{head_->next};
      return const_iterator(head_->next);
    }

    iterator begin() {
      return iterator(head_->next);
    }

    const_iterator end() const {
      return const_iterator(tail_);
    }

    iterator end() {
      return iterator(tail_);
    }

    // Inserts data as itr.current_'s previous node - lvalue data.
    iterator insert(iterator& itr, const T& data) {
      Node* p = itr.current_;
      Node* i = new Node(data, p->prev, p);
      p->prev->next = i;
      p->prev = i;
      size_++;
      return iterator(i);
    }

    // Inserts data as itr.current_'s previous node - lvalue data.
    iterator insert(iterator& itr, T&& data) {
      Node* p = itr.current_;
      size_++;
      // One-line version of the same logic.
      return iterator(p->prev = p->prev->next =
        new Node(std::move(data), p->prev, p));
    }

    // erase removes the `current_` node and returns the iterator corresponding
    // to the `next` node in the list.
    iterator erase(iterator& itr) {
      Node* p = itr.current_;
      // Remove references to p.
      p->prev->next = p->next;
      p->next->prev = p->prev;

      iterator ret(p->next);
      size_--;
      delete p;

      return ret;
    }

    // Insert a new node at the end of list (immediately preceding the tail
    // sentinel node) - lvalue.
    void push_back(const T& data) {
      insert(end(), data);
    }

    // Insert a new node at the end of list (immediately preceding the tail
    // sentinel node) - rvalue.
    void push_back(T&& data) {
      insert(end(), std::move(data));
    }

    // Insert a new node at the front of list (immediately following the head
    // sentinel node) - lvalue.
    void push_front(const T& data) {
      iterator b = begin();
      insert(b, data);
    }

    // Insert a new node at the front of list (immediately following the head
    // sentinel node) - rvalue.
    void push_front(T&& data) {
      iterator b = begin();
      insert(b, std::move(data));
    }

    // Remove the node at the front of the list (immediately following the head
    // sentinel node).
    void pop_front() {
      iterator b = begin();
      erase(b);
    }

    void clear() {
      while (!empty()) {
        pop_front();
      }
    }

  private:
    void init() {
      size_ = 0;
      head_ = new Node;
      tail_ = new Node;
      head_->next = tail_;
      tail_->prev = head_;
    }

    Node* head_;
    Node* tail_;
    int size_;
};

}

#endif //CPPTOOLS_LINKEDLIST_H_
