#ifndef IMAGE_H
#define IMAGE_H

#include <vector>

class Image {
    public:
        Image(char *);
        int get_width();
        int get_height();
        int get_color_depth();
        void fill(char *);
        void print();

        void flip(char orientation);
        void zoom();
        void rmcolor();
        void puzzle();
    private:
        int width, height, color_depth;
        std::vector<short int> t_red;
        std::vector<short int> t_green;
        std::vector<short int> t_blue;
        std::vector<std::vector<short int>> red;
        std::vector<std::vector<short int>> green;
        std::vector<std::vector<short int>> blue;

};

#endif /* IMAGE_H */
