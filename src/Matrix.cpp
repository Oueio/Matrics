#include <Matrix.h>

Matrix::Matrix() {
    arr = nullptr;
    rows = 0;
    cols = 0;
}

Matrix::Matrix(VectorDouble *vectors, size_t r) {
    cols = vectors[0].length();
    for (int i = 1; i < r; ++i) if (vectors[i].length() != cols) exit(WRONG_DIMENSION_MATRIX);
    rows = r;
    arr = new VectorDouble(rows * cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr->push_back(vectors[i][j]);
        }
    }
}

std::istream &operator>>(std::istream &in, Matrix &obj) {
    in >> obj.rows >> obj.cols;
    obj.arr = new VectorDouble(obj.rows * obj.cols);
    in >> *obj.arr;
    return in;
}

double &Matrix::operator()(int r, int c) const {
    if (r < 0 or r >= rows or c < 0 or c >= cols) {
        exit(WRONG_INDEX);
    }
    return (*arr)[(int) (r * cols) + c];
}

std::ostream &operator<<(std::ostream &out, const Matrix &obj) {
    for (int i = 0; i < obj.rows; ++i) {
        for (int j = 0; j < obj.cols; ++j) {
            out << obj(i, j) << ' ';
        }
        if (i != obj.rows - 1) out << std::endl;
    }
    return out;
}

Matrix::~Matrix() {
    delete arr;
}

VectorDouble Matrix::get_row(int r) const {
    VectorDouble obj(cols);
    for (int i = 0; i < cols; ++i) obj.push_back((*this)(r, i));
    return obj;
}

VectorDouble Matrix::get_col(int c) const {
    VectorDouble obj(rows);
    for (int i = 0; i < rows; ++i) obj.push_back((*this)(i, c));
    return obj;
}

VectorDouble Matrix::get_side_diag() const {
    if (rows != cols) exit(CANT_EXTRACT_DIAG);
    VectorDouble obj(rows);
    for (int i = 0; i < rows; ++i) obj.push_back((*this)((int) (rows - i - 1), i));
    return obj;
}

VectorDouble Matrix::get_main_diag() const {
    if (rows != cols) exit(CANT_EXTRACT_DIAG);
    VectorDouble obj(rows);
    for (int i = 0; i < rows; ++i) obj.push_back((*this)(i, i));
    return obj;
}

Matrix &Matrix::operator+=(const Matrix &obj) {
    if (rows != obj.rows or cols != obj.cols) exit(WRONG_DIMENSION_MATRIX);
    *arr += *obj.arr;
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &obj) {
    if (rows != obj.rows or cols != obj.cols) exit(WRONG_DIMENSION_MATRIX);
    *arr -= *obj.arr;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &obj) {
    if (rows != obj.rows or cols != obj.cols) exit(WRONG_DIMENSION_MATRIX);
    *arr *= *obj.arr;
    return *this;
}

Matrix Matrix::operator+(const Matrix &obj) const {
    if (rows != obj.rows or cols != obj.cols) exit(WRONG_DIMENSION_MATRIX);
    Matrix res(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res(i, j) = (*this)(i, j) + obj(i, j);
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix &obj) const {
    if (rows != obj.rows or cols != obj.cols) exit(WRONG_DIMENSION_MATRIX);
    Matrix res(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res(i, j) = (*this)(i, j) - obj(i, j);
        }
    }
    return res;
}

Matrix &Matrix::operator=(const Matrix &obj) {
    if (this == &obj) return *this;
    rows = obj.rows;
    cols = obj.cols;
    delete arr;
    arr = new VectorDouble(rows * cols);
    size_t size = rows * cols;
    for (int i = 0; i < size; ++i) (*arr)[i] = (*obj.arr)[i];
    return *this;
}

Matrix::Matrix(size_t r, size_t c) {
    arr = new VectorDouble(r * c);
    rows = r;
    cols = c;
}

Matrix &Matrix::operator*=(int num) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            (*this)(i, j) *= num;
        }
    }
    return *this;
}

Matrix Matrix::operator*(int num) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res(i, j) = (*this)(i, j) * num;
        }
    }
    return res;
}

VectorDouble Matrix::operator*(const VectorDouble &obj) const {
    if (cols != obj.length()) exit(WRONG_DIMENSION_VECTOR);
    VectorDouble res;
    res = obj;
    for (int i = 0; i < rows; ++i) {
        double r = 0;
        for (int j = 0; j < cols; ++j) {
            r += (*this)(i, j) * obj[j];
        }
        res[i] = r;
    }
    return res;
}

Matrix Matrix::operator*(const Matrix &obj) const {
    if (cols != obj.rows) exit(WRONG_DIMENSION_MATRIX);
    Matrix res(rows, obj.cols);
    for (int k = 0; k < obj.cols; ++k) {
        for (int i = 0; i < obj.rows; ++i) {
            double r = 0;
            for (int j = 0; j < cols; ++j) {
                r += (*this)(i, j) * obj(j, k);
            }
            res(i, k) = r;
        }
    }
    return res;
}

void Matrix::put_row(const VectorDouble &obj, int row, char c) const {
    if (cols != obj.length()) exit(WRONG_DIMENSION_VECTOR);
    switch (c) {
        case '+':
            for (int i = 0; i < obj.length(); ++i) {
                (*this)(row, i) += obj[i];
            }
            break;
        case '-':
            for (int i = 0; i < obj.length(); ++i) {
                (*this)(row, i) -= obj[i];
            }
        default:
            return;
    }
}

void Matrix::put_col(const VectorDouble &obj, int col, char c) const {
    if (rows != obj.length()) exit(WRONG_DIMENSION_VECTOR);
    switch (c) {
        case '+':
            for (int i = 0; i < obj.length(); ++i) {
                (*this)(i, col) += obj[i];
            }
            break;
        case '-':
            for (int i = 0; i < obj.length(); ++i) {
                (*this)(i, col) -= obj[i];
            }
        default:
            return;
    }
}

double Matrix::determinant() {
    if (cols != rows) exit(WRONG_DIMENSION_MATRIX);
    if (rows == 2) return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    else {
        double res = 0;
        for (int i = 0; i < cols; ++i) {
            if (i % 2 == 0) res += (*this)(0, i) * (this->minor(0, i).determinant());
            else res += -(*this)(0, i) * (this->minor(0, i).determinant());
        }
        return res;
    }
}

Matrix Matrix::minor(int row, int col) {
    if (rows != cols) exit(WRONG_DIMENSION_MATRIX);
    if (rows - 1 == 0) return *this;
    Matrix res(rows - 1, cols - 1);
    int r = 0;
    int c;
    for (int i = 0; i < rows; ++i) {
        c = 0;
        if (i == row) continue;
        for (int j = 0; j < cols; ++j) {
            if (j == col) continue;
            res(r, c++) = (*this)(i, j);
        }
        r++;
    }
    return res;
}

Matrix::Matrix(const Matrix &obj) {
    arr = new VectorDouble(obj.rows * obj.cols);
    *arr = *obj.arr;
    rows = obj.rows;
    cols = obj.cols;
}

Matrix Matrix::trans() const {
    Matrix res(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            res(j, i) = (*this)(i, j);
        }
    }
    return res;
}

