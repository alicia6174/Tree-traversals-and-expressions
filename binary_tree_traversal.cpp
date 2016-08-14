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
TreeNode<T>::TreeNode(T v):
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

bool isOperand(string str)
{
    return (str[0] >= '0' && str[0] <= '9')? true: false;
}

int EvalTreePost(TreeNode<string> * node)
{
    if (!node)
    {
        fprintf(stderr, "error!\n");
        exit(-1);
        return 0;
    }

    int a1, a2;

    if (node->left)
        a1 = EvalTreePost(node->left);
    if (node->right)
        a2 = EvalTreePost(node->right);

    if (isOperand(node->val))
    {
        return atoi(node->val.c_str());
    }

    string op = node->val;

    return (op == "+")? a1 + a2:
           (op == "-")? a1 - a2:
           (op == "*")? a1 * a2:
           999;
}

void showHumanRep(TreeNode<string> * node)
{

    if (node->left)
    {
        printf("(");
        showHumanRep(node->left);
    }

    printf("%s", node->val.c_str());
    //cout << node->val;

    if (node->right)
    {
        showHumanRep(node->right);
        printf(")");
    }
}

TreeNode<string>* PostorderToParseTree(string str)
{
    deque< TreeNode<string>* > q;
    for (int i = 0; i < str.size(); ++i)
    {
        char buf[2] = {0};
        buf[0] = str[i];
        TreeNode<string> *tmp = new TreeNode<string>(buf);
        q.push_back(tmp);
    }

    stack< TreeNode<string>* > st;
    while (!q.empty())
    {
        TreeNode<string>  * nd = q.front();
        q.pop_front();

        string buf = nd->val;

        if (isOperand(buf))
        {
            st.push(nd);
        }
        else
        {
            TreeNode<string> * n2 = st.top();
            st.pop();

            TreeNode<string> * n1 = st.top();
            st.pop();

            TreeNode<string> * nnd =
                new TreeNode<string>(buf);

            nnd->left = n1;
            nnd->right = n2;
            st.push(nnd);
        }

    }

    TreeNode<string> * root = st.top();
    return root;
}


int main(int argc, const char *argv[])
{
    {
        string str = "12+3*";
        TreeNode<string>* root = new TreeNode<string>();
        root = PostorderToParseTree(str);
        root->Postorder(root);

        cout << endl;
        cout << "eval = " << EvalTreePost(root) << endl;
        showHumanRep(root);
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
