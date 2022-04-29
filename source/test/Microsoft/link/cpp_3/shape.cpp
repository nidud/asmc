
class Shape {
   public:
      virtual void setWidth(int w) {
        width = w;
      }
      virtual void setHeight(int h) {
        height = h;
      }
   protected:
      int width;
      int height;
};

class Rectangle : public Shape {
   public:
      virtual int getArea() {
        return (width * height);
      }
};

extern "C" {

int main(void);

Rectangle *Rect;

int mainCRTStartup(void)
{
    Rectangle sRect;

    Rect = (Rectangle *)&sRect;

    return main();
}

};
