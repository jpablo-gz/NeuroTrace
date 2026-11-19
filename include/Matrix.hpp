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
    explicit Matrix(std::size_t rows, std::size_t columns): rows_(rows), columns_(columns){
        // Las dimensiones deben ser mayores que cero
        if (rows_ == 0 || columns_ == 0){
            throw DimensionError(
                "(Matrix) Las dimensiones deben ser mayores que cero."
            );
        }

        // Posible overflow si las dimensiones son demasiado grandes
        if (rows_ > data_.max_size() / columns_){
            throw DimensionError(
                "(Matrix) Las dimensiones son demasiado grandes."
            );
        }

        data_.resize(rows_ * columns_);
    }

    // usamos un operador de llamada a función para acceder a los elementos de la matriz.

    // Accede a un elemento para lectura y escritura.
    T& operator()(std::size_t row, std::size_t column){

        // Verificar que el indice esté dentro de los límites
        if (row >= rows_ || column >= columns_){
            throw IndexError("(Matrix) Indice fuera de los límites.");
        }

        return data_[row * columns_ + column];
    }

    // Accede a un elemento para solo lectura.
    const T& operator()(std::size_t row, std::size_t column) const {

        // Verificar que el indice esté dentro de los límites
        if (row >= rows_ || column >= columns_){
            throw IndexError("(Matrix) Indice fuera de los límites.");
        }

        return data_[row * columns_ + column];
    }

    // Imprime la matriz y sus datos en la terminal. 
    friend std::ostream& operator<<(std::ostream& output, const Matrix<T>& matrix) {
        output << "Matrix ("<< matrix.rows_ << "x" << matrix.columns_<< "):" << std::endl;

        for (std::size_t row = 0; row < matrix.rows_; ++row){
            for (std::size_t column = 0; column < matrix.columns_; ++column){
                output << matrix(row, column) << ' ';
            }

            output << std::endl;
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