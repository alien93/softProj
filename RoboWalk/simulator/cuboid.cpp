#include "cuboid.h"

Cuboid::Cuboid()
{

}

Cuboid::Cuboid(double width, double height, double depth)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
}

void Cuboid::drawCuboid()
{
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);


    // right
    glVertex3d(width / 2, -height / 2, -depth / 2);
    glVertex3d(width / 2, height / 2, -depth / 2);
    glVertex3d(width / 2, height / 2, depth / 2);
    glVertex3d(width / 2, -height / 2, depth / 2);


    // left
    glVertex3d(-width / 2, -height / 2, depth / 2);
    glVertex3d(-width / 2, height / 2, depth / 2);
    glVertex3d(-width / 2, height / 2, -depth / 2);
    glVertex3d(-width / 2, -height / 2, -depth / 2);


    // back
    glVertex3d(-width / 2, -height / 2, -depth / 2);
    glVertex3d(-width / 2, height / 2, -depth / 2);
    glVertex3d(width / 2, height / 2, -depth / 2);
    glVertex3d(width / 2, -height / 2, -depth / 2);


    // front
    glVertex3d(width / 2, -height / 2, depth / 2);
    glVertex3d(width / 2, height / 2, depth / 2);
    glVertex3d(-width / 2, height / 2, depth / 2);
    glVertex3d(-width / 2, -height / 2, depth / 2);


    // bottom
    glVertex3d(-width / 2, -height / 2, -depth / 2);
    glVertex3d(width / 2, -height / 2, -depth / 2);
    glVertex3d(width / 2, -height / 2, depth / 2);
    glVertex3d(-width / 2, -height / 2, depth / 2);

    // up
    glVertex3d(-width / 2, height / 2, -depth / 2);
    glVertex3d(-width / 2, height / 2, depth / 2);
    glVertex3d(width / 2, height / 2, depth / 2);
    glVertex3d(width / 2, height / 2, -depth / 2);


    glEnd();
    glPopMatrix();
}
