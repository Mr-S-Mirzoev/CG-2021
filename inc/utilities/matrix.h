/*! \file matrix.h
    \brief Representation of matrix template (quite a common representation element)
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <ostream>

template <typename T>
class Matrix {
    std::vector <T> data_ {};
    size_t width_{0}, height_{0};
public:
    Matrix(std::size_t width, std::size_t height);
    Matrix();

    void resize(std::size_t width, std::size_t height);

    std::pair<int, int> size() const;

    std::vector <T> operator [] (int i) const;

    T &operator [] (std::pair <int, int> indexes);
    T operator [] (std::pair <int, int> indexes) const;

    friend std::ostream& operator<<(std::ostream& out, const Matrix <T>& mat) {
        auto sz = mat.size();
        for (int i = 0; i < sz.first; ++i) {
            for (int j = 0; j < sz.second; ++j) {
                if (j == 0)
                    out << mat.data_[i * sz.first + j];
                else
                    out << " " << mat.data_[i * sz.first + j];
            }
            
            if (i != sz.first - 1)
                out << std::endl;
        }

        return out;
    }
};

template <typename T>
Matrix<T>::Matrix(std::size_t width, std::size_t height): 
    data_(width * height), width_(width), height_(height) {}

template <typename T>
void Matrix<T>::resize(std::size_t width, std::size_t height) {
    if (width_ == 0 && height_ == 0) {
        width_ = width;
        height_ = height;
        data_.resize(width_ * height_);
    } else if (width == width_ && height > height_) {
        height_ = height;
        data_.resize(width_ * height_);
    } else {
        std::vector <T> cpy{std::move(data_)};
        data_ = std::vector<T>{width * height};

        for (int i = 0; i < width_; ++i)
            for (int j = 0; j < height_; ++j)
                data_[i * width + j] = cpy[i * width_ + j];
    }
}

template <typename T>
std::vector <T> Matrix<T>::operator [] (int i) const {
    return std::vector<T>(data_.begin() + i * width_, data_.begin() + (i + 1) * width_);
}

template <typename T>
T &Matrix<T>::operator [] (std::pair <int, int> indexes) {
    return (*this)[indexes.first * width_ + indexes.second];
}

template <typename T>
T Matrix<T>::operator [] (std::pair <int, int> indexes) const {
    return (*this)[indexes.first * width_ + indexes.second];
}

template <typename T>
std::pair <int, int> Matrix<T>::size() const {
    return {width_, height_};
}

#endif //MATRIX_H