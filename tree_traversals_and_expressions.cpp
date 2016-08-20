#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <deque>
#include <vector>
#include <assert.h>

using namespace std;

//TO DO:
//iterative traversals,
//imp_postorder(root), postorder().

//---Expressions---//
enum
{
    NONE = 0,
    OPERAND,
    OPERATOR,
    L_PARA,
    R_PARA
};

int getType(string ch)
{
    return
        ( ch[0] >= '0' && ch[0] <= '9' )? OPERAND:
        ( ch == "*" || ch == "/" )? OPERATOR:
        ( ch == "+" || ch == "-" )? OPERATOR:
        ( ch == "(" )? L_PARA:
        ( ch == ")" )? R_PARA:
        NONE;
}

int getIcp(string ch)
{
    int ret =
        ( ch == "*" || ch == "/" )? 10:
        ( ch == "+" || ch == "-" )? 9:
        ( ch == "(")? 20:
        -1;
    assert(ret >= 0); //to debug
    return ret;
}

int getIsp(string ch)
{
    int ret =
        ( ch == "*" || ch == "/" )? 10:
        ( ch == "+" || ch == "-" )? 9:
        ( ch == "(")? 0:
        -1;
    assert(ret >= 0); //to debug
    return ret;
}

bool isNumber(char c)
{
    return c >= '0' && c <= '9';
}

vector<string> str2Expr(const char * str) //to a 'separated string'
{
    vector<string> ret;
    while (*str)
    {
        int ps_num = strspn(str, "0123456789");
        int ps_op = strspn(str, "()+-*/");

        if (ps_op)
            ps_op = 1;

        int pos = max(ps_num, ps_op); //to differeentiate consetutive num and op
        char buf[16] = {0};
        strncpy(buf, str, pos);
        str += pos;
        ret.push_back(string(buf));
    }

    for (int i = 0; i < ret.size(); ++i)
    {
        printf("%s", ret[i].c_str());
    }
    printf("\n");

    return ret;
}

vector<string> infix2Postfix(vector<string> str)
{
    stack<string> st;
    vector<string> ret;

    for (int r = 0; r < str.size(); ++r)
    {
        string tmp = str[r];
        int type = getType(tmp);
        switch(type)
        {
            case OPERAND:
                ret.push_back(tmp);
                break;
            case OPERATOR:
                while ( !(st.empty()) && getIcp(tmp) < getIsp(st.top()) )
                {
                    ret.push_back(st.top());
                    st.pop();
                }
                st.push(tmp);
                break;
            case L_PARA:
                st.push(tmp);
                break;
            case R_PARA:
                while(st.top() != "(")
                {
                    ret.push_back(st.top());
                    st.pop();
                }
                st.pop();
                break;
            case NONE:
            default:
                fprintf(stderr, "Error!\n"); //to debug
                exit(-1);
                break;
        };
    }

    while (!st.empty()) //pop the rest remined in the stack
    {
        ret.push_back(st.top());
        st.pop();
    }

    for (int i = 0; i < ret.size(); ++i) //print the result
    {
        printf("%s ", ret[i].c_str());
    }
    printf("\n");

    return ret;
}

//---Tree traversals---//
template <class T>
class TreeNode
{
public:
    TreeNode<T>(void);
    TreeNode<T>(T v);

    T val;
    TreeNode<T>* left;
    TreeNode<T>* right;
    void preorder(TreeNode<T> *root);
    void inorder(TreeNode<T> *root);
    void postorder(TreeNode<T> *root);
    void freeTree(TreeNode<T> *root);
    bool isOperand(string str);
    int evalTreePost(TreeNode<T> *node);
    void showHumanRep(TreeNode<T> *node);
    TreeNode<T>* postfix2ParseTree(vector<string> str);
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
TreeNode<T>* TreeNode<T>::postfix2ParseTree(vector<string> str)
{

    deque< TreeNode<string>* > q;
    for (int i = 0; i < str.size(); ++i)
    {
        TreeNode<string> *node = new TreeNode<string>(str[i]);
        q.push_back(node);
    }

    stack< TreeNode<string>* > st;
    while (!q.empty())
    {
        TreeNode<string>* nd = q.front();
        q.pop_front();

        string tmp = nd->val;

        if (nd->isOperand(tmp))
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
                new TreeNode<string>(tmp);

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

    //---Tree traversals---//
    cout << "Tree traversals:" << endl;
    Nodes[0]->preorder(Nodes[0]);
    //printf("str\n");
    cout << "\n";
    Nodes[0]->inorder(Nodes[0]);
    cout << "\n";
    Nodes[0]->postorder(Nodes[0]);

    //---Infix to postfix---//
    const char * str = "(12+34)*45";
    cout << endl;
    cout << "String to Expression:" << endl; // Expression means a 'separated string'
    vector<string> expr = str2Expr(str);
    cout << "Expression to Postfix:" << endl;
    vector<string> buf = infix2Postfix(expr);

    //---Postfix to Parse tree---//
    TreeNode<string> *root = new TreeNode<string>();
    root = root->postfix2ParseTree(buf);

    //---Parse tree goes each traversal---//
    cout << "Parse tree goes Preorder:" << endl;
    root->preorder(root);
    cout << endl;
    cout << "Parse tree goes Inorder:" << endl;
    root->showHumanRep(root); //inorder with paratheses
    cout << endl;
    cout << "Parse tree goes Postorder:" << endl;
    root->postorder(root);
    cout << endl;

    return 0;
}
