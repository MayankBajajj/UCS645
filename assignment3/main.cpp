#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void correlate(int ny, int nx, const float* data, float* result);

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cout << "Usage: ./program ny nx" << endl;
        return 0;
    }

    int ny = atoi(argv[1]);
    int nx = atoi(argv[2]);

    float* data = new float[ny * nx];
    float* result = new float[ny * ny];

    srand(time(0));

    for(int i = 0; i < ny * nx; i++)
        data[i] = rand() % 100;

    correlate(ny, nx, data, result);

    cout << "Sample Output:" << endl;
    for(int i = 0; i < min(ny, 5); i++)
    {
        for(int j = 0; j < min(ny, 5); j++)
            cout << result[i + j * ny] << " ";
        cout << endl;
    }

    delete[] data;
    delete[] result;

    return 0;
}