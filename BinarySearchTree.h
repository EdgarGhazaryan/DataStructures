#pragma once

#include <stack>
#include <iostream>
template <typename T>
struct Node {
    Node(T info, Node<T>* left = nullptr, Node<T>* right = nullptr)
        : m_info(info), m_left(left), m_right(right) {}
    T m_info;
    Node<T>* m_left;
    Node<T>* m_right;
};
template <typename T>
class Binarytree {
private:
    Node<T>* m_root;
public:
    Binarytree() : m_root(nullptr) {};

    ~Binarytree();

    void insert(T);

    void remove(T);

    void preorder_traverse_It(void (*function)(T));

    void postorder_traverse_It(void (*function)(T));

    void inorder_traverse_It(void (*function)(T));

    void preorder_traverse(void(*function)(T));

    void postorder_traverse(void (*function)(T));

    void inorder_traverse(void (*function)(T));

    int height();

    int node();

    Node<T>* search(T);

    Node<T>* searchfather(T);

private:
    int node(Node<T>*);

    int height(Node<T>*);

    void destroy(Node<T>*);

    void insert(T, Node<T>*);

    void remove(T, Node<T>*);

    void preorder_traverse_It(Node<T>*, void (*function)(T));

    void postorder_traverse_It(Node<T>*, void (*function)(T));

    void inorder_traverse_It(Node<T>*, void (*function)(T));

    void preorder_traverse(Node<T>*, void (*function)(T));

    void postorder_traverse(Node<T>*, void (*function)(T));

    void inorder_traverse(Node<T>*, void (*function)(T));

    Node<T>* search(T, Node<T>*);

    Node<T>* searchfather(T, Node<T>*);
};
template <typename T>
Binarytree<T>::~Binarytree() { destroy(m_root); }
template <typename T>
void Binarytree<T>::inorder_traverse(Node<T>* t, void (*function)(T)) {
    if (t != nullptr) {
        inorder_traverse(t->m_left, function);
        std::cout << t->m_info << ',';
        inorder_traverse(t->m_right, function);
    }
}
template <typename T>
void Binarytree<T>::inorder_traverse(void (*function)(T)) {
    inorder_traverse(m_root,function);
    std::cout << std::endl;
}
template <typename T>
void Binarytree<T>::preorder_traverse(Node<T>* t, void (*function)(T)) {
    if (t != nullptr) {
        function(t->m_info);
        preorder_traverse(t->m_left,function);
        preorder_traverse(t->m_right,function);
    }
}
template <typename T>
void Binarytree<T>::preorder_traverse(void (*function)(T)) {
    preorder_traverse(m_root,function);
    std::cout << std::endl;
}
template <typename T>
void Binarytree<T>::postorder_traverse(Node<T>* t, void (*function)(T)) {
    if (t != nullptr) {
        postorder_traverse(t->m_left, function);
        postorder_traverse(t->m_right, function);
        function(t->m_info);
    }
}
template <typename T>
void Binarytree<T>::postorder_traverse(void (*function)(T)) {
    postorder_traverse(m_root, function);
    std::cout << std::endl;
}
template <typename T>
void Binarytree<T>::insert(T info, Node<T>* t) {
    if (info < t->m_info) {
        if (t->m_left != nullptr) {
            insert(info, t->m_left);
        }
        else {
            t->m_left = new Node<T>(info);
        }
    }
    else {
        if (t->m_right != nullptr) {
            insert(info, t->m_right);
        }
        else {
            t->m_right = new Node<T>(info);
        }
    }
}
template <typename T>
void Binarytree<T>::insert(T info) {
    if (m_root == nullptr) {
        m_root = new Node<T>(info);
    }
    else {
        insert(info, m_root);
    }
}
template <typename T>
void Binarytree<T>::remove(T element, Node<T>* t) {
    if (t != nullptr) {
        Node<T>* ptr1 = searchfather(element);
        Node<T>* ptr = search(element);
        if (ptr->m_left == nullptr && ptr->m_right == nullptr) {
            ptr1->m_left == ptr ? ptr1->m_left = nullptr : ptr1->m_right = nullptr;
            delete ptr;
            return;
        }
        if (ptr == m_root) {
            Node<T>* ptr2 = m_root->m_left;
            if (ptr2) {
                Node<T>* tmp = nullptr;
                if (ptr2->m_right == nullptr) {
                    m_root = ptr2;
                    m_root->m_right = ptr->m_right;
                    delete ptr;
                    return;
                }
                while (ptr2->m_right != nullptr) {
                    tmp = ptr2;
                    ptr2 = ptr2->m_right;
                }
                tmp->m_right = ptr2->m_left;
            }
            else {
                ptr2 = m_root->m_right;
                if (ptr2) {
                    Node<T>* tmp = nullptr;
                    if (ptr2->m_left == nullptr) {
                        m_root = ptr2;
                        m_root->m_left = ptr->m_left;
                        delete ptr;
                        return;
                    }
                    while (ptr2->m_left != nullptr) {
                        tmp = ptr2;
                        ptr2 = ptr2->m_left;
                    }
                    tmp->m_left = ptr2->m_right;
                }
            }
            ptr2->m_left = ptr->m_left;
            ptr2->m_right = ptr->m_right;
            m_root = ptr2;
            delete ptr;
            return;
        }
        else if (ptr->m_right == nullptr) {
            ptr1->m_right == ptr ? ptr1->m_right = ptr->m_left : ptr1->m_left = ptr->m_left;
            delete ptr;
            return;
        }
        else if (ptr->m_left == nullptr) {
            ptr1->m_left == ptr ? ptr1->m_left = ptr->m_right : ptr1->m_right = ptr->m_right;
            delete ptr;
            return;
        }
        else {
            Node<T>* tmp = ptr->m_left;
            while (tmp->m_right != nullptr) {
                tmp = tmp->m_right;
            }
            if (ptr1->m_left == ptr) {
                ptr1->m_left = tmp;
            }
            else {
                ptr1->m_right = tmp;
            }
            tmp->m_right = ptr->m_right;
            delete ptr;
            }
        }
   }

template<typename T>
void Binarytree<T>::remove(T element) {
    remove(element, m_root);
}
template <typename T>
void Binarytree<T>::destroy(Node<T>* t) {
    if (t != nullptr) {
        destroy(t->m_left);
        destroy(t->m_right);
        delete t;
    }
}
template <typename T>
Node<T>* Binarytree<T>::search(T info) {
    return search(info, m_root);
}
template <typename T>
Node<T>* Binarytree<T>::search(T info, Node<T>* t) {
    if (t != nullptr) {
        if (t->m_info == info) {
            return t;
        }
        else if (t->m_info > info) {
            return search(info, t->m_left);
        }
        else {
            return search(info, t->m_right);
        }
    }
    return nullptr;
}
template <typename T>
Node<T>* Binarytree<T>::searchfather(T info) {
    return searchfather(info, m_root);
}
template <typename T>
Node<T>* Binarytree<T>::searchfather(T info, Node<T>* t) {
    if (t != nullptr) {
        if (info == t->m_info) {
            return nullptr;
        }
        Node<T>* ptr = search(info);
        if (t->m_left == ptr || t->m_right == ptr) {
            return t;
        }
        else if (t->m_info > info) {
            return searchfather(info, t->m_left);
        }
        else {
            return searchfather(info, t->m_right);
        }
    }
    return nullptr;
}
template <typename T>
int Binarytree<T>::node() {
    return node(m_root);
}
template <typename T>
int Binarytree<T>::node(Node<T>* t) {
    if (t == nullptr) {return 0;}
    return node(t->m_left) + node(t->m_right) + 1;
}
template <typename T>
int Binarytree<T>::height() {
    return height(m_root);
}
template <typename T>
int Binarytree<T>::height(Node<T>* t) {
    if ((t == nullptr)||( t->m_left == nullptr && t->m_right == nullptr)){
        return 0;
    }
    int left = height(t->m_left);
    int right = height(t->m_right);
    if (left > right) {
        return left + 1;
    }
    else {
        return right + 1;
    }
}
template <typename T>
void Binarytree<T>::preorder_traverse_It(void (*function)(T)) {
    preorder_traverse_It(m_root, function);
}
template <typename T>
void Binarytree<T>::preorder_traverse_It(Node<T>* t, void (*function)(T)){
    Node<T>* ptr = t;
    std::stack<Node<T>*> s;
    while (true) {
        while (ptr != nullptr) {
            function(ptr->m_info);
            if (ptr->m_right != nullptr) {
                s.push(ptr->m_right);
            }
            ptr = ptr->m_left;
        }
        if (s.empty()) { break; }
            ptr = s.top();
            s.pop();
    }
}
template <typename T>
void Binarytree<T>::inorder_traverse_It(void (*function)(T)) {
    inorder_traverse_It(m_root, function);
}
template <typename T>
void Binarytree<T>::inorder_traverse_It(Node<T>* t, void (*function)(T)) {
    Node<T>* ptr = t;
    std::stack<Node<T>*> s;
    while (true) {
        while (ptr != nullptr) {
            s.push(ptr);
            ptr = ptr->m_left;
        }
        if (s.empty()) { break; }
        ptr = s.top();
        s.pop();
        function(ptr->m_info);
        ptr = ptr->m_right;
    }
}
template <typename T>
void Binarytree<T>::postorder_traverse_It(void (*function)(T)) {
    postorder_traverse_It(m_root, function);
}
template <typename T>
void Binarytree<T>::postorder_traverse_It(Node<T>* t, void (*function)(T)) {
    Node<T>* ptr = t;
    std::stack<Node<T>*> s;
    while (true) {
        while (ptr != nullptr ) {
            s.push(ptr);
            s.push(ptr);
            ptr = ptr->m_left;
        }
        if (s.empty()) { break; }
        ptr = s.top();
        s.pop();
        if (!s.empty() && s.top() == ptr) {
            ptr = ptr->m_right;
        }
        else {
            function(ptr->m_info);
            ptr = nullptr;
        }
    }
}
