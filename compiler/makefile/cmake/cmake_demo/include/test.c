#include <stdio.h>

struct point {
	int x;
	int y;
}; 
  
struct point *get_struct(struct point *);
void ouput(struct point p);
void print(const struct point *p);


int main(int argc, char const *argv[]) {
	struct point xx = {0, 0};
	get_struct(&xx);
//	output(xx);
//	output(*get_struct(&xx));
	print(get_struct(&xx));

	return 0;
}


struct point *get_struct(struct point *p) {
	scanf("%d", &p->x);
	scanf("%d", &p->y);
	printf("%d, %d\n", p->x, p->y);
	return p;
}

/*
void output(struct point p) {
	printf("%d, %d\n", p.x, p.y);
}
*/


void print(const struct point *p) {
	printf("%d, %d\n", p->x, p->y);
}

