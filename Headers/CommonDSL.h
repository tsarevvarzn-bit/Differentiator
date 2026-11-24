#ifndef COMMONDSL_H
#define COMMONDSL_H

#define _NUM(x) createConstNode(x, NULL, NULL)
#define _ADD(x,y) createOpNode(ADD, x, y)
#define _SUB(x,y) createOpNode(SUB, x, y)
#define _MUL(x,y) createOpNode(MUL, x, y)
#define _DIV(x,y) createOpNode(DIV, x, y)
#define _POW(x,y) createOpNode(POW, x, y)

#define _CL createCopy(func_root_p->left_p)
#define _CR createCopy(func_root_p->right_p)

#define _DL differentiateSubtree(func_root_p->left_p)
#define _DR differentiateSubtree(func_root_p->right_p)

#define _SIN(x) createOpNode(SIN, x, NULL)
#define _COS(x) createOpNode(COS, x, NULL)
#define _LN(x) createOpNode(LN, x, NULL)

#endif
