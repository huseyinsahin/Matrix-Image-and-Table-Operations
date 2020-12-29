/*
    #Ad-Soyad = Huseyin Sahin
    #E-posta = huseyin.sahin@ceng.ktu.edu.tr
    #Proje = Matrix, Image and Table Operations
*/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

typedef uint32_t rgb;

template<class T> class matrix{
    protected:
        int row;
        int column;
        T **data;
    public:
        matrix();

        matrix(int r,int c,T fill);

        matrix(int r,int c,char letter);

        int getRowC();

        int getColC();

        void resize(int r,int c);

        void print();

        void print(string filename);

        void imwrite(string filename);

        matrix<T>& operator=(const matrix<T> &m1);

        matrix<T> operator+(const matrix<T> m1);

        matrix<T> operator-(const matrix<T> m1);

        matrix<T> operator*(const matrix<T> m1);

        matrix<T> operator+(double skaler);

        matrix<T> operator-(double skaler);

        matrix<T> operator*(double skaler);

        matrix<T> operator/(int skaler);

        matrix<T> operator%(int skaler);

        matrix<T> operator^(int skaler);

        matrix<T> transpoze();

        matrix emul(const matrix<T> m1);

        matrix<T> sub_matrix(int x,int y);

        matrix<T> minor_matrix();

        matrix<T> cofactor();

        matrix<T> inv();

        double det();
};

template<typename T>
matrix<T>::matrix(){
    int i,j;
    row = 10;
    column = 10;
    data = new T*[row];
    for(i = 0;i < row;i++){
        data[i] = new T[column];
        for(j = 0;j < column;j++){
            data[i][j] = 0;
        }
    }
}

template<typename T>
matrix<T>::matrix(int r,int c,T fill){
    int i,j;
    row = r;
    column = c;
    data = new T*[row];
    for(i = 0;i < row;i++){
        data[i] = new T[column];
        for(j = 0;j < column;j++){
            data[i][j] = fill;
        }
    }
}

template<typename T>
matrix<T>::matrix(int r,int c,char letter){
    int i,j;
    row = r;
    column = c;
    switch(letter){
        case 'r' :
            data = new T*[row];
            for(i = 0;i < row;i++){
                data[i] = new T[column];
                for(j = 0;j < column;j++){
                    data[i][j] = rand() % 256;
                }
            }
        break;
        case 'e' :
            data = new T*[row];
            for(i = 0;i < row;i++){
                data[i] = new T[column];
                for(j = 0;j < column;j++){
                        data[i][j] = (i == j)? 1 : 0;
                }
            }
        break;
    }
}

template<typename T>
int matrix<T>::getRowC(){
    return this->row;
}

template<typename T>
int matrix<T>::getColC(){
    return this->column;
}

template<typename T>
void matrix<T>::resize(int r,int c){
    int i,j;
    
    for(i = 0;i < row;i++){
        delete data[i];
    }
    delete data;
    
    
    row = r;
    column = c;
    data = new T*[row];
    for(i = 0;i < row;i++){
        data[i] = new T[column];
        for(j = 0;j < column;j++){
            data[i][j] = 0;
        }
    }
}

template<typename T>
void matrix<T>::print(){
    int i,j;
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            cout << data[i][j] << "   ";
        }
        cout << endl << endl;
    }
}

template<typename T>
void matrix<T>::print(string filename){
    int i,j;
    ofstream file(filename);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            file << data[i][j] << "  ";
        }
        file << endl << endl;
    }
    file.close();
}

template<typename T>
void matrix<T>::imwrite(string filename){
    int i,j;
    ofstream file(filename);
    int iter = 0;
    file << (char)row;
    file << (char)column;
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            file << (char)data[i][j];
            iter++;
        }
    }
    cout << iter << endl;
    file.close();
}

template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T> &m1){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    if(row != m1.row || column != m1.column){
        cout << "matrislerin boyutlari ayni olmali";
    }else{
        for(i = 0;i < row;i++){
            for(j = 0;j < column;j++){
                data[i][j] = m1.data[i][j];
            }
        }
    }
    return *this;
    
}


template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T> m1){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    if(row != m1.row || column != m1.column){
        cout << "Matrislerin boyutlari ayni olmali!!";
    }else{
        for(i = 0;i < row;i++){
            for(j = 0;j < column;j++){
                m2.data[i][j] = data[i][j] + m1.data[i][j];
            }
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T> m1){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    if(row != m1.row || column != m1.column){
        cout << "Matrislerin boyutlari ayni olmali!!";
    }else{
        for(i = 0;i < row;i++){
            for(j = 0;j < column;j++){
                m2.data[i][j] = data[i][j] - m1.data[i][j];
            }
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T> m1){
    int i,j,k;
    double sum = 0;
    matrix<T> m2(row,m1.column,(T)0);
    if(column != m1.row){
        cout << "Bu matrisler carpilamaz!!" << endl;
    }else{
        for(i = 0;i < m2.row;i++){
            for(j = 0;j < m2.column;j++){
                for(k = 0;k < row;k++){
                    sum += data[i][k] * m1.data[k][j]; 
                }
                m2.data[i][j] = (sum > 1e-10)? sum : 0;
                sum = 0;
            }
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator+(double skaler){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            m2.data[i][j] = data[i][j] + skaler;
        }
    }
    return m2;
}
template<typename T>
matrix<T> matrix<T>::operator-(double skaler){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            m2.data[i][j] = data[i][j] - skaler;
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator*(double skaler){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            m2.data[i][j] = data[i][j] * skaler;
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator/(int skaler){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            m2.data[i][j] = data[i][j] / skaler;
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator%(int skaler){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            m2.data[i][j] = data[i][j] % skaler;
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::operator^(int skaler){
    int i,j,k;
    matrix<T> m2(row,column,(T)0);
    m2 = (*this);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            for(k = 1;k < skaler;k++){
                m2.data[i][j] *= data[i][j];
            }
        }
    }
    return m2;
}

template<typename T>
matrix<T> matrix<T>::transpoze(){
    int i,j;
    matrix<T> m2(column,row,(T)0);
    for(i = 0;i < m2.row;i++){
        for(j = 0;j < m2.column;j++){
            m2.data[i][j] = data[j][i];
        }
    }
    return m2;
}


template<typename T>
matrix<T> matrix<T>::inv(){
    if(row != column){
        cout << "Bu matrisin tersi alinamaz!!" << endl;
    }else{
        return this->cofactor().transpoze() * (1 / this->det());
    }
    return *this;
}

template<typename T>
matrix<T> matrix<T>::cofactor(){
    int i,j;
    matrix<T> m1(row,column,(T)0);
    m1 = this->minor_matrix();
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            if((i + j) % 2 != 0){
                m1.data[i][j] *= -1;
            }
        }
    }
    return m1;
}

template<typename T>
matrix<T> matrix<T>::minor_matrix(){
    int i,j;
    matrix<T> m1(row,column,(T)0);
    for(i = 0;i < row;i++){
        for(j = 0;j < column;j++){
            m1.data[i][j] = this->sub_matrix(i,j).det(); 
        }
    }
    return m1;
}

template<typename T>
matrix<T> matrix<T>::sub_matrix(int x,int y){
    int i,j,k,l;
    matrix<T> m1(row - 1,column - 1,(T)0);
    k = l = 0;
    for(i = 0;i < row;i++){
        if(i == x)continue;
        for(j = 0;j < column;j++){
            if(j == y)continue;
            m1.data[k][l] = (*this).data[i][j];
            l++;
        }
        l = 0;
        k++;
    }
    return m1;
}

template<typename T>
matrix<T> matrix<T>::emul(const matrix<T> m1){
    int i,j;
    matrix<T> m2(row,column,(T)0);
    if(row != m1.row || column != m1.column){
        cout << "Matrislerin boyutlari ayni olmali!!" << endl;
    }else{
        for(i = 0;i < row;i++){
            for(j = 0;j < column;j++){
                m2.data[i][j] = data[i][j] * m1.data[i][j];
            }
        }
    }
    return m2;
}

template<typename T>
double matrix<T>::det(){
    int i, sum = 0;
    if(this->row != this->column){
        cout << "Bu matrisin determinanti alinamaz!!" << endl;
    }else if(this->row == 1){
        return data[0][0];
    }else{
        for(i = 0;i < row;i++){
            sum += this->data[i][0] * this->sub_matrix(i,0).det() * 
            ((i % 2)? -1 : 1);
        }
    }
    return sum;
}

struct bmp_header_t
{
    char bm[2];
    uint32_t file_size;
    uint16_t app_s1;
    uint16_t app_s2;
    uint32_t bitmap_offset;    
};

struct dib_header_t
{
    uint32_t dib_header_size;
    uint32_t bitmask_width;
    uint32_t bitmask_height;
    uint16_t num_of_color_planes_used;
    uint16_t num_of_bits_per_pixel;
    uint32_t compression;
    uint32_t bitmap_data_size;
    uint32_t pr_hor;
    uint32_t pr_ver;
    uint32_t num_of_colors_in_palette;
    uint32_t num_of_colors_important;
};

template<typename T> class image : public matrix<T>{
    private:
        uint16_t color_palette_size;
        char * color_palette;
        char * header;
        string file_name;
        bmp_header_t * bmp_header;
        dib_header_t * dib_header;
    public:
        image();
        
        image(int w,int h);

        image(string filename,const string format);

        void imread(string filename,const string format);

        void imwrite(string filename,string format);

        void color2gray();

        void gray2binary(int threshold);
};

template<typename T>
void image<T>::imread(string filename,const string format){

    ifstream file;
    file.open(filename.c_str(), ios::in | ios::binary);
    
    if(file.fail()){
        cout << "Dosya bulunamadi!!" << endl;
    }

    if(!format.compare("bmp")){
        char buffer[2048]; /* generic buffer */

        file.seekg(0,ios::beg);

        file.read(buffer, 2);
        memcpy(this->bmp_header->bm, buffer, 2);

        if(this->bmp_header->bm[0] != 'B' || 
            this->bmp_header->bm[1] != 'M'){
            cout << this->bmp_header->bm[0] << "not bmp file" << endl;
            return;
        } else {
            cout << bmp_header->bm << endl;
        }
        
        /* reading 16 bytes bmp header part */
        
        file.read(buffer, 4);
        memcpy(&(this->bmp_header->file_size), buffer, 4);
       
        cout << "bmp header file size : " 
             << bmp_header->file_size << endl;

        file.read(buffer, 2);
        memcpy(&(this->bmp_header->app_s1), buffer, 2);
        cout << "bmp header application reserved 1 : " 
             << bmp_header->app_s1 << endl;

        file.read(buffer, 2);
        memcpy(&(this->bmp_header->app_s2), buffer, 2);
        cout << "bmp header application reserved 2 : " 
             << bmp_header->app_s2 << endl;

        file.read(buffer, 4);
        memcpy(&(this->bmp_header->bitmap_offset), buffer, 4);
        cout << "bmp header bitmap offset : " 
             << bmp_header->bitmap_offset << endl;
        
        /* reading 40 bytes dib header part */

        file.read(buffer, 4);
        memcpy(&(this->dib_header->dib_header_size), buffer, 4);
        cout << "dib header header size : " 
             << dib_header->dib_header_size << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->bitmask_width), buffer, 4);
        cout << "dib header bitmask width : " 
             << dib_header->bitmask_width << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->bitmask_height), buffer, 4);
        cout << "dib header bitmask height : "
             << dib_header->bitmask_height << endl;

        file.read(buffer, 2);
        memcpy(&(this->dib_header->num_of_color_planes_used),buffer,2);
        cout << "dib header number of channels : " 
             << dib_header->num_of_color_planes_used << endl;

        file.read(buffer, 2);
        memcpy(&(this->dib_header->num_of_bits_per_pixel), buffer, 2);
        cout << "dib header number of bits per pixel : " 
             << dib_header->num_of_bits_per_pixel << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->compression), buffer, 4);
        cout << "dib header compression flag : "
             << dib_header->compression << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->bitmap_data_size), buffer, 4);
        cout << "dib header raw bitmap data size (bytes) : " 
             << dib_header->bitmap_data_size << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->pr_hor), buffer, 4);
        cout << "dib header print resolution hor : " 
             << dib_header->pr_hor << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->pr_ver), buffer, 4);
        cout << "dib header print resolution ver : " 
             << dib_header->pr_ver << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->num_of_colors_in_palette),buffer,4);
        cout << "dib header number of colors in palette : " 
             << dib_header->num_of_colors_in_palette << endl;

        file.read(buffer, 4);
        memcpy(&(this->dib_header->num_of_colors_important),buffer,4);
        cout << "dib header number of important colors (default = 0) :" 
             << dib_header->num_of_colors_important << endl;

        this->color_palette_size = (this->bmp_header->file_size - 
        ((this->dib_header->bitmask_width * 
        this->dib_header->bitmask_height * 
        (this->dib_header->num_of_bits_per_pixel >> 3)) + 54));
        this->color_palette = new char[color_palette_size];
        file.read(this->color_palette, color_palette_size);
        
        cout << "seeking bitmap ! offset : " 
             << bmp_header->bitmap_offset << endl;
        file.seekg(this->bmp_header->bitmap_offset, ios::beg);
        
        this->resize(this->dib_header->bitmask_width, 
        this->dib_header->bitmask_height);

        for(int i = 0; i < this->row; i++){
            for(int j = 0; j < this->column; j++){
                for(int k = 0; k < 4; k++){
                    this->data[i][j] = this->data[i][j] << 8;
                    if(k < this->dib_header->num_of_bits_per_pixel 
                        >> 3){ // divided to 8
                        file.read(buffer,1);
                        this->data[i][j] |= (uint8_t) buffer[0];
                    }
                }
            }
        }
        
        cout << "done ! " << endl;
        return;
    }else{
        char ch;
        file.seekg (0, ios::beg);
        file.get(ch);
        int temp = ch;
        if(temp < 0)
            temp = 256+temp;
        int sutun =  temp;
        file.get(ch);
        temp = ch;

        if(temp < 0)
            temp = 256+temp;

        int satir =  temp;
        this->resize(satir,sutun);
        //cout << this->row << endl;
        //cout << this->column << endl;
        for(int i = 0;i < this->row;i++){
            for(int j = 0;j < this->column;j++){
                file.get(ch);
                temp = ch;
                if(temp < 0)
                    temp = 256+temp;
                this->data[i][j] = temp;
            }
        }
    }
    file.close();
}

template<typename T>
void image<T>::imwrite(string filename,string format){
    char buffer[16]; // generic buffer
    
    ofstream file;
    file.open(filename, ofstream::out | ofstream::binary);

    if(!format.compare("bmp")){
        this->bmp_header->bitmap_offset = 54 + 1024;
        this->dib_header->bitmap_data_size = 
        (this->dib_header->bitmask_height * 
        this->dib_header->bitmask_width) * 
        (this->dib_header->num_of_bits_per_pixel >> 3);
        this->bmp_header->file_size =1024 + 
        (this->bmp_header->bitmap_offset + 
        this->dib_header->bitmap_data_size);
        file.write((char *)&(this->bmp_header->bm),2);
        file.write((char *)&(this->bmp_header->file_size),4);
        file.write((char *)&(this->bmp_header->app_s1),2);
        file.write((char *)&(this->bmp_header->app_s2),2);
        file.write((char *)&(this->bmp_header->bitmap_offset),4);
        file.write((char *)&(this->dib_header->dib_header_size),4);
        file.write((char *)&(this->dib_header->bitmask_width),4);
        file.write((char *)&(this->dib_header->bitmask_height),4);
        file.write((char *)
        &(this->dib_header->num_of_color_planes_used),2);
        file.write((char *)
        &(this->dib_header->num_of_bits_per_pixel),2);
        file.write((char *)&(this->dib_header->compression),4);
        file.write((char *)&(this->dib_header->bitmap_data_size),4);
        file.write((char *)&(this->dib_header->pr_hor),4);
        file.write((char *)&(this->dib_header->pr_ver),4);
        file.write((char *)
        &(this->dib_header->num_of_colors_in_palette),4);
        file.write((char *)
        &(this->dib_header->num_of_colors_important),4);

        file.write((char *)this->color_palette, 1024); // remove this
        for(int i = 0; i < this->row; i++){
            for(int j = 0; j < this->column; j++){
                for(int k = 0; k < 
                    (this->dib_header->num_of_bits_per_pixel >> 3);k++)
                    {buffer[0] = (char)(this->data[i][j] >> 
                    (8 * (3 - k)) & 0xff);
                    //cout << hex << ((int)buffer[0] & 0xff) << " ";
                    file.write((char *)buffer, sizeof(char));
                }
            }
            //cout << endl;
        }

        file.close();
    }
    else{
        file << (char)this->column;
        file << (char)this->row;
    }
    int cnt = 0; 
    for(int i=0; i<this->row; i++){
        for(int j=0; j<this->column; j++){
            file << (char)this->data[i][j];
            cnt++;
            if(cnt == 3){
                //file << (char) 0xFF;
                cnt = 0;
            }
        }
    }
    file.close();
}
template<typename T>
image<T>::image():matrix<T>(255,255,0){
    bmp_header = new bmp_header_t;
    dib_header = new dib_header_t;
}

template<typename T>
image<T>::image(int w,int h):matrix<T>(h,w,(T)0){
    bmp_header = new bmp_header_t;
    dib_header = new dib_header_t;
}

template<typename T>
image<T>::image(string filename,const string format){
    bmp_header = new bmp_header_t;
    dib_header = new dib_header_t;
    this->imread(filename,format);
}     

template<typename T>
void image<T>::color2gray(){
    this->dib_header->num_of_bits_per_pixel = 8;
    for(int i = 0;i < this->row;i++){
        for(int j = 0;j < this->column;j++){
            this->data[i][j] = (uint32_t)(0.2989*((0xffffffff  & 
            this->data[i][j]) >> 24) + 0.5870*((0xffffff  & 
            this->data[i][j]) >> 16) + 0.1140*((0xffff  & 
            this->data[i][j]) >> 8)) << 24;
        }
    }
}

template<typename T>
void image<T>::gray2binary(int threshold){
    for(int i = 0;i < this->row;i++){
        for(int j = 0;j < this->column;j++){
            this->data[i][j] = 
            ((this->data[i][j] > threshold)? 0xffffff00 : 0x00000000);
        }
    }
}



template<typename T> class table : public matrix<T>{
    private:
        string *row_names;
        string *column_names;
    public:
        table();

        table(int r,int c,int d);

        table(int r,int c,char t);

        T itemAt(int x,int y);

        T itemAt(string code);

        T itemAt(string row,string col);

        void setRowNames(string rows[],int n);

        void setColumnNames(string cols[],int n);

        void print();
};


template<typename T>
table<T>::table():matrix<T>(){
    row_names = new string[10];
    column_names = new string[10];
    string temp = "A";
    for(int i = 0; i < this->row; i++){
        row_names[i] = to_string(i);
    }
    for(int i = 0; i < min(this->column, 26) ; i++){
        column_names[i] = temp[0] + i;
    }
}

template<typename T>
table<T>::table(int r,int c,int d):matrix<T>(r,c,d){
    row_names = new string[r];
    column_names = new string[c];
    string temp = "A";
    for(int i = 0; i < this->row; i++){
        row_names[i] = to_string(i);
    }
    for(int i = 0; i < min(this->column, 26) ; i++){
        column_names[i] = temp[0] + i;
    }
}

template<typename T>
table<T>::table(int r,int c,char t):matrix<T>(r,c,t){
    row_names = new string[r];
    column_names = new string[c];
    string temp = "A";
    for(int i = 0; i < this->row; i++){
        row_names[i] = to_string(i);
    }
    for(int i = 0; i < min(this->column, 26) ; i++){
        column_names[i] = temp[0] + i;
    }
}

template<typename T>
T table<T>::itemAt(int x,int y){
    return this->data[x][y];
}

template<typename T>
T table<T>::itemAt(string code){
    int row = code[1] - '0';
    int col = code[0] - 'A';
    return this->data[row][col];
}

template<typename T>
T table<T>::itemAt(string row,string col){
    return this->data[row[0] - '0'][col[0] - 'A'];
}

template<typename T>
void table<T>::setRowNames(string rows[],int n){
    int i;
    for(i = 0;i < n;i++){
        if(rows[i].length() > 8){
            cout << "Satir uzunlugu 8 karakterden fazla olmamali!!" 
                 << endl;
        }else{
            row_names[i] = rows[i];
        }
    }
}

template<typename T>
void table<T>::setColumnNames(string cols[],int n){
    int i;
    for(i = 0;i < n;i++){
        if(cols[i].length() > 4){
            cout << "Sutun uzunlugu 4 karakterden fazla olmamali!!" 
                 << endl;
        }else{
            column_names[i] = cols[i];
        }
    }
}

template<typename T>
void table<T>::print(){
    int i,j;
    cout << "\t";
    for(i = 0;i < this->column;i++){
        cout << column_names[i] << "\t";
    }
    cout << endl;
    for(i = 0;i < this->row;i++){
        cout << row_names[i] << "\t";
        for(j = 0;j < this->column;j++){
            cout << this->data[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
   
   /* DENEMELER   

    matrix<int> a(3,4,5);
    a.print();

    matrix<int> *h;
    h = new matrix<int>(5,5,10);

    matrix<int> *m;
    m = new matrix<int>(5,5,4);

    (*m) = (*m) - (*h);

    (*m).print();

    table<int> t(5,7,'r');
    t.print();

    image<rgb> image1("image_file2.bmp","bmp");
    image1.imwrite("kopya","bmp");
    
    */
    
} 
    
