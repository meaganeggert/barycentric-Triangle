//This exact header was given to us as we had previously created it for another project.

#pragma once
#include <iostream>
#include <cmath>

//Basically a point in space, used to be called Asteroid
//If you want to make a point in space representing (3,4) in the Cartesian system:
//Point bob{3,4};
//If you want to represent (-10,20), you can do this:
//Point cindy{-10,20};
//All the examples below will use the above bob and cindy
struct Point {
        float x= 0, y = 0; //Default position is (0,0)

        //The "friend" keyword means this function is actually outside the class
        //(Friend also gives access to private members, but here we don't have any, so it's just an organization thing.)
        //Point steve = bob - cindy; //steve is {13,16}
        friend Point operator-(const Point &lhs, const Point &rhs) {
                return {lhs.x-rhs.x,lhs.y-rhs.y};
        }

        //Allows us to scale a point towards or away from the origin
        //Point steve = bob / 2; //steve is {1.5,2}
        friend Point operator/(const Point &lhs, float scale) {
                return {lhs.x/scale,lhs.y/scale};
        }

        //How far is this point from the origin?
        //cout << length(bob) << endl; //Prints 5
        friend float length(const Point &foo) {
                return hypot(foo.x,foo.y);
        }

        //You can usually pick between a global or friend or a member function
        //So we could have done length like this instead with a member function -
        //cout << bob.length() << endl; //Prints 5
        float length() {
                return hypot(x,y);
        }

        //cout << abs(cindy); //Prints (10,20)
        friend Point abs(const Point &foo) {
                return {std::abs(foo.x),std::abs(foo.y)};
        }

        //Returns the distance from us to the coordinate passed in
        //cout << bob.distance_to(6,0); //Prints 5
        float distance_to(int x, int y) const {
                return this->distance_to(Point{float(x),float(y)});
        }

        //You can overload a function so it can take different kinds of parameters...
        //cout << bob.distance_to(cindy); //Prints 20.6155 if I did the math right
        float distance_to(const Point &rhs) const {
                return hypot(rhs.x-this->x,rhs.y-this->y);
        }

        //This allows you to read a point in from cin, like this -
        //cin >> steve; //Reads two doubles in
        friend std::istream& operator>>(std::istream& ins, Point &rhs) {
                return ins >> rhs.x >> rhs.y;
        }

        //This allows you to print a point to cout, like this -
        //cout << bob; //Prints "(3,4)"
        friend std::ostream& operator<<(std::ostream& outs, const Point &rhs) {
                return outs << '(' << rhs.x << ',' << rhs.y << ')';
        }

};
