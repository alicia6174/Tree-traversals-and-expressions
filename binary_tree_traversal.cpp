#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <deque>
#include <vector>

using namespace std;

//TO DO: preorder/inorder to postorder (priority),
//converting,
//iterative traversals,
//postorder()...

template <class T>
class TreeNode
{
public:
    TreeNode<T>(void);
    TreeNode<T>(T v);

    T val;
    TreeNode<T> *left;
    TreeNode<T> *right;
    void preorder(TreeNode<T> *root);
    void inorder(TreeNode<T> *root);
    void postorder(TreeNode<T> *root);
    void freeTree(TreeNode<T> *root);
    bool isOperand(string str);
    int evalTreePost(TreeNode<T> *node);
    void showHumanRep(TreeNode<T> *node);
    TreeNode<T>* postorderToParseTree(string str);
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
void TreeNode<T>::preorder(TreeNode<T> *root)
{
    if (!root) return;
    cout << "[" << root->val << "]";
    root->preorder(root->left);
    root->preorder(root->right);
}

template <class T>
void TreeNode<T>::inorder(TreeNode<T> *root)
{
    if (!root) return;
    root->inorder(root->left);
    cout << "[" << root->val << "]";
    root->inorder(root->right);
}

template <class T>
void TreeNode<T>::postorder(TreeNode<T> *root)
{
    if (!root) return;
    root->postorder(root->left);
    root->postorder(root->right);
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

template <class T>
bool TreeNode<T>::isOperand(string str)
{
    bool r = (str[0] >= '0' && str[0] <= '9')? true: false;

    return r;
}

template <class T>
int TreeNode<T>::evalTreePost(TreeNode<T> * node)
{
    if (!node)
    {
        fprintf(stderr, "error!\n");
        exit(-1);
        return 0;
    }

    int a1, a2;

    if (node->left)
        a1 = node->evalTreePost(node->left);
    if (node->right)
        a2 = node->evalTreePost(node->right);

    if (node->isOperand(node->val))
    {
        return atoi(node->val.c_str());
    }

    string op = node->val;

    return (op == "+")? a1 + a2:
           (op == "-")? a1 - a2:
           (op == "*")? a1 * a2:
           999;
}

template <class T>
void TreeNode<T>::showHumanRep(TreeNode<T> * node)
{

    if (node->left)
    {
        printf("(");
        node->showHumanRep(node->left);
    }

    printf("%s", node->val.c_str());
    //cout << node->val;

    if (node->right)
    {
        node->showHumanRep(node->right);
        printf(")");
    }
}

template <class T>
TreeNode<T>* TreeNode<T>::postorderToParseTree(string str)
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
        TreeNode<string>* nd = q.front();
        q.pop_front();

        string buf = nd->val;

        if (nd->isOperand(buf))
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

enum
{
    NONE = 0,
    OPERAND,
    OPERATOR,
    L_PARA,
    R_PARA
};

int getType(char ch)
{
    return
        ( ch >= '0' && ch <= '9' )? OPERAND:
        ( ch == '*' || ch == '/' )? OPERATOR:
        ( ch == '+' || ch == '-' )? OPERATOR:
        ( ch == '(' )? L_PARA:
        ( ch == ')' )? R_PARA:
        NONE;
}

int getIcp(char ch)
{
    return
        ( ch == '*' || ch == '/' )? 10:
        ( ch == '+' || ch == '-' )? 9:
        ( ch == '(')? 20:
        -1;
}

int getIsp(char ch)
{
    return
        ( ch == '*' || ch == '/' )? 10:
        ( ch == '+' || ch == '-' )? 9:
        ( ch == '(')? 0:
        -1;
}

int main(int argc, const char *argv[])
{
    {
        const char * str = "(1+2)*3";
        stack<char> st;
        vector<char> vec;
        while(*str)
        {
            char ch = *str;
            int type = getType(ch);
            switch(type)
            {
                case OPERAND:
                    printf("%c",ch);
                    vec.push_back(ch);
                    break;
                case OPERATOR:
                    while ( !(st.empty()) && getIcp(ch) < getIsp(st.top()) )
                    {
                        printf("%c",st.top());
                        vec.push_back(st.top());
                        st.pop();
                    }
                    st.push(ch);
                    break;
                case L_PARA:
                    st.push(ch);
                    break;
                case R_PARA:
                    while(st.top() != '(')
                    {
                        printf("%c",st.top());
                        vec.push_back(st.top());
                        st.pop();
                    }
                    st.pop();
                    break;
                case NONE:
                    break;
            };
            str++;
        }

        while (!st.empty())
        {
            printf("%c", st.top());
            st.pop();
        }
        printf("\n");


        {

            string str_ret;
            for (int i = 0; i < vec.size(); ++i)
            {
                str_ret.push_back(vec[i]);
            }

        }

        return 0;
    }

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
    Nodes[0]->preorder(Nodes[0]);
    //printf("str\n");
    cout << "\n";
    Nodes[0]->inorder(Nodes[0]);
    cout << "\n";
    Nodes[0]->postorder(Nodes[0]);

    //---Postorder to parse tree---//
    string str = "12+3*";
    TreeNode<string>* root = new TreeNode<string>();
    root = root->postorderToParseTree(str);
    root->postorder(root);

    cout << endl;
    cout << "Eval = " << root->evalTreePost(root) << endl;
    cout << "Human Repre.: ";
    root->showHumanRep(root);
    cout << endl;

    return 0;
}
