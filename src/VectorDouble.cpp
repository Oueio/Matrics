#include <VectorDouble.h>

VectorDouble::VectorDouble() {
    arr = nullptr;
    size = 0;
}

VectorDouble::VectorDouble(size_t n) {
    arr = new double[n];
    size = n;
}

VectorDouble::~VectorDouble() {
    delete[] arr;
    size = 0;
}

size_t VectorDouble::length() const {
    return size;
}

double &VectorDouble::operator[](const size_t it) const {
    if (it >= size) {
        throw std::out_of_range("Wrong index");
    }
    return arr[it];
}

std::istream &operator>>(std::istream &in, VectorDouble &obj) {
    if (obj.size == 0) {
        in >> obj.size;
        obj.arr = new double[obj.size];
    }
    int i;
    for (i = 0; i < obj.size; i++) {
        double t;
        in >> t;
        obj[i] = t;
    }
    return in;
}

VectorDouble &VectorDouble::operator+=(const VectorDouble &obj) {
    if (obj.size != size) {
        throw std::length_error("Not same size");
    }
    int i;
    for (i = 0; i < size; ++i) {
        arr[i] += obj[i];
    }
    return *this;
}

VectorDouble &VectorDouble::operator-=(const VectorDouble &obj) {
    if (obj.size != size) {
        throw std::length_error("Not same size");
    }
    int i;
    for (i = 0; i < size; ++i) {
        arr[i] -= obj[i];
    }
    return *this;
}

VectorDouble &VectorDouble::operator*=(const VectorDouble &obj) {
    if (obj.size != size) {
        throw std::length_error("Not same size");
    }
    int i;
    for (i = 0; i < size; ++i) {
        arr[i] *= obj[i];
    }
    return *this;
}

VectorDouble VectorDouble::operator+(const VectorDouble &obj) const {
    if (obj.size != size) {
        throw std::length_error("Not same size");
    }
    VectorDouble res(size);
    int i;
    for (i = 0; i < size; ++i) {
        res[i] = arr[i] + obj[i];
    }
    return res;
}

VectorDouble VectorDouble::operator-(const VectorDouble &obj) const {
    if (obj.size != size) {
        throw std::length_error("Not same size");
    }
    VectorDouble res(size);
    int i;
    for (i = 0; i < size; ++i) {
        res[i] = arr[i] - obj[i];
    }
    return res;
}

VectorDouble VectorDouble::operator*(const VectorDouble &obj) const {
    if (obj.size != size) {
        throw std::length_error("Not same size");
    }
    VectorDouble res(size);
    int i;
    for (i = 0; i < size; ++i) {
        res[i] = arr[i] * obj[i];
    }
    return res;
}

std::ostream &operator<<(std::ostream &out, const VectorDouble &obj) {
    int i;
    for (i = 0; i < obj.size; ++i) {
        out << obj[i] << ' ';
    }
    return out;
}

VectorDouble &VectorDouble::operator=(const VectorDouble &obj) {
    if (&obj == this) {
        return *this;
    }
    size = obj.size;
    delete[] arr;
    arr = new double[size];
    int i;
    for (i = 0; i < size; ++i) {
        arr[i] = obj.arr[i];
    }
    return *this;
}

VectorDouble::VectorDouble(const double *p, size_t n) {
    size = n;
    int i;
    arr = new double[size];
    for (i = 0; i < size; ++i) {
        arr[i] = p[i];
    }
}

bool VectorDouble::operator==(const VectorDouble &obj) {
    bool flag = true;
    if (size != obj.size) flag = false;
    int i;
    for (i = 0; i < size; ++i) {
        if (arr[i] != obj.arr[i]) {
            flag = false;
            break;
        }
    }
    return flag;
}
