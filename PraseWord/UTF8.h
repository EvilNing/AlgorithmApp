#ifndef  __UTF8_H__
#define __UTF8_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class UTF8
{
public:
	static int get_utf8_length(char c);

	static int utf8_to_unicode(const char* word , int length);     //�Ӵ洢��wordת��Ϊutf8����
	static int unicode_to_utf8(int code , char* word);  //utf8����ֵ ת��Ϊ�洢��ֵ

	static int filter_utf8_chinese_code(int code);
	static void print_binary(char c);
	
};


#endif
