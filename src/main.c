#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: not enough arguments, need 1 path to image");
        exit(1);
    }

    if (argc > 2) {
        fprintf(stderr, "Error: Too many arguments\n");
        exit(1);
    }

    const char *file_path = argv[1];
    int width, height, components;

    unsigned char *img_data = stbi_load(file_path, &width, &height, &components, 0);
    if (img_data == NULL) {
        fprintf(stderr, "Error: Failed to load image %s\n", file_path);
        exit(1);
    }

    size_t img_size = sizeof(char) * width * height * components;
    unsigned char *new_img_data = (unsigned char*) malloc(img_size);
    if (new_img_data == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new image data.\n");
        exit(1);
    }

    for (unsigned char *p = img_data, *np = new_img_data; p != img_data + img_size; p += 1, np += 1) {
        *np = 255 - *p;
    };

    stbi_write_jpg("./output.jpg", width, height, 3, new_img_data, 100);

    stbi_image_free(img_data);
    free(new_img_data);
    exit(0);
}