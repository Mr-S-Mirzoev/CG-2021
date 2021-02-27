/*! \file matrix.h
    \brief Representation of matrix template (quite a common representation element)
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>

template <typename T>
class Matrix {
    std::vector < std::vector <T> > data_;
    size_t width, height;
public:
    Matrix(std::size_t width, std::size_t height);

    std::pair<int, int> size() const;

    std::vector <T> &operator [] (int i);
    std::vector <T> operator [] (int i) const;

    T &operator [] (std::pair <int, int> indexes);
    T operator [] (std::pair <int, int> indexes) const;

    friend std::ostream& operator<<(std::ostream& out, const Matrix <T>& mat) {
        auto sz = mat.size();
        for (int i = 0; i < sz.first; ++i) {
            for (int j = 0; j < sz.second; ++j) {
                if (j == 0)
                    out << mat.data_[i][j];
                else
                    out << " " << mat.data_[i][j];
            }
            
            if (i != sz.first - 1)
                out << std::endl;
        }

        return out;
    }
};

template <typename T>
Matrix<T>::Matrix(std::size_t width, std::size_t height): data_(height) {
    for (auto &line : data_)
        line.resize(width);
}

template <typename T>
std::vector <T> &Matrix<T>::operator [] (int i) {
    return data_[i];
}

template <typename T>
std::vector <T> Matrix<T>::operator [] (int i) const {
    return data_[i];
}

template <typename T>
T &Matrix<T>::operator [] (std::pair <int, int> indexes) {
    return (*this)[indexes.first][indexes.second];
}

template <typename T>
T Matrix<T>::operator [] (std::pair <int, int> indexes) const {
    return (*this)[indexes.first][indexes.second];
}

template <typename T>
std::pair <int, int> Matrix<T>::size() const {
    return {data_.size(), data_[0].size()};
}

#endif //MATRIX_H