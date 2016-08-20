#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;

enum
{
    NONE,
    OPERAND,
    OPERATOR,
    L_PARA,
    R_PARA
};


int getType(char ch)
{
    return
        (ch >= '0' && ch <= '9')? OPERAND:
        (ch == '+' || ch == '*') ? OPERATOR:
        (ch == '(')? L_PARA:
        (ch == ')')? R_PARA:
        NONE;
}

int getIsp(char ch)
{
    int ret =
        (ch == '+')? 9:
        (ch == '*')? 10:
        (ch == '(')? 0:
        -1;

    assert(ret >= 0);
    return ret;
}

int getIcp(char ch)
{
    int ret =
        (ch == '+')? 9:
        (ch == '*')? 10:
        (ch == '(')? 20:
        -1;

    assert(ret >= 0);
    return ret;
}



vector<char> run(const char * expr)
{
    stack<char> st;
    vector<char> ret;

    while (*expr)
    {
        char ch = *expr;

        int type = getType(ch);

        switch (type)
        {
            case OPERAND:
                ret.push_back(ch);
                printf("%c", ch);
                break;
            case OPERATOR:
                while (!st.empty() && getIsp(st.top()) >= getIcp(ch))
                {
                    printf("%c", st.top());
                    ret.push_back(st.top());
                    st.pop();
                }
                st.push(ch);

                break;
            case L_PARA:
                st.push(ch);
                break;
            case R_PARA:
                while (st.top() != '(')
                {
                    printf("%c", st.top());
                    ret.push_back(st.top());
                    st.pop();
                }
                st.pop();

                break;
            case NONE:
            default:
                fprintf(stderr, "error\n");
                exit(-1);
                break;
        };

        ++expr;
    }

    while (!st.empty())
    {
        printf("%c", st.top());
        ret.push_back(st.top());
        st.pop();
    }
    return ret;
}

class TreeNode
{
public:
    TreeNode(void): left(NULL), right(NULL), val(0) {}
    TreeNode(char ch): left(NULL), right(NULL), val(ch) {}
    TreeNode * left;
    TreeNode * right;
    char val;

};

TreeNode * createTreeByPrefix(const vector<char>& expr)
{
    stack<TreeNode*> st;

    for (int i = 0; i < expr.size(); ++i)
    {
        char ch = expr[i];
        TreeNode * nd = new TreeNode(ch);

        if (getType(ch) == OPERAND)
        {
            st.push(nd);
        }
        else
        {
            TreeNode * op2 = st.top();
            st.pop();
            TreeNode * op1 = st.top();
            st.pop();

            nd->left = op1;
            nd->right = op2;
            st.push(nd);
        }

    }
    assert(st.size() == 1);
    return st.top();


}


void postorder(TreeNode * nd)
{
    if (!nd)
        return;
    postorder(nd->left);
    postorder(nd->right);
    printf("%c", nd->val);

}

void Inorder(TreeNode * nd)
{
    if (!nd)
        return;


    if (nd->left)
        printf("(");

    Inorder(nd->left);
    printf("%c", nd->val);
    Inorder(nd->right);

    if (nd->right)
        printf(")");

}

int main(int argc, const char * argv[])
{
    const char * expr = "1+(2+3)*4+5*6";
    printf("%s\n", expr);
    vector<char> postfix = run(expr);
    printf("\n");

    TreeNode * root = createTreeByPrefix(postfix);

    postorder(root);
    printf("\n");
    Inorder(root);
    printf("\n");

    return 0;
}
