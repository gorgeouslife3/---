#include "Queue.h"
#include "Stack.h"
#include "Car.h"
#define input "./data/data.txt"
#define output "./output/yours.txt"
void read_number(int& n,int& m, int& p, FILE *fp)
{	
	fscanf(fp,"%d %d %d\n",&n,&m,&p);
}

bool read_car(Car car_, FILE *fp){
	fscanf(fp, "('%c',%d,%d)\n",&car_.Instruct,&car_.Plate,&car_.Time);
	if(car_.Instruct=='E')
	return false;
	else
	return true;
}

void Goin(Car car_, Stack s, Queue q){
	FILE *fp = fopen(output , "a");
	if(s.rear<=s.size-1)
	{
		s.Push(car_);
		fprintf(fp, "%d at P %d\n", s.elem[s.rear].Plate,s.rear+1);
	}
	else if(q.calculate()<=q.size)
	{
		q.Push(car_);
		fprintf(fp, "%d at W %d\n", q.rear->elem.Plate,q.calculate());
	}
	else
	fprintf(fp, "You can't park any car here.\n");
	fclose(fp);
}
void Goout(Car car_, Stack s, Queue q,int n, int prize)
{
	Stack s_(n);
	Queue q_;
	Car p;
	int t;
	FILE *fp = fopen(output , "a");
	if(q.Search(car_)==false&&s.Search(car_)==false)
	fprintf(fp, "Can't find %d.\n", car_.Plate);
	else if (q.Search(car_)==true)
	{
		while (q.head->next!=NULL)
		{
			q.Pop(p);
			if(p.Plate!=car_.Plate)
			q_.Push(p);
			else
			t=p.Time-car_.Time;
		}
		while (q_.head->next!=NULL)
		{
			q_.Pop(p);
			q.Push(p);
		}
		fprintf(fp,"id=%d time=%d fee=%d\n",car_.Plate,t,t*prize);
	}
	else
	{
		do{
			s.Pop(p);
			s_.Push(p);
		}while(p.Plate!=car_.Plate);
		s_.Pop(p);
		t=p.Time-car_.Time;
		while (s_.rear!=-1)
		{
			s_.Pop(p);
			s.Push(p);
		}
		if(q.calculate()!=0)
		{
			q.Pop(p);
			s.Push(p);
		}
		fprintf(fp,"id=%d time=%d fee=%d\n",car_.Plate,t,t*prize);
	}
	fclose(fp);
}
void print_stack(Stack s)
{
	int i;
	FILE *fp = fopen(output , "a");
	if(s.rear==-1)
	fprintf(fp,"The parking lot is empty.\n");
	else
	{
		fprintf(fp, "P:");
		for(i=0;i<s.rear;i++) fprintf(fp, "%d,", s.elem[i].Plate);
		fprintf(fp,"%d\n",s.elem[s.rear].Plate);
	}
	fclose(fp);
}
void print_queue(Queue q){
	QueueUnit *p=q.head->next;
	FILE *fp = fopen(output , "a");
	if(q.calculate()==0)
	fprintf(fp,"The waiting area is empty.\n");
	else
	{
		fprintf(fp, "W:");
		while (p->next!=NULL)
		{
			fprintf(fp, "%d,", p->elem.Plate);
			p=p->next;
		}
		fprintf(fp,"%d\n",p->elem.Plate);
	}
	fclose(fp);
}
/*
TODO: Fill your code here.
*/
int main(){
	Car car_;
	Queue q;
	int n,m,prize;
	FILE *fp=fopen(input,"r");
	read_number(n,m,prize,fp);
	printf("%d %d %d\n",n,m,prize);
	Stack s(n);
	q.size=m;
	read_car(car_,fp);
	printf("%d",car_.Plate);
	/*while (read_car(car_,fp)==true)
	switch(car_.Instruct)
	{
		case 'A':
			Goin(car_, s, q);
			break;
		case 'D':
			Goout(car_, s, q, n, prize);
			break;
		case 'P':
			print_stack(s);
			break;
		case 'W':
			print_queue(q);
			break;
	}
	fclose(fp);*/
	return 0;
}