#include "Image_Class.h"
#include <iostream>
using namespace std;
Image check_name(string& imgName) {
    Image img;
    while (true) {
        try {
            img = Image(imgName);
            cout << "Image loaded successfully." << endl;
            return img;
        } catch (std::invalid_argument const& e) {
            cout << "Error loading image: " << e.what() << ". Please try again." << endl;
            cout << "Please enter the image file name again: ";
            cin >> imgName;
        }
    }
}
Image load_img(string img_name) {
    return Image(img_name);
}
void save_img(Image img, string& img_name, string imgName) {
    char choice;
    cout << "Do you want to save the image with the same file name? (y/n): ";
    cin >> choice;

    if (choice == 'y') {
        img.saveImage(imgName);
        cout << "Image saved as " << imgName << endl;
    } else {
        cout << "Please enter the new name with format: ";
        string new_name;
        cin >> new_name;
        img.saveImage(new_name);
        cout << "Image saved as " << new_name << endl;
    }
}
Image invert_image(Image img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < 3; k++) {
                img(i, j, k) = 255 - img(i, j, k);
            }
        }
    }
    return img;
}
Image grey_scale(Image img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            int red = img(j, i, 0);
            int green = img(j, i, 1);
            int blue = img(j, i, 2);
            int avg = (red + green + blue) / 3;
            img(j, i, 0) = avg;
            img(j, i, 1) = avg;
            img(j, i, 2) = avg;
        }
    }
    return img;
}
Image merge_img(Image img1, Image img2) {
    if (img1.width == img2.width && img1.height == img2.height) {
        Image merged_img(img1.width, img1.height);
        for (int i = 0; i < img1.width; i++) {
            for (int j = 0; j < img1.height; j++) {
                int red   = (img1(i, j, 0) + img2(i, j, 0)) / 2;
                int green = (img1(i, j, 1) + img2(i, j, 1)) / 2;
                int blue  = (img1(i, j, 2) + img2(i, j, 2)) / 2;
                merged_img(i, j, 0) = red;
                merged_img(i, j, 1) = green;
                merged_img(i, j, 2) = blue;
            }
        }
        return merged_img;
    } else {
        int min_width, min_height;
        if (img1.width < img2.width) {
            min_width = img1.width;
        }else {
            min_width = img2.width;
        }if (img1.height < img2.height) {
            min_height = img1.height;
        }else {
            min_height = img2.height;
        }
        Image merged_img(min_width, min_height);
        for (int i = 0; i < min_width; i++) {
            for (int j = 0; j < min_height; j++) {
                int red   = (img1(i, j, 0) + img2(i, j, 0)) / 2;
                int green = (img1(i, j, 1) + img2(i, j, 1)) / 2;
                int blue  = (img1(i, j, 2) + img2(i, j, 2)) / 2;
                merged_img(i, j, 0) = red;
                merged_img(i, j, 1) = green;
                merged_img(i, j, 2) = blue;
            }
        }
        return merged_img;
    }
}
int main() {
    string imgName;
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> imgName;
    Image current_img = check_name(imgName);
    int x = -1;
    while (x != 0) {
        cout << "\n1: Load new image\n"
                "2: Grey scale filter\n"
                "3: Invert filter\n"
                "4: Merge filter\n"
                "5: Save the image\n"
                "0: Exit\n";
        cin >> x;
        switch (x) {
            case 1:
                cout << "Enter new image file name: ";
                cin >> imgName;
                current_img = check_name(imgName);
                break;
            case 2:
                current_img = grey_scale(current_img);
                break;
            case 3:
                current_img = invert_image(current_img);
                break;
            case 4 : {
                string second_img_name;
                cout << "Enter the second image file name to merge: ";
                cin >> second_img_name;
                Image second_img = check_name(second_img_name);
                current_img = merge_img(current_img, second_img);
                cout << "Images merged successfully." << endl;
                break;
                }
            case 5:
                save_img(current_img, imgName, imgName);
                break;
            case 0: {
                char choice;
                cout << "Do you want to save before exit? (y/n): ";
                cin >> choice;
                if (choice == 'y') {
                    save_img(current_img, imgName, imgName);
                }
                break;
            }
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
