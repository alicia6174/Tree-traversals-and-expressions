#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <deque>

using namespace std;

template <class T>
class TreeNode
{
public:
    TreeNode<T>(void);
    TreeNode<T>(T v);

    T val;
    TreeNode<T> *left;
    TreeNode<T> *right;
    void Preorder(TreeNode<T> *root);
    void Inorder(TreeNode<T> *root);
    void Postorder(TreeNode<T> *root);
    void freeTree(TreeNode<T> *root);
};

template <class T>
TreeNode<T>::TreeNode(void):
    val(),
    left(NULL),
    right(NULL)
{

}

template <class T>
TreeNode<T>::TreeNode(T  v):
    val(v),
    left(NULL),
    right(NULL)
{

}

template <class T>
void TreeNode<T>::Preorder(TreeNode<T> *root)
{
    if (!root) return;
    cout << "[" << root->val << "]";
    root->Preorder(root->left);
    root->Preorder(root->right);
}

template <class T>
void TreeNode<T>::Inorder(TreeNode<T> *root)
{
    if (!root) return;
    root->Inorder(root->left);
    cout << "[" << root->val << "]";
    root->Inorder(root->right);
}

template <class T>
void TreeNode<T>::Postorder(TreeNode<T> *root)
{
    if (!root) return;
    root->Postorder(root->left);
    root->Postorder(root->right);
    cout << "[" << root->val << "]";
}

template <class T>
void TreeNode<T>::freeTree(TreeNode<T> *root)
{
    if (!root) return;
    root->freeTree(root->left);
    root->freeTree(root->right);
    root->left = root->right = NULL;
    free(root);
}

bool isOperand(char c)
{
    return (c >= '0' && c <= '9')? true: false;
}

int main(int argc, const char *argv[])
{
    {
        string str = "12+3*";
        deque< TreeNode<char>* > q;
        for (int i = 0; i < str.size(); ++i)
        {
            TreeNode<char> *tmp = new TreeNode<char>(str[i]);
            q.push_back(tmp);
        }

        stack< TreeNode<char>* > st;
        while (!q.empty())
        {
            TreeNode<char>  * nd = q.front();
            q.pop_front();

            char c = nd->val;

            if (isOperand(c))
            {
                st.push(nd);
            }
            else
            {
                TreeNode<char> * n2 = st.top();
                st.pop();

                TreeNode<char> * n1 = st.top();
                st.pop();

                TreeNode<char> * nnd =
                    new TreeNode<char>(c);

                nnd->left = n1;
                nnd->right = n2;
                st.push(nnd);
            }

        }

        TreeNode<char> * root = st.top();
        root->Postorder(root);

        cout << endl;
    }
    return 0;

    //---Construct a tree---//
    TreeNode<int> * Nodes[16];
    for (int i = 0; i < 16; ++i)
    {
        Nodes[i] = new TreeNode<int>(i);
        //Wrong: Nodes[i] = Nodes[i]->getNewNode(i);
        //since Nodes[i] is empty.
    }

    Nodes[0]->left = Nodes[1];
    Nodes[0]->right = Nodes[2];
    Nodes[1]->left = Nodes[3];
    Nodes[1]->right = Nodes[4];
    //Nodes[2]->left = Nodes[5];
    Nodes[2]->right = Nodes[6];

    //---Tree traversal---//
    Nodes[0]->Preorder(Nodes[0]);
    cout << "\n";
    Nodes[0]->Inorder(Nodes[0]);
    cout << "\n";
    Nodes[0]->Postorder(Nodes[0]);



    return 0;
}
