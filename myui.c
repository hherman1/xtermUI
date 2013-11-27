#include <stdio.h>

//structs
struct array {
	int length;
	struct key *data;
};
struct key {
	char *key;
	char *value;
};

//prototype
struct array* parse(char *string);
char* find(char **string,char end);


//main
void main(int argc, char *argv[]) {
	char *src;
	if(!argv[1]) {
		char buf[256];
		buf[0] = '\0';
		fread(buf,256,1,stdin);
		src = buf;
	} else {
		src = argv[1];
	}
	struct array *data = parse(src);
	int i = data->length;
	struct key temp;
	while(i--) {
		temp = data->data[i];
		printf("%s: %s\n",temp.key,temp.value);
	}
	free(data->data);
	free(data);
	
}

//functions
/*
Possible inputs:
|a: b|
|c: d|
|dog: brown|
*/
struct array* parse(char* string) {
	int numPairs = 0;
	int current = 0;
	char* c = string;
	while(*c != '\0' && ((*(c++) == '|' && numPairs++) || 1)); //get number of '|'
	numPairs /= 2; // number of pairs
	
	struct key *a = malloc(sizeof(struct key) * numPairs);
	struct key *b = a;
	
	struct array *ans = malloc(sizeof(struct array));
	ans->length = numPairs;
	ans->data = a;
	
	while(*string != '\0') {
		if(*string == '|') {
			current++;
			if(current%2) {
				string++;
				//printf(find(&string,':'));
				b->key = find(&string,':');
				while(*string == ' ' && string++);
				
				b->value = find(&string,'|');
				//printf("%s, %s\n",b->key,b->value);
				current++;
				b++;
			}
		}
		else {
			string++;
		}
	}
	//printf("%s: %s\n",a->key,a->value);
	//free(a);
	return ans;
}
//takes any string
char* find(char **string,char end) {
	char *ans = *string;
	while(*(++(*string)) != end);
	*(*string) = '\0';
	(*string)++;
	return ans;
}
