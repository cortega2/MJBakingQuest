#ifndef GRAPHICSVIEWEDITOR_H
#define GRAPHICSVIEWEDITOR_H

#include "objects.h"
#include "engine.h"

#define BLOCK_SIZE ( 30 )

class GraphicsViewEditor : public GraphicsView
{
public:
    GraphicsViewEditor(engine *gin);

    Q_OBJECT
public slots:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void cellDoubleClicked(int row, int column);
    // void mouseDoubleClickEvent(QMouseEvent * e);
    //void mouseMoveEvent(QMouseEvent * event);
protected:
    QTableWidget *rightClickMenu;
private:
    engine *ginny;
};

#endif // GRAPHICSVIEWEDITOR_H

