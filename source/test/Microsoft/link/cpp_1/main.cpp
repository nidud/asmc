#include <stdio.h>

class Shape {
   public:
      void setWidth(int);
      void setHeight(int);

   protected:
      int width;
      int height;
};

class Rectangle: public Shape {
   public:
      int getArea();
};

extern class Rectangle *Rect;

int main(void)
{
   Rect->setWidth(5);
   Rect->setHeight(7);

   printf("Total area: %d\n",  Rect->getArea() );

   return 0;
}
