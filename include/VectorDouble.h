#ifndef VECTORDOUBLE_H
#define VECTORDOUBLE_H

#include <Utility.h>

class VectorDouble {
private:
    double *arr;
    size_t size;
    size_t iterator;
public:
    VectorDouble();

    explicit VectorDouble(size_t);

    ~VectorDouble();

    [[nodiscard]] size_t length() const;

    int push_back(double);

    double &operator[](int) const;

    friend std::istream &operator>>(std::istream &, VectorDouble &);

    VectorDouble &operator+=(const VectorDouble &);

    VectorDouble &operator-=(const VectorDouble &);

    VectorDouble &operator*=(const VectorDouble &);

    VectorDouble operator+(const VectorDouble &) const;

    VectorDouble operator-(const VectorDouble &) const;

    VectorDouble operator*(const VectorDouble &) const;

    VectorDouble &operator=(const VectorDouble &);

    friend std::ostream &operator<<(std::ostream &, const VectorDouble &);
};

#endif //VECTORDOUBLE_H