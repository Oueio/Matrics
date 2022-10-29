#include <Matrix.h>

Matrix::Matrix() {
    arr = nullptr;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(VectorDouble *vectors, size_t r) {
    cols = vectors[0].length();
    int i, j;
    for (i = 1; i < r; ++i) {
        if (vectors[i].length() != cols) {
            throw std::length_error("Not same size for all vectors");
        }
    }
    rows = r;
    arr = new VectorDouble(rows * cols);
    size_t x = 0;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            (*arr)[x++] = vectors[i][j];
        }
    }
}

std::istream &operator>>(std::istream &in, Matrix &obj) {
    in >> obj.rows >> obj.cols;
    obj.arr = new VectorDouble(obj.rows * obj.cols);
    in >> *obj.arr;
    return in;
}

double &Matrix::operator()(const size_t r, const size_t c) const {
    if (r >= rows or c >= cols) {
        throw std::out_of_range("Wrong index");
    }
    return (*arr)[(int) (r * cols) + c];
}

std::ostream &operator<<(std::ostream &out, const Matrix &obj) {
    int i, j;
    for (i = 0; i < obj.rows; ++i) {
        for (j = 0; j < obj.cols; ++j) {
            out << obj(i, j) << ' ';
        }
        if (i != obj.rows - 1) {
            out << std::endl;
        }
    }
    return out;
}

VectorDouble Matrix::get_row(int r) const {
    VectorDouble obj(cols);
    int i;
    for (i = 0; i < cols; ++i) {
        obj[i] = (*this)(r, i);
    }
    return obj;
}

VectorDouble Matrix::get_col(int c) const {
    VectorDouble obj(rows);
    int i;
    for (i = 0; i < rows; ++i) {
        obj[i] = (*this)(i, c);
    }
    return obj;
}

VectorDouble Matrix::get_side_diag() const {
    if (rows != cols) {
        throw std::bad_function_call();
    }
    VectorDouble obj(rows);
    int i;
    for (i = 0; i < rows; ++i) {
        obj[i] = (*this)(rows - i - 1, i);
    }
    return obj;
}

VectorDouble Matrix::get_main_diag() const {
    if (rows != cols) {
        throw std::bad_function_call();
    }
    VectorDouble obj(rows);
    int i;
    for (i = 0; i < rows; ++i) {
        obj[i] = (*this)(i, i);
    }
    return obj;
}

Matrix &Matrix::operator+=(const Matrix &obj) {
    if (rows != obj.rows or cols != obj.cols) {
        throw std::length_error("Not same size");
    }
    *arr += *obj.arr;
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &obj) {
    if (rows != obj.rows or cols != obj.cols) {
        throw std::length_error("Not same size");
    }
    *arr -= *obj.arr;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &obj) {
    if (rows != obj.rows or cols != obj.cols) {
        throw std::length_error("Not same size");
    }
    *arr *= *obj.arr;
    return *this;
}

Matrix Matrix::operator+(const Matrix &obj) const {
    if (rows != obj.rows or cols != obj.cols) {
        throw std::length_error("Not same size");
    }
    Matrix res(rows, cols);
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res(i, j) = (*this)(i, j) + obj(i, j);
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &obj) const {
    if (rows != obj.rows or cols != obj.cols) {
        throw std::length_error("Not same size");
    }
    Matrix res(rows, cols);
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res(i, j) = (*this)(i, j) - obj(i, j);
        }
    }
    return res;
}

Matrix::Matrix(size_t r, size_t c) {
    arr = new VectorDouble(r * c);
    rows = r;
    cols = c;
}

Matrix &Matrix::operator*=(double num) {
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            (*this)(i, j) *= num;
        }
    }
    return *this;
}

Matrix Matrix::operator*(double num) const {
    Matrix res(rows, cols);
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res(i, j) = (*this)(i, j) * num;
        }
    }
    return res;
}

VectorDouble Matrix::operator*(const VectorDouble &obj) const {
    if (cols != obj.length()) {
        throw std::length_error("Wrong dimensions for operator *");
    }
    VectorDouble res;
    res = obj;
    int i, j;
    for (i = 0; i < rows; ++i) {
        double r = 0;
        for (j = 0; j < cols; ++j) {
            r += (*this)(i, j) * obj[j];
        }
        res[i] = r;
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &obj) const {
    if (cols != obj.rows) {
        throw std::length_error("Wrong dimensions for operator *");
    }
    Matrix res(rows, obj.cols);
    int i, j, k;
    double r;
    for (k = 0; k < obj.cols; ++k) {
        for (i = 0; i < obj.rows; ++i) {
            r = 0;
            for (j = 0; j < cols; ++j) {
                r += (*this)(i, j) * obj(j, k);
            }
            res(i, k) = r;
        }
    }
    return res;
}

void Matrix::put_row(const VectorDouble &obj, int row, char c) {
    if (cols != obj.length()) {
        throw std::length_error("Not same size");
    }
    int i;
    switch (c) {
        case '+':
            for (i = 0; i < obj.length(); ++i) {
                (*this)(row, i) += obj[i];
            }
            break;
        case '-':
            for (i = 0; i < obj.length(); ++i) {
                (*this)(row, i) -= obj[i];
            }
        default:
            return;
    }
}

void Matrix::put_col(const VectorDouble &obj, int col, char c) {
    if (rows != obj.length()) {
        throw std::length_error("Not same size");
    }
    int i;
    switch (c) {
        case '+':
            for (i = 0; i < obj.length(); ++i) {
                (*this)(i, col) += obj[i];
            }
            break;
        case '-':
            for (i = 0; i < obj.length(); ++i) {
                (*this)(i, col) -= obj[i];
            }
        default:
            return;
    }
}

double Matrix::determinant() {
    if (cols != rows) {
        throw std::length_error("Wrong dimensions");
    }
    if (rows == 2) {
        return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    } else {
        double res = 0;
        int i;
        for (i = 0; i < cols; ++i) {
            if (i % 2 == 0) {
                res += (*this)(0, i) * (this->minor(0, i).determinant());
            } else {
                res -= (*this)(0, i) * (this->minor(0, i).determinant());
            }
        }
        return res;
    }
}

Matrix Matrix::minor(const size_t row, const size_t col) {
    if (rows != cols) {
        throw std::length_error("Wrong dimensions");
    }
    if (rows - 1 == 0) {
        return *this;
    }
    Matrix res(rows - 1, cols - 1);
    int r = 0, c, i, j;
    for (i = 0; i < rows; ++i) {
        c = 0;
        if (i == row) continue;
        for (j = 0; j < cols; ++j) {
            if (j == col) continue;
            res(r, c++) = (*this)(i, j);
        }
        r++;
    }
    return res;
}

Matrix Matrix::trans() const {
    Matrix res(cols, rows);
    int i, j;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res(j, i) = (*this)(i, j);
        }
    }
    return res;
}

Matrix::Matrix(const Matrix &obj) {
    arr = new VectorDouble(obj.rows * obj.cols);
    *arr = *obj.arr;
    rows = obj.rows;
    cols = obj.cols;
}

Matrix &Matrix::operator=(const Matrix &obj) {
    if (&obj == this) {
        return *this;
    }
    rows = obj.rows;
    cols = obj.cols;
    arr = new VectorDouble(rows * cols);
    *arr = *obj.arr;
    return *this;
}

Matrix::~Matrix() {
    delete arr;
}

Matrix::Matrix(double *p, size_t r, size_t c) {
    rows = r;
    cols = c;
    arr = new VectorDouble(p, rows * cols);
}

bool Matrix::operator==(const Matrix &obj) {
    if (rows == obj.rows and cols == obj.cols and *arr == *obj.arr) {
        return true;
    }
    return false;
}

Matrix Matrix::reverse() {
    int i, j;
    Matrix res(rows, cols);
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            if ((i + j) % 2 == 0) {
                res(i, j) = this->minor(i, j).determinant();
            }
            else {
                res(i, j) = -this->minor(i, j).determinant();
            }
        }
    }
    res = res.trans();
    res *= (1 / this->determinant());
    return res;
}
