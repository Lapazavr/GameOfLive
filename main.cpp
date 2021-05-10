//Алгоритм поиска матрицы соседей вынесен в функцию
//Алгоритм поиска матрицы следующего поколения вынесен в функцию
//Алгоритм вывода матрицы вынесен в функцию
//Алгоритм заполнения случайной матрицы вынесен в функцию
//С консоли задается размерность матрицы и количество поколений

#include <QCoreApplication>

#include <iostream>
#include <vector>
#include <QDebug>

//Функция для определения целочисленного рандома в промежутке
static int randomBetween(int low, int high)
{
    return (std::rand() % ((high + 1) - low) + low);
}

//Функция поиска матрицы соседства
static std::vector< std::vector<double>> kolSosed (int n, int m, std::vector< std::vector<double>> Matrix){
    std::vector< std::vector<double> > MatrixN(n, std::vector<double>(m,0));

    for (int i=0; i<n; i++){


        for (int j=0; j<m; j++){
            if (i>0 && i<n-1 && j>0 && j<m-1){
                MatrixN[i][j] = Matrix[i-1][j-1]+Matrix[i-1][j]+Matrix[i-1][j+1]+
                        Matrix[i][j-1]+Matrix[i][j+1]+
                        Matrix[i+1][j-1]+Matrix[i+1][j]+Matrix[i+1][j+1];
            }
            if (i==0 && j==0){
                MatrixN[i][j] = Matrix[0][1]+Matrix[1][0]+Matrix[1][1];
            }

            if (i==n-1 && j==0){
                MatrixN[i][j] = Matrix[n-2][0]+Matrix[n-2][1]+Matrix[n-1][1];
            }

            if (i==0 && j==m-1){
                MatrixN[i][j] = Matrix[0][m-2]+Matrix[1][m-2]+Matrix[1][m-1];
            }

            if (i==n-1 && j==m-1){
                MatrixN[i][j] = Matrix[n-2][m-2]+Matrix[n-2][m-1]+Matrix[n-1][m-2];
            }

            if (i==0 && j>0 && j<m-1){
                MatrixN[i][j] = Matrix[0][j-1]+Matrix[0][j+1]+
                        Matrix[1][j-1]+Matrix[1][j]+Matrix[1][j+1];
            }

            if (i==n-1 && j>0 && j<m-1){
                MatrixN[i][j] = Matrix[n-2][j-1]+Matrix[n-2][j]+Matrix[n-2][j+1]+
                        Matrix[n-1][j-1]+Matrix[n-1][j+1];
            }

            if (j==0 && i>0 && i<n-1){
                MatrixN[i][j] = Matrix[i-1][0]+Matrix[i+1][0]+
                        Matrix[i-1][1]+Matrix[i][1]+Matrix[i+1][1];
            }

            if (j==m-1 && i>0 && i<n-1){
                MatrixN[i][j] = Matrix[i-1][m-2]+Matrix[i][m-2]+Matrix[i+1][m-2]+
                        Matrix[i-1][m-1]+Matrix[i+1][m-1];
            }

        }
    }
    return MatrixN;
}

//Функция поиска матрицы следующего поколения
static std::vector< std::vector<double>> nextGeneration (int n, int m, std::vector< std::vector<double>> MatrixN, std::vector< std::vector<double>> MatrixP1){
    std::vector< std::vector<double> > MatrixP2(n, std::vector<double>(m,0));

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){

            if ((MatrixN[i][j]<2 || MatrixN[i][j]>3) && MatrixP1[i][j]==1){
                MatrixP2[i][j]=0;
            }else if ((MatrixN[i][j] == 2 || MatrixN[i][j] == 3) && MatrixP1[i][j]==1){
                MatrixP2[i][j]=1;
            }else if (MatrixP1[i][j]==0 && MatrixN[i][j]==3){
                MatrixP2[i][j]=1;
            }else{
                MatrixP2[i][j]=0;
            }
        }
    }

    return MatrixP2;
}

//Функция вывода матрицы в консоль
static void printMatrix (int n, int m, std::vector< std::vector<double>> Matrix){
    for (int i=0; i<n; i++){
        std::cout<<std::endl;
        for (int j=0; j<m; j++){
            std::cout<<Matrix[i][j]<<" ";
        }
    }
}

//Функция случайного заполнения матрицы
static std::vector< std::vector<double>> createMatrixRand (int n, int m){

    std::vector< std::vector<double> > NewMatrix(n, std::vector<double>(m,0));

    for (int i=0; i<n; i++) {
     for (int j=0; j<m; j++) {
         NewMatrix[i][j] = randomBetween(0,1);
         }
    }

    return NewMatrix;
}

int main() {

 //Размерность матрицы
 int n,m;

 //Количество поколений
 int p;

 std::cout<<"y:";
 std::cin>>n;
 std::cout<<std::endl;

 std::cout<<"x:";
 std::cin>>m;
 std::cout<<std::endl;

 std::cout<<"p:";
 std::cin>>p;
 std::cout<<std::endl;

 //Инициализируем и переопределяем размерность матрицы от n и m
 std::vector< std::vector<double> > MatrixP1(n, std::vector<double>(m,0));
 std::vector< std::vector<double> > MatrixN(n, std::vector<double>(m,0));
 std::vector< std::vector<double> > MatrixP2(n, std::vector<double>(m,0));

 //Впервые заполняем матрицу случайными состояниями
 std::cout<<"First matrix with random:"<<std::endl;
 MatrixP1 = createMatrixRand(n,m);
 printMatrix(n,m,MatrixP1);

for (int Cikl=0; Cikl<p; Cikl++){
    std::cout<<std::endl;
    std::cout<<std::endl;

    //Определяем матрицу соседей
    MatrixN = kolSosed(n,m,MatrixP1);

    system("pause");
    system("CLS");

    //Определяем матрицу следующего поколения, параллельно переопределяя матрицу первого поколения
    std::cout<<"Next generation:"<<std::endl;
    MatrixP2 = nextGeneration(n,m,MatrixN,MatrixP1);
    MatrixP1 = MatrixP2;

    printMatrix(n,m,MatrixP2);

}

 return 0;
}
