#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
#define STEP 8
#define LP  1023
#define NEXT_STEP(t) do{path[max_step-step]=(t);_run(_pass_func[path[max_step-step]](number), step-1);}while(0)
static byte path[LP+1] = {0};
static byte mask[2] = {1, 3};
static int max_step = STEP;

static char* _desc[] = {
	"null",
	"+7 ",
	"/2 ",
	"*3 ",
	"-5 "
};

typedef int (*pass)(int);
static int pass0(int number){
	return number+7;
}

static int pass1(int number){
	return number/2;
}

static int pass2(int number){
	return number*3;
}

static int pass3(int number){
	return number-5;
}

static pass _pass_func[] = {
	NULL,
	pass0,
	pass1,
	pass2,
	pass3	
};

static void print_path(){
	int i=0;
	while(path[i]){
		printf("%s ", _desc[path[i++]]);
	}
	printf("\n");
}

static void _run(int number, int step){
	if(step==max_step){						  // goto step 1
		NEXT_STEP(1);
		NEXT_STEP(2);
	}else if(step==1){						 // last step
		if(path[max_step-step-1] == 3 || path[max_step-step-1] == 4) return;
		NEXT_STEP(3);
		NEXT_STEP(4);
	}else if(step == 0){ 						// end step
		if(number == 2012){
			printf("find it !\n");
			print_path();
			exit(0);
		}
		return;
	}else{									// other step
		NEXT_STEP(mask[!((path[max_step-step-1]-1)>>1)]);
		NEXT_STEP(path[max_step-step]+1);
	}
}

int main(int argc, char const *argv[])
{
	int i;
	for(i=2; i<=LP; i++){
		_run(2011, max_step=i);
		printf("not find it! max step = %d\n", max_step);
	}
	return 0;
}
