#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
#define STEP 8
#define LP  1023
static byte path[LP+1] = {0};
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
		path[0] = 1;
		_run(_pass_func[1](number), step-1);  
		path[0] = 2;
		_run(_pass_func[2](number), step-1);  
	}else if(step==1){
	if(path[max_step-step-1] != 3){				// last step
		path[max_step-step] = 3;
		_run(_pass_func[3](number), step-1);
	}
	if(path[max_step-step-1] != 4){
		path[max_step-step] = 4;
		_run(_pass_func[4](number), step-1);
	}
	}else if(step == 0){ 						// end step
		if(number == 2012){
			printf("find it !\n");
			print_path();
			exit(0);
		}
		return;
	}else{										// other step
		int i;
		for(i=1; i<=4; i++){
			if(i==path[max_step-step-1])		//self is pass
				continue;
			path[max_step-step] = i;
			_run(_pass_func[i](number), step-1);
		}
	}
}

static void run(int step){
	_run(2011, step);
}

int main(int argc, char const *argv[])
{
	int i;
	for(i=2; i<=LP; i++){
		memset(path, 0, sizeof(path));
		run(max_step=i);
		printf("not find it! max step = %d\n", max_step);
	}
	return 0;
}
