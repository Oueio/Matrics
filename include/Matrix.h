#ifndef MATRIX_H
#define MATRIX_H

#include <Utility.h>
#include <VectorDouble.h>

class Matrix {
private:
    VectorDouble *arr;
    size_t rows;
    size_t cols;
public:
    Matrix();

    Matrix(VectorDouble *, size_t);

    Matrix(size_t, size_t);

    Matrix(const Matrix &);

    ~Matrix();

    friend std::istream &operator>>(std::istream &, Matrix &);

    double &operator()(int, int) const;

    friend std::ostream &operator<<(std::ostream &, const Matrix &);

    [[nodiscard]] VectorDouble get_row(int) const;

    [[nodiscard]] VectorDouble get_col(int) const;

    [[nodiscard]] VectorDouble get_main_diag() const;

    [[nodiscard]] VectorDouble get_side_diag() const;

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    Matrix &operator*=(const Matrix &);

    Matrix operator+(const Matrix &) const;

    Matrix operator-(const Matrix &) const;

    Matrix &operator=(const Matrix &);

    Matrix &operator*=(int);

    Matrix operator*(int) const;

    VectorDouble operator*(const VectorDouble &) const;

    [[nodiscard]] size_t get_rows() const { return rows; }

    [[nodiscard]] size_t get_cols() const { return cols; }

    Matrix operator*(const Matrix &) const;

    void put_row(const VectorDouble &obj, int row, char c) const;

    void put_col(const VectorDouble &obj, int col, char c) const;

    double determinant();

    Matrix minor(int, int);

    Matrix trans() const;
};


#endif //MATRIX_H