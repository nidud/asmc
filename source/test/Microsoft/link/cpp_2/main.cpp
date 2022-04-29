#include <stdio.h>

class Shape {
   public:
      virtual void setWidth(int);
      virtual void setHeight(int);

   protected:
      int width;
      int height;
};

class Rectangle: public Shape {
   public:
      virtual int getArea();
};

extern "C" { extern class Rectangle *Rect; };

int mainCRTStartup(void)
{
   Rect->setWidth(5);
   Rect->setHeight(7);

   printf("Total area: %d\n",  Rect->getArea() );

   return 0;
}
