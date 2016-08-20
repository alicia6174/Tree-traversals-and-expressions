### Classification of trees ###
1. Tree.
2. Binary tree.

\* The following focuses on binary tree only.<br />
\* The data of each tree node is of int type.

### Methods of constructing a binary tree ###
1. Array - root[i], left\_node[2i], right\_node[2i+1].
2. Linked list - array of pointers to nodes, including data, left\_node, and right\_node.

### Tree traversals ###
1. Preorder - root, left node, right node.
2. Inorder - left node, root, right node.
3. Postorder - left node, right node, root.

### Methods of implementing postorder ###
1. Recursive.
2. Iterative.

### Arithmetic expression ###
1. Prefix - \*+123
2. Infix - (1+2)*3
(for human use, including parentheses)
3. Postfix - 12+3\*

### Methods of converting expressions ###
1. Construct the parse tree.

   Fix one of the traversals, for example, the postorder.
   Use one Queue and one Stack to construct the parse tree.
   
   ```
   Steps:
   
   1. First put the string into the queue.
   
   2. At each time of dequeuing -
   If the dequeued one is an operand, then push it into the stack. 
   If the dequeued  one is an operator, then set it as a root. 
   And pop the previous two operands in the stack. 
   Set the first popped one as the right node. 
   Set the second one as the left node. 
   Then push the root into the stack.
   
   3. The last root remained in the stack will be the one of the parse tree.
   ```
 
 Doing any of the three kinds of traversals, we will get the corresponding expression.
2. Set the priority of operators.
(To be continued)

### Evaluation ###
Use all of the expressions to obtain different values.