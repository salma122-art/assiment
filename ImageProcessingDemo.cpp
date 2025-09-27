#include <iostream>
using namespace std;
#include "Image_Class.h"
int main()
{
    string filename;
    cout << "Pls enter image name to flip: ";
    cin >> filename;

    Image image(filename);

    int choice;
    cout << "Choose flipping type:\n";
    cout << "1 - Horizontal Flip (Left <-> Right)\n";
    cout << "2 - Vertical Flip (Top <-> Bottom)\n";
    cin >> choice;
    if (choice == 1)
    {
        for (int i = 0; i < image.width / 2; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    unsigned char temp = image(i, j, k);
                    image(i, j, k) = image(image.width - 1 - i, j, k);
                    image(image.width - 1 - i, j, k) = temp;
                }
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height / 2; ++j)
            {
                for (int k = 0; k < 3; ++k)
                {
                    unsigned char temp = image(i, j, k);
                    image(i, j, k) = image(i, image.height - 1 - j, k);
                    image(i, image.height - 1 - j, k) = temp;
                }
            }
        }
    }
    else
    {
        cout << "Invalid choice!" << endl;
        return 0;
    }
    cout << "Pls enter new image name to save flipped result\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);

    cout << "Flipping done successfully!" << endl;
    return 0;
}