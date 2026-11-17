#ifndef NEUROTRACE_MATRIX_HPP
#define NEUROTRACE_MATRIX_HPP

// includes:
#include <cstddef>
#include <iostream>
#include <vector>
#include "NeuroTraceError.hpp"

template <typename T>
class Matrix {
private:
    std::size_t rows_;
    std::size_t columns_;
    std::vector<T> data_;

public:
    // Constructor
    Matrix(std::size_t rows, std::size_t columns): rows_(rows), columns_(columns){
        // Check for zero dimensions
        if (rows_ == 0 || columns_ == 0){
            throw DimensionError(
                "(Matrix) Dimensions must be greater than zero."
            );
        }

        // Check potential overflow when calculating the total number of elements
        if (rows_ > data_.max_size() / columns_){
            throw DimensionError("(Matrix) Dimensions are too large.");
        }

        data_.resize(rows_ * columns_);
    }

    // Access to an element for reading and writing.
    T& operator()(std::size_t row, std::size_t column){

        // Check for out-of-bounds access
        if (row >= rows_ || column >= columns_){
            throw IndexError("(Matrix) Index out of bounds.");
        }

        return data_[row * columns_ + column];
    }

    // Access to an element for reading only.
    const T& operator()(std::size_t row, std::size_t column) const {

        // Check for out-of-bounds access
        if (row >= rows_ || column >= columns_){
            throw IndexError("(Matrix) Index out of bounds.");
        }

        return data_[row * columns_ + column];
    }

    // Print the dimensions and values of the matrix.
    friend std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix) {
        output << "Matrix ("<< matrix.rows_ << "x" << matrix.columns_<< "):\n";

        for (std::size_t row = 0; row < matrix.rows_; ++row){
            for (std::size_t column = 0; column < matrix.columns_; ++column){
                output << matrix(row, column) << ' ';
            }

            output << '\n';
        }

        return output;
    }

    // Getters

    std::size_t get_Rows() const{
        return rows_;
    }

    std::size_t get_Cols() const{
        return columns_;
    }
};

#endif // NEUROTRACE_MATRIX_HPP