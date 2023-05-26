#include "/public/read.h"
#include "/public/colors.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include "./point.h"
#include "./color.h"
using namespace std;

//void renderLine ( float x1, float x2, float y1, float y2, Color colorParam);

float crossProduct(Point A, Point B);
void fillTriangle (float x1, float x2, float x3, float y1, float y2, float y3, Color colorparam);
bool isItInside (Point testPoint, Point topVertex, Point leftVertex, Point rightVertex);
Color colorPicker (Point testPoint, Point topVertex, Point leftVertex, Point rightVertex);

int main() {
        //These are in screenspace coordinates
        //(The triangle has already been projected from local space to world space to image space to screen space)
        Point p1 = read("Please enter the x,y coordinates for Point 1:\n");
        Point p2 = read("Please enter the x,y coordinates for Point 2:\n");
        Point p3 = read("Please enter the x,y coordinates for Point 3:\n");

//Determines Bounding Box for the Triangle
        float minBoundX, minBoundY, maxBoundX, maxBoundY;
        minBoundX = min(p1.x, min(p2.x, p3.x));
        minBoundY = min(p1.y, min(p2.y, p3.y));
        maxBoundX = max(p1.x, max(p2.x, p3.x));
        maxBoundY = max(p1.y, max(p2.y, p3.y));

//Organizes the Vertices for My Cross Product Function
  //There's something wrong with this. Most of the time the rasterization works fine, but sometimes it doesn't work at all. I'm clearly vetting the data incorrectly, but I haven't fixed yet.
        Point leftVert, topVert, rightVert;
        if (p1.x == minBoundX) leftVert = p1;
        else if (p2.x == minBoundX) leftVert = p2;
        else if (p3.x == minBoundX) leftVert = p3;

        if (p1.y == minBoundY && p1.x != minBoundX) topVert = p1;
        else if (p2.y == minBoundY && p2.x != minBoundX) topVert = p2;
        else if (p3.y == minBoundY && p3.x != minBoundX) topVert = p3;

        if ((p1.x != minBoundX) && (p1.y != minBoundY)) rightVert= p1;
        else if ((p2.x != minBoundX) && (p2.y != minBoundY)) rightVert = p2;
        else if ((p3.x != minBoundX) && (p3.y != minBoundY)) rightVert = p3;


        clearscreen();

        for (int y = minBoundY; y <= maxBoundY; y++){
                for (int x = minBoundX; x <= maxBoundX; x++){
                        Point testSpot = Point(x, y);
                        if (isItInside(testSpot, topVert, leftVert, rightVert)){
                                Color currentGradient = colorPicker(testSpot, topVert, leftVert, rightVert);
                                movecursor(y, x);
                                setbgcolor(currentGradient.r, currentGradient.g, currentGradient.b);
                                //cout << currentGradient << endl;
                                cout << " ";
                        }
                }
        }
        resetcolor();
        movecursor(25, 0);
        cout << endl << endl;


//Checking That The Vertex Organizing Worked As Expected
        /*
        cout << "left: " << leftVert << endl;
        cout << "top: " << topVert << endl;
        cout << "right/bottom: " << rightVert << endl;
        */

//Checking that the isItInside function works
        /*
        Point check = Point(4, 4);
        cout << isItInside(check, topVert, leftVert, rightVert) << endl;
        check = Point(10, 15);
        cout << isItInside(check, topVert, leftVert, rightVert) << endl;
        */

//Draws and fills a triangle with the color sent by parameter
        /*
        fillTriangle(p1.x, p2.x, p3.x, p1.y, p2.y, p3.y, c1);
        */

//Draws 3 individual lines to render the outline of a triangle
        /*
        renderLine (p1.x, p2.x, p1.y, p2.y, c1);
        renderLine (p2.x, p3.x, p2.y, p3.y, c2);
        renderLine (p3.x, p1.x, p3.y, p1.y, c3);
        */


}



//THIS WHOLE SECTION DRAWS THE OUTLINE OF A TRIANGLE
/*
void renderLine (float userX1, float userX2, float userY1, float userY2, Color colorParam) {
        float rise, run, slope;
        float xMin, xMax, yMin, yMax;

        rise = userY2 - userY1;
        run = userX2 - userX1;

//If the line is really one point, output the background color
        if (rise == 0 and run == 0){
                movecursor(userY1, userX1);
                setbgcolor(colorParam.r, colorParam.g, colorParam.b);
                cout << " ";
        }
//This section renders the line when it's wider than it is steep
        if (abs(run) > abs(rise)){
                if (userX1 < userX2) {
                        xMin = userX1;
                        xMax = userX2;
                }
                else {
                        xMin = userX2;
                        xMax = userX1;
                }

                slope = rise/run;

                for (float x = xMin; x <= xMax; x++){
                        float y = userY1 + ((x - userX1) * slope);
                        movecursor(y, x);
                        setbgcolor(colorParam.r, colorParam.g, colorParam.b);
                        cout << " ";
                }
        }
//This section renders the line when it's steeper than it is wide
        else {
                if (userY1 < userY2) {
                        yMin = userY1;
                        yMax = userY2;
                }
                else {
                        yMin = userY2;
                        yMax = userY1;
                }

                slope = run/rise;

                for (float y = yMin; y <= yMax; y ++){
                        float x = userX1 + ((y - userY1) * slope);
                        movecursor(y, x);
                        setbgcolor(colorParam.r, colorParam.g, colorParam.b);
                        cout << " ";
                }
        }
                cout << endl;
                resetcolor();
}
*/



//GLITCHY FILL FUNCTION
/*
//Draws and fills a triangle with the color sent by parameter
//Glitchy
//Sometimes it works, sometimes it draws a rectangle, sometimes nothing happens
//Something is wrong with the logic
void fillTriangle (float x1, float x2, float x3, float y1, float y2, float y3, Color colorParam) {
//Determines the bounding box of the triangle
        float minBoundX, minBoundY, maxBoundX, maxBoundY;
        minBoundX = min(x1, min(x2, x3));
        minBoundY = min(y1, min(y2, y3));
        maxBoundX = max(x1, max(x2, x3));
        maxBoundY = max(x1, max(x2, x3));

        Point currentSpot;

        Point delta_1_2, delta_1_3;
        delta_1_2 = Point(x2 - x1, y2 - y1);
        delta_1_3 = Point(x3 - x1, y3 - y1);

        for (float x = minBoundX; x <= maxBoundX; x++) {
                for (float y = minBoundY; y <= maxBoundY; y++) {
                        Point delta_current_1;
                        delta_current_1.x = x - x1;
                        delta_current_1.y = y - y1;

                        float crossWithRight = (float)crossProduct(delta_current_1, delta_1_3)/crossProduct(delta_1_2, delta_1_3);
                        float crossWithLeft = (float)crossProduct(delta_1_2, delta_current_1)/crossProduct(delta_1_2, delta_1_3);

                        if ((crossWithRight <= 0) && (crossWithLeft >= 0) && (crossWithRight + crossWithLeft <= 1)) {
                                movecursor(y, x);
                                setbgcolor(colorParam.r, colorParam.g, colorParam.b);
                                cout << " ";
                        }
                }
        }
        resetcolor();
        cout << endl;
}
*/

//Chooses a color based on how close the point is to the respective red, green, and blue vertices using barycentric coordinates
Color colorPicker (Point testPoint, Point topVertex, Point leftVertex, Point rightVertex) {

        Color currentColor;
        Point leftVector, rightVector, bottomVector, testVector;

    leftVector = Point(leftVertex.x - topVertex.x, leftVertex.y - topVertex.y);
    rightVector = Point(rightVertex.x - topVertex.x, rightVertex.y - topVertex.y);
    bottomVector = Point(leftVertex.x - rightVertex.x, leftVertex.y - rightVertex.y);
    testVector = Point(testPoint.x - topVertex.x, testPoint.y - topVertex.y);

        float totalArea, redArea, greenArea, blueArea;

        totalArea = abs(crossProduct(leftVector, rightVector));

        greenArea = abs(crossProduct(leftVector, testVector));
        redArea = abs(crossProduct(testVector, rightVector));

        testVector = Point(testPoint.x - rightVertex.x, testPoint.y - rightVertex.y); //Set the test vector to the displacement vector from the right vertex to the test point
        blueArea = abs(crossProduct(testVector, bottomVector));

        float redRatio, greenRatio, blueRatio;

        redRatio = redArea/totalArea;
        greenRatio = greenArea/totalArea;
        blueRatio = blueArea/totalArea;

        currentColor.r = redRatio*255;
        currentColor.g = greenRatio*255;
        currentColor.b = blueRatio*255;

        return currentColor;

}

//Crossproduct function so I don't have to do this every time
float crossProduct(Point A, Point B) {
        float result;
        result = B.x*A.y - A.x*B.y;
        return result;
}

//Checks to see if the point in question is actually inside the triangle. If it is, it returns true.
bool isItInside (Point testPoint, Point topVertex, Point leftVertex, Point rightVertex) {
    Point leftVector, rightVector, bottomVector, testVector;
    leftVector = Point(leftVertex.x - topVertex.x, leftVertex.y - topVertex.y);
    rightVector = Point(rightVertex.x - topVertex.x, rightVertex.y - topVertex.y);
    bottomVector = Point(leftVertex.x - rightVertex.x, leftVertex.y - rightVertex.y);
    testVector = Point(testPoint.x - topVertex.x, testPoint.y - topVertex.y);

    float crossVector;

    crossVector = crossProduct(leftVector, testVector);

    if (crossVector > 0) {
        crossVector = crossProduct(testVector, rightVector);
        if (crossVector > 0) {
            testVector = Point(testPoint.x - rightVertex.x, testPoint.y - rightVertex.y);
            crossVector = crossProduct(testVector, bottomVector);
            if (crossVector > 0){
                return true;
            }
        }
    }
    return false;
}


//Kerney's Starter Code
//This is code provided by our professor to show us how to use the colors.h library to color the screen in PuTTy

//Delete these lines, they're just to show you the way
/*      clearscreen();
        movecursor(1, 0); //Move cursor to Row 1 Col 0
        cout << c1 << ": ";
        movecursor(1, 30); //Move cursor to Row 1 Col 30
        setbgcolor(c1.r,c1.g,c1.b); //Set background color to whatever color is in c1
        cout << "        " << endl; //Print some spaces to get the colors to show
        movecursor(2, 0); //Move cursor to Row 2 Col 0, etc.
        cout << RESET << c2 << ": ";
        movecursor(2, 30);
        setbgcolor(c2.r,c2.g,c2.b);
        cout << "        " << endl;
        movecursor(3, 0);
        cout << RESET << c3 << ": ";
        movecursor(3, 30);
        setbgcolor(c3.r,c3.g,c3.b);
        cout << "        " << endl;
        resetcolor();
*/

