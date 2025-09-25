#pragma once

#include <string>
#include <regex>
#include <iostream>

class AVLTree {
public:
    struct Node {
        std::string name;
        int id;
        Node* left;
        Node* right;
        int height;
        Node(const std::string& n, int i) : name(n), id(i), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root = nullptr;

    AVLTree() = default;

    bool isValidName(const std::string& name){
        std::regex nameRegex("^[A-Za-z ]+$");
        return std::regex_match(name, nameRegex);
    }

    bool isValidUFID(const std::string& id){
        std::regex idRegex("^[0-9]{8}$");
        return std::regex_match(id, idRegex);
    }

    void insert(const std::string& name, int id){
        if (isValidName(name) && isValidUFID(std::to_string(id))){
            bool inserted = false;
            root = insertRec(root, id, name, inserted);
            if (inserted) std::cout << "successful" << std::endl;
            else std::cout << "unsuccessful" << std::endl;
        } else {
            std::cout<<"unsuccessful"<<std::endl;
        }
    }

    int getHeight(Node* n){
        if (n==nullptr){
            return 0;
        }
        return n->height;
    }
    
    int getBalance(Node* n){
        if (n==nullptr){
            return 0;
        }
        return getHeight(n->left)-getHeight(n->right);
    }

    Node* leftRotate(Node* n){
        Node* r = n->right;
        if (r == nullptr) {
            return n;
        }
        Node* rl = r->left;

        r->left = n;
        n->right = rl;

        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        r->height = 1 + std::max(getHeight(r->left), getHeight(r->right));

        return r;
    }

    Node* rightRotate(Node* n){
        Node* l = n->left;
        if (l == nullptr) {
            return n;
        }
        Node* lr = l->right;

        l->right = n;
        n->left = lr;

        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
        l->height = 1 + std::max(getHeight(l->left), getHeight(l->right));

        return l;
    }

    Node* insertRec(Node* node, int key, const std::string& name, bool &inserted){
        if (node==nullptr){
            inserted = true;
            return new Node(name, key);
        }
        if (key<node->id){
            node->left=insertRec(node->left, key, name, inserted);
        } else if (key>node->id){
            node->right=insertRec(node->right, key, name, inserted);
        } else {
            inserted = false;
            return node;
        }

        node->height=1+std::max(getHeight(node->left), getHeight(node->right));
        int balance=getBalance(node);

        if (balance > 1 && key < node->left->id){
            return rightRotate(node);
        }

        if (balance < -1 && key > node->right->id){
            return leftRotate(node);
        }

        if (balance > 1 && key > node->left->id){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->id){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void remove(int key){
        bool deleted = false;
        root = removeRec(root, key, deleted);
        if (deleted){
            std::cout << "successful." << std::endl;
        }
        else{
            std::cout << "unsuccessful." << std::endl;
        }
    }

        Node* minValueNode(Node* node){
            Node* current = node;
            while (current != nullptr && current->left != nullptr){
                current = current->left;
            }
            return current;
        }

        Node* removeRec(Node* node, int key, bool &deleted){
            if (node == nullptr) return node;

            if (key < node->id) {
                node->left = removeRec(node->left, key, deleted);
            } else if (key > node->id) {
                node->right = removeRec(node->right, key, deleted);
            } else {
               
                deleted = true;
             
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    delete node;
                    return temp;
                }

              
                Node* succ = minValueNode(node->right);
        
                node->id = succ->id;
                node->name = succ->name;
              
                bool del = false;
                node->right = removeRec(node->right, succ->id, del);
            }

         
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
            return node;
        }

    void printInOrder(Node* node) {
        std::vector<std::string> out;
        std::function<void(Node*)> inorder = [&](Node* n){
            if (!n) return;
            inorder(n->left);
            out.push_back(n->name);
            inorder(n->right);
        };
        inorder(node);
        for (size_t i = 0; i < out.size(); ++i){
            if (i) std::cout << ",";
            std::cout << out[i];
        }
        std::cout << std::endl;
    }

    void printPreOrder(Node* node) {
        std::vector<std::string> out;
        std::function<void(Node*)> preorder = [&](Node* n){
            if (!n) return;
            out.push_back(n->name);
            preorder(n->left);
            preorder(n->right);
        };
        preorder(node);
        for (size_t i = 0; i < out.size(); ++i){
            if (i) std::cout << ",";
            std::cout << out[i];
        }
        std::cout << std::endl;
    }

    void printPostOrder(Node* node) {
        std::vector<std::string> out;
        std::function<void(Node*)> postorder = [&](Node* n){
            if (!n) return;
            postorder(n->left);
            postorder(n->right);
            out.push_back(n->name);
        };
        postorder(node);
        for (size_t i = 0; i < out.size(); ++i){
            if (i) std::cout << ",";
            std::cout << out[i];
        }
        std::cout << std::endl;
    }

    void searchByID(int id){
        Node* cur = root;
        while (cur){
            if (id == cur->id){
                std::cout << cur->name << std::endl;
                return;
            } else if (id < cur->id) cur = cur->left;
            else cur = cur->right;
        }
        std::cout << "unsuccessful" << std::endl;
    }

    void searchByName(const std::string& name){
        bool found = false;
        if (!root) {
            std::cout << "unsuccessful" << std::endl;
            return;
        }
        std::vector<Node*> stack;
        stack.push_back(root);
        while (!stack.empty()){
            Node* cur = stack.back(); stack.pop_back();
            if (cur->name == name){
                std::cout << cur->id << std::endl;
                found = true;
            }
            if (cur->right) stack.push_back(cur->right);
            if (cur->left) stack.push_back(cur->left);
        }
        if (!found) std::cout << "unsuccessful" << std::endl;
    }

    void printLevelCount(){
        if (!root) { std::cout << 0 << std::endl; return; }
        std::cout << getHeight(root) << std::endl;
    }

    void removeInorder(int N){
        std::vector<Node*> nodes;
        std::function<void(Node*)> inorder = [&](Node* n){
            if (!n) return;
            inorder(n->left);
            nodes.push_back(n);
            inorder(n->right);
        };
        inorder(root);
        if (N < 0 || N >= (int)nodes.size()){
            std::cout << "unsuccessful" << std::endl;
            return;
        }
        int id = nodes[N]->id;
        bool deleted = false;
        root = removeRec(root, id, deleted);
        if (deleted) std::cout << "successful" << std::endl;
        else std::cout << "unsuccessful" << std::endl;
    }
};

 
