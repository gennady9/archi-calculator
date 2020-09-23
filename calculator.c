#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------ extern functions ------

// ---asm_add - requires 2 string of bignums, the first one should be the bigger and they both should have equal number of digits[add placeholder]
extern int asm_add(char*, char*, int, char*); // @@param: num1.digit, num2.digit, higher num length, allocated result space
extern int asm_sub(char*, char*, int, char*); // @@param: num1.digit, num2.digit, higher num length, allocated result space
extern int asm_mul(char*, char*, int, char*); // @@param: num1.digit, num2.digit, higher num length, allocated result space
extern int asm_div(char*, char*, int, char*); // @@param: num1.digit, num2.digit, higher num length, allocated result space

typedef struct bignum {
    long number_of_digits;
    char *digit;
    int negetive;
} bignum;


// assisting 
// push function
void push(bignum** s, bignum* num, int* spointer){
    s[*spointer]= num;
    (*spointer)++;
}
// pop function
bignum* pop(bignum** s, int* spointer){
    bignum* num = s[(*spointer)-1];
    (*spointer)--;
    return num;
}
// peek function
bignum* peek(bignum** s, int* spointer){
    bignum* num = s[(*spointer)-1];
    return num;
}
// extended zeros for num
char* add_zeros(char* num,int num_size, int zeros_add){
    int len = strlen(num);
    char* ret = calloc (len+zeros_add+1,sizeof(char)); // +1 for null terminator 
    int i=0;
    for(; i<zeros_add; i++){
        ret[i] = '0';
    }
    int j=0;
    for(; i<num_size + zeros_add; i++){
        ret[i] = num[j];
        j++;
    }
    return ret;
}
// assist func -'remove leading zeros'
char* remove_zeros(char* num){
	int num_size = strlen(num);
    int zeros = 0;
    for(int i=0; i<num_size; i++){
    	if('0'==num[i]){
    		zeros++;
    	}else{ // if not leading zero
    		break;
    	}
    }
	if(zeros == num_size){ // if only zeros
		return num + zeros-1; // return just the last zero
	}else{
		return num + zeros;
	}
}

int compare_numbers(bignum* n1, bignum* n2, int abs){
    // compare numbers function (if abs=1 -> only absolute value compare)
    int n1_neg = n1->negetive;
    int n2_neg = n2->negetive;
    if(abs){
		n1_neg = 0;
		n2_neg = 0;
    }
    if(n1_neg ^ n2_neg){ // if both have same sign
        if(!n1_neg && n2_neg){ // n1 postive, n2 negetive
            return 1;
        }else{ // n1 negetive, n2 postive
            return -1;
        }
    }else{ // if both have different sign
        int n1_len = n1->number_of_digits;
        int n2_len = n2->number_of_digits;
        if(n1_len > n2_len){ // n1>n2
            return 1;
        }else if(n1_len < n2_len){ // n1<n2
            return -1;
        }else{ // n1 = n2, compare digits one by one
            char* n1_digit = n1->digit;
            char* n2_digit = n2->digit;
            for(int i=0; i<n1_len; i++){ // consider changing n1_len to strlen(digit)
                if(n1_digit[i] > n2_digit[i]){
                    return 1;
                }else if(n1_digit[i] < n2_digit[i]){
                    return -1;
                }
            }
            // if finished for without returning, n1=n2
            return 0;
        }
    }
}

// asm_add func(but modified to be bigger number first parameter)
void asm_add_bigger_first(bignum* num1, bignum* num2, char* m){
    if(compare_numbers(num1, num2, 1)>=0){
    	asm_add(num1->digit, num2->digit, num1->number_of_digits, m);
    }else{
    	asm_add(num2->digit, num1->digit, num2->number_of_digits, m);
    }
}
// asm_sub func(but modified to be bigger number first parameter)
void asm_sub_bigger_first(bignum* num1, bignum* num2, char* m){
    if(compare_numbers(num1, num2, 1)>=0){
    	asm_sub(num1->digit, num2->digit, num1->number_of_digits, m);
    }else{
    	asm_sub(num2->digit, num1->digit, num2->number_of_digits, m);
    }
}

char* add_underscore(char* num){
    int len = strlen(num);
    char* ret = realloc(num, len + sizeof(char));
    ret[0]='_';
    int i=1;
    int j=0;
    for(; i<=len; i++){
        ret[i] = num[j];
        j++;
    }
    return ret;
}

int check_if_zero(char* num){
    for(int i=0; i<strlen(num); i++){
    	if(num[i]!='0'){
    		return 0; // not zero 
    	}
    	
    }
    return 1; // zero
}
void clear_stack(bignum** s, int* spointer){
    while((*spointer)>0){
        bignum* head = pop(s, spointer);
        if(head!=NULL){
            free(head);
        }
    }
}

int main() {
    // stack-related vars
    bignum** s = malloc(sizeof(bignum*)*1024); 
    int spointer=0;
    // input-related vars
    int creating_big_num = 0;
    int negetive = 0;
    long char_count = 0;
    char* acc_string;
    char* temp_string;
    char tmpstr[1] = {0};
    int dont_push_result = 0;
    
    // reading input
    char c = fgetc(stdin);
    while(c!=EOF){
        
        if(c>='0' && c<='9'){ // number
            if(!creating_big_num){
                 creating_big_num = 1;
                 char_count = 0;

                 acc_string = calloc (8,sizeof(char));
                 temp_string = calloc (8, sizeof(char));
                 
            }
            
            // already started creating string
            char_count++;
            
            // concatinate string
            char* temp_pointer = realloc(acc_string, sizeof(char)*(char_count+1+1)); // +1 for additional char, +1 for null terminator
            acc_string = temp_pointer;
            if(acc_string==NULL){
            	printf("realloc error");
            }
            tmpstr[0]=c;
            strcat(acc_string, tmpstr);
            
        }else{ // if not number char
            if(creating_big_num){
                creating_big_num = 0;
                
                // adding null-terminator
                int len = strlen(acc_string);
                acc_string[len]='\0'; // null terminator
                // turning into big num & inserting into stack
                struct bignum *push_num = malloc (sizeof (struct bignum));
                push_num->number_of_digits = char_count;
                push_num->digit = acc_string;
                push_num->negetive = negetive;
                push(s, push_num, &spointer);
                free(temp_string);
                negetive = 0;
            }
            if(c>32){ // if not whitespace
                if(c=='+' || c=='-' || c=='/' || c=='*'){
                    // pop the target numbers
                    bignum* num2 = pop(s, &spointer);
                    bignum* num1 = pop(s, &spointer);
                    
                    // add zeros to lower number
                    if(num1->number_of_digits > num2->number_of_digits){ // num1 > num 2
						num2->digit = add_zeros(num2->digit, num2->number_of_digits, num1->number_of_digits - num2->number_of_digits);    
					}
					else if(num1->number_of_digits < num2->number_of_digits){ // num1 < num2
						num1->digit = add_zeros(num1->digit, num1->number_of_digits, num2->number_of_digits - num1->number_of_digits);   
					}
					// result-related vars
                    int result_positive = 1;
                    int comp_result = compare_numbers(num1, num2, 1);
                    int bigger_digit = comp_result >= 0? strlen(num1->digit) : strlen(num2->digit);
                    char* m=calloc(bigger_digit+1+1, sizeof(char));// result space allocation
        			if(temp_string==NULL){
						printf("realloc error (m allocation)");
					}
                    switch(c){
                        case '+':
                        	if(!num1->negetive && !num2->negetive){ // n1&n2 positive
                        		asm_add_bigger_first(num1, num2, m);
                        	}
                        	else if(!num1->negetive && num2->negetive){ // only n1 positive
                        		asm_sub_bigger_first(num1,num2, m);
                        		if(comp_result < 0){ // n1 < n2
                        			result_positive = 0;
                        		}
                        	}
                        	else if(num1->negetive && !num2->negetive){ // only n2 positive
                        		asm_sub_bigger_first(num1,num2, m);
                        		if(comp_result > 0){ // n1 > n2
                        			result_positive = 0;
                        		}
                        	}else{ // both negetive
                        		asm_add_bigger_first(num1, num2, m);
                        		result_positive = 0;
                        	}
							m = remove_zeros(m);
                            break;
                        case '-':
                        	if(!num1->negetive && !num2->negetive){ // n1&n2 positive
                        		asm_sub_bigger_first(num1,num2, m);
                        		if(comp_result < 0){ // n1 < n2
                        			result_positive = 0;
                        		}
                        	}
                        	else if(!num1->negetive && num2->negetive){ // only n1 positive
                       			asm_add_bigger_first(num1, num2, m);
                        	}
                        	else if(num1->negetive && !num2->negetive){ // only n2 positive
                        		asm_add_bigger_first(num1, num2, m);
                        		result_positive = 0;
                        	}else{ // both negetive
                        		asm_sub_bigger_first(num1,num2, m);
                        		if(comp_result > 0){ // n1 > n2
                        			result_positive = 0;
                        		}
                        	}
                        	m = remove_zeros(m);
                            break;
                            
                        case '/':
                            if(num1->negetive ^ num2->negetive){ // if exactly one is negetive
                            	result_positive = 0;
                            }
                            if(check_if_zero(num2->digit)){ 
                            	printf("divide by zero\n");
                            	dont_push_result = 1;
                            }else{
		                        asm_div(num1->digit, num2->digit, bigger_digit, m);
		                        m = remove_zeros(m);
		                        if (strcmp(m, "0") == 0){ // special case - result is 0
		                        	result_positive = 1;
		                        }
                            }
                            break;
                            
                        case '*':
                            if(num1->negetive ^ num2->negetive){ // if exactly one is negetive
                            	result_positive = 0;
                            }
                            free(m);
                            m = calloc(bigger_digit*2+1, sizeof(char));
                            if(m==NULL){
                                    printf("relloc error (mul)");
                            }
                            // mul, highest first
                            if(comp_result>=0){ // n1 >= n2
                            	asm_mul(num1->digit, num2->digit, num1->number_of_digits, m);
                            }else{ // n2 > n1
                            	asm_mul(num2->digit, num1->digit, num2->number_of_digits, m);
                            }
                            m = remove_zeros(m);
                            if (strcmp(m, "0") == 0){ // special case - result is 0
                            	result_positive = 1;
                            }
                            break;
                    }
                    // after result
                    if(!dont_push_result){ // if not divided by zero
                        // adding '\0' to result string
                        int len = strlen(m);
                        m[len]='\0';
                        //creating result bignum
                        struct bignum *result = malloc (sizeof (struct bignum));
                        result->number_of_digits = len;
                        result->digit = m;
                        result->negetive = !result_positive;
                        // inserting into 'stack'
                        push(s, result, &spointer);
                        free(num1);
                        free(num2);
                	}else{
                		dont_push_result = 0;
                	}
                }
                else if(c=='_'){
                    negetive=1;
                }
                else if(c=='p'){
                    bignum* head = peek(s, &spointer); // view the head
                    printf("%s%s\n",head->negetive?"-":"", head->digit);
                }
                else if(c=='c'){
                    clear_stack(s, &spointer);
                }
                else if(c=='q'){
                    clear_stack(s, &spointer);
                    free(s);
                    return 0;
                }
            }
        }
        
        c = fgetc(stdin);
    }
    // freeing space
    clear_stack(s, &spointer);
    free(s);
    return 0;
}
