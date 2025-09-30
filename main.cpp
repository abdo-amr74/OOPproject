
#include "Image_Class.h"
#include <iostream>
using namespace std;
bool validExtension(string filename) {
    size_t dotPos = filename.find_last_of(".");
    if (dotPos == -1) {
        return false;
    }
    string ext = filename.substr(dotPos);
    if (ext == ".jpg" || ext == ".bmp" || ext == ".png" || ext == ".tga") {
        return true;
    } else {
        return false;
    }
}
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
        while (!validExtension(new_name)) {
            cout << "Invalid extension! Please enter a valid one (.jpg, .bmp, .png, .tga): ";
            cin >> new_name;
        }
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
Image rotated_image(Image img )
{
    cout << "Please choose what degree adjustment do you want?" <<"\n"<< "90 degree - 180 degree - 270 degree" << endl;
    int x;
    while (true) {
        cin >> x;

        if (x == 90 || x == 180 || x == 270) {
            Image final_img;
            if (x == 90)
            {
                final_img = Image(img.height, img.width);
                for (int i = 0; i < img.width; i++)
                {
                    for (int j = 0; j < img.height; j++)
                    {
                        int temp1 = img.height - 1 - j;
                        int temp2 = i;
                        for (int k = 0; k < 3; k++)
                        {
                            final_img(temp1, temp2, k) = img(i, j, k);
                        }
                    }
                }
                return final_img;
            }
            else if (x == 180)
            {
                final_img = Image(img.width, img.height);
                for (int i = 0; i < img.width; i++)
                {
                    for (int j = 0; j < img.height; j++)
                    {
                        int temp1 = img.width - 1 - i;
                        int temp2 = img.height - 1 - j;
                        for (int k = 0; k < 3; k++)
                        {
                            final_img(temp1, temp2, k) = img(i, j, k);
                        }
                    }
                }
                return final_img;
            }
            else if (x == 270)
            {
                final_img = Image(img.height, img.width);
                for (int i = 0; i < img.width; i++)
                {
                    for (int j = 0; j < img.height; j++)
                    {
                        int temp1 = j;
                        int temp2 = img.width - 1 - i;
                        for (int k = 0; k < 3; k++)
                        {
                            final_img(temp1, temp2, k) = img(i, j, k);
                        }
                    }
                }
                return final_img;
            }
        }
        else {
            cout << "Invalid input. Please enter 90, 180, or 270:" << endl;
        }
    }
}
Image BW(const Image& original) {

    Image image = original;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }

            avg /= 3;

            int val;
            if (avg >= 128) {
                val = 255;
            }
            else {
                val = 0;
            }

            image(i, j, 0) = val;
            image(i, j, 1) = val;
            image(i, j, 2) = val;
        }
    }
    return image;
}
Image cropImage(Image& image) {
    int x,y,w,h;
        cout << "Pls enter starting point: ";
        cin >> x >> y;
        cout << "please enter the dimensions of the area to cut: ";
        cin >> w >> h;

    if (x + w > image.width || y + h > image.height)
    {
        cout << "Error ";
        exit(1);
    }
    else {
        Image cropped(w, h);

        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {

                for (int k = 0; k < 3; ++k) {
                    cropped(i, j, k) = image(i + x, j + y, k);
                }
            }
        }
        return cropped;
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
                "5:rotation filter\n"
                "6:Black and While filter\n"
                "7:Crop filter\n"
                "8: Save the image\n"
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
            case 5 : {
                current_img = rotated_image(current_img);
                break;
            }
            case 6 :
            {
                current_img = BW(current_img);
                break;
            }
            case 7: {
                current_img = cropImage(current_img);
                break;
            }
            case 8:
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







