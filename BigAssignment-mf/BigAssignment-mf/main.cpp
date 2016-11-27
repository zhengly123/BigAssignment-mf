  // created by lyc. level 1, level 2, level 3 has been finished.
#include <iostream>
#include "MagicCube.h"
using namespace std;
int lf[8]={1,4,3,2,1,4,3,2};  // lf = lateral face, [0] = green, [1] = orange, [2] = blue, [3] = red;
MagicCube a, b, c;  // assume that cube is the cube that we are going to restore in function level 1 to 7
bool bts(int a1, int a2, int a3)  // bts = big to small
{
    if (a1>a2 && a2>a3)
        return 1;
    return 0;
}
bool b50(int a0)  // between 5 and 0
{
    if (5>a0 && a0>0)
        return 1;
    return 0;
}
struct line
{
    int direct,time;
};
bool cb(MagicCube *cube, int face, int color)  // cb = check block.
{
    if (cube->query(face,color) == make_pair(face,color))
        return 1;
    return 0;
}
pii mp(int first, int second)  // mp is short for make_pair
{
    return make_pair(first, second);
}
pii cline(MagicCube precube, int face1, int pos1, int face2, int pos2)  // 用来检查是否能只旋转一面（不包括中间那一面）达到目标地点，pos = position, 输出第二块以顺时针按照(第一个输出）方向转（第二个输出）次能够到达第一块的位置，不能做到则输出1，0. 如果不用转，输出0，0.
{
    int i0,j0;
    MagicCube v = precube;
    if (face1==face2 && pos1==pos2)
        return make_pair(0, 0);
    for (i0=0; i0<6; i0++)
    {
        v = precube;
        for (j0=1; j0<=3; j0++)
        {
            v.rotate(i0,0);
            if ((v.num[face1][pos1] == precube.num[face2][pos2]) && (v.color[face1][pos1] == precube.color[face2][pos2]))
                return make_pair(i0,j0);
        }
    }
    return make_pair(-1,0);
}  // complete
void vlateralch(MagicCube *aimc, bool clockwise)  // view lateral change, aimc = aim cube. If clockwise view lateral change looked from the top, green turn to orange. suspicious
{
    MagicCube a0;
    int i0,j0=1,j1,k0;
    for (k0=0; k0<4; k0++)
    {
        if (clockwise)
            j1 = lf[3-k0];
        else
            j1 = lf[(k0+1)%4];
        for (i0=0; i0<9; i0++)
        {
            a0.num[j0][i0] = aimc->num[j1][i0];
            a0.color[j0][i0] = aimc->color[j1][i0];
        }
        j0 = j1;
    }
    aimc->rotate(0,!clockwise);
    aimc->rotate(5,clockwise);
    for (i0=0; i0<9; i0++)
    {
        a0.num[5][i0] = aimc->num[5][i0];
        a0.color[5][i0] = aimc->color[5][i0];
    }
    for (i0=0; i0<9; i0++)
    {
        a0.num[0][i0] = aimc->num[0][i0];
        a0.color[0][i0] = aimc->color[0][i0];
    }
    *aimc = a0;
    cout << "view lateral change " << clockwise << ".\n";
}  // preparative work completed
void level1()  // 底层十字架
{
    const pii notro = make_pair(0,0), unable = make_pair(1,0);  // notro = not rotate.
    MagicCube vir = c;  // vir = virtural cube
    int i,k,t,gpot;  //face represents the face going to rotate in each step. gpot = goal position on top
    pii ppo,rodir,rodir2;  // ppo = present position. gpo = goal position. rodir = rotate direction.
    bool finish;  // finish = finish one piece.
    for (i=1; i<8; i+=2)
    {
        finish = false;
        t = 0;
        if ((i == 3) || (i == 5))
            gpot = i;
        else
            gpot = 8-i;
        while ((!finish) && (t<100))
        {
            ppo = c.query(0, i);
            rodir = cline(c, 0, i, ppo.first, ppo.second);
            if (rodir == notro)
            {
                finish = true;
                break;
            }
            if (ppo.first == 0)  // 目标在底层，放到顶层
            {
                if (ppo.second == 1)
                {
                    c.rotate(1);
                    c.rotate(1);
                }
                if (ppo.second == 3)
                {
                    c.rotate(2);
                    c.rotate(2);
                }
                if (ppo.second == 5)
                {
                    c.rotate(4);
                    c.rotate(4);
                }
                if (ppo.second == 7)
                {
                    c.rotate(3);
                    c.rotate(3);
                }
                ppo = c.query(0, i);
            }
            rodir = cline(c, 0, i, ppo.first, ppo.second);
            if ((ppo.first != 1) && (ppo.first != 5) && (rodir == unable))  // 目标在中间层，转到顶层
            {
                if (ppo.second == 1)  // 中间层的底部，转到中间层的中间
                {
                    c.rotate(ppo.second, 0);
                    ppo = c.query(0, i);
                }
                if (ppo.second == 7)  // 中间层的上部，转到中间层的中间
                {
                    int bg,rotatetime=0;  // bg = goal
                    if (i <= 3)
                        bg = (i+1) / 2;
                    else
                        bg = (13-i) / 2;
                    while (c.query(0, i).first != bg)
                    {
                        c.rotate(5,0);
                        rotatetime += 1;
                    }
                    c.rotate(bg, 0);
                    for (k=0; k<rotatetime; k++)
                        c.rotate(5, 1);
                }
                if (ppo.second == 3 || ppo.second == 5)  // 中间层的中间，转到顶层
                {
                    for (k=2; k<=9; k++)
                    {
                        vir = c;
                        vir.rotate(k/2, k%2);
                        if (vir.query(0, i).first == 5)
                        {
                            c.rotate(k/2, k%2);
                            break;
                        }
                    }
                    c.rotate(5,0);
                    c.rotate(k/2, (k+1)%2);
                    ppo = c.query(0, i);
                }
            }
            
            if (ppo.first == 5)  // 目标在顶层，放到gpot
            {
                while (c.query(0,i).second != gpot)
                    c.rotate(5,0);
                ppo = c.query(0, i);
            }
            rodir = cline(c, 0, i, ppo.first, ppo.second);  // 当直接可以转到位置
            if ((rodir != unable) && (rodir.first != 0))
            {
                for (k=0; k<rodir.first; k++)
                    c.rotate(rodir.first,0);
                finish = true;
            }
            t += 1;
        }
        if (t >= 100)
            cout << "level 1 failed\n";
    }
}  // complete
void l2for()  // level 2 formula.
{
    c.rotate(2,1);
    c.rotate(5,1);
    c.rotate(2,0);
    c.rotate(5,0);
}
void level2()  // 底角
{
    int i,t=0,rotatetime;
    pii ppo,rodir;
    MagicCube vir = c;
    for (i=0; i<9; i+=2)
    {
        if (i == 4)
            i = 6;
        while (c.query(0, 0) != make_pair(0, 0) && t < 400)
        {
            ppo = c.query(0, 0);  //
            if (ppo == make_pair(0, 0))  // don't need rotate
                break;
            if ((ppo.first<5) && (ppo.second > 5))  // If ppo not on top level, move it to top;
            {
                rotatetime=0;
                while (ppo != make_pair(1,6) && ppo != make_pair(2,8))  // 白色不在（0，0）及其相邻位置时
                {
                    rotatetime += 1;
                    c.rotate(0,0);
                    ppo = c.query(0,0);
                }
                l2for();
                while (rotatetime != 4)
                    c.rotate(0,0);
                ppo = c.query(0,0);
            }
            if  (!(ppo.first<5) && (ppo.second > 5)) // ppo on top
            {
                while (c.query(0,0) != make_pair(5,6) && c.query(0,0) != make_pair(1,0) && c.query(0,0) != make_pair(2,2))
                    c.rotate(5);  // 白色不在（5，6）及其相邻位置时
                while (c.query(0,0) != make_pair(0,0))// 当转到顶上
                    l2for();
            }
            t += 1;
        }
        vlateralch(&c,false);
        if (t>=400)
            cout << "level 2 failed";
    }
}  // level 2 completed
void l3for(bool right)
{
    if (right)
    {
        c.rotate(5,0);
        c.rotate(4,0);
        c.rotate(5,1);
        c.rotate(4,1);
        c.rotate(5,1);
        c.rotate(1,1);
        c.rotate(5,0);
        c.rotate(1,0);
    }
    else
    {
        c.rotate(5,1);
        c.rotate(2,1);
        c.rotate(5,0);
        c.rotate(2,0);
        c.rotate(5,0);
        c.rotate(1,0);
        c.rotate(5,1);
        c.rotate(1,1);
    }
}
bool isib(MagicCube cu, int num) // isib = is side block. 只能用于目标在正面, num = 3 or 5.
{
    if ((num==3 && b50(cu.color[1][3]) && b50(cu.color[2][5]))
        || (num==5 && b50(cu.color[1][5]) && b50(cu.color[4][3])))
        return 1;
    return 0;
}
void level3()
{
    pii ppo;
    int t=0,i,finish=0,j;
    for (i=1; i<=4; i++)  // 把中间层全部移到顶上
    {
        if (isib(c,3) && c.color[2][5] != 2 && c.color[1][3] != 1)
        {
            while (b50(c.color[1][1]) && b50(c.color[5][7]))
                c.rotate(5,0);
            l3for(false);
        }
        vlateralch(&c, true);
    }
    while (finish < 4)
    {
        for (i=1; i<5; i++)
            if (c.color[i][1] == i)
            {
                for (j=1; j<=i-1; j++)
                    vlateralch(&c,false);
                if (c.color[5][7] == 2)
                    l3for(false);
                if (c.color[5][7] == 4)
                    l3for(true);
                if (c.color[5][7] != 2 && c.color[5][7] != 4)  // test
                    cout << "level 3 aalgorithm wrong.\n";
                    l3for(true);
                for (j=1; j<=i-1; j++)
                    vlateralch(&c,true);
                finish += 1;
            }
        c.rotate(5,0);
    }
    if (t>=400)
        cout << "level 3 failed.\n";
}  // level 3 completed
void l4for1()  // f,u,r,ui,ri,fi
{
    c.rotate(1,0);
    c.rotate(5,0);
    c.rotate(4,0);
    c.rotate(5,1);
    c.rotate(4,1);
    c.rotate(1,1);
}
void l4for2()  // f,r,u,ri,ui,fi
{
    c.rotate(1,0);
    c.rotate(4,0);
    c.rotate(5,0);
    c.rotate(4,1);
    c.rotate(5,1);
    c.rotate(1,1);
}
int yline(MagicCube cube)  // yellow line. If there is yellow blocks in (5,1) (5,7), return 1. The other kind of yellow line return 2. If no yellow line, return 0.
{
    if (cube.color[5][1] == 5 && cube.color[5][7] == 5)
        return 1;
    if (cube.color[5][3] == 5 && cube.color[5][5] == 5)
        return 2;
    return 0;
}
int ycor(MagicCube cube)  // yellow corner. If (5,1)(5,3) return 1. If (5,3)(5,7) return 2
{
    if (cube.color[5][1] == 5 && cube.color[5][3] == 5)
        return 1;
    if ((cube.color[5][3] == 5 && cube.color[5][7] == 5) ||
        (cube.color[5][7] == 5 && cube.color[5][5] == 5) ||
        (cube.color[5][5] == 5 && cube.color[5][1] == 5))
        return 2;
    return 0;
}
void l4for3()  // r,b,ri,b,r,b,b,ri
{
    c.rotate(4,0);
    c.rotate(5,0);
    c.rotate(4,1);
    c.rotate(5,0);
    c.rotate(4,0);
    c.rotate(5,0);
    c.rotate(5,0);
    c.rotate(4,1);
}
void level4cross()
{
    if (!yline(c) && !ycor(c))
    {
        l4for1();
        level4cross();
    }
    else
    {
        if (yline(c) == 1)
            c.rotate(5,0);
        if (yline(c) == 2)
        {
            l4for2();
            return;
        }
        if (ycor(c))
        {
            while (ycor(c) != 1)
                c.rotate(5,0);
            l4for1();
            return;
        }
    }
}
void level4()
{
    level4cross();
    
}
int main()
{
    c.randomize(200);
    level1();
    level2();
    c.output();
    
    
    return 0;
}
