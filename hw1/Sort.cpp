#include "include/Sort.h"
#include "include/Shapes.h"
void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList)
{
	shapeList->sort([](Shape* a, Shape* b){return a->perimeter() < b->perimeter();});
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList)
{
    shapeList->sort([](Shape* a, Shape* b){return a->perimeter() > b->perimeter();});
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList)
{
    shapeList->sort([](Shape* a, Shape* b){return a->area() < b->area();});
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList)
{
    shapeList->sort([](Shape* a, Shape* b){return a->area() > b->area();});
}

void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList)
{
    shapeList->sort([](Shape* a, Shape* b){return (a->area()/a->perimeter()) < (b->area()/b->perimeter());});
}
