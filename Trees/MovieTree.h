#ifndef MOVIETREE_H
#define MOVIETREE_H

#include <json/json.h>

struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    bool isRed;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        // Now that we are using nil these NULL's should be overwritten in addMovieNode.
    	leftChild = NULL;
    	rightChild = NULL;
        parent = NULL;
        isRed = true;
    }

};

class MovieTree
{
        int opCount = 0;

    public:
        MovieTree();
        virtual ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title);
        void DeleteAll();
        void rbDelete(std::string title);
        bool isValid();
        int countLongestPath();
        //use this to return the json object from the class when you are ready to write it to a file
        json_object* getJsonObject();

    protected:

    private:
        void DeleteAll(MovieNode * node);//done
        void rbInsert(MovieNode *x); //done
        void initJson();
        void printMovieInventory(MovieNode * node, json_object * traverseLog);//done
        void rbAddFixup(MovieNode * node); //done
        void leftRotate(MovieNode * x); //done
         /**needs work**/
        void rightRotate(MovieNode * x); //done
        void rbDeleteFixup(MovieNode * node); /**needs work**/
        void rbTransplant(MovieNode * u, MovieNode * v); //done
        int rbValid(MovieNode * node); //dont know
        int countMovieNodes(MovieNode *node);//done
        int countLongestPath(MovieNode *node);/**needs work**/
        MovieNode* searchMovieTree(MovieNode * node, std::string title, json_object * traverseLog);//done
        MovieNode* treeMinimum(MovieNode *x);
        MovieNode *root;
        MovieNode *nilNode;
        bool original_color;
        int movieCounter = 0;
        // Count of how many operations we have done.
        //including the json_object in the class makes it global within the class, much easier to work with
        json_object * Assignment6Output = json_object_new_object();


};

#endif // MOVIETREE_H
