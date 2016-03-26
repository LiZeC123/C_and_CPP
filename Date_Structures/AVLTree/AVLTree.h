#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <stdlib.h>


typedef int ElementType;

typedef struct AVLNode *Position;

typedef Position AVLTree; /* AVL������ */

struct AVLNode{
    ElementType Data; /* ������� */
    AVLTree Left;     /* ָ�������� */
    AVLTree Right;    /* ָ�������� */
    int Height;       /* ���� */
};



AVLTree SingleLeftRotation ( AVLTree A );
AVLTree SingleRightRotation( AVLTree A );
AVLTree DoubleLeftRightRotation ( AVLTree A );
AVLTree DoubleRightLeftRotation( AVLTree A );
 

#endif
