#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

typedef std::vector<short int> vector;
typedef std::vector<vector> doubleVector;
typedef std::vector<doubleVector> doubleVectorWrapper;

class Image {
    public:
        Image(char *);
        int get_width();
        int get_height();
        int get_color_depth();
        int get_type();
        void fill(char *);
        void print();

        void crop(int, int, int, int);
        void write();
        void flip(char orientation);
        void zoom();
        void rmcolor();
        void puzzle();
    private:
        void get_square(int, int, int, int, int);
        void fill_with_value(doubleVector &, short int);
        int round_to_n_multiple(int,int);
        void pause();
        int width, height, color_depth;
        char * type;
        vector t_red;
        vector t_green;
        vector t_blue;
        doubleVector red;
        doubleVector green;
        doubleVector blue;



};

#endif /* IMAGE_H */
