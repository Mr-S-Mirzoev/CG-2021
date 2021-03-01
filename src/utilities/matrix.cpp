#include "utilities/matrix.h"

Matrix<Pixel> from_image(const Image &img) {
    Matrix<Pixel> m(img.Width(), img.Height());
    for (int i = 0; i < img.Width(); ++i)
        for (int j = 0; j < img.Height(); ++j)
            m[{i, j}] = img.GetPixel(i, j);
    
    return m;
}

Image to_image(const Matrix <Pixel>& m) {
    auto sz = m.size();
    Image img(sz.first, sz.second, 4);

    for (int i = 0; i < img.Width(); ++i)
        for (int j = 0; j < img.Height(); ++j)
            img.PutPixel(i, j, m[{i, j}]);

    return img;
}