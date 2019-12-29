#ifndef GRID_H
#define GRID_H
#include <QVector>
/*
 *一个网格类，采用xy坐标系
 * 其实就是把二维的QVector<QVector<T>>进行封装，防止出现坐标问题。。
 *
 * |----width----|
 * XXXXXXXXXXXXXX
 * XXXXXXXXXXXXXX
 * XXXXXXXXXXXXXX
 *(x,y)坐标系和Qt默认坐标系相同
 *
 *  (0,0)(1,0)(2,0)
 *     ------------------->x
 *(0,1)|XXXXXXXXXXXXXX
 *(0,2)|XXXXXXXXXXXXXX
 *(0,3)|XXXXXXXXXXXXXX
 *     y
 */
template <typename T>
class Grid
{
private:
    QVector<QVector<T>> data;
    int width;
    int height;
public:
    Grid(int width,int height,T val);
    void set(int x,int y,T val);
    T get(int x,int y)const;
    int getHeight(){return height;}
    int getWidth(){return  width;}
    int transpose();
    void upSideDown();
    void flipLeftRight();
    void rightRotate();
    void rotation();
    void antiRotation();
};
template<typename T>
Grid<T>::Grid(int width, int height,T val):width(width),height(height)
{
    for(int i = 0;i<height;i++)
        data.push_back(QVector<T>(width, val));
}

template<typename T>
void Grid<T>::set(int x, int y, T val)
{
    data[y][x] = val;
}

template<typename T>
int Grid<T>::transpose()
{
    if(width != height)return -1;
    for(int i = 0;i<width;i++)
        for(int j = 0;j<i;j++)
            std::swap(data[i][j],data[j][i]);
    return 0;
}

template<typename T>
void Grid<T>::upSideDown()
{
    for(int i = 0;i<height/2;i++)
        for(int j = 0;j<width;j++)
            std::swap(data[i][j],data[height-1-i][j]);
}

template<typename T>
void Grid<T>::flipLeftRight()
{
    for(int i = 0;i<width;i++)
        for(int j = 0;j<height/2;j++)
            std::swap(data[i][j],data[i][width-j-1]);
}

template<typename T>
void Grid<T>::rotation()
{
    transpose();
    flipLeftRight();
}

template<typename T>
void Grid<T>::antiRotation()
{
    transpose();
    upSideDown();
}

template<typename T>
T Grid<T>::get(int x, int y)const
{
    return data[y][x];
}
#endif // GRID_H
