//test commit
/*
=====================================================
 CS213 - Object Oriented Programming
 Assignment 1 - Part 2 (Filters + Menu)

 Team Members:
 - Salma Ahmed Mohamed   (20242161) → Filters 2,5,8,11,15
 - Fatma Khaled Fathy    (20240410) → Filters 1,4,7,10,14
 - Hana Ahmed El-Sayed   (20242386) → Filters 3,6,9,12,13,16

 Section: [6]

 Work Breakdown:
 Filter 1 (Grayscale)        -> Fatma
 Filter 2 (Black & White)    -> Salma
 Filter 3 (Invert Colors)    -> Hana
 Filter 4 (Merge Images)     -> Fatma
 Filter 5 (Flip)             -> Salma
 Filter 6 (Rotate)           -> Hana
Filter 7 (Darken / Lighten) → Fatma
Filter 8 (Crop Image) → Salma
Filter 9 (Add Frame) → Hana
Filter 10 (Edge Detection) → Fatma
Filter 11 (Resize Image) → Salma
Filter 12 (Blur Effect) → Hana
Filter 13 (Sunlight Effect) → Hana
Filter 14 (Oil Paint Effect) → Fatma
Filter 15 (Old TV Effect) → Salma
Filter 16 (Purple Effect) → Hana
 - Menu Integration & Testing  -> ALL the team
 Video Demo Link:
[.................]

Shared Google Doc Link:
[..................................]



 Notes:
 - This program uses Image_Class.h provided with the assignment.
 - The code applies 6 filters with a continuous menu until exit.
=====================================================
*/

#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
#include "Image_Class.h"
#include <vector>
#include <cstdlib>
// ================= Filter 1: Grayscale =================
void ImageGray()
{
    string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);
    cout << "Image saved successfully!\n";
}

Image resizeImage(const Image &src, int newWidth, int newHeight)
{
    Image resized(newWidth, newHeight);
    double x_ratio = (double)src.width / newWidth;
    double y_ratio = (double)src.height / newHeight;

    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            int srcX = (int)(i * x_ratio);
            int srcY = (int)(j * y_ratio);

            for (int k = 0; k < 3; k++)
            {
                resized(i, j, k) = src(srcX, srcY, k);
            }
        }
    }
    return resized;
}

// ================= Filter 2: Black & White =================
void ImageBW()
{
    string filename;
    cout << "Pls enter colored image name to turn to black & white: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
            {
                avg += image(i, j, k);
            }
            avg /= 3;
            int bw = (avg < 128) ? 0 : 255;
            image(i, j, 0) = bw;
            image(i, j, 1) = bw;
            image(i, j, 2) = bw;
        }
    }

    cout << "Pls enter image name to store new B&W image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);
    cout << "Black & White image saved successfully!\n";
}

// ================= Filter 3: Invert =================
void invertImage()
{
    string filename;
    cout << "Pls enter colored image name to turn to invert: ";
    cin >> filename;

    Image image(filename);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);
    cout << "Invert filter applied successfully!\n";
}

// ================= Filter 4: Merge Images =================
void ImageMergeImages()
{
    string filename1, filename2, outputFilename;
    int mergeChoice;

    cout << "Enter first image filename: ";
    cin >> filename1;
    Image image1(filename1);

    cout << "Enter second image filename: ";
    cin >> filename2;
    Image image2(filename2);

    cout << "\nChoose merge method:\n";
    cout << "1. Resize smaller image to match bigger (Full Merge)\n";
    cout << "2. Merge only the overlapping (common) area (Crop Merge)\n";
    cout << "Enter choice (1 or 2): ";
    cin >> mergeChoice;

    int newWidth, newHeight;

    if (mergeChoice == 1)
    {
        if (image1.width * image1.height >= image2.width * image2.height)
        {
            image2 = resizeImage(image2, image1.width, image1.height);
            newWidth = image1.width;
            newHeight = image1.height;
        }
        else
        {
            image1 = resizeImage(image1, image2.width, image2.height);
            newWidth = image2.width;
            newHeight = image2.height;
        }
    }
    else if (mergeChoice == 2)
    {
        newWidth = min(image1.width, image2.width);
        newHeight = min(image1.height, image2.height);
    }
    else
    {
        cout << "Invalid choice!\n";
        return;
    }

    Image mergedImage(newWidth, newHeight);
    for (int i = 0; i < newWidth; ++i)
    {
        for (int j = 0; j < newHeight; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                int pixel1 = image1(i, j, k);
                int pixel2 = image2(i, j, k);
                int merged = (pixel1 + pixel2) / 2;
                mergedImage(i, j, k) = merged;
            }
        }
    }

    cout << "\nEnter output image filename (with .jpg, .bmp, .png, .tga): ";
    cin >> outputFilename;
    mergedImage.saveImage(outputFilename);
    cout << "Merged image saved successfully!\n";
}

// ================= Filter 5: Flip =================
void flipImage()
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
        return;
    }

    cout << "Pls enter new image name to save flipped result\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    image.saveImage(filename);

    cout << "Flipping done successfully!" << endl;
}

// ================= Filter 6: Rotate =================
Image rotate90(const Image &image)
{
    Image rotated(image.height, image.width);
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                rotated(image.height - j - 1, i, k) = image(i, j, k);
            }
        }
    }
    return rotated;
}

void rotateImage()
{
    string filename;
    cout << "Pls enter colored image name to rotate: ";
    cin >> filename;

    Image image(filename);

    int angle;
    cout << "Enter rotation angle (90 / 180 / 270): ";
    cin >> angle;

    if (angle == 90)
    {
        image = rotate90(image);
    }
    else if (angle == 180)
    {
        image = rotate90(image);
        image = rotate90(image);
    }
    else if (angle == 270)
    {
        image = rotate90(image);
        image = rotate90(image);
        image = rotate90(image);
    }
    else
    {
        cout << "Invalid angle! Only 90, 180, 270 allowed.\n";
        return;
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;

    image.saveImage(filename);

    cout << "Image rotated and saved successfully!\n";
}

// ================= Filter 7: Darken / Lighten =================
void ImageDarkenLighten()
{
    string filename;
    cout << "Pls enter image name to darken or lighten: ";
    cin >> filename;

    Image image(filename);

    int choice;
    cout << "Choose option:\n";
    cout << "1. Darken image by 50%\n";
    cout << "2. Lighten image by 50%\n";
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                if (choice == 1)
                {
                    image(i, j, k) = image(i, j, k) * 0.5; 
                }
                else if (choice == 2)
                {
                    int newVal = image(i, j, k) * 1.5; 
                    if (newVal > 255)
                        newVal = 255;
                    image(i, j, k) = newVal;
                }
            }
        }
    }

    cout << "Pls enter image name to save new image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    image.saveImage(filename);
    cout << "Image saved successfully!\n";
}
// ================= Filter 8: Crop Image =================
void ImageCrop()
{
    string filename;
    cout << "Pls enter image name to crop: ";
    cin >> filename;

    Image image(filename);

    int x, y, width, height;
    cout << "Enter top-left x coordinate: ";
    cin >> x;
    cout << "Enter top-left y coordinate: ";
    cin >> y;
    cout << "Enter crop width (W): ";
    cin >> width;
    cout << "Enter crop height (H): ";
    cin >> height;

    if (x < 0 || y < 0 || x + width > image.width || y + height > image.height)
    {
        cout << "Error: Crop area is outside image boundaries!" << endl;
        return;
    }

    Image cropped(width, height);

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                cropped(i, j, k) = image(x + i, y + j, k);
            }
        }
    }

    cout << "Enter image name to save cropped image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    cropped.saveImage(filename);
    cout << "Cropped image saved successfully!\n";
}
// ================= Filter 9: Add Frame (Simple / Fancy) =================
void ImageAddFrame()
{
    string filename;
    cout << "Pls enter colored image name to add frame: ";
    cin >> filename;

    Image image(filename);

    int frameType;
    cout << "Choose frame type:\n";
    cout << "1 - Simple Blue Frame\n";
    cout << "2 - Fancy White Frame\n";
    cout << "Enter choice (1 or 2): ";
    cin >> frameType;

    if (frameType == 1)
    {
        
        for (int x = 0; x < image.width; ++x)
        {
            for (int y = 0; y < image.height; ++y)
            {
                if (x < 20 || x >= image.width - 20 || y < 20 || y >= image.height - 20)
                {
                    image(x, y, 0) = 0;   
                    image(x, y, 1) = 0;   
                    image(x, y, 2) = 255; 
                }
            }
        }
    }

    else if (frameType == 2)
    {

        for (int x = 0; x < image.width; ++x)
        {
            for (int y = 0; y < image.height; ++y)
            {
                bool border =
                    (x < 5 || x >= image.width - 5 || y < 5 || y >= image.height - 5) || 
                    ((x >= 15 && x <= 20) || (x >= image.width - 21 && x <= image.width - 16) ||
                     (y >= 15 && y <= 20) || (y >= image.height - 21 && y <= image.height - 16)); 

                if (border)
                {
                    image(x, y, 0) = 255;
                    image(x, y, 1) = 255;
                    image(x, y, 2) = 255;
                }
            }
        }
    }

    else
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    cout << "Pls enter image name to store new image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    image.saveImage(filename);
    cout << "Frame added successfully!\n";
}
// ================= Filter 10: Edge Detection =================
void ImageDetectEdges()
{
    string filename;
    cout << "Pls enter image name to detect edges: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k)
                avg += image(i, j, k);
            avg /= 3;
            image(i, j, 0) = image(i, j, 1) = image(i, j, 2) = avg;
        }
    }

    Image edgeImg(image.width, image.height);

    for (int i = 1; i < image.width - 1; ++i)
    {
        for (int j = 1; j < image.height - 1; ++j)
        {
            int gx = abs(image(i + 1, j, 0) - image(i - 1, j, 0));
            int gy = abs(image(i, j + 1, 0) - image(i, j - 1, 0));
            int edgeVal = min(255, gx + gy);

            int inverted = 255 - edgeVal;

            edgeImg(i, j, 0) = inverted;
            edgeImg(i, j, 1) = inverted;
            edgeImg(i, j, 2) = inverted;
        }
    }

    cout << "Enter filename to save edge-detected image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    edgeImg.saveImage(filename);

    cout << "Edge detection completed successfully!\n";
}
// ================= Filter 11: Resize Image =================
void ImageResize()
{
    string filename;
    cout << "Pls enter image name to resize: ";
    cin >> filename;

    Image image(filename);

    int choice;
    cout << "Choose resize method:\n";
    cout << "1. By scale (percentage)\n";
    cout << "2. By new dimensions (width & height)\n";
    cout << "Enter choice (1 or 2): ";
    cin >> choice;

    int newWidth, newHeight;

    if (choice == 1)
    {
        double scalePercent;
        cout << "Enter scale percentage (e.g., 50 for half size, 200 for double size): ";
        cin >> scalePercent;

        double scale = scalePercent / 100.0;
        newWidth = static_cast<int>(image.width * scale);
        newHeight = static_cast<int>(image.height * scale);
    }
    else if (choice == 2)
    {
        cout << "Enter new width: ";
        cin >> newWidth;
        cout << "Enter new height: ";
        cin >> newHeight;
    }
    else
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    Image resized(newWidth, newHeight);
    double x_ratio = (double)image.width / newWidth;
    double y_ratio = (double)image.height / newHeight;

    for (int i = 0; i < newWidth; i++)
    {
        for (int j = 0; j < newHeight; j++)
        {
            int srcX = static_cast<int>(i * x_ratio);
            int srcY = static_cast<int>(j * y_ratio);
            for (int k = 0; k < 3; k++)
            {
                resized(i, j, k) = image(srcX, srcY, k);
            }
        }
    }

    cout << "Pls enter image name to store resized image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    resized.saveImage(filename);

    cout << "Resized image saved successfully!\n";
}
// ================= Filter 12: Blur Effect =================
void ImageBlur()
{
    string filename;
    cout << "Pls enter image name to apply blur: ";
    cin >> filename;

    Image image(filename);
    Image blurred(image.width, image.height);

    int kernelSize;
    cout << "Enter blur strength (recommended 10 to 50): ";
    cin >> kernelSize;

    if (kernelSize < 1)
    {
        cout << "Invalid blur size!" << endl;
        return;
    }

    int half = kernelSize / 2;

    for (int x = 0; x < image.width; x++)
    {
        for (int y = 0; y < image.height; y++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            for (int i = -half; i <= half; i++)
            {
                for (int j = -half; j <= half; j++)
                {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height)
                    {
                        sumR += image(nx, ny, 0);
                        sumG += image(nx, ny, 1);
                        sumB += image(nx, ny, 2);
                        count++;
                    }
                }
            }

            blurred(x, y, 0) = sumR / count;
            blurred(x, y, 1) = sumG / count;
            blurred(x, y, 2) = sumB / count;
        }
    }

    cout << "Pls enter image name to save blurred image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    blurred.saveImage(filename);

    cout << "Blur applied successfully!\n";
}
// ================= Filter 13: Sunlight Effect =================
void ImageSunlight()
{
    string filename;
    cout << "Pls enter colored image name to apply sunlight effect: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            unsigned char R = image(i, j, 0);
            unsigned char G = image(i, j, 1);
            unsigned char B = image(i, j, 2);

            R = min(255, int(R * 1.2));
            G = min(255, int(G * 1.1));
            B = min(255, int(B * 0.9));

            image(i, j, 0) = R;
            image(i, j, 1) = G;
            image(i, j, 2) = B;
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;

    image.saveImage(filename);
    cout << "Sunlight effect applied successfully!\n";
}
// ================= Filter 14: Oil Paint Effect =================
void ImageOilPaint()
{
    string filename;
    cout << "Pls enter image name to apply Oil Paint effect: ";
    cin >> filename;

    Image image(filename);
    Image out(image.width, image.height);

    int radius = 1;  
    int levels = 40; 

    for (int i = radius; i < image.width - radius; ++i)
    {
        for (int j = radius; j < image.height - radius; ++j)
        {

            vector<int> count(levels, 0);
            vector<int> sumR(levels, 0);
            vector<int> sumG(levels, 0);
            vector<int> sumB(levels, 0);

            for (int x = -radius; x <= radius; ++x)
            {
                for (int y = -radius; y <= radius; ++y)
                {
                    int r = image(i + x, j + y, 0);
                    int g = image(i + x, j + y, 1);
                    int b = image(i + x, j + y, 2);

                    int avg = (r + g + b) / 3;
                    int id = (avg * levels) / 255;
                    if (id >= levels)
                        id = levels - 1;

                    count[id]++;
                    sumR[id] += r;
                    sumG[id] += g;
                    sumB[id] += b;
                }
            }

            int idx = 0;
            for (int k = 1; k < levels; ++k)
                if (count[k] > count[idx])
                    idx = k;

            if (count[idx] != 0)
            {
                out(i, j, 0) = sumR[idx] / count[idx];
                out(i, j, 1) = sumG[idx] / count[idx];
                out(i, j, 2) = sumB[idx] / count[idx];
            }
        }
    }

    cout << "Pls enter image name to save new image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;

    out.saveImage(filename);
    cout << "Oil Paint effect applied successfully!\n";
}
// ================= Filter 15: Old TV Effect (no OpenCV) =================

void ImageOldTVEffect()
{
    string filename;
    cout << "Pls enter image name to apply Old TV effect: ";
    cin >> filename;

    Image image(filename);
    Image out(image.width, image.height);

    for (int x = 0; x < image.width; ++x)
    {
        for (int y = 0; y < image.height; ++y)
        {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            int gray = (r + g + b) / 3;

            r = int(r * 0.7 + gray * 0.3) - 20;
            g = int(g * 0.7 + gray * 0.3) - 20;
            b = int(b * 0.7 + gray * 0.3) - 20;

            r = max(0, min(255, r));
            g = max(0, min(255, g));
            b = max(0, min(255, b));

            out(x, y, 0) = r;
            out(x, y, 1) = g;
            out(x, y, 2) = b;
        }
    }

    for (int y = 0; y < out.height; y += 2)
    {
        for (int x = 0; x < out.width; ++x)
        {
            out(x, y, 0) = out(x, y, 0) / 2;
            out(x, y, 1) = out(x, y, 1) / 2;
            out(x, y, 2) = out(x, y, 2) / 2;
        }
    }

    srand((unsigned)time(nullptr));
    for (int x = 0; x < out.width; ++x)
    {
        for (int y = 0; y < out.height; ++y)
        {
            int noise = (rand() % 41) - 20;
            for (int c = 0; c < 3; ++c)
            {
                int v = out(x, y, c) + noise;
                if (v < 0)
                    v = 0;
                if (v > 255)
                    v = 255;
                out(x, y, c) = v;
            }
        }
    }

    cout << "Pls enter image name to save new image (.jpg, .bmp, .png, .tga): ";
    cin >> filename;
    out.saveImage(filename);

    cout << "Old TV effect saved successfully!\n";
}
// ================= Filter 16: Purple Effect =================
void ImagePurpleEffect()
{
    string filename;
    cout << "Pls enter colored image name to apply Purple Effect: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            unsigned char R = image(i, j, 0);
            unsigned char G = image(i, j, 1);
            unsigned char B = image(i, j, 2);

            R = min(255, int(R * 1.2));
            G = min(255, int(G * 0.7));
            B = min(255, int(B * 1.3));

            image(i, j, 0) = R;
            image(i, j, 1) = G;
            image(i, j, 2) = B;
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;

    image.saveImage(filename);
    cout << "Purple Effect applied and image saved successfully!\n";
}
// ================= Main Menu =================
int main()
{
    int choice;
    do
    {
        cout << "\n===== Image Filters Menu =====\n";
        cout << "1 - Grayscale\n";
        cout << "2 - Black & White\n";
        cout << "3 - Invert Colors\n";
        cout << "4 - Merge Two Images\n";
        cout << "5 - Flip (Horizontal / Vertical)\n";
        cout << "6 - Rotate (90 / 180 / 270)\n";
        cout << "7 - Darken / Lighten Image\n";
        cout << "8 - Crop Image\n";
        cout << "9 - Add Frame (Simple / Fancy)\n";
        cout << "10 - Edge Detection\n";
        cout << "11 - Resize Image\n";
        cout << "12 - Blur Effect\n";
        cout << "13 - Sunlight Effect\n";
        cout << "14 - Oil Paint Effect\n";
        cout << "15 - Old TV Effect\n";
        cout << "16 - Purple Effect\n";
        cout << "0 - Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ImageGray();
            break;
        case 2:
            ImageBW();
            break;
        case 3:
            invertImage();
            break;
        case 4:
            ImageMergeImages();
            break;
        case 5:
            flipImage();
            break;
        case 6:
            rotateImage();
            break;
        case 7:
            ImageDarkenLighten();
            break;
        case 8:
            ImageCrop();
            break;
        case 9:
            ImageAddFrame();
            break;
        case 10:
            ImageDetectEdges();
            break;
        case 11:
            ImageResize();
            break;
        case 12:
            ImageBlur();
            break;
        case 13:
            ImageSunlight();
            break;
        case 14:
            ImageOilPaint();
            break;
        case 15:
            ImageOldTVEffect();
            break;
        case 16:
            ImagePurpleEffect();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 0);

    return 0;

}
