#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Hàm nhân hai số nguyên lớn A và B, kết quả được lưu vào result
void multiply(char *num1, char *num2, char *result) {
	int len1 = strlen(num1);
	int len2 = strlen(num2);

	// Khởi tạo mảng kết quả có thể chứa được kết quả nhân lớn nhất
	int *res = (int *)malloc(sizeof(int)* (len1 + len2));

	// Khởi tạo các giá trị của mảng res bằng 0
	for (int i = 0; i < len1 + len2; i++) {
		res[i] = 0;
	}

	// Lặp từ phải sang trái qua từng chữ số của num1
	for (int i = len1 - 1; i >= 0; i--) {
		// Lặp từ phải sang trái qua từng chữ số của num2
		for (int j = len2 - 1; j >= 0; j--) {
			// Tính toán vị trí của kết quả trong mảng res
			int pos1 = i + j;
			int pos2 = i + j + 1;

			// Nhân từng chữ số của num1 và num2
			int mul = (num1[i] - '0') * (num2[j] - '0');

			// Cộng vào vị trí đang xét và cập nhật lại kết quả
			int sum = mul + res[pos2];
			res[pos1] += sum / 10;
			res[pos2] = sum % 10;
		}
	}

	// Bỏ qua các chữ số 0 dư thừa ở đầu mảng res
	int idx = 0;
	while (idx < len1 + len2 && res[idx] == 0) {
		idx++;
	}

	// Nếu mảng res chỉ chứa số 0 thì kết quả là "0"
	if (idx == len1 + len2) {
		strcpy(result, "0");
		return;
	}

	// Chuyển đổi mảng res thành chuỗi kết quả
	int resultIdx = 0;
	while (idx < len1 + len2) {
		result[resultIdx++] = res[idx++] + '0';
	}
	result[resultIdx] = '\0';

	// Giải phóng bộ nhớ
	free(res);
}

// Hàm main để kiểm tra
int main() {
	char num1[] = "2112";
	char num2[] = "1707";
	char result[100];  // Để chứa kết quả, có thể là đủ lớn để chứa kết quả nhân lớn nhất

	multiply(num1, num2, result);

	printf("%s * %s Ket qua: %s\n",num1 , num2, result);
	getchar();
	return 0;
}
