# avltree
This is a quick implementation of a type-agnostic AVL tree in C++.
I mostly followed [this](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/) guide,
but made some small changes here and there and added a bit of functionality.

## "Installation"
Just copy the header file into your project folder and include it somewhere.
I can't be bothered to make a makefile for something this simple.

## Usage
This tree functions like a ```vector``` or any type-agnostic data structure, meaning that you have to tell it what kind of data you want to store in it. I wrote five functions for manipulating and printing the data: ```insert()```, ```remove()```, ```find()```, ```printContents()``` and ```deleteTree()```. Here's an example that uses all of them:
```
#include "avltree.hpp"
#include <iostream>

using namespace std;

int main(){
    avltree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);

    if(tree.find(30)) cout << "Found it!" << endl;
    tree.remove(30);
    if(tree.find(30)) cout << "Found it!" << endl;

    tree.printContents();
    
    tree.deleteTree();
    return 0;
}
```
This outputs:
```
./exec
Found it!
10
20
40
```
You should always call ```deleteTree()``` last to free up memory, but you don't need to call a constructor of any kind. ```printContents``` is really only useful if ```std::cout``` can parse the type you choose to use, but it's a nice and quick way to check if the data you're trying to store has actually been inserted.
### Multiple trees with the same data type
If you want to create multiple trees with the same data type, you don't actually need to create different tree objects for it, one will do. Instead, create a ```node``` pointer of the same type as your tree, initialize it to ```NULL``` and feed it as the first argument to any of the functions, and that will be you new "tree". I like to think of them as seeds, but whatever. Here's what I mean:
```
#include "avltree.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
    avltree<std::string> tree;
    tree.insert("ten");
    tree.insert("twenty");
    tree.insert("thirty");

    node<std::string>* seed = NULL;
    tree.insert(seed, "ten");
    tree.insert(seed, "forty");
    tree.insert(seed, "thirty");
    tree.insert(seed, "fifty");

    if(tree.find("fifty")) cout << "Found fifty in tree!" << endl;
    if(tree.find(seed, "fifty")) cout << "Found fifty in seed!" << endl;

    tree.deleteTree();
    tree.deleteTree(seed);
    return 0;
}
```
And the output:
```
./exec
Found fifty in seed!
```
Just remember to also delete the seed.
