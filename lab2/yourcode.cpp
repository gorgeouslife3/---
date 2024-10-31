#include "Queue.cpp"
#include "Stack.cpp"
#include "Car.h"
#include <iostream>
#include <fstream>
#define input "./data/data.txt"
#define output "./output/yours.txt"
void Goin(Car car_, Stack& s, Queue& q){
	FILE *fp = fopen(output , "a");
	if(s.rear<s.size)
	{
		s.Push(car_);
		fprintf(fp, "%d at P %d\n", car_.Plate,s.rear);
	}
	else if(q.calculate()<q.size)
	{
		q.Push(car_);
		fprintf(fp, "%d at W %d\n", car_.Plate,q.calculate());
	}
	else
	fprintf(fp, "You can't park any car here.\n");
	fclose(fp);
}
void Goout(Car car_, Stack& s, Queue& q,int n, int prize, int m)
{
	Stack s_(n);
	Queue q_;
	Car p;
	int t;
	FILE *fp = fopen(output , "a");
	q_.size=m;
	if(q.Search(car_)==false && s.Search(car_)==false)
	fprintf(fp, "Can't find %d.\n", car_.Plate);
	else if (q.Search(car_) == true)//在waiting
	{
		while (q.head != NULL)
		{
			q.Pop(p);
			if(p.Plate != car_.Plate)
			q_.Push(p);
			else
			t=car_.Time-p.Time;
		}
		while (q_.head!=NULL)
		{
			q_.Pop(p);
			q.Push(p);
		}
		fprintf(fp,"id=%d time=%d fee=%d\n",car_.Plate,t,0);
	}
	else//在parkng
	{
		while(s.rear>0)
		{
			s.Pop(p);
			if(p.Plate != car_.Plate)
			s_.Push(p);
			else
			t=car_.Time - p.Time;
		}
		while (s_.rear>0)
		{
			s_.Pop(p);
			s.Push(p);
		}
		if(q.calculate()!=0)
		{
			q.Pop(p);
			p.Time=car_.Time;
			s.Push(p);
		}
		fprintf(fp,"id=%d time=%d fee=%d\n",car_.Plate,t,t*prize);
	}
	fclose(fp);
}

void print_stack(Stack s)
{
	int i=1;
	FILE *fp = fopen(output , "a");
	if(s.rear==0)
	fprintf(fp,"The parking lot is empty.\n");
	else
	{
		fprintf(fp, "P:");
		for(i=1;i<s.rear;i++) fprintf(fp, "%d,", s.elem[i].Plate);
		fprintf(fp,"%d\n",s.elem[s.rear].Plate);
	}
	fclose(fp);
}

void print_queue(Queue q){
	QueueUnit *p=q.head;
	FILE *fp = fopen(output , "a");
	if(q.calculate()==0)
	fprintf(fp,"The waiting area is empty.\n");
	else
	{
		fprintf(fp, "W:");
		while (p != q.rear)
		{
			fprintf(fp, "%d,", p->elem.Plate);
			p = p->next;
		}
		fprintf(fp,"%d\n",p->elem.Plate);
	}
	fclose(fp);
}

int main(){
	Car car_;
	Queue q;
	int n,m,prize;
	FILE *fp=fopen(input,"r");
	fscanf(fp,"%d %d %d\n",&n,&m,&prize);
	Stack s(n);
	q.size=m;

	std::string filename = output;
    std::ofstream ofs(filename);
    ofs.clear();
    ofs.close();
	//重写文件
	while (1)
	{
	fscanf(fp, "('%c',%d,%d)\n", &car_.Instruct, &car_.Plate, &car_.Time);
	if(car_.Instruct=='E') break;
	switch(car_.Instruct)
	{
		case 'A':
			Goin(car_, s, q);
			break;
		case 'D':
			Goout(car_, s, q, n, prize, m);
			break;
		case 'P':
			print_stack(s);
			break;
		case 'W':
			print_queue(q);
			break;
	}
	}
	fclose(fp);
	return 0;
}