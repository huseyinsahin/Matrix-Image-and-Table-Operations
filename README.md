# Matris, Görüntü ve Tablo İşlemleri / Matrix, Image and Table Operations

Veri bilimcisinin matris işlemleri, görüntü işleme uygulamaları yapması ve bazı tablo verilerini incelemesi gerekmektedir. Bu nedenle, veri bilimcisinin kullanabileceği bir uygulama oluşturmak oldukça önemlidir. Bu proje, veri bilimcinin yapmak istediği gerekli eylemleri içerir. / It is necessary for the data scientist to perform matrix operations, image processing applications and to study some tabular data. Therefore, it is necessary to create an application that the data scientist can use. This project includes the necessary actions the data scientist wants to do.

## Proje Özellikleri / Project Features
Tamsayı değerleri olan bir Matrix sınıfı bulunur. Ana fonksiyonda aşağıdaki işlemleri matris sınıfıyla yapılabilir. / There is a Matrix class with integer values. In the main function, the following operations can be done with the matrix class.
- Matrix<int> *m1 = new Matrix<int>(); → 0 değerli 10x10 matris. / 10x10 matrix with zeros.
- Matrix<int> *m2 = new Matrix<int>(3,2,1); → 1 değerli 3x2 matris. / 3x2 matrix with ones.
- Matrix<int> *m2 = new Matrix<int>(3,4,9); → 9 değerli 3x4 matris. / 3x4 matrix with 9’s.
- Matrix<int> *m3 = new Matrix<int>(5,5,'e'); → 5x5 birim matris. / 5x5 identification matrix. 
- Matrix<int> *m4 = new Matrix<int>(15,15,'r'); → değerleri 0-255 arasında rastgele değerler olan 15x15 matris. / 15x15 matrix with random integers between [0-255].
- m2->resize(5,5); → Matris oluşturulduktan sonra boyutu değiştirilebilir. / After matrix is created, its size can be changed.
- m3->print(); → Matris ekrana yazdırılabilir. / Matrix can be printed on the screen.
- m3->print(“file.txt”); → Matris dosyaya yazdırılabilir. / Matrix can be printed to file.
#### Matris İşlemleri / Matrix Operations
- (*m1) = (*m1) + (*m2); → m1, m2, pointer ise
- m1 = m1 - m2; → m1, m2, nesne ise
- m1 = m1 * m2;
- m1->T(); → Transpoze
- m1->emul(m2); → eleman düzeyinde çarpma. / elementwise multiply
- m1->inv() → matrisin tersi. / matrix inversion if available 
- m1->det() → matrisin determinantı / determinant of matrix
#### Matris Skalar İşlemleri / Matrix Scalar Operations
- m1 = m1 + 12;
- m1 = m1 - 20;
- m1 = m1 * 10;
- m1 = m1 / 10;
- m1 = m1 % 10;
- m1 = m1 ^ 2; →üs alma / power
