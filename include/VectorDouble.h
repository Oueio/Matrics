#ifndef VECTORDOUBLE_H
#define VECTORDOUBLE_H

#include <Utility.h>

class VectorDouble {
private:
    double *arr;
    size_t size;
public:
    VectorDouble();

    explicit VectorDouble(size_t);

    ~VectorDouble();

    explicit VectorDouble(const double *, size_t);

    [[nodiscard]] size_t length() const;

    double &operator[](size_t) const;

    friend std::istream &operator>>(std::istream &, VectorDouble &);

    VectorDouble &operator+=(const VectorDouble &);

    VectorDouble &operator-=(const VectorDouble &);

    VectorDouble &operator*=(const VectorDouble &);

    VectorDouble operator+(const VectorDouble &) const;

    VectorDouble operator-(const VectorDouble &) const;

    VectorDouble operator*(const VectorDouble &) const;

    VectorDouble &operator=(const VectorDouble &);

    friend std::ostream &operator<<(std::ostream &, const VectorDouble &);

    bool operator==(const VectorDouble &);
};

#endif //VECTORDOUBLE_H
