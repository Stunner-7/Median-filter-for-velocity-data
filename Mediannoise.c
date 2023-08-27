#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA_POINTS 1665
#define WINDOW_SIZE 5

void median_filter(float* data, int data_length, float* filtered_data) {
    for (int i = 0; i < data_length; i++) {
        int start = i - WINDOW_SIZE / 2;
        int end = i + WINDOW_SIZE / 2;

        if (start < 0) {
            start = 0;
        }
        if (end >= data_length) {
            end = data_length - 1;
        }

        int window_size = end - start + 1;
        float window[WINDOW_SIZE];

        for (int j = start; j <= end; j++) {
            window[j - start] = data[j];
        }

        for (int j = 0; j < window_size - 1; j++) {
            for (int k = 0; k < window_size - j - 1; k++) {
                if (window[k] > window[k + 1]) {
                    float temp = window[k];
                    window[k] = window[k + 1];
                    window[k + 1] = temp;
                }
            }
        }

        int median_index = window_size / 2;
        filtered_data[i] = window[median_index];
    }
}

int main() {
    const char* input_filename = "appdata.csv";
    const char* output_filename = "filtered_data.csv";

    float data[MAX_DATA_POINTS];
    float filtered_data[MAX_DATA_POINTS];
    int data_length = 0;

    FILE* input_file;
    if (fopen_s(&input_file, input_filename, "r") != 0) {
        perror("Error opening input file");
        return 1;
    }

    while (data_length < MAX_DATA_POINTS && fscanf_s(input_file, "%f", &data[data_length]) == 1) {
        data_length++;
    }

    fclose(input_file);

    median_filter(data, data_length, filtered_data);

    FILE* output_file;
    if (fopen_s(&output_file, output_filename, "w") != 0) {
        perror("Error opening output file");
        return 1;
    }

    for (int i = 0; i < data_length; i++) {
        fprintf(output_file, "%f\n", filtered_data[i]);
    }

    fclose(output_file);

    printf("Filtered data saved to %s\n", output_filename);

    return 0;
}
