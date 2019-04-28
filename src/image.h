#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

typedef std::vector<short int> vector;
typedef std::vector<vector> doubleVector;
typedef std::vector<doubleVector> doubleVectorWrapper;
typedef std::vector<doubleVectorWrapper> tripleVectorWrapper;

class Image {
    public:
        Image(std::string);
        int get_width();
        int get_height();
        int get_color_depth();
        int get_type();
        std::string to_string();
        void crop(int, int, int, int);
        void write();
        void flip(char orientation);
        void zoom();
        void pause();
        void rmcolor();
        void puzzle();
    private:
        void get_square(int, int, int, int, int);
        void colors_to_base(doubleVectorWrapper &, tripleVectorWrapper &, int, int, int);
        void base_to_colors(tripleVectorWrapper &, doubleVectorWrapper &, int, int, int);
        void fill_with_value(doubleVector &, short int);
        int round_to_n_multiple(int,int);
        int type, width, height, color_depth;
        void set_dims(int, int);
        doubleVector red;
        doubleVector green;
        doubleVector blue;
};

#endif /* IMAGE_H */
