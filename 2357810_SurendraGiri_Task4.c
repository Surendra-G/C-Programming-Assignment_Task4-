// Assignment Task 4
// Name: Surendra Giri
// Student ID: 2357810

Task4.c
/*HEADER FILES*/
#include <stdio.h> //library for input and output operations(prinf and scanf function).
#include <pthread.h> //library for multithreading.
#include <stdlib.h> //library for memory allocation, process control (malloc and calloc)
#include "lodepng.h"//library for encoding and decoding PNG image files
#include <semaphore.h>//definitions and functions for working with semaphores(synchronization)



//declaration semaphore as semaphore data type and name is "semaphore."
sem_t semaphore;
// Declares Image and NewImage pointers to store image data in memory
unsigned char *Image, *NewImage;
//r, g, b, a: red, green, blue, and alpha values for a pixel and 
// i: iterator or index variable
unsigned int w, h, r, g, b, a, i;
//Declear Struct as threadStruct
struct threadStruct
{
    int StartFrom;//Starting pixel index for the thread
    int EndTo;//Ending pixel index for the thread
};
//declares a function name thread as pointer
void *thread(void *threadArgs)
{
    //wait on the semaphore to ensure synchronization of access to shared resources
    sem_wait(&semaphore);
    //Struct cointain range of pixels the thread will process
    struct threadStruct *structure = (struct threadStruct *)threadArgs;
    int start = structure->StartFrom;//starting pixel index for the thread
    int end = structure->EndTo;//ending pixel index for the thread
    // Loop through each column of the row 'i' in the image
    for (int i = start; i < end; i++)
    {

        for (int j = 0; j < w; j++)
        {
            r = Image[4 * w * i + 4 * j + 0];// Extract the red channel value from the image
            g = Image[4 * w * i + 4 * j + 1];// Extract the green channel value from the image
            b = Image[4 * w * i + 4 * j + 2];// Extract the blue channel value from the image
            a = Image[4 * w * i + 4 * j + 3]; // Extract the alpha channel value from the image
            // Check if this is the first pixel in the image
            if (i == 0 && j == 0)
            {
                // Calculates the average of the colors of the pixel at (i,j) and its three neighboring pixels in all colume
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * i + 4 * 1 + 0] + Image[4 * w * 1 + 4 * j + 0] + Image[4 * w * 1 + 4 * 1 + 0]) / 4;
                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * i + 4 * 1 + 1] + Image[4 * w * 1 + 4 * j + 1] + Image[4 * w * 1 + 4 * 1 + 1]) / 4;
                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * i + 4 * 1 + 2] + Image[4 * w * 1 + 4 * j + 2] + Image[4 * w * 1 + 4 * 1 + 2]) / 4;
                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * i + 4 * 1 + 3] + Image[4 * w * 1 + 4 * j + 3] + Image[4 * w * 1 + 4 * 1 + 3]) / 4;
            }
            // Check if the current pixel is at the top-left corner of the image
            if (i == 0 && j != 0 && j != w - 1)
            {  
                 // Compute the average of the current pixel and its surrounding pixels
                // and assign the resulting values to the corresponding channels of the new image
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * i + 4 * (j - 1) + 0] + Image[4 * w * i + 4 * (j + 1) + 0] + Image[4 * w * (i + 1) + 4 * j + 0] + Image[4 * w * (i + 1) + 4 * (j - 1) + 0] + Image[4 * w * i + 4 * (j + 1) + 0]) / 6;
                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * i + 4 * (j - 1) + 1] + Image[4 * w * i + 4 * (j + 1) + 1] + Image[4 * w * (i + 1) + 4 * j + 1] + Image[4 * w * (i + 1) + 4 * (j - 1) + 1] + Image[4 * w * i + 4 * (j + 1) + 1]) / 6;
                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * i + 4 * (j - 1) + 2] + Image[4 * w * i + 4 * (j + 1) + 2] + Image[4 * w * (i + 1) + 4 * j + 2] + Image[4 * w * (i + 1) + 4 * (j - 1) + 2] + Image[4 * w * i + 4 * (j + 1) + 2]) / 6;
                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * i + 4 * (j - 1) + 3] + Image[4 * w * i + 4 * (j + 1) + 3] + Image[4 * w * (i + 1) + 4 * j + 3] + Image[4 * w * (i + 1) + 4 * (j - 1) + 3] + Image[4 * w * i + 4 * (j + 1) + 3]) / 6;
            }
               // checks if the current pixel is in the top-right corner of the image
            if (i == 0 && j == w - 1)
            {
                
                // current pixel and its immediate neighbors to the left and down, as well as the pixel located at the intersection of the
                // first row and last column. The resulting pixel values are stored in the corresponding indices of the NewImage array.
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * i + 4 * (j - 1) + 0] + Image[4 * w * 1 + 4 * (j - 1) + 0] + Image[4 * w * 1 + 4 * j + 0]) / 4;
                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * i + 4 * (j - 1) + 1] + Image[4 * w * 1 + 4 * (j - 1) + 1] + Image[4 * w * 1 + 4 * j + 1]) / 4;
                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * i + 4 * (j - 1) + 2] + Image[4 * w * 1 + 4 * (j - 1) + 2] + Image[4 * w * 1 + 4 * j + 2]) / 4;
                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * i + 4 * (j - 1) + 3] + Image[4 * w * 1 + 4 * (j - 1) + 3] + Image[4 * w * 1 + 4 * j + 3]) / 4;
            }
            // checks if the current pixel being processed is the last pixel in the image (bottom right corner).
            if (i == h - 1 && j == w - 1)
            {
                // 3x3 box filter to average neighboring pixel values
                // Center pixel is at (i,j)
                // Top left pixel is at (i-1, j-1)
                // Top pixel is at (i-1, j)
                // Top right pixel is at (i-1, j+1)
                // Left pixel is at (i, j-1)
                // Right pixel is at (i, j+1)
                // Bottom left pixel is at (i+1, j-1)
                // Bottom pixel is at (i+1, j)
                // Bottom right pixel is at (i+1, j+1)
                
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * (i - 1) + 4 * j + 0] + Image[4 * w * (i - 1) + 4 * (j + 1) + 0] + Image[4 * w * i + 4 * (j + 1) + 0]) / 4;
                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * (i - 1) + 4 * j + 1] + Image[4 * w * (i - 1) + 4 * (j + 1) + 1] + Image[4 * w * i + 4 * (j + 1) + 1]) / 4;
                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * (i - 1) + 4 * j + 2] + Image[4 * w * (i - 1) + 4 * (j + 1) + 2] + Image[4 * w * i + 4 * (j + 1) + 2]) / 4;
                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * (i - 1) + 4 * j + 3] + Image[4 * w * (i - 1) + 4 * (j + 1) + 3] + Image[4 * w * i + 4 * (j + 1) + 3]) / 4;
            }
            //checks if the current pixel is on the left edge of the image (j == 0) and is not on the top or bottom row of the image (i != 0 && i != h - 1).
            if (j == 0 && i != 0 && i != h - 1)
            {
                //calculating the average pixel value of a given pixel and its surrounding 5 pixels, and
                //toring it in the corresponding pixel location in a new image array.
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * i + 4 * (j + 1) + 0] + Image[4 * w * (i - 1) + 4 * j + 0] + Image[4 * w * (i + 1) + 4 * j + 0] + Image[4 * w * (i - 1) + 4 * (j + 1) + 0] + Image[4 * w * (i + 1) + 4 * (j + 1) + 0]) / 6;

                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * i + 4 * (j + 1) + 1] + Image[4 * w * (i - 1) + 4 * j + 1] + Image[4 * w * (i + 1) + 4 * j + 1] + Image[4 * w * (i - 1) + 4 * (j + 1) + 1] + Image[4 * w * (i + 1) + 4 * (j + 1) + 1]) / 6;

                NewImage[4 * w * i + 4 * j + 2] = (r + Image[4 * w * i + 4 * (j + 1) + 2] + Image[4 * w * (i - 1) + 4 * j + 2] + Image[4 * w * (i + 1) + 4 * j + 2] + Image[4 * w * (i - 1) + 4 * (j + 1) + 2] + Image[4 * w * (i + 1) + 4 * (j + 1) + 2]) / 6;

                NewImage[4 * w * i + 4 * j + 3] = (r + Image[4 * w * i + 4 * (j + 1) + 3] + Image[4 * w * (i - 1) + 4 * j + 3] + Image[4 * w * (i + 1) + 4 * j + 3] + Image[4 * w * (i - 1) + 4 * (j + 1) + 3] + Image[4 * w * (i + 1) + 4 * (j + 1) + 3]) / 6;
            }
            //checking if the current column represented by j is the last column (with index w-1) and if the current row represented by i is not the first or last row
            if (j == w - 1 && i != 0 && i != h - 1)
            {
                // calculates the color values of the new pixel at coordinates (i, j) based on the color values of the surrounding pixels in the original image
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * (i - 1) + 4 * (j + 1) + 0] + Image[4 * w * (i + 1) + 4 * j + 0] + Image[4 * w * i + 4 * (j - 1) + 0] + Image[4 * w * (i - 1) + 4 * (j - 1) + 0] + Image[4 * w * (i + 1) + 4 * (j - 1) + 0]) / 6;

                NewImage[4 * w * i + 4 * j + 1] = (g + r + Image[4 * w * (i - 1) + 4 * j + 1] + Image[4 * w * (i + 1) + 4 * j + 1] + Image[4 * w * i + 4 * (j - 1) + 1] + Image[4 * w * (i - 1) + 4 * (j - 1) + 1] + Image[4 * w * (i + 1) + 4 * (j - 1) + 1]) / 6;

                NewImage[4 * w * i + 4 * j + 2] = (b + r + Image[4 * w * (i - 1) + 4 * j + 2] + Image[4 * w * (i + 1) + 4 * j + 2] + Image[4 * w * i + 4 * (j - 1) + 2] + Image[4 * w * (i - 1) + 4 * (j - 1) + 2] + Image[4 * w * (i + 1) + 4 * (j - 1) + 2]) / 6;

                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * (i - 1) + 4 * (j + 1) + 0] + Image[4 * w * (i + 1) + 4 * j + 3] + Image[4 * w * i + 4 * (j - 1) + 3] + Image[4 * w * (i - 1) + 4 * (j - 1) + 3] + Image[4 * w * (i + 1) + 4 * (j - 1) + 3]) / 6;
            }
            // checks if both the value of variable i is equal to h - 1 and the value of variable j is equal to 0.
            if (i == h - 1 && j == 0)
            {
                //average is taking into account the red, green, blue, and alpha (transparency) channels of the pixels,
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * (i - 1) + 4 * j + 0] + Image[4 * w * (i - 1) + 4 * (j - 1) + 0] + Image[4 * w * i + 4 * (j - 1) + 0]) / 4;
                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * (i - 1) + 4 * j + 1] + Image[4 * w * (i - 1) + 4 * (j - 1) + 1] + Image[4 * w * i + 4 * (j - 1) + 1]) / 4;
                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * (i - 1) + 4 * j + 2] + Image[4 * w * (i - 1) + 4 * (j - 1) + 2] + Image[4 * w * i + 4 * (j - 1) + 2]) / 4;
                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * (i - 1) + 4 * j + 3] + Image[4 * w * (i - 1) + 4 * (j - 1) + 3] + Image[4 * w * i + 4 * (j - 1) + 3]) / 4;
            }
            //checking if the current pixel being processed is in the bottom row of the image (i.e., i is equal to h - 1), but not in either the leftmost or rightmost columns (j is not equal to 0 and not equal to w - 1).
            if (i == h - 1 && j != 0 && j != w - 1)
            {
                //calculating the average of the current pixel and its three neighboring pixels above and to the right, above and to the left, and directly above,
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * i + 4 * j + 0] + Image[4 * w * i + 4 * (j + 1) + 0] + Image[4 * w * (i - 1) + 4 * j + 0] + Image[4 * w * (i - 1) + 4 * (j - 1) + 0] + Image[4 * w * (i - 1) + 4 * (j + 1) + 0]) / 6;
                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * i + 4 * j + 1] + Image[4 * w * i + 4 * (j + 1) + 1] + Image[4 * w * (i - 1) + 4 * j + 1] + Image[4 * w * (i - 1) + 4 * (j - 1) + 1] + Image[4 * w * (i - 1) + 4 * (j + 1) + 1]) / 6;
                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * i + 4 * j + 2] + Image[4 * w * i + 4 * (j + 1) + 2] + Image[4 * w * (i - 1) + 4 * j + 2] + Image[4 * w * (i - 1) + 4 * (j - 1) + 2] + Image[4 * w * (i - 1) + 4 * (j + 1) + 2]) / 6;
                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * i + 4 * j + 3] + Image[4 * w * i + 4 * (j + 1) + 3] + Image[4 * w * (i - 1) + 4 * j + 3] + Image[4 * w * (i - 1) + 4 * (j - 1) + 3] + Image[4 * w * (i - 1) + 4 * (j + 1) + 3]) / 6;
            }
             //checks if i is not the first or last row of the image, and j is not the first or last column of the image.
            if (i != 0 && i != h - 1 && j != 0 && j != w - 1)
            {
                //calculating the average value of a pixel and its eight neighboring pixels in an image, and storing the result in a corresponding pixel in a new image.
                NewImage[4 * w * i + 4 * j + 0] = (r + Image[4 * w * i + 4 * (j - 1) + 0] + Image[4 * w * i + 4 * (j + 1) + 0] + Image[4 * w * (i - 1) + 4 * j + 0] + Image[4 * w * (i + 1) + 4 * j + 0] + Image[4 * w * (i - 1) + 4 * (j - 1) + 0] + Image[4 * w * (i - 1) + 4 * (j + 1) + 0] + Image[4 * w * (i + 1) + 4 * (j - 1) + 0] + Image[4 * w * (i + 1) + 4 * (j + 1) + 0]) / 9;

                NewImage[4 * w * i + 4 * j + 1] = (g + Image[4 * w * i + 4 * (j - 1) + 2] + Image[4 * w * i + 4 * (j + 1) + 1] + Image[4 * w * (i - 1) + 4 * j + 1] + Image[4 * w * (i + 1) + 4 * j + 1] + Image[4 * w * (i - 1) + 4 * (j - 1) + 1] + Image[4 * w * (i - 1) + 4 * (j + 1) + 1] + Image[4 * w * (i + 1) + 4 * (j - 1) + 1] + Image[4 * w * (i + 1) + 4 * (j + 1) + 1]) / 9;

                NewImage[4 * w * i + 4 * j + 2] = (b + Image[4 * w * i + 4 * (j - 1) + 2] + Image[4 * w * i + 4 * (j + 1) + 2] + Image[4 * w * (i - 1) + 4 * j + 2] + Image[4 * w * (i + 1) + 4 * j + 2] + Image[4 * w * (i - 1) + 4 * (j - 1) + 2] + Image[4 * w * (i - 1) + 4 * (j + 1) + 2] + Image[4 * w * (i + 1) + 4 * (j - 1) + 2] + Image[4 * w * (i + 1) + 4 * (j + 1) + 2]) / 9;

                NewImage[4 * w * i + 4 * j + 3] = (a + Image[4 * w * i + 4 * (j - 1) + 3] + Image[4 * w * i + 4 * (j + 1) + 3] + Image[4 * w * (i - 1) + 4 * j + 3] + Image[4 * w * (i + 1) + 4 * j + 3] + Image[4 * w * (i - 1) + 4 * (j - 1) + 3] + Image[4 * w * (i - 1) + 4 * (j + 1) + 3] + Image[4 * w * (i + 1) + 4 * (j - 1) + 3] + Image[4 * w * (i + 1) + 4 * (j + 1) + 3]) / 9;
            }
        }
    }
    //call the semaphore function
    sem_post(&semaphore);
}
void main()
{
    // Declare variables to store input and output image file names, and the number of threads
    char inputImage[200], outputImage[200];
    
    int threadNumber;
    //Print messages to prompt the user to enter the input and output image file names
    printf("Note: Only .png image can Enter.\n");
    printf("Image name.png to apply gaussian blur filter\n");
    scanf("%s", inputImage);
    printf("Input output image name as.png \n");
    scanf("%s", outputImage);
    // Prompt the user to enter the number of threads
    printf("Enter number of threads: \n");
    scanf("%d", &threadNumber);
    //Decode the input image file and store the image data in two arrays, Image and NewImage
    unsigned int error;
    error = lodepng_decode32_file(&Image, &w, &h, inputImage);
    lodepng_decode32_file(&NewImage, &w, &h, inputImage);
    // Check for any decoding errors
    if (error)
    {
        printf("%d %s", error, lodepng_error_text(error));
    }
    // Calculate how many rows of image each thread will process
    int divide[threadNumber];
    for (int c = 0; c < threadNumber; c++)
    {
        divide[c] = h / threadNumber;
    }
    // If the image height is not divisible by the number of threads,
    // distribute the remaining rows among the threads
     //Calculate the starting and ending row indices for each thread

    int remainder = h % threadNumber;
    //Populate each element of mainStruct with the corresponding startFrom and endTo values.
    for (int d = 0; d < remainder; d++)
    {
        divide[d] = divide[d] + 1;
    }
    //Declare an array of threadStruct with size threadNumber
    int startFrom[threadNumber];
    int endTo[threadNumber];
    for (int e = 0; e < threadNumber; e++)
    {
        if (e == 0) //if condition 
        {
            startFrom[e] = 0;
        }
        else//else statement
        {
            startFrom[e] = endTo[e - 1] + 1;
        }
        endTo[e] = startFrom[e] + divide[e] - 1;
    }
    //Declare an array of threadStruct with size threadNumber.
    struct threadStruct mainStruct[threadNumber];
    //Populate each element of mainStruct with the corresponding startFrom and endTo values
    for (int f = 0; f < threadNumber; f++)
    {
        mainStruct[f].StartFrom = startFrom[f];
        mainStruct[f].EndTo = endTo[f];
    }
    //Declare an array of pthread_t with size threadNumber.
    pthread_t threadId[threadNumber];
    //Initialize a semaphore named semaphore with a value of 1 and with process-local scope.
    sem_init(&semaphore, 0, 1);
    //Create threadNumber threads with the thread function and pass the corresponding element
    for (int g = 0; g < threadNumber; g++)
    {
        pthread_create(&threadId[g], NULL, thread, &mainStruct[g]);
    }
    //Wait for each thread to terminate before proceeding
    for (int h = 0; h < threadNumber; h++)
    {
        pthread_join(threadId[h], NULL);
    }
    //Destroy the semaphore semaphore
    sem_destroy(&semaphore);
    //Print a message indicating that the program has finished.
    printf("Done applying guassian blur!!!\n");
    // Encode the NewImage array as a PNG image and specified in outputImage
    lodepng_encode32_file(outputImage, NewImage, w, h);
    //Free the memory allocated for the Image and NewImage arrays.
    free(Image);
    free(NewImage);
}
