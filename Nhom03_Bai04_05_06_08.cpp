#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Hàm đệ quy tìm vị trí của phần tử lớn nhất trong mảng arr từ vị trí left đến right
int find_max_position(double arr[], int left, int right) {
	if (left == right) {
		return left;
	}

	int mid = (left + right) / 2;
	int max_left = find_max_position(arr, left, mid);
	int max_right = find_max_position(arr, mid + 1, right);

	if (arr[max_left] > arr[max_right]) {
		return max_left;
	}
	else {
		return max_right;
	}
}

// Hàm đệ quy tính tổng các phần tử của mảng từ l đến r
double sum(double arr[], int l, int r) {
	if (l == r) {
		return arr[l];
	}
	else {
		int mid = (l + r) / 2;
		double left_sum = sum(arr, l, mid);
		double right_sum = sum(arr, mid + 1, r);
		return left_sum + right_sum;
	}
}

// Hàm tính phần tử trung bình của mảng
double average(double arr[], int n) {
	double total_sum = sum(arr, 0, n - 1);
	return total_sum / n;
}

// Hàm tìm dãy con có tổng lớn nhất bắt đầu từ index low đến index high
double find_max_crossing_subarray(double arr[], int low, int mid, int high, int *start, int *end) {
	double left_sum = -1000000;
	double sum = 0;
	int i;

	// Tìm tổng lớn nhất của dãy con bắt đầu từ mid đi về phía low
	double left_max_sum = -1000000;
	for (i = mid; i >= low; i--) {
		sum += arr[i];
		if (sum > left_sum) {
			left_sum = sum;
			*start = i;  // Lưu lại chỉ số bắt đầu của dãy con lớn nhất bên trái
		}
	}

	double right_sum = -1000000;
	sum = 0;

	// Tìm tổng lớn nhất của dãy con bắt đầu từ mid+1 đi về phía high
	double right_max_sum = -1000000;
	for (i = mid + 1; i <= high; i++) {
		sum += arr[i];
		if (sum > right_sum) {
			right_sum = sum;
			*end = i;  // Lưu lại chỉ số kết thúc của dãy con lớn nhất bên phải
		}
	}

	// Trả về tổng của hai dãy con lớn nhất bắt qua mid
	return left_sum + right_sum;
}

// Hàm đệ quy để tìm dãy con có tổng lớn nhất trong mảng arr từ index low đến index high
double find_max_subarray_sum(double arr[], int low, int high, int *start, int *end) {
	// Trường hợp cơ sở: khi chỉ có một phần tử
	if (low == high) {
		*start = low;
		*end = high;
		return arr[low];
	}

	// Tìm chỉ số mid
	int mid = (low + high) / 2;

	// Tìm tổng lớn nhất của dãy con bên trái, bên phải và bắt qua giữa
	int left_start, left_end, right_start, right_end;
	double left_sum = find_max_subarray_sum(arr, low, mid, &left_start, &left_end);
	double right_sum = find_max_subarray_sum(arr, mid + 1, high, &right_start, &right_end);
	double cross_sum = find_max_crossing_subarray(arr, low, mid, high, &left_start, &right_end);

	// Trả về tổng lớn nhất trong ba trường hợp và cập nhật start và end cho dãy con lớn nhất
	if (left_sum >= right_sum && left_sum >= cross_sum) {
		*start = left_start;
		*end = left_end;
		return left_sum;
	}
	else if (right_sum >= left_sum && right_sum >= cross_sum) {
		*start = right_start;
		*end = right_end;
		return right_sum;
	}
	else {
		*start = left_start;
		*end = right_end;
		return cross_sum;
	}
}

// Hàm chính để tìm dãy con có tổng lớn nhất trong mảng arr
void find_maximum_subarray(double arr[], int n) {
	if (n == 0) {
		printf("Khong co day con nao\n");
		return;
	}

	int start, end;
	double max_sum = find_max_subarray_sum(arr, 0, n - 1, &start, &end);

	printf("Day con co tong lon nhat la: %.2lf\n", max_sum);
	printf("Day con do la: ");
	for (int i = start; i <= end; i++) {
		printf("%.2lf ", arr[i]);
	}
	printf("\n");
}

// Hàm hoán đổi giá trị của hai phần tử double
void swap(double *a, double *b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

// Hàm chuyển các phần tử âm trong mảng lên đầu mảng
void separate_negatives(double arr[], int n) {
	int positive_start = 0;  // Vị trí bắt đầu của phần tử dương

	// Duyệt qua mảng và đổi chỗ các phần tử âm với phần tử dương đầu tiên gặp phía sau
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0) {
			swap(&arr[i], &arr[positive_start]);
			positive_start++;
		}
	}
}

// Hàm partition được sửa đổi để sắp xếp các phần tử âm lên đầu mảng
int partition(double arr[], int left, int right, int *pivotIndex) {
	float pivot = arr[right];  // Chọn pivot là phần tử cuối cùng của mảng
	int negative_end = left - 1;  // Chỉ số cuối cùng của phần tử âm đã sắp xếp

	// Duyệt qua mảng từ left đến right - 1
	for (int j = left; j < right; j++) {
		if (arr[j] <= pivot && arr[j] < 0) {  // Nếu phần tử âm nhỏ hơn hoặc bằng pivot
			negative_end++;
			swap(&arr[negative_end], &arr[j]);  // Hoán đổi với phần tử âm cuối cùng đã sắp xếp
		}
		else if (arr[j] <= pivot) {  // Nếu là phần tử dương nhỏ hơn hoặc bằng pivot
			negative_end++;
			swap(&arr[negative_end], &arr[j]);  // Hoán đổi với phần tử âm cuối cùng đã sắp xếp
		}
	}

	// Hoán đổi pivot với phần tử dương đầu tiên gặp phía sau
	swap(&arr[negative_end + 1], &arr[right]);
	*pivotIndex = negative_end + 1;  // Cập nhật pivotIndex
	return negative_end + 1;
}

// Hàm sắp xếp Quick Sort để sắp xếp các phần tử âm và dương trong mảng
void quick_sort(double arr[], int left, int right) {
	if (left < right) {
		int pivotIndex;
		pivotIndex = partition(arr, left, right, &pivotIndex);  // Sử dụng partition đã sửa đổi để sắp xếp

		quick_sort(arr, left, pivotIndex - 1);  // Sắp xếp đệ quy các phần tử âm
		quick_sort(arr, pivotIndex + 1, right);  // Sắp xếp đệ quy các phần tử dương
	}
}

// Hàm tạo mảng ngẫu nhiên gồm n phần tử từ -maxValue đến maxValue
void create_random_array(double arr[], int n, double max_value) {
	srand(time(NULL));  // Khởi tạo seed cho hàm sinh số ngẫu nhiên
	for (int i = 0; i < n; ++i) {
		arr[i] = ((double)rand() / RAND_MAX) * 2 * max_value - max_value;  // Sinh ngẫu nhiên từ -maxValue đến maxValue
	}
}

// Hàm in mảng
void print_array(double arr[], int n) {
	printf("Mang: ");
	for (int i = 0; i < n; ++i) {
		printf("%.2lf ", arr[i]);
	}
	printf("\n");
}

int main() {
	int n, choice, max_position;
	double arr[100], max_value = 100.0;
	double avg;

	do {
		printf("\n--------MENU--------\n");
		printf("1. Tao mang ngau nhien\n");
		printf("2. Tim vi tri cua phan tu lon nhat trong mang n so thuc.\n");
		printf("3. Tim phan tu trung binh cua mang.\n");
		printf("4. Tim day con co tong lon nhat.\n");
		printf("5. Sap xep cac phan tu cua mot day n so thuc cho truoc sao cho tat ca cac phan tu am cua mang dung truoc tat ca cac phan tu duong trong mang.\n");
		printf("0. Thoat chuong trinh\n");
		printf("Lua chon cua ban: ");
		scanf("%d", &choice);

		switch (choice) {
		case 0:
			printf("\nThoat chuong trinh\n");
			break;
		case 1:
			printf("Nhap so luong phan tu cua mang (toi da %d): ", 100);
			scanf("%d", &n);
			// Kiểm tra nếu số lượng phần tử vượt quá 100 hoặc nhỏ hơn 1
			if (n <= 0 || n > 100) {
				printf("So luong phan tu khong hop le.\n");
				break;
			}
			printf("Mang ngau nhien duoc sinh ra:\n");
			create_random_array(arr, n, max_value);
			print_array(arr, n);
			break;
		case 2:
			print_array(arr, n);

			// Tìm và in ra vị trí của phần tử lớn nhất trong mảng
			max_position = find_max_position(arr, 0, n - 1);
			printf("Phan tu lon nhat trong mang la %.2lf tai vi tri %d\n", arr[max_position], max_position);
			break;
		case 3:
			print_array(arr, n);

			// Tính và in ra phần tử trung bình của mảng
			avg = average(arr, n);
			printf("Phan tu trung binh cua mang la: %.2lf\n", avg);
			break;
		case 4:
			print_array(arr, n);

			// Tìm và in ra dãy con có tổng lớn nhất
			find_maximum_subarray(arr, n);
			break;
		case 5:
			print_array(arr, n);

			separate_negatives(arr, n);  // Chuyển các phần tử âm lên đầu mảng
			quick_sort(arr, 0, n - 1);  // Sắp xếp mảng
			printf("Mang sau khi sap xep: \n");
			print_array(arr, n);
			break;
		default:
			printf("Lua chon khong hop le. Vui long chon lai.\n");
			break;
		}

	} while (choice != 0);

	return 0;
}
