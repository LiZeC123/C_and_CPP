#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <stdlib.h>


typedef int ElementType;

typedef struct AVLNode *Position;

typedef Position AVLTree; /* AVL树类型 */

struct AVLNode{
    ElementType Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};



AVLTree SingleLeftRotation ( AVLTree A );
AVLTree SingleRightRotation( AVLTree A );
AVLTree DoubleLeftRightRotation ( AVLTree A );
AVLTree DoubleRightLeftRotation( AVLTree A );
 

#endif
