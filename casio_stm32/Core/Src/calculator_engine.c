/*
 * calculator_engine.c
 *
 *  Created on: Oct 6, 2025
 *      Author: ADMIN
 */

#include "calculator_engine.h"

//Private function
static float eval_simple(char *expr) {
	float nums[17];
	int n = 0;
	char last_op = '+';
	int i = 0, len = strlen(expr);
	while (i < len) {
		while (expr[i] == ' ')
			i++;
		float num = 0, neg = 1, frac = 0.1;
		int has_dot = 0;
		if (expr[i] == '-') {
			neg = -1;
			i++;
		}
		while (isdigit(expr[i]) || expr[i] == '.') {
			if (expr[i] == '.') {
				has_dot = 1;
				i++;
				continue;
			}
			if (!has_dot) {
				num = num * 10 + (expr[i++] - '0');
			} else {
				num = num + (expr[i++] - '0') * frac;
				frac *= 0.1;
			}
		}
		num *= neg;
		if (last_op == '*')
			nums[n - 1] *= num;
		else if (last_op == ':')
			nums[n - 1] /= num;
		else if (last_op == '-')
			nums[n++] = -num;
		else
			nums[n++] = num;
		while (expr[i] == ' ')
			i++;
		last_op = expr[i++];
	}
	float result = 0;
	for (int j = 0; j < n; j++) {
		result += nums[j];
	}
	return result;
}

// Hàm binary search tìm nghiệm trong [l,r] với độ chính xác eps
static float calc(char *expr, float x) {
	char buf[64], numbuf[32];
	buf[0] = '\0';
	for (int i = 0; expr[i]; i++) {
		if (expr[i] == 'x') {
			float_to_str(x, numbuf, 7);
			strcat(buf, numbuf);
		} else {
			char tmp[2] = { expr[i], '\0' };
			strcat(buf, tmp);
		}
	}
	return Calculate(buf);
}

static int binary_search_root(char *expr, float l, float r, float eps,
		float *root) {
	float mid, f_l, f_mid;

	f_l = calc(expr, l);
	if (fabs(f_l) < eps) {
		*root = l;
		return 1;
	}

	while (r - l > eps) {
		mid = (l + r) / 2;
		f_mid = calc(expr, mid);

		if (fabs(f_mid) < eps) {
			*root = mid;
			return 1;
		}

		f_l = calc(expr, l);  // luôn tính lại
		if (f_l * f_mid < 0)
			r = mid;
		else
			l = mid;
	}
	*root = (l + r) / 2;
	return 1;
}

static void reverse_str(char *str) {
	int i = 0;
	int j = strlen(str) - 1;
	char temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Public function
float Calculate(char *data) {
	while (strchr(data, '(')) {
		int right = -1, left = -1;
		for (int i = 0; data[i]; i++) {
			if (data[i] == ')') {
				right = i;
				break;
			}
		}

		for (int i = right; i >= 0; i--) {
			if (data[i] == '(') {
				left = i;
				break;
			}
		}
		if (left == -1 || right == -1)
			break;
		char sub[64] = { 0 };
		strncpy(sub, data + left + 1, right - left - 1);
		double val = eval_simple(sub);

		char newdata[64] = { 0 };
		strncpy(newdata, data, left);
		char numbuf[64];
		float_to_str(val, numbuf, 2);
		strcat(newdata, numbuf);
		strcat(newdata, data + right + 1);
		strcpy(data, newdata);
	}

	float result = eval_simple(data);
	return result;
}

void solve_the_equation(char *expr) {
	float eps = 1e-4f;
	float step = 1.0f;
	float root;
	int found_root = 0;
	char kq[17];
	int col = 16;
	LCD_setCursor(1, 0);
	LCD_puts("tim");
	for (float l = -10000; l < 10000; l += step) {
		float r = l + step;
		float f_l = calc(expr, l);
		float f_r = calc(expr, r);

		if (fabs(f_l) < eps) {  // nghiệm ngay tại l
			found_root = 1;
			float_to_str(l, kq, 2);
			LCD_setCursor(1, col - strlen(kq));
			LCD_puts(kq);
			col -= col - strlen(kq) - 1;
		} else if (f_l * f_r < 0 || fabs(f_r) < eps) {
			found_root = 1;
			if (binary_search_root(expr, l, r, eps, &root)) {
				if (fabs(root) < eps)
					root = 0;
				float_to_str(root, kq, 2);
				LCD_setCursor(1, col - strlen(kq));
				LCD_puts(kq);
				if (col - strlen(kq) > 0) {
					LCD_setCursor(1, col - strlen(kq) - 1);
					LCD_puts(" ");
					col -= (strlen(kq) + 1);
				} else {
					col -= strlen(kq);
				}
			}
		}
	}
	if (!found_root) {
		LCD_setCursor(1, 0);
		LCD_puts("Not found");
	} else {
		LCD_setCursor(1, 0);
		LCD_puts("x: ");
	}
}

void int_to_str(long num, char *str, int base) {
	int i = 0;
	bool is_negative = false;
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return;
	}
	if (num < 0 && base == 10) {
		is_negative = true;
		num = -num;
	}
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}
	if (is_negative) {
		str[i++] = '-';
	}
	str[i] = '\0';
	reverse_str(str);
}

void float_to_str(float num, char *buffer, int precision) {
	// Xử lý dấu âm
	int idx = 0;
	if (num < 0) {
		buffer[idx++] = '-';
		num = -num;
	}

	// Phần nguyên
	int int_part = (int) num;
	float frac_part = num - int_part;

	// Chuyển phần nguyên sang chuỗi
	char temp[20];
	int t = 0;
	if (int_part == 0) {
		temp[t++] = '0';
	} else {
		while (int_part > 0) {
			temp[t++] = (int_part % 10) + '0';
			int_part /= 10;
		}
	}
	// Đảo ngược
	for (int i = t - 1; i >= 0; i--)
		buffer[idx++] = temp[i];

	// Thêm dấu thập phân
	if (precision > 0) {
		buffer[idx++] = '.';

		// Xử lý phần thập phân
		for (int i = 0; i < precision; i++) {
			frac_part *= 10;
			int digit = (int) frac_part;
			buffer[idx++] = digit + '0';
			frac_part -= digit;
		}

		// Bỏ bớt số 0 dư ở cuối
		while (precision > 0 && buffer[idx - 1] == '0') {
			idx--;
			precision--;
		}
		if (buffer[idx - 1] == '.')
			idx--; // bỏ dấu "." nếu ko còn số thập phân
	}

	buffer[idx] = '\0';
}

