#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 80
#define HEIGHT 40
#define ASPECT_RATIO 2.1

typedef enum {
    SHAPE_CIRCLE = 1,
    SHAPE_RECTANGLE,
    SHAPE_LINE,
    SHAPE_TRIANGLE
} ShapeType;

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point center;
    double radius;
} Circle;

typedef struct {
    Point topLeft;
    Point bottomRight;
} Rectangle;

typedef struct {
    Point start, end;
} Line;

typedef struct {
    Point p1, p2, p3;
} Triangle;

typedef struct GraphicalObject {
    int id;
    ShapeType type;
    union {
        Circle circle;
        Rectangle rectangle;
        Line line;
        Triangle triangle;
    } data;
    struct GraphicalObject *next;
} GraphicalObject;

char canvas[HEIGHT][WIDTH];
GraphicalObject *objectList = NULL;
int nextObjectId = 1;
int showAll = 1; // 1: Show all, 0: Show latest only

// Viewport settings
double offsetX = 0;
double offsetY = 0;
double zoomLevel = 1.0;

void clearCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

void drawPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = '*';
    }
}

Point transform(double x, double y) {
    Point p;
    p.x = (x - offsetX) * zoomLevel * ASPECT_RATIO;
    p.y = (y - offsetY) * zoomLevel;
    return p;
}

void drawLine(double x0, double y0, double x1, double y1) {
    Point p0 = transform(x0, y0);
    Point p1 = transform(x1, y1);
    int ix0 = (int)round(p0.x), iy0 = (int)round(p0.y);
    int ix1 = (int)round(p1.x), iy1 = (int)round(p1.y);
    int dx = abs(ix1 - ix0), sx = ix0 < ix1 ? 1 : -1;
    int dy = -abs(iy1 - iy0), sy = iy0 < iy1 ? 1 : -1;
    int err = dx + dy, e2;
    while (1) {
        drawPixel(ix0, iy0);
        if (ix0 == ix1 && iy0 == iy1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; ix0 += sx; }
        if (e2 <= dx) { err += dx; iy0 += sy; }
    }
}

void drawCircle(double xm, double ym, double r) {
    Point center = transform(xm, ym);
    double rx = r * zoomLevel * ASPECT_RATIO;
    double ry = r * zoomLevel;
    int num_segments = (int)(2 * M_PI * fmax(rx, ry) * 2);
    if (num_segments < 16) num_segments = 16;
    for (int i = 0; i <= num_segments; i++) {
        double theta = 2.0 * M_PI * i / num_segments;
        drawPixel((int)round(center.x + rx * cos(theta)), (int)round(center.y + ry * sin(theta)));
    }
}

void drawRectangle(double x0, double y0, double x1, double y1) {
    drawLine(x0, y0, x1, y0);
    drawLine(x1, y0, x1, y1);
    drawLine(x1, y1, x0, y1);
    drawLine(x0, y1, x0, y0);
}

void drawTriangle(double x0, double y0, double x1, double y1, double x2, double y2) {
    drawLine(x0, y0, x1, y1);
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x0, y0);
}

void drawObject(GraphicalObject *obj) {
    if (!obj) return;
    switch (obj->type) {
        case SHAPE_CIRCLE: drawCircle(obj->data.circle.center.x, obj->data.circle.center.y, obj->data.circle.radius); break;
        case SHAPE_RECTANGLE: drawRectangle(obj->data.rectangle.topLeft.x, obj->data.rectangle.topLeft.y, obj->data.rectangle.bottomRight.x, obj->data.rectangle.bottomRight.y); break;
        case SHAPE_LINE: drawLine(obj->data.line.start.x, obj->data.line.start.y, obj->data.line.end.x, obj->data.line.end.y); break;
        case SHAPE_TRIANGLE: drawTriangle(obj->data.triangle.p1.x, obj->data.triangle.p1.y, obj->data.triangle.p2.x, obj->data.triangle.p2.y, obj->data.triangle.p3.x, obj->data.triangle.p3.y); break;
    }
}

void redrawAllObjects() {
    clearCanvas();
    if (objectList == NULL) return;
    if (showAll) {
        GraphicalObject *current = objectList;
        while (current != NULL) {
            drawObject(current);
            current = current->next;
        }
    } else {
        drawObject(objectList);
    }
}

void addObject(GraphicalObject *newObj) {
    newObj->id = nextObjectId++;
    newObj->next = objectList;
    objectList = newObj;
    // Automatically switch to "Show Latest Only" after adding an object
    showAll = 0;
}

void displayCanvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) putchar(canvas[i][j]);
        putchar('\n');
    }
}

int main() {
    char input[10];
    double x0, y0, x1, y1, x2, y2, r;
    int id;

    while (1) {
        redrawAllObjects();
        printf("\n--- 2D Graphics Editor ---\n");
        displayCanvas();
        printf("\n1. Add Circle\n2. Add Rectangle\n3. Add Line\n4. Add Triangle\n5. Delete Object\n6. Modify Object\n7. List Objects\n8. Clear All Objects\n9. %s\np. Pan\nz. Zoom In\nZ. Zoom Out\nr. Reset View\nq. Quit\nChoice: ", showAll ? "Toggle to Show Latest Only" : "Go Back to Show All");
        
        if (scanf("%s", input) != 1) break;
        if (input[0] == 'q') break;

        GraphicalObject *newObj;
        if (input[0] == '1') {
            printf("Enter center x, y and radius: ");
            scanf("%lf %lf %lf", &x0, &y0, &r);
            newObj = (GraphicalObject*)malloc(sizeof(GraphicalObject));
            newObj->type = SHAPE_CIRCLE; newObj->data.circle.center.x = x0; newObj->data.circle.center.y = y0; newObj->data.circle.radius = r;
            addObject(newObj);
        } else if (input[0] == '2') {
            printf("Enter top-left x, y and bottom-right x, y: ");
            scanf("%lf %lf %lf %lf", &x0, &y0, &x1, &y1);
            newObj = (GraphicalObject*)malloc(sizeof(GraphicalObject));
            newObj->type = SHAPE_RECTANGLE; newObj->data.rectangle.topLeft.x = x0; newObj->data.rectangle.topLeft.y = y0; newObj->data.rectangle.bottomRight.x = x1; newObj->data.rectangle.bottomRight.y = y1;
            addObject(newObj);
        } else if (input[0] == '3') {
            printf("Enter start x, y and end x, y: ");
            scanf("%lf %lf %lf %lf", &x0, &y0, &x1, &y1);
            newObj = (GraphicalObject*)malloc(sizeof(GraphicalObject));
            newObj->type = SHAPE_LINE; newObj->data.line.start.x = x0; newObj->data.line.start.y = y0; newObj->data.line.end.x = x1; newObj->data.line.end.y = y1;
            addObject(newObj);
        } else if (input[0] == '4') {
            printf("Enter three points (x1 y1 x2 y2 x3 y3): ");
            scanf("%lf %lf %lf %lf %lf %lf", &x0, &y0, &x1, &y1, &x2, &y2);
            newObj = (GraphicalObject*)malloc(sizeof(GraphicalObject));
            newObj->type = SHAPE_TRIANGLE; newObj->data.triangle.p1.x = x0; newObj->data.triangle.p1.y = y0; newObj->data.triangle.p2.x = x1; newObj->data.triangle.p2.y = y1; newObj->data.triangle.p3.x = x2; newObj->data.triangle.p3.y = y2;
            addObject(newObj);
        } else if (input[0] == '5') {
            printf("Enter ID to delete: "); scanf("%d", &id);
            GraphicalObject *curr = objectList, *prev = NULL;
            while (curr) {
                if (curr->id == id) {
                    if (prev) prev->next = curr->next; else objectList = curr->next;
                    free(curr); break;
                }
                prev = curr; curr = curr->next;
            }
        } else if (input[0] == '6') {
            printf("Enter ID to modify: "); scanf("%d", &id);
            GraphicalObject *curr = objectList;
            while (curr && curr->id != id) curr = curr->next;
            if (curr) {
                printf("Enter new parameters: ");
                if (curr->type == SHAPE_CIRCLE) scanf("%lf %lf %lf", &curr->data.circle.center.x, &curr->data.circle.center.y, &curr->data.circle.radius);
                else if (curr->type == SHAPE_RECTANGLE) scanf("%lf %lf %lf %lf", &curr->data.rectangle.topLeft.x, &curr->data.rectangle.topLeft.y, &curr->data.rectangle.bottomRight.x, &curr->data.rectangle.bottomRight.y);
                else if (curr->type == SHAPE_LINE) scanf("%lf %lf %lf %lf", &curr->data.line.start.x, &curr->data.line.start.y, &curr->data.line.end.x, &curr->data.line.end.y);
                else if (curr->type == SHAPE_TRIANGLE) scanf("%lf %lf %lf %lf %lf %lf", &curr->data.triangle.p1.x, &curr->data.triangle.p1.y, &curr->data.triangle.p2.x, &curr->data.triangle.p2.y, &curr->data.triangle.p3.x, &curr->data.triangle.p3.y);
            }
        } else if (input[0] == '7') {
            GraphicalObject *curr = objectList;
            while (curr) { printf("ID: %d, Type: %d\n", curr->id, curr->type); curr = curr->next; }
        } else if (input[0] == '8') {
            while (objectList) { GraphicalObject *temp = objectList; objectList = objectList->next; free(temp); }
            nextObjectId = 1; showAll = 1;
        } else if (input[0] == '9') {
            showAll = !showAll;
        } else if (input[0] == 'p') {
            printf("Enter dx and dy: ");
            scanf("%lf %lf", &x0, &y0);
            offsetX += x0; offsetY += y0;
        } else if (input[0] == 'z') {
            zoomLevel *= 1.2;
        } else if (input[0] == 'Z') {
            zoomLevel /= 1.2;
        } else if (input[0] == 'r') {
            offsetX = 0; offsetY = 0; zoomLevel = 1.0;
        } else {
            printf("Invalid choice.\n");
        }
    }
    return 0;
}