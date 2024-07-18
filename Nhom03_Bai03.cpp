#include <stdio.h>
#include <math.h>

// Hàm tính dấu của số nguyên
long long Sign(long long num) {
	if (num > 0) return 1;
	if (num < 0) return -1;
	return 0;
}

// Hàm tính lũy thừa của một số nguyên base với số mũ exponent
long long Pow(long long base, int exponent) {
	if (exponent == 0) return 1;
	if (exponent == 1) return base;

	long long half = Pow(base, exponent / 2);
	if (exponent % 2 == 0) {
		return half * half;
	}
	else {
		return base * half * half;
	}
}
// Hàm trả về n chữ số đầu của số nguyên num
long long Left(long long num, int digits) {
	return num / Pow(10, digits);
}

// Hàm trả về n chữ số cuối của số nguyên num
long long Right(long long num, int digits) {
	return num % Pow(10, digits);
}


// Hàm Big_Number_Multi để nhân hai số nguyên lớn sử dụng phương pháp chia để trị
long long Big_Number_Multi(long long X, long long Y, int n) {
	long long m1, m2, m3, A, B, C, D;
	long long s; // Lưu dấu của tích XY

	// Tính dấu của X * Y
	s = Sign(X) * Sign(Y);

	// Lấy giá trị tuyệt đối của X và Y
	X = llabs(X);
	Y = llabs(Y);

	// Trường hợp cơ bản: X và Y có 1 chữ số
	if (n == 1)
		return X * Y * s;
	else {
		// Chia X và Y thành các phần A, B và C, D tương ứng
		A = Left(X, n / 2);  // Số có n/2 chữ số đầu của X
		B = Right(X, n / 2); // Số có n/2 chữ số cuối của X
		C = Left(Y, n / 2);  // Số có n/2 chữ số đầu của Y
		D = Right(Y, n / 2); // Số có n/2 chữ số cuối của Y

		// Đệ quy tính toán các giá trị m1, m2, m3
		m1 = Big_Number_Multi(A, C, n / 2);        // m1 = A * C
		m2 = Big_Number_Multi(A - B, D - C, n / 2); // m2 = (A - B) * (D - C)
		m3 = Big_Number_Multi(B, D, n / 2);        // m3 = B * D

		// Tính kết quả theo công thức đệ quy
		return s * (m1 * Pow(10, n) + (m1 + m2 + m3) * Pow(10, n / 2) + m3);
	}
}

int main() {
	long long X = 123456789012345;
	long long Y = 987654321098765;
	int n = 15; // Số chữ số của X và Y

	long long result = Big_Number_Multi(X, Y, n);

	printf("Ket qua cua %lld * %lld là: %lld\n", X, Y, result);
	getchar();
	return 0;
}
