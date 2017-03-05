#include <iostream>
#include "MovieTree.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

MovieTree::MovieTree()
{

    opCount = 1;
    Assignment6Output = json_object_new_object();
    MovieNode *nilNode = new MovieNode;
    nilNode->isRed = false;
    root = nilNode;

}

MovieTree::~MovieTree()
{
    DeleteAll(root);

    // Clean up json object
    json_object_put(Assignment6Output);
}

/* Used to delete all nodes in the tree */
void MovieTree::DeleteAll(MovieNode * node)
{
    // clean to the left
    if (node->leftChild != nilNode)
        DeleteAll(node->leftChild);
    // clean to the right
    if (node->rightChild != nilNode)
        DeleteAll(node->rightChild);
    // delete this node
    delete node;

    return;
}

void MovieTree::initJson()
{
    Assignment6Output = json_object_new_object();
}

/* Helper for the printMovieInventory recursive function */
void MovieTree::printMovieInventory()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    printMovieInventory(root,travLog);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("traverse");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);

    opCount++;

    return;
}

/* Prints the inventory(in order traversal) */
void MovieTree::printMovieInventory(MovieNode * node, json_object * traverseLog)
{

    // Left Node
    if(node->leftChild!=nilNode)
        printMovieInventory(node->leftChild,traverseLog);

    // Value
    cout<<"Movie: "<<node->title<< endl;

    // Update the traversal log
    json_object *curTitle = json_object_new_string(node->title.c_str());
    json_object_array_add(traverseLog, curTitle);

    // Right Node
    if(node->rightChild!=nilNode)
        printMovieInventory(node->rightChild,traverseLog);

    return;
}



void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    //cout << "entered!\n";
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();
    // Create a log for the traversal
    json_object * travLog = json_object_new_array();

    // Create the node we will be inserting
    MovieNode * newMovie = new MovieNode(ranking,title,releaseYear,quantity);
    MovieNode * x = root;
    MovieNode * y = NULL;

    // Do we have an empty tree?
    if (root == nilNode)
        root = newMovie;

    // If the tree is not empty
    else
    {

        // Get to the end of the tree, where we need to add this node.
        while (x != nilNode)
        {
            // Add the current node to the traversal log before moving to next.
            json_object *curTitle = json_object_new_string(x->title.c_str());
            json_object_array_add(travLog, curTitle);

            y = x;
            if(newMovie->title.compare(x->title) < 0)
                x = x->leftChild;
            else
                x = x->rightChild;

        }

        // set the parent of this node to be the previous node.
        newMovie->parent = y;

        // Determine which child to this previous node we are at.
        if (newMovie->title.compare(y->title) < 0)
            y->leftChild = newMovie;
        else
            y->rightChild = newMovie;
    }
    rbInsert(newMovie);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("add");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonTitle = json_object_new_string(title.c_str());
    json_object_object_add(newJSON,"parameter",jsonTitle);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
    opCount++;

    return;

}

/* used to find movie information, provides info or says movie can't be found */
void MovieTree::findMovie(std::string title)
{
    // Create a traversal log
    json_object * travLog = json_object_new_array();
    // Find the movie
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);
    if (foundMovie != NULL)
    {
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << foundMovie->ranking << endl;
        cout << "Title:" << foundMovie->title << endl;
        cout << "Year:" << foundMovie->year << endl;
        cout << "Quantity:" << foundMovie->quantity << endl;
    }
    else
        cout << "Movie not found." << endl;

    return;
}

MovieNode* MovieTree::searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog)
{
    // Add the current node to the traverse log
    if (node != nilNode)
    {
        json_object *curTitle = json_object_new_string(node->title.c_str());
        json_object_array_add(traverseLog, curTitle);
    }

    // If the node is NULL, we just return. Failed to find node.
    if (node == nilNode)
        return NULL;
    // Return this node if it is the one we are searching for
    else if (node->title == title)
        return node;

    // Else return the correct recursive call.
    else
    {
        if(title.compare(node->title) < 0)
            return searchMovieTree(node->leftChild,title,traverseLog);

        else
            return searchMovieTree(node->rightChild,title,traverseLog);
    }
}

void MovieTree::rentMovie(std::string title)
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    int stockOutput = 0;

    json_object * travLog = json_object_new_array();
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);

    // If the movie exists.
    if (foundMovie != nilNode)
    {
        // If it's in stock.
        if (foundMovie->quantity > 0)
        {
            cout << "Movie has been rented." << endl;
            foundMovie->quantity--;
            stockOutput = foundMovie->quantity;

            // Update our json object
            json_object *jsonOperation = json_object_new_string("rent");
            json_object_object_add(newJSON,"operation",jsonOperation);
            json_object *jsonTitle = json_object_new_string(title.c_str());
            json_object_object_add(newJSON,"parameter",jsonTitle);
            json_object *jsonOutput = json_object_new_string(to_string(stockOutput).c_str());
            json_object_object_add(newJSON,"output",jsonOutput);
            json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);

            opCount++;

            //change this to print information
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
            // If the stock is 0 delete the movie
            if (foundMovie->quantity == 0)
                deleteMovieNode(foundMovie->title);

        }
        // If it's not in stock.
        else
            cout << "Movie out of stock." << endl;

    }
    // If it doesn't exist.
    else
        cout << "Movie not found." << endl;

}

void MovieTree::deleteMovieNode(std::string title)
{

    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    json_object * travLog = json_object_new_array();
    MovieNode * foundMovie = searchMovieTree(root,title,travLog);

    // If the movie exists
    if (foundMovie != nilNode)
    {
        // If it has no children
        if (foundMovie->leftChild == nilNode && foundMovie->rightChild == nilNode)
        {
            // If this node is the left child, set the parents left child to NULL
            if (foundMovie->parent->leftChild == foundMovie)
                foundMovie->parent->leftChild = nilNode;
            // Else, this node is the right child, set that to NULL
            else
                foundMovie->parent->rightChild = nilNode;
            // Delete the node
            delete foundMovie;

        }
        // If it only has a left child
        else if (foundMovie->rightChild == nilNode)
        {
            if (foundMovie->parent->leftChild == foundMovie)
                foundMovie->parent->leftChild = foundMovie->leftChild;
            else
                 foundMovie->parent->rightChild = foundMovie->leftChild;

            delete foundMovie;

        }
        // If it only has a right child
        else if (foundMovie->leftChild == nilNode)
        {
            if (foundMovie->parent->leftChild == foundMovie)
                foundMovie->parent->leftChild = foundMovie->rightChild;
            else
                 foundMovie->parent->rightChild = foundMovie->rightChild;

            delete foundMovie;
        }

        // Node has two children, we need the smallest node from the right child
        else
        {
            // Start on the right sub-tree
            MovieNode * replacementNode = foundMovie->rightChild;

            // search for the smallest left child
            while (replacementNode->leftChild != nilNode)
            {
                replacementNode = replacementNode->leftChild;
            }

            // Swap in all the info from the replacement to this node we are "deleting"
            foundMovie->title = replacementNode->title;
            foundMovie->quantity = replacementNode->quantity;
            foundMovie->ranking = replacementNode->ranking;
            foundMovie->year = replacementNode->year;


            // If the replacement node has a right child, update the parent
            if (replacementNode->rightChild != nilNode)
                replacementNode->rightChild->parent = replacementNode->parent;

            // If the replacement node is a left child
            if (replacementNode->parent->leftChild == replacementNode)
                replacementNode->parent->leftChild = replacementNode->rightChild;
            // If it is a right child
            else
                replacementNode->parent->rightChild = replacementNode->rightChild;

            // Delete the node
            delete replacementNode;
        }

        // Update our json object
        json_object *jsonOperation = json_object_new_string("delete");
        json_object_object_add(newJSON,"operation",jsonOperation);
        json_object *jsonTitle = json_object_new_string(title.c_str());
        json_object_object_add(newJSON,"parameter",jsonTitle);
        json_object_object_add(newJSON,"output",travLog);
        json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
        opCount++;

    }
    // If it doesn't exist
    else
        cout << "Movie not found." << endl;



}

int MovieTree::countMovieNodes()
{
    // Create the json object for this operation
    json_object * newJSON = json_object_new_object();

    // Determine the count
    int count = countMovieNodes(root);

    // Update our json object
    json_object *jsonOperation = json_object_new_string("count");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonOutput = json_object_new_string(to_string(count).c_str());
    json_object_object_add(newJSON,"output",jsonOutput);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
    opCount++;

    return count;
}

int MovieTree::countMovieNodes(MovieNode *node)
{
    if (node == nilNode)
        return 0;
    return countMovieNodes(node->leftChild) + countMovieNodes(node->rightChild) + 1;
}

json_object* MovieTree::getJsonObject()
{
    return Assignment6Output;
}

void MovieTree::rbInsert(MovieNode *temp)
{
    temp->leftChild = nilNode;
    temp->rightChild = nilNode;
    temp->isRed = true;
    MovieNode *newMovie = new MovieNode;
    while ((temp != root) && (temp->parent->isRed)){
        if( temp->parent == temp->parent->parent->leftChild ) {
            newMovie = temp->parent->parent->rightChild;
            if(newMovie != NULL && newMovie->isRed){
              temp->parent->isRed = false;
              newMovie->isRed = false;
              temp->parent->parent->isRed = true;
              temp = temp->parent->parent;
            }
            else {
                if(temp == temp->parent->rightChild ) {
                temp = temp->parent;
                leftRotate(temp);
            }
              temp->parent->isRed = false;
              temp->parent->parent->isRed = true;
              rightRotate(temp->parent->parent);
         }
        }
        else{
            //cout << "temp" << temp->title << endl;
            //cout << "temp parent" << temp->parent->title << endl;
            //cout << "temp->parent->parent->left" << temp->parent->parent->leftChild->title << endl;
                newMovie = temp->parent->parent->leftChild;
                if(newMovie != NULL && newMovie->isRed){
                    temp->parent->isRed = false;
                    newMovie->isRed = false;
                    temp->parent->parent->isRed = true;
                    temp = temp->parent->parent;
                }
                else{
                    if(temp == temp->parent->leftChild ) {
                        temp = temp->parent;
                        rightRotate(temp);
                      }
                      temp->parent->isRed = false;
                      temp->parent->parent->isRed = true;
                      leftRotate(temp->parent->parent);
                    }
                }


    }

    root->isRed = false;
}
void MovieTree::rightRotate(MovieNode *node)
{
    MovieNode *x = new MovieNode;
    x = node->leftChild;
    node->leftChild = x->rightChild;
    if(x->rightChild != nilNode){
        x->rightChild->parent = node;
    }
    x->parent = node->parent;
    if(node->parent == nilNode)
    {
        root = x;
    }
    else if(node == node->parent->leftChild)
    {
        node->parent->leftChild = node;
    }
    else
    {
        node->parent->rightChild = node;
    }
    x->rightChild = node;
    node->parent = x;
}

void MovieTree::leftRotate(MovieNode * node)
{

    MovieNode *y = new MovieNode;
    y = node->rightChild;
    node->rightChild = y->leftChild;
    if(y->leftChild != nilNode)
    {
        y->leftChild->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == nilNode)
    {
        root = y;
    }
    else if(node == node->parent->leftChild)
    {
        node->parent->leftChild = y;
    }
    else
    {
        node->parent->rightChild = y;
    }
    y->leftChild = node;
    node->parent = y;
}
void MovieTree::rbTransplant(MovieNode * u, MovieNode * v)
{
    if(u->parent == nilNode)
    {
        root = v;
    }
    else if(u == u->parent->leftChild)
    {
        u->parent->leftChild= v;
    }
    else{
        u->parent->rightChild = v;
    }
    v->parent = u->parent;
}

MovieNode* MovieTree::treeMinimum(MovieNode *x)
{
    while(x->leftChild != nilNode)
    {
        x = x->leftChild;
    }
    return x;
}

void MovieTree::rbDelete(std::string title)
{
    json_object * newJSON = json_object_new_object();
    json_object * travLog = json_object_new_array();

    MovieNode *z = searchMovieTree(root,title,travLog);
    MovieNode *y = new MovieNode;
    MovieNode *x = new MovieNode;
    y = z;
    if(y != NULL){
        original_color = y->isRed;
        if(z->leftChild == nilNode)
        {
            x = z->rightChild;
            rbTransplant(z, z->rightChild);
        }
        else if(z->rightChild == nilNode)
        {
            x = z->leftChild;
            rbTransplant(z, z->leftChild);
        }
        else{
            y = treeMinimum(z->rightChild);
            original_color = y->isRed;
            x = y->rightChild;
            if(x != NULL && y->parent == z){
                //cout << "xparent" << x->parent << endl;
                //cout << "y" << y << endl;
                x->parent = y;
            }
            else{
                rbTransplant(y, y->rightChild);
                y->rightChild = z->rightChild;
                y->rightChild->parent = y;
            }
            rbTransplant(z, y);
            y->leftChild = z->leftChild;
            y->leftChild->parent = y;
            y->isRed = z->isRed;
        }
    }
        if(!y->isRed)
            rbDeleteFixup(x);

    json_object *jsonOperation = json_object_new_string("delete");
    json_object_object_add(newJSON,"operation",jsonOperation);
    json_object *jsonTitle = json_object_new_string(title.c_str());
    json_object_object_add(newJSON,"parameter",jsonTitle);
    json_object_object_add(newJSON,"output",travLog);
    json_object_object_add(Assignment6Output,to_string(opCount).c_str(),newJSON);
    opCount++;

}

void MovieTree::rbDeleteFixup(MovieNode *x)
{
    MovieNode *w = new MovieNode;
    while(x != root && x->isRed == false)
    {
        if(x == x->parent->leftChild)
        {
            w = x->parent->rightChild;
            if(w->isRed)
            {
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->rightChild;
            }
            if(w->rightChild->isRed == false && w->leftChild->isRed == false)
            {
                w->isRed = true;
                x = x->parent;
            }
            else{
                if(w->rightChild->isRed == false)
                {
                    w->leftChild->isRed = false;
                    w->isRed = true;
                    rightRotate(w);
                    w = x->parent->rightChild;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->rightChild->isRed = false;
                leftRotate(x->parent);
                x = root;

            }
        }
        else{
            w = x->parent->leftChild;
            if(w->isRed)
            {
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->leftChild;
            }
            if(w->leftChild->isRed == false && w->rightChild->isRed == false)
            {
                w->isRed = true;
                x = x->parent;
            }
            else{
                if(w->leftChild->isRed == false)
                {
                    w->rightChild->isRed = false;
                    w->isRed = true;
                    leftRotate(w);
                    w = x->parent->leftChild;
                }
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->leftChild->isRed = false;
                rightRotate(x->parent);
                x = root;

        }

        }
    }
}
