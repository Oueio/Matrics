#include <VectorDouble.h>

VectorDouble::VectorDouble() {
    arr = nullptr;
    size = 0;
    iterator = 0;
}

VectorDouble::VectorDouble(size_t n) {
    arr = new double[n];
    size = n;
    iterator = 0;
}

VectorDouble::~VectorDouble() {
    delete[] arr;
    size = 0;
    iterator = 0;
}

size_t VectorDouble::length() const {
    return size;
}

int VectorDouble::push_back(double num) {
    if (iterator >= size) {
        exit(OVERLOADING);
    }
    arr[iterator++] = num;
    return 0;
}

double &VectorDouble::operator[](int it) const {
    if (it < 0 or it >= size) {
        exit(WRONG_INDEX);
    }
    return arr[it];
}

std::istream &operator>>(std::istream &in, VectorDouble &obj) {
    if (obj.size == 0) {
        in >> obj.size;
        obj.arr = new double[obj.size];
    }
    for (int i = 0; i < obj.size; i++) {
        double t;
        in >> t;
        obj.push_back(t);
    }
    return in;
}

VectorDouble &VectorDouble::operator+=(const VectorDouble &obj) {
    if (obj.size != size) {
        exit(WRONG_DIMENSION_VECTOR);
    }
    for (int i = 0; i < size; ++i) {
        arr[i] += obj[i];
    }
    return *this;
}

VectorDouble &VectorDouble::operator-=(const VectorDouble &obj) {
    if (obj.size != size) {
        exit(WRONG_DIMENSION_VECTOR);
    }
    for (int i = 0; i < size; ++i) {
        arr[i] -= obj[i];
    }
    return *this;
}

VectorDouble &VectorDouble::operator*=(const VectorDouble &obj) {
    if (obj.size != size) {
        exit(WRONG_DIMENSION_VECTOR);
    }
    for (int i = 0; i < size; ++i) {
        arr[i] *= obj[i];
    }
    return *this;
}

VectorDouble VectorDouble::operator+(const VectorDouble &obj) const {
    if (obj.size != size) {
        exit(WRONG_DIMENSION_VECTOR);
    }
    VectorDouble res(size);
    res.iterator = iterator;
    for (int i = 0; i < size; ++i) {
        res[i] = arr[i] + obj[i];
    }
    return res;
}

VectorDouble VectorDouble::operator-(const VectorDouble &obj) const {
    if (obj.size != size) {
        exit(WRONG_DIMENSION_VECTOR);
    }
    VectorDouble res(size);
    res.iterator = iterator;
    for (int i = 0; i < size; ++i) {
        res[i] = arr[i] - obj[i];
    }
    return res;
}

VectorDouble VectorDouble::operator*(const VectorDouble &obj) const {
    if (obj.size != size) {
        exit(WRONG_DIMENSION_VECTOR);
    }
    VectorDouble res(size);
    res.iterator = iterator;
    for (int i = 0; i < size; ++i) {
        res[i] = arr[i] * obj[i];
    }
    return res;
}

VectorDouble &VectorDouble::operator=(const VectorDouble &obj) {
    if (this == &obj) return *this;
    size = obj.size;
    iterator = obj.iterator;
    delete[] arr;
    arr = new double[size];
    for (int i = 0; i < size; ++i) (*this)[i] = obj[i];
    return *this;
}

std::ostream &operator<<(std::ostream &out, const VectorDouble &obj) {
    for (int i = 0; i < obj.size; ++i) out << obj[i] << ' ';
    return out;
}