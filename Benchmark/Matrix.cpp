#include "Matrix.h"
using namespace std;

vector<vector<ll>> Matrix::MatrixPrepare(int Row, int Col) 
{
    vector<ll> Array(Row * Col);
    for (ll i = 0; i < Row * Col; ++i) Array[i] = i;
    shuffle(Array.begin(), Array.end(), default_random_engine(0));
    vector<vector<ll>> Result(Row, vector<ll>(Col));
    for (int i = 0; i < Row; ++i) 
        for (int j = 0; j < Col; ++j) 
            Result[i][j] = Array[i * Col + j];
    return Result;
}

vector<vector<ll>> Matrix::MatrixMultiply(vector<vector<ll>>& A, vector<vector<ll>>& B) 
{
    int RowA = A.size(), ColA = A[0].size(), RowB = B.size(), ColB = B[0].size();
    vector<vector<ll>> Result(RowA, vector<ll>(ColB));
    for (int i = 0; i < RowA; ++i) 
        for (int j = 0; j < ColB; ++j) 
            for (int k = 0; k < ColA; ++k) 
                Result[i][j] += A[i][k] * B[k][j];
    return Result;
}

Tuple Matrix::MultiplyTest(int TestSize, PerfCounter& pc) 
{
    pc.reset();
    vector<vector<ll>> A = MatrixPrepare(TestSize, TestSize);
    vector<vector<ll>> B = MatrixPrepare(TestSize, TestSize);
    pc.start();
    vector<vector<ll>> C = MatrixMultiply(A, B);
    return pc.stop();
}