#pragma once

class BoundingBox
{
public:
    int bottom;
    int left;
    int right;


    BoundingBox(int bottom, int left, int right):
        bottom(bottom), left(left), right(right){}

};
