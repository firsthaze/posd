#ifndef UTSORT_H
#define UTSORT_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
#include <vector>
#include <string>
using namespace std;
TEST (Sort, sortByIncreasingPerimeter) {
    vector<string> NameList;
    Rectangle r(0,0,2,2);   //perimeter = 8
    Circle c(0,0,2);        //perimeter = 12.56
    vertex vertex1,vertex2, vertex3;
    vertex1.x = 0;
    vertex1.y = 0;
    vertex2.x = 0;
    vertex2.y = 3;
    vertex3.x = 4;
    vertex3.y = 0;
    Triangle t(vertex1, vertex2, vertex3); // perimeter = 12
    list<Shape *> ShapeList;
    ShapeList.push_back(&r);
    ShapeList.push_back(&c);
    ShapeList.push_back(&t);
    Sort::sortByIncreasingPerimeter(&ShapeList);
    for(Shape* shape : ShapeList)
    {
        NameList.push_back(shape->getShapeName());
    }
    ASSERT_EQ("r", NameList.at(0));
    ASSERT_EQ("t", NameList.at(1));
    ASSERT_EQ("c", NameList.at(2));
}

TEST (Sort, sortByDecreasingPerimeter) {
    vector<string> NameList;
    Rectangle r(0,0,2,2);   //perimeter = 8
    Circle c(0,0,2);        //perimeter = 12.56
    vertex vertex1,vertex2, vertex3;
    vertex1.x = 0;
    vertex1.y = 0;
    vertex2.x = 0;
    vertex2.y = 3;
    vertex3.x = 4;
    vertex3.y = 0;
    Triangle t(vertex1, vertex2, vertex3); // perimeter = 12
    list<Shape *> ShapeList;
    ShapeList.push_back(&r);
    ShapeList.push_back(&c);
    ShapeList.push_back(&t);
    Sort::sortByDecreasingPerimeter(&ShapeList);
    for(Shape* shape : ShapeList)
    {
        NameList.push_back(shape->getShapeName());
    }
    ASSERT_EQ("c", NameList.at(0));
    ASSERT_EQ("t", NameList.at(1));
    ASSERT_EQ("r", NameList.at(2));
}

TEST (Sort, sortByIncreasingArea) {
    vector<string> NameList;
    Rectangle r(0,0,2,2);   //perimeter = 8 area = 4
    Circle c(0,0,2);        //perimeter = 12.56 area = 12.56
    vertex vertex1,vertex2, vertex3;
    vertex1.x = 0;
    vertex1.y = 0;
    vertex2.x = 0;
    vertex2.y = 3;
    vertex3.x = 4;
    vertex3.y = 0;
    Triangle t(vertex1, vertex2, vertex3); // perimeter = 12 area = 6
    list<Shape *> ShapeList;
    ShapeList.push_back(&r);
    ShapeList.push_back(&c);
    ShapeList.push_back(&t);
    Sort::sortByIncreasingArea(&ShapeList);
    for(Shape* shape : ShapeList)
    {
        NameList.push_back(shape->getShapeName());
    }
    ASSERT_EQ("r", NameList.at(0));
    ASSERT_EQ("t", NameList.at(1));
    ASSERT_EQ("c", NameList.at(2));
}

TEST (Sort, sortByDecreasingArea) {
    vector<string> NameList;
    Rectangle r(0,0,2,2);   //perimeter = 8 area = 4
    Circle c(0,0,2);        //perimeter = 12.56 area = 12.56
    vertex vertex1,vertex2, vertex3;
    vertex1.x = 0;
    vertex1.y = 0;
    vertex2.x = 0;
    vertex2.y = 3;
    vertex3.x = 4;
    vertex3.y = 0;
    Triangle t(vertex1, vertex2, vertex3); // perimeter = 12 area = 6
    list<Shape *> ShapeList;
    ShapeList.push_back(&r);
    ShapeList.push_back(&c);
    ShapeList.push_back(&t);
    Sort::sortByDecreasingArea(&ShapeList);
    for(Shape* shape : ShapeList)
    {
        NameList.push_back(shape->getShapeName());
    }
    ASSERT_EQ("c", NameList.at(0));
    ASSERT_EQ("t", NameList.at(1));
    ASSERT_EQ("r", NameList.at(2));
}

TEST (Sort, sortByIncreasingCompactness) { //Compactness = area/perimeter
    vector<string> NameList;
    Rectangle r(0,0,2,2);   //perimeter = 8 area = 4    Compactness = 0.5
    Circle c(0,0,2);        //perimeter = 12.56 area = 12.56    Compactness = 1
    vertex vertex1,vertex2, vertex3;
    vertex1.x = 0;
    vertex1.y = 0;
    vertex2.x = 0;
    vertex2.y = 3;
    vertex3.x = 4;
    vertex3.y = 0;
    Triangle t(vertex1, vertex2, vertex3); // perimeter = 12 area = 6   Compactness = 0.5
    list<Shape *> ShapeList;
    ShapeList.push_back(&r);
    ShapeList.push_back(&c);
    ShapeList.push_back(&t);
    Sort::sortByIncreasingCompactness(&ShapeList);
    for(Shape* shape : ShapeList)
    {
        NameList.push_back(shape->getShapeName());
    }
    ASSERT_EQ("r", NameList.at(0));
    ASSERT_EQ("t", NameList.at(1));
    ASSERT_EQ("c", NameList.at(2));
}

#endif
