#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QStyleOption>

struct TransparentSprite : public QGraphicsPixmapItem
{
  TransparentSprite(
    const std::string& filename,
    const QColor& transparency_color = QColor(0,255,0)) //Lime green
    : dx(1), dy(1), maxx(320), maxy(200)
  {
    QPixmap pixmap(filename.c_str());
    const QBitmap mask = pixmap.createMaskFromColor(transparency_color);
    pixmap.setMask(mask);
    this->setPixmap(pixmap);
  }
  void advance(int)
  {
    int new_x = this->x();
    int new_y = this->y();
    new_x+=dx;
    new_y+=dy;
    if (new_x<0 || new_x>maxx) dx= -dx;
    if (new_y<0 || new_y>maxy) dy= -dy;
    this->setX(new_x);
    this->setY(new_y);
  }
  void setRect(const int width, const int height)
  {
    maxx = width  - this->pixmap().width();
    maxy = height - this->pixmap().height();
  }
  private:
  int dx;
  int dy;
  int maxx;
  int maxy;
};

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QGraphicsScene scene;

    scene.setSceneRect(-400, -400, 400, 400);
    scene.setItemIndexMethod(QGraphicsScene :: NoIndex);

    QGraphicsView view(&scene);

    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/stuff/testIMG.png"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "TEST"));

    TransparentSprite sprite(":/stuff/cheese.jpg");
    sprite.setRect(40, 40);

    scene.addItem(&sprite);
    view.show();

    return app.exec();

}
