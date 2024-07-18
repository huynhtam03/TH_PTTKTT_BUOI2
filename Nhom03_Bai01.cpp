#include <stdio.h>
#include <stdlib.h>  // Để sử dụng malloc và free

// Hàm nguyên mẫu
void MatMul(int **A, int **B, int **C, int size);
void MatrixAdd(int **A, int **B, int **C, int size);
void MatrixSub(int **A, int **B, int **C, int size);
void Strassen(int **A, int **B, int **C, int size);
void PrintMatrix(int **matrix, int size);

// Hàm nhân hai ma trận sử dụng phương pháp chia để trị (Strassen)
void Strassen(int **A, int **B, int **C, int size) {
	if (size == 1) {
		C[0][0] = A[0][0] * B[0][0];
		return;
	}

	// Bước 1: Chia ma trận A và B thành các ma trận con
	int newSize = size / 2;
	int **A11 = (int **)malloc(newSize * sizeof(int *));
	int **A12 = (int **)malloc(newSize * sizeof(int *));
	int **A21 = (int **)malloc(newSize * sizeof(int *));
	int **A22 = (int **)malloc(newSize * sizeof(int *));

	int **B11 = (int **)malloc(newSize * sizeof(int *));
	int **B12 = (int **)malloc(newSize * sizeof(int *));
	int **B21 = (int **)malloc(newSize * sizeof(int *));
	int **B22 = (int **)malloc(newSize * sizeof(int *));

	int **C11 = (int **)malloc(newSize * sizeof(int *));
	int **C12 = (int **)malloc(newSize * sizeof(int *));
	int **C21 = (int **)malloc(newSize * sizeof(int *));
	int **C22 = (int **)malloc(newSize * sizeof(int *));

	for (int i = 0; i < newSize; ++i) {
		A11[i] = (int *)malloc(newSize * sizeof(int));
		A12[i] = (int *)malloc(newSize * sizeof(int));
		A21[i] = (int *)malloc(newSize * sizeof(int));
		A22[i] = (int *)malloc(newSize * sizeof(int));

		B11[i] = (int *)malloc(newSize * sizeof(int));
		B12[i] = (int *)malloc(newSize * sizeof(int));
		B21[i] = (int *)malloc(newSize * sizeof(int));
		B22[i] = (int *)malloc(newSize * sizeof(int));

		C11[i] = (int *)malloc(newSize * sizeof(int));
		C12[i] = (int *)malloc(newSize * sizeof(int));
		C21[i] = (int *)malloc(newSize * sizeof(int));
		C22[i] = (int *)malloc(newSize * sizeof(int));
	}

	// Chia ma trận A và B thành các ma trận con
	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j) {
			A11[i][j] = A[i][j];
			A12[i][j] = A[i][j + newSize];
			A21[i][j] = A[i + newSize][j];
			A22[i][j] = A[i + newSize][j + newSize];

			B11[i][j] = B[i][j];
			B12[i][j] = B[i][j + newSize];
			B21[i][j] = B[i + newSize][j];
			B22[i][j] = B[i + newSize][j + newSize];
		}
	}

	// Bước 2: Tính toán các ma trận phụ cần thiết
	int **M1 = (int **)malloc(newSize * sizeof(int *));
	int **M2 = (int **)malloc(newSize * sizeof(int *));
	int **M3 = (int **)malloc(newSize * sizeof(int *));
	int **M4 = (int **)malloc(newSize * sizeof(int *));
	int **M5 = (int **)malloc(newSize * sizeof(int *));
	int **M6 = (int **)malloc(newSize * sizeof(int *));
	int **M7 = (int **)malloc(newSize * sizeof(int *));

	for (int i = 0; i < newSize; ++i) {
		M1[i] = (int *)malloc(newSize * sizeof(int));
		M2[i] = (int *)malloc(newSize * sizeof(int));
		M3[i] = (int *)malloc(newSize * sizeof(int));
		M4[i] = (int *)malloc(newSize * sizeof(int));
		M5[i] = (int *)malloc(newSize * sizeof(int));
		M6[i] = (int *)malloc(newSize * sizeof(int));
		M7[i] = (int *)malloc(newSize * sizeof(int));
	}

	MatrixAdd(A11, A22, C11, newSize);
	MatrixAdd(B11, B22, C12, newSize);
	Strassen(C11, C12, M1, newSize);  // M1 = (A11 + A22) * (B11 + B22)

	MatrixAdd(A21, A22, C11, newSize);
	Strassen(C11, B11, M2, newSize);  // M2 = (A21 + A22) * B11

	MatrixSub(B12, B22, C11, newSize);
	Strassen(A11, C11, M3, newSize);  // M3 = A11 * (B12 - B22)

	MatrixSub(B21, B11, C11, newSize);
	Strassen(A22, C11, M4, newSize);  // M4 = A22 * (B21 - B11)

	MatrixAdd(A11, A12, C11, newSize);
	Strassen(C11, B22, M5, newSize);  // M5 = (A11 + A12) * B22

	MatrixSub(A21, A11, C11, newSize);
	MatrixAdd(B11, B12, C12, newSize);
	Strassen(C11, C12, M6, newSize);  // M6 = (A21 - A11) * (B11 + B12)

	MatrixSub(A12, A22, C11, newSize);
	MatrixAdd(B21, B22, C12, newSize);
	Strassen(C11, C12, M7, newSize);  // M7 = (A12 - A22) * (B21 + B22)

	// Bước 3: Tính toán các ma trận con của ma trận kết quả C
	MatrixAdd(M1, M4, C11, newSize);
	MatrixSub(C11, M5, C11, newSize);
	MatrixAdd(C11, M7, C11, newSize);

	MatrixAdd(M3, M5, C12, newSize);

	MatrixAdd(M2, M4, C21, newSize);

	MatrixAdd(M1, M3, C22, newSize);
	MatrixSub(C22, M2, C22, newSize);
	MatrixAdd(C22, M6, C22, newSize);

	// Gán các ma trận con vào ma trận kết quả C
	for (int i = 0; i < newSize; ++i) {
		for (int j = 0; j < newSize; ++j) {
			C[i][j] = C11[i][j];
			C[i][j + newSize] = C12[i][j];
			C[i + newSize][j] = C21[i][j];
			C[i + newSize][j + newSize] = C22[i][j];
		}
	}

	// Giải phóng bộ nhớ
	for (int i = 0; i < newSize; ++i) {
		free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
		free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
		free(C11[i]); free(C12[i]); free(C21[i]); free(C22[i]);
		free(M1[i]); free(M2[i]); free(M3[i]); free(M4[i]);
		free(M5[i]); free(M6[i]); free(M7[i]);
	}
	free(A11); free(A12); free(A21); free(A22);
	free(B11); free(B12); free(B21); free(B22);
	free(C11); free(C12); free(C21); free(C22);
	free(M1); free(M2); free(M3); free(M4);
	free(M5); free(M6); free(M7);
}

// Hàm cộng hai ma trận
void MatrixAdd(int **A, int **B, int **C, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

// Hàm trừ hai ma trận
void MatrixSub(int **A, int **B, int **C, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

// Hàm in ma trận
void PrintMatrix(int **matrix, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			printf("%d\t", matrix[i][j]);
		}
		printf("\n");
	}
}


int main() {
	const int n = 4;  // Kích thước của các ma trận (giả sử là ma trận 4x4 để minh họa)

	// Khởi tạo các ma trận A và B ngẫu nhiên
	int **A = (int **)malloc(n * sizeof(int *));
	int **B = (int **)malloc(n * sizeof(int *));
	int **C = (int **)malloc(n * sizeof(int *));

	printf("Ma tran A:\n");
	for (int i = 0; i < n; ++i) {
		A[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; ++j) {
			A[i][j] = rand() % 10;  // Giá trị ngẫu nhiên từ 0 đến 9
			printf("%d\t", A[i][j]);
		}
		printf("\n");
	}

	printf("\nMa tran B:\n");
	for (int i = 0; i < n; ++i) {
		B[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; ++j) {
			B[i][j] = rand() % 10;  // Giá trị ngẫu nhiên từ 0 đến 9
			printf("%d\t", B[i][j]);
		}
		printf("\n");
	}

	// Khởi tạo ma trận kết quả C với giá trị 0
	for (int i = 0; i < n; ++i) {
		C[i] = (int *)malloc(n * sizeof(int));
		for (int j = 0; j < n; ++j) {
			C[i][j] = 0;
		}
	}

	// Gọi hàm Strassen để nhân hai ma trận
	Strassen(A, B, C, n);

	// In ma trận kết quả C
	printf("\nMa tran ket qua C:\n");
	PrintMatrix(C, n);

	// Giải phóng bộ nhớ
	for (int i = 0; i < n; ++i) {
		free(A[i]);
		free(B[i]);
		free(C[i]);
	}
	free(A);
	free(B);
	free(C);

	getchar();
	return 0;
}