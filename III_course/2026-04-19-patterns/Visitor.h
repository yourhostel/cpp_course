//
// Created by tysser on 19.04.26.
//

#pragma once

class Circle;
class Rectangle;

class Visitor
{
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
    virtual ~Visitor() = default;
};

class Element
{
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Element() = default;
};

class Circle : public Element
{
public:
    explicit Circle(int radius);
    int get_radius() const;
    void accept(Visitor& visitor) override;

private:
    int radius_;
};

class Rectangle : public Element
{
public:
    Rectangle(int width, int height);
    int get_width() const;
    int get_height() const;
    void accept(Visitor& visitor) override;

private:
    int width_;
    int height_;
};

class PrintVisitor : public Visitor
{
public:
    void visit(Circle& circle) override;
    void visit(Rectangle& rectangle) override;
};

