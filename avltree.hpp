#include <iostream>

template<typename T>
struct node{
    node *left;
    node *right;
    int height;
    T value;
    int hashvalue;
};

template<typename T>
class avltree{

    public:
        node<T>* insert(T value){
            return root = _insert(root, value);
        }

        node<T>* remove(T value){
            return root = _remove(root, value);
        }

        node<T>* insert(node<T>* &noder, T value){
            return noder = _insert(noder, value);
        }

        node<T>* remove(node<T>* &noder, T value){
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            return noder = _remove(noder, value);
        }

        void deleteTree(){
            deleteTree(root);
        }
        void deleteTree(node<T>* noder){
            if(noder != NULL){
                if(noder->left != NULL){
                    deleteTree(noder->left);
                }
                if(noder->right != NULL){
                    deleteTree(noder->right);
                }
            }
            delete noder;
        }

        void printContents(){
            printContents(root);
        }

        void printContents(node<T>* noder){
            if(noder != NULL){
                std::cout << noder->value << std::endl;
                if(noder->left != NULL){
                    printContents(noder->left);
                }
                if(noder->right != NULL){
                    printContents(noder->right);
                }
            }
        }

        bool find(T value){
            return find(root, value);
        }

        bool find(node<T>* noder, T value, int hashvalue = 0){
            if(hashvalue == 0){
                hashvalue = std::hash<T>()(value);
            }
            if(noder != NULL){

                if(hashvalue < noder->hashvalue){
                    return find(noder->left, value, hashvalue);
                } else if (hashvalue > noder->hashvalue){
                    return find(noder->right, value, hashvalue);
                } else if ( value == noder->value){
                    return true;
                }

                return false;
            }
            return false;

        }

    private:

        node<T>* root = NULL;

        node<T>* createNode(T value, int hash = 0){
            if(hash == 0){
                hash = std::hash<T>()(value);
            }
            node<T>* newNode = new node<T>();
            newNode->right = NULL;
            newNode->left = NULL;
            newNode->height = 0;
            newNode->value = value;
            newNode->hashvalue = hash;

            return newNode;
        }

        int getHeight(node<T>* noder){
            if(noder == NULL){
                return 0;
            }
            return noder->height;
        }

        int getBalance(int l, int r){
            return l-r; // if >1, leans to the left, if <-1, leans to the right
        }

        node<T>* turnLeft(node<T>* noder){
            node<T>* X = noder->right;
            node<T>* Y = X->left;

            X->left = noder;
            noder->right = Y;

            X->height = std::max(getHeight(X->left),
                                getHeight(X->right) + 1);
            noder->height = std::max(getHeight(noder->left),
                                getHeight(noder->right) + 1);
            return X;

        }
        node<T>* turnRight(node<T>* noder){
            node<T>* X = noder->left;
            node<T>* Y = X->right;

            X->right = noder;
            noder->left = Y;

            X->height = std::max(getHeight(X->left),
                                getHeight(X->right) + 1);
            noder->height = std::max(getHeight(noder->left),
                                getHeight(noder->right) + 1);


            return X;
        }

        node<T>* minValueNode(node<T>* noder){
            node<T>* current = noder;
            while(current->left != NULL){
                current = current->left;
            }
            return current;
        }

        node<T> * _insert(node<T>* noder, T value, int hashvalue = 0){
            if(hashvalue == 0){
                hashvalue = std::hash<T>()(value);
            }

            if(noder == NULL){
                return createNode(value, hashvalue);
            }
            if(hashvalue < noder->hashvalue){
                noder->left = _insert(noder->left, value, hashvalue);
            } else if(hashvalue > noder->hashvalue){
                noder->right = _insert(noder->right, value, hashvalue);
            } else{
                return noder;
            }

            //handle rotations etc
            //get height of right branch and height of left branch
            int l = getHeight(noder->left);
            int r = getHeight(noder->right);
            int balance = getBalance(l, r);

            if(balance > 1 && hashvalue < noder->left->hashvalue){
                //leftLeft
                return turnRight(noder);
            } else if (balance > 1 && hashvalue > noder->left->hashvalue){
                //leftRight
                noder->left = turnLeft(noder->left);
                return turnRight(noder);
            } else if (balance < -1 && hashvalue < noder->right->hashvalue){
                //rightLeft
                noder->right = turnRight(noder->right);
                return turnLeft(noder);
            } else if (balance < -1 && hashvalue > noder->right->hashvalue){
                //rightRight
                return turnLeft(noder);
            }

            return noder;
        }

        node<T>* _remove(node<T>* noder, T value, int hashvalue = 0){
            if(noder == NULL){
                return noder;
            }
            if(hashvalue == 0){
                hashvalue = std::hash<T>()(value);
            }

            if(hashvalue < noder->hashvalue){
                noder->left = _remove(noder->left, value, hashvalue);
            } else if (hashvalue > noder->hashvalue){
                noder->right = _remove(noder->right, value, hashvalue);
            } else {
                //if there is only one child (or no children)
                if((noder->left == NULL) || (noder->right == NULL)){
                    node<T>* temp = noder->left ? noder->left : noder->right;
                    //zero children
                    if(temp == NULL){
                        temp = noder;
                        noder = NULL;
                    } else { //one child
                        *noder = *temp;
                    }
                    delete temp;

                } else { // there are two children
                    node<T>* temp = minValueNode(noder->right);
                    noder->value = temp->value;
                    noder->hashvalue = temp->hashvalue;
                    noder->right =  _remove(noder->right, temp->value);
                }
            }

            if(noder == NULL){
                return noder;
            }

            //get balance
            int l = getHeight(noder->left);
            int r = getHeight(noder->right);
            int balance = getBalance(l, r);

            if(balance > 1 && hashvalue < noder->left->hashvalue){
                //leftLeft
                return turnRight(noder);
            } else if (balance > 1 && hashvalue > noder->left->hashvalue){
                //leftRight
                noder->left = turnLeft(noder->left);
                return turnRight(noder);
            } else if (balance < -1 && hashvalue < noder->right->hashvalue){
                //rightLeft
                noder->right = turnRight(noder->right);
                return turnLeft(noder);
            } else if (balance < -1 && hashvalue > noder->right->hashvalue){
                //rightRight
                return turnLeft(noder);
            }

            return noder;
        }
};
