/*
 * Author: Ryxus, Founder of Specialized System Management Software (SSMS).
 * Copyright © [2024] Specialized System Management Software (SSMS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#define ROWS 3
#define COLS 3

char* add_binary(const char* bin1, const char* bin2);
char* subtract_binary(const char* bin1, const char* bin2);
char* multiply_binary(const char* bin1, const char* bin2);
char* divide_bin(const char* dividend, const char* divisor);
char* modulus_bin(const char* dividend, const char* divisor);
long long AND_bin(long long bin1, long long bin2);
long long OR_bin(long long bin1, long long bin2);
long long XOR_bin(long long bin1, long long bin2);
long long NOT_bin(long long bin1);
long long lshift_bin(long long bin1, long long bin2);
long long rshift_bin(long long bin1, long long bin2);
char* addhex(char hex1[], char hex2[]);
char* subhex(char hex1[], char hex2[]);
char* mulhex(char hex1[], char hex2[]);
char* divhex(char hex1[], char hex2[]);
char* mod_hex(char hex1[], char hex2[]);
long long decimal_to_bin(long long decimal);
char* decimal_to_hex(long decimal);
int bin_to_decimal(long long binary);
int hex_to_decimal(char hex[]);
unsigned long long hex_to_bin(char hex[]);
char* bin_to_hex(unsigned long long bin);
bool bitwise_matrix_addition(int matrix_A[ROWS][COLS], int matrix_B[ROWS][COLS], int resultant_matrix[ROWS][COLS]);
void set_bit(uint8_t *buffer, size_t index);
void clear_bit(uint8_t *buffer, size_t index);
void toggle_bit(uint8_t *buffer, size_t index);

char* add_binary(const char* bin1, const char* bin2) {
	int len1 = strlen(bin1);
	int len2 = strlen(bin2);
	int maxlen = len1 > len2 ? len1 : len2;

	// Allocate memory for the result (including space for possible carry)
	char* result = (char*)malloc((maxlen + 2) * sizeof(char));
	if (result == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}

	// Initialize variables
	int carry = 0;
	int index = 0;

	// Iterate over digits from right to left
	for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0; i--, j--) {
		int bit1 = (i >= 0) ? bin1[i] - '0' : 0; // convert char to int
		int bit2 = (j >= 0) ? bin2[j] - '0' : 0; // convert char to int

		int sum = bit1 + bit2 + carry;
		result[index++] = sum % 2 + '0'; // convert integer(int) to char
		carry = sum / 2;
	}

	// if there is a carry left after addition:
	if (carry > 0) {
		result[index++] = carry + '0'; // convert integer(i32) to char
	}

	// terminate the string (NULL-TERMINATION)
	result[index] = '\0';

	// reverse the result string -
	int start = 0;
	int end = index - 1;
	while (start < end) {
		char temp = result[start];
		result[start] = result[end];
		result[end] = temp;
		start++;
		end--;
	}

	return result;
}

char* subtract_binary(const char* bin1, const char* bin2) {
	int len1 = strlen(bin1);
	int len2 = strlen(bin2);
	int maxlen = len1 > len2 ? len1 : len2;

	// memalloc for the result
	char* result = (char*)malloc((maxlen + 1) * sizeof(char));
	if (result == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}

	int borrow = 0;
	int index = 0;

	for (int i = len1 - 1, j = len2 - 1; i >= 0 || j >= 0; i--, j--) {
		int bit1 = (i >= 0) ? bin1[i] - '0' : 0;
		int bit2 = (j >= 0) ? bin2[j] - '0' : 0;

		int diff = bit1 - bit2 - borrow;

		// if the result is negative, borrow from the next higher bit
		if (diff < 0) {
			diff += 2; // Adding 2 since we're dealing with binary (0 or 1)
			borrow = 1;
		} else {
			borrow = 0;
		}

		result[index++] = diff + '0';
	}

	// rm leading zeros:
	while (index > 1 && result[index - 1] == '0') {
		index--;
	}

	// Terminate the string (NULL-TERMINATION)
	result[index] = '\0';

	int start = 0;
	int end = index - 1;
	while (start < end) {
		char temp = result[start];
		result[start] = result[end];
		result[end] = temp;
		start++;
		end--;
	}

	return result;
}

char* multiply_binary(const char* bin1, const char* bin2) {
	int len1 = strlen(bin1);
	int len2 = strlen(bin2);

	// memalloc for the result
	char* result = (char*)calloc(len1 + len2 + 1, sizeof(char)); // MAX possible length
	if (result == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}

	for (int i = len2 - 1; i >= 0; i--) {
		int carry = 0;

		for (int j = len1 - 1; j >= 0; j--) {
			int bit1 = bin1[j] - '0';
			int bit2 = bin2[i] - '0';

			int product = bit1 * bit2 + carry + (result[i + j + 1] - '0');
			result[i + j + 1] = (product % 2) + '0';
			carry = product / 2;
		}

		// if there's a carry after processing all bits of bin1, add it to the next position
		result[i] += carry;
	}

	// rm leading zeros
	int index = 0;
	while (index < len1 + len2 && result[index] == '0') {
		index++;
	}

	// shift the result to the beginning of the string -
	if (index > 0) {
		memmove(result, result + index, len1 + len2 - index + 1);
	}

	return result;
}

char* divide_bin(const char* dividend, const char* divisor) {
	int len_dividend = strlen(dividend);
	int len_divisor = strlen(divisor);

	// check for division by zero, if true then return NULL:
	if (len_divisor == 0 || (len_divisor == 1 && divisor[0] == '0')) {
		fprintf(stderr, "Division by zero error!\n");
		return NULL;
	}

	if (strcmp(dividend, divisor) < 0) {
		char* result = (char*)malloc(2 * sizeof(char));
		if (result == NULL) {
			fprintf(stderr, "Memory allocation failed!\n");
			return NULL;
		}
		result[0] = '0';
		result[1] = '\0';
		return result;
	}

	// memalloc the result
	char* quotient = (char*)malloc((len_dividend + 1) * sizeof(char));
	if (quotient == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}

	// quotient Initialization
	strcpy(quotient, "");

	// Initialize remainder as dividend
	char* remainder = (char*)malloc((len_dividend + 1) * sizeof(char));
	if (remainder == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		free(quotient);
		return NULL;
	}
	strcpy(remainder, dividend);

	// Iterate through the dividend, performing long division
	for (int i = 0; i < len_dividend; i++) {
		// Shift the remainder left by one position
		int len_remainder = strlen(remainder);
		memmove(remainder + 1, remainder, len_remainder + 1);
		remainder[0] = '0';

		// Try subtracting the divisor from the shifted remainder
		while (strcmp(remainder, divisor) >= 0) {
			char* temp = subtract_binary(remainder, divisor);
			free(remainder);
			remainder = temp;

			// Increment quotient
			quotient[i]++;
		}
	}

	// rm leading zeros from quotient
	int len_quotient = strlen(quotient);
	int i = 0;
	while (i < len_quotient && quotient[i] == '0') {
		i++;
	}
	if (i == len_quotient) {
		i--;
	}
	memmove(quotient, quotient + i, len_quotient - i + 1);

	free(remainder);
	return quotient;
}

char* modulus_bin(const char* dividend, const char* divisor) {
	int len_dividend = strlen(dividend);
	int len_divisor = strlen(divisor);

	// Check for division by zero and if dividend < divisor
	if (len_divisor == 0 || (len_divisor == 1 && divisor[0] == '0')) {
		fprintf(stderr, "Division by zero error!\n");
		return NULL;
	}

	if (strcmp(dividend, divisor) < 0) {
		char* result = (char*)malloc((len_dividend + 1) * sizeof(char));
		if (result == NULL) {
			fprintf(stderr, "Memory allocation failed!\n");
			return NULL;
		}
		strcpy(result, dividend);
		return result;
	}

	// Initialize remainder as dividend
	char* remainder = (char*)malloc((len_dividend + 1) * sizeof(char));
	if (remainder == NULL) {
		fprintf(stderr, "Memory allocation failed!\n");
		return NULL;
	}
	strcpy(remainder, dividend);

	// Iterate through the dividend, performing long division
	for (int i = 0; i < len_dividend; i++) {
		// Shift the remainder left by one position
		shift_left(remainder);

		// Try subtracting the divisor from the shifted remainder
		while (strcmp(remainder, divisor) >= 0) {
			char* temp = subtract_bin(remainder, divisor);
			free(remainder);
			remainder = temp;
		}
	}

	return remainder;
}

long long AND_bin(long long bin1, long long bin2) {
	long long result = bin1 & bin2;
	long long binary_result = decimal_to_bin(result);
	return binary_result;
}

long long OR_bin(long long bin1, long long bin2) {
	long long result = bin1 | bin2;
	long long binary_result = decimal_to_bin(result);
	return binary_result;
}

long long XOR_bin(long long bin1, long long bin2) {
	long long result = bin1 ^ bin2;
	long long binary_result = decimal_to_bin(result);
	return binary_result;
}

long long NOT_bin(long long bin) {
	long long result = ~bin;
	long long binary_result = decimal_to_bin(result);
	return binary_result;
}

long long lshift_bin(long long bin1, long long bin2) {
	long long result = bin1 << bin2;
	long long binary_result = decimal_to_bin(result);
	return binary_result;
}

long long rshift_bin(long long bin1, long long bin2) {
	long long result = bin1 >> bin2;
	long long binary_result = decimal_to_bin(result);
	return binary_result;
}

char* addhex(char hex1[], char hex2[]) {
	long long result;
	int decimal_hex1 = hex_to_decimal(hex1);
	int decimal_hex2 = hex_to_decimal(hex2);
	result = decimal_hex1 + decimal_hex2;
	return decimal_to_hex(result);
}

char* subhex(char hex1[], char hex2[]) {
	long long result;
	int decimal_hex1 = hex_to_decimal(hex1);
	int decimal_hex2 = hex_to_decimal(hex2);
	result = decimal_hex1 - decimal_hex2;
	return decimal_to_hex(result);
}

char* mulhex(char hex1[], char hex2[]) {
	long long result;
	int decimal_hex1 = hex_to_decimal(hex1);
	int decimal_hex2 = hex_to_decimal(hex2);
	result = decimal_hex1 * decimal_hex2;
	return decimal_to_hex(result);
}

char* divhex(char hex1[], char hex2[]) {
	long long result;
	int decimal_hex1 = hex_to_decimal(hex1);
	int decimal_hex2 = hex_to_decimal(hex2);
	result = decimal_hex1 / decimal_hex2;
	return decimal_to_hex(result);
}

char* mod_hex(char hex1[], char hex2[]) {
	int remainder;
	long long decimal_hex1 = hex_to_decimal(hex1);
	long long decimal_hex2 = hex_to_decimal(hex2);
	remainder = decimal_hex1 % decimal_hex2;
	return decimal_to_hex(remainder);
}

long long decimal_to_bin(long long decimal) {
	long long binary = 0, base = 1, remainder;

	while (decimal > 0) {
		remainder = decimal % 2;
		binary = binary + remainder * base;
		decimal = decimal / 2;
		base = base * 10;
	}

	return binary;
}

char* decimal_to_hex(long decimal) {
	char* hexresult;
	int remainder, index = 0;
	int length = (int)log10(decimal) + 1;

	hexresult = (char*)malloc(length + 1);
	if (hexresult == NULL) {
		fprintf(stderr, "error: failed to allocate memory!");
		return NULL;
	}

	while (decimal != 0) {
		remainder = decimal % 16;
		if (remainder < 10) {
			hexresult[index++] = remainder + '0';
		} else {
			hexresult[index++] = remainder + 'A' - 10;
		}
		decimal /= 16;
	}

	hexresult[index] = '\0';

	for (int i = 0, j = index - 1; i < j; i++, j--) {
		char temp = hexresult[i];
		hexresult[i] = hexresult[j];
		hexresult[j] = temp;
	}

	return hexresult;
}

int bin_to_decimal(long long bin) {
	long long binary = 0, base = 1, remainder;
	int decimal = 0;

	while (bin > 0) {
		remainder = bin % 10;
		decimal = decimal + remainder * base;
		bin = bin / 10;
		base = base * 2;
	}

	return decimal;
}

int hex_to_decimal(char hex[]) {
	int decimal = 0;

	for (int i = 0; hex[i] != '\0'; ++i) {
		int digitValue;
		if (hex[i] >= '0' && hex[i] <= '9') {
			digitValue = hex[i] - '0';
		} else if (hex[i] >= 'A' && hex[i] <= 'F') {
			digitValue = hex[i] - 'A' + 10;
		} else if (hex[i] >= 'a' && hex[i] <= 'f') {
			digitValue = hex[i] - 'a' + 10;
		} else {
			printf("Invalid hexadecimal number!\n");
			return -1;
		}
		decimal += digitValue * pow(16, strlen(hex) - 1 - i);
	}

	return decimal;
}

unsigned long long hex_to_bin(char hex[]) {
	long long decimal_hex;
	decimal_hex = hex_to_decimal(hex);
	unsigned long long bin = decimal_to_bin(decimal_hex);
	return bin;
}

char* bin_to_hex(unsigned long long bin) {
	long long decimal_bin;
	decimal_bin = bin_to_decimal(bin);
	return decimal_to_hex(decimal_bin);
}

bool bitwise_matrix_addition(int matrix_A[ROWS][COLS], int matrix_B[ROWS][COLS], int resultant_matrix[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			int sum = matrix_A[i][j] + matrix_B[i][j];
			if (sum < matrix_A[i][j] || sum < matrix_B[i][j]) {
				return false;
			}
			resultant_matrix[i][j] = sum;
		}
	}
	return true;
}

void set_bit(uint8_t *buffer, size_t index) {
	buffer[index / 8] |= (1 << (index % 8));
}

void clear_bit(uint8_t *buffer, size_t index) {
	buffer[index / 8] &= ~(1 << (index % 8));
}

void toggle_bit(uint8_t *buffer, size_t index) {
	buffer[index / 8] ^= (1 << (index % 8));
}
