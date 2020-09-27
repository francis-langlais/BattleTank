//
// This class comes from StackExchange user TemplateRex which is based on the Boost.Operator library.
// https://codereview.stackexchange.com/questions/26608/review-of-2d-vector-class
//

#pragma once

#include <iostream>
#include <cfloat>
#include <climits>
#include <tuple>

template<class T>
class Vector2D
{
public:
    T x;
    T y;

    Vector2D(): x(T(0)), y(T(0)) {}
    Vector2D(const T vx, const T vy): x(vx), y(vy) {}

    Vector2D& operator+=(const Vector2D& vec) { x += vec.x; y += vec.y; return *this; }
    Vector2D& operator-=(const Vector2D& vec) { x -= vec.x; y -= vec.y; return *this; }
    Vector2D& operator*=(const Vector2D& vec) { x *= vec.x; y *= vec.y; return *this; }
    Vector2D& operator/=(const Vector2D& vec) { x /= vec.x; y /= vec.y; return *this; }

    friend bool operator==(const Vector2D& v1, const Vector2D& v2) { return std::tie(v1.x, v1.y) == std::tie(v2.x, v2.y); }
    friend bool operator!=(const Vector2D& v1, const Vector2D& v2) { return !(v1 == v2); }

    friend bool operator< (const Vector2D& v1, const Vector2D& v2) { return std::tie(v1.x, v1.y) < std::tie(v2.x, v2.y); }
    friend bool operator>=(const Vector2D& v1, const Vector2D& v2) { return !(v1 < v2); }
    friend bool operator> (const Vector2D& v1, const Vector2D& v2) { return v2 < v1; }
    friend bool operator<=(const Vector2D& v1, const Vector2D& v2) { return !(v2 < v1); }

    Vector2D operator-() const { return Vector2D(-x, -y); }

    Vector2D&operator*=(const T s) { x *= s; y *= s; return *this; }
    Vector2D&operator/=(const T s) { x /= s; y /= s; return *this; }

    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) { stream << "X = " << vec.x << "    Y = " << vec.y; return stream; }
};

template<class T> Vector2D<T> operator+(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1) += v2; }
template<class T> Vector2D<T> operator-(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1) -= v2; }
template<class T> Vector2D<T> operator*(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1) *= v2; }
template<class T> Vector2D<T> operator/(const Vector2D<T>& v1, const Vector2D<T>& v2) { return Vector2D<T>(v1) /= v2; }

template<class T> Vector2D<T> operator*(const T& s, const Vector2D<T>& vec) { return Vector2D<T>(vec) *= s; }
template<class T> Vector2D<T> operator*(const Vector2D<T>& vec, const T& s) { return Vector2D<T>(vec) *= s; }
template<class T> Vector2D<T> operator/(const T& s, const Vector2D<T>& vec) { return Vector2D<T>(vec) /= s; }
template<class T> Vector2D<T> operator/(const Vector2D<T>& vec, const T& s) { return Vector2D<T>(vec) /= s; }

//Product functions
template<class T> T DotProduct(const Vector2D<T>& v1, const Vector2D<T>& v2){
    return ((v1.x * v2.x) + (v1.y * v2.y));
}
template<class T> T CrossProduct(const Vector2D<T>& v1, const Vector2D<T>& v2){
    return ((v1.x * v2.y) - (v1.y * v2.x));
}

//Return the length of the vector from the origin.
template<class T> T EuclideanNorm(const Vector2D<T>& vec){
    return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

//Return the unit vector of the input.
template<class T> Vector2D<T> Normal(const Vector2D<T>& vec){
    T magnitude = EuclideanNorm(vec);
    return Vector2D<T>(vec.x / magnitude, vec.y / magnitude);
}

//Return a vector perpendicular to the left.
template<class T> Vector2D<T> Perpendicular(const Vector2D<T>& vec){
    return Vector2D<T>(vec.y, -vec.x);
}

//Return true if two line segments intersect.
template<class T> bool Intersect(const Vector2D<T>& p1, const Vector2D<T>& p2, const Vector2D<T>& p3, const Vector2D<T>& p4){
    Vector2D<T> p = p1;
    Vector2D<T> r = p2 - p1;
    Vector2D<T> q = p3;
    Vector2D<T> s = p4 - p3;

    T t = (CrossProduct((q - p), s) / CrossProduct(r, s));
    T u = (CrossProduct((q - p), r) / CrossProduct(r, s));

    return (0.0 <= t && t <= 1.0) &&
           (0.0 <= u && u <= 1.0);
}

//Return the point were two line intersect.
template<class T> Vector2D<T> GetIntersectPoint(const Vector2D<T>& p1, const Vector2D<T>& p2, const Vector2D<T>& p3, const Vector2D<T>& p4){
    T pX = CrossProduct(p1, p2) * (p3.x - p4.x) -
           CrossProduct(p3, p4) * (p1.x - p2.x);
    T pY = CrossProduct(p1, p2) * (p3.y - p4.y) -
           CrossProduct(p3, p4) * (p1.y - p2.y);
    T denominator = (p1.x - p2.x) * (p3.y - p4.y) -
                    (p1.y - p2.y) * (p3.x - p4.x);

    return Vector2D<T>(pX / denominator, pY / denominator);
}