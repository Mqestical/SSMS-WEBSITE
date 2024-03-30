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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef OS_MATH_LIB_H
#define OS_MATH_LIB_H

long long add_bin(long long bin1, long long bin2);
long long sub_bin(long long bin1, long long bin2);
long long mul_bin(long long bin1, long long bin2);
long long div_bin(long long bin1, long long bin2);
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
long long decimal_to_bin(long decimal);
char* decimal_to_hex(long decimal);
int bin_to_decimal(long long bin);
int hex_to_decimal(char hex[]);
unsigned long long hex_to_bin(char hex[]);
char* bin_to_hex(unsigned long long bin);

long long add_bin(long long bin1, long long bin2) {
	int result;
	long long decimal_bin1 = bin_to_decimal(bin1);
	long long decimal_bin2 = bin_to_decimal(bin2);
	result = decimal_bin1 + decimal_bin2;
	return result;
}

long long sub_bin(long long bin1, long long bin2) {
	int result;
	long long decimal_bin1 = bin_to_decimal(bin1);
	long long decimal_bin2 = bin_to_decimal(bin2);
	result = decimal_bin1 - decimal_bin2;
	return result;
}

long long mul_bin(long long bin1, long long bin2) {
	int result;
	long long decimal_bin1 = bin_to_decimal(bin1);
	long long decimal_bin2 = bin_to_decimal(bin2);
	result = decimal_bin1 * decimal_bin2;
	return result;
}

long long div_bin(long long bin1, long long bin2) {
	int result;
	long long decimal_bin1 = bin_to_decimal(bin1);
	long long decimal_bin2 = bin_to_decimal(bin2);
	result = decimal_bin1 / decimal_bin2;
	return result;
}

long long AND_bin(long long bin1, long long bin2) {
	long long result = bin1 & bin2;
	return result;
}

long long OR_bin(long long bin1, long long bin2) {
	long long result = bin1 | bin2;
	return result;
}

long long XOR_bin(long long bin1, long long bin2) {
	long long result = bin1 ^ bin2;
	return result;
}

long long NOT_bin(long long bin) {
	long long result = ~bin;
	return result;
}

long long lshift_bin(long long bin1, long long bin2) {
	long long result = bin1 << bin2;
	return result;
}

long long rshift_bin(long long bin1, long long bin2) {
	long long result = bin1 >> bin2;
	return result;
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

long long decimal_to_bin(long decimal) {
	long long binaryNumber = 0;
	int remainder, base = 1;

	// convert decimal to binary.
	while (decimal > 0) {
		remainder = decimal % 2;
		binaryNumber += remainder * base;
		decimal /= 2;
		base *= 10;
	}

	return binaryNumber;
}

char* decimal_to_hex(long decimal) {
	char* hexresult = malloc(8000);
	if (hexresult == NULL) {
		fprintf(stderr, "error: failed to allocate memory!");
		return NULL;
	}
	int remainder, index = 0;

	// convert decimal to hexadecimal.
	while (decimal != 0) {
		remainder = decimal % 16;

		// convert remainder to hexadecimal char
		if (remainder < 10) {
			hexresult[index++] = remainder + '0';
		} else {
			hexresult[index++] = remainder + 'A' - 10;
		}

		decimal /= 16;
	}

	hexresult[index] = '\0';

	// reverse the string
	int i, j;
	char temp;
	for (i = 0, j = index - 1; i < j; i++, j--) {
		temp = hexresult[i];
		hexresult[i] = hexresult[j];
		hexresult[j] = temp;
	}

	return hexresult;
}

int bin_to_decimal(long long bin) {
	int decimal = 0, i = 0, remainder;

	while (bin != 0) {
		// extract the last digit (rightmost).
		remainder = bin % 10;

		// multiply the digit by 2 raised to the power of its position.
		decimal += remainder * pow(2, i);

		// remove the last digit from the binary number.
		bin /= 10;

		++i;
	}

	return decimal;
}

int hex_to_decimal(char hex[]) {
	int decimal = 0;
	int length = 0;


	// calculate the length of the hexadecimal number.
	while (hex[length] != '\0') {
		length++;
	}

	// iterate through each digit of the hexadecimal number.
	for (int i = 0; hex[i] != '\0'; ++i) {
		int digitValue;

		// Convert hexadecimal character to decimal value.
		if (hex[i] >= '0' && hex[i] <= '9') {
			digitValue = hex[i] - '0';
		} else if (hex[i] >= 'A' && hex[i] <= 'F') {
			digitValue = hex[i] - 'A' + 10;
		} else if (hex[i] >= 'a' && hex[i] <= 'f') {
			digitValue = hex[i] - 'a' + 10;
		} else {
			// Invalid hexadecimal character
			printf("Invalid hexadecimal number!\n");
			return -1;
		}

		// update the decimal number with the value of the current digit.
		decimal += digitValue * pow(16, length - 1 - i);
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

#endif
