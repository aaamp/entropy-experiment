#ifndef VEC2_H_
#define VEC2_H_

#include <cmath>
#include <ostream>

template <class T>
class vec2
{
public:
    using floatingType = T;
    vec2(floatingType X, floatingType Y)
        : x(X), y(Y) {}
    vec2() {} // std::pair goes crazy if class does not have default constructor
    const floatingType& getX() const { return x; }
    const floatingType& getY() const { return y; }
    void setX(const floatingType& v) { x = v; }
    void setY(const floatingType& v) { y = v; }
    floatingType getLength() const
    {
        return std::sqrt(x*x + y*y);
    }
    floatingType getSquaredLength() const
    {
        return x*x + y*y;
    }
    floatingType getAngle() const
    {
        return std::atan2(y, x);
    }
    vec2 getNormalized() const
    {
        return *this * (1/getLength());
    }
    vec2& operator +=(const vec2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2& operator -=(const vec2& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    vec2& operator *=(floatingType s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    vec2 operator +(const vec2& v) const
    {
        return vec2(x + v.x, y + v.y);
    }
    vec2 operator -(const vec2& v) const
    {
        return vec2(x - v.x, y - v.y);
    }
    vec2 operator *(const floatingType& s) const
    {
        return vec2(x * s, y * s);
    }
    floatingType operator *(const vec2& v) const // Dot product
    {
        return x * v.x + y * v.y;
    }
private:
    floatingType x, y;
};

template <class T>
std::ostream& operator <<(std::ostream& out, const vec2<T>& v)
{
    return out << "{" << v.getX() << ", " << v.getY() << "}";
}

template <class T>
vec2<T> operator *(const T& s, const vec2<T>& v)
{
    return vec2<T>(v.getX() * s, v.getY() * s);
}

using vec2f = vec2<float>; 

#endif
