#ifndef VECTOR_HPP
#define VECTOR_HPP

// includes:
#include <cstddef>
#include <iostream>
#include <vector>
#include <initializer_list>
#include "NeuroTraceError.hpp"

template <typename T>
class Vector {
private:
    std::vector<T> data_;

public:
    // Constructor
    explicit Vector(std::size_t size): data_(size) {
        // Las dimensiones deben ser mayores que cero
        if (size == 0){
            throw DimensionError(
                "(Vector) Las dimensiones deben ser mayores que cero."
            ); 
        }
    }

    // permite crear un vector a partir de una lista de inicialización.
    Vector(std::initializer_list<T> list): data_(list) {
        if (data_.empty()){
            throw DimensionError(
                "(Vector) Las dimensiones deben ser mayores que cero."
            );
        }
    }

    // Accede a un elemento para lectura y escritura.
    T& operator[](std::size_t index){
        if (index >= data_.size()){
            throw IndexError("(Vector) Indice fuera de los límites.");
        }
        return data_[index];
    }

    // Accede a un elemento para solo lectura.
    const T& operator[](std::size_t index) const {
        if (index >= data_.size()){
            throw IndexError("(Vector) Indice fuera de los límites.");
        }
        return data_[index];
    }

    // Devuelve el tamaño del vector.
    std::size_t size() const {
        return data_.size();
    }

    // suma otro vector al vector actual
    Vector& operator+=(const Vector& other) {
        if (size() != other.size()) {
            throw DimensionError(
                "(Vector) Dimensiones incompatibles para la suma."
            );
        }

        for (std::size_t i = 0; i < size(); ++i) {
            data_[i] += other.data_[i];
        }

        return *this;
    }

    // Imprime el vector y sus datos en la terminal.
    friend std::ostream& operator<<(std::ostream& output, const Vector<T>& vector) {
        output << "Vector (" << vector.size() << "): {";
        for (std::size_t i = 0; i < vector.size(); ++i) {
            output << vector.data_[i];
            if (i < vector.size() - 1) {
                output << ", ";
            }
        }
        output << "}";

        return output;
    }
};

/*
Para representar los pixeles del lienzo para la red neuronal, se utiliza un vector 
de 784 elementos (28x28) para almacenar los valores de intensidad de cada pixel. 
Cada elemento del vector corresponde a un pixel en la imagen, y su valor representa 
la intensidad del color en escala de grises (0-255).
*/

#endif // VECTOR_HPP