struct klient{
	string ime, prezime;
	char spol;
	int dan, mj, god;
	int ai, bi, ci, di;
};
struct que{
	klient klienti[10000];
	int front, rear;
};
int AddOne(int n){
	return ((n+1)%10000);
}
que *InitQ(que *Q){
	Q = new que;
	Q->front = 0;
	Q->rear = 9999;
	return Q;
}
bool IsEmptyQ(que *Q){
	if(AddOne(Q->front) == Q->rear) return true;
	else return false;
}
klient FrontQ(que *Q){
	if(IsEmptyQ(Q)) cout << "prazan!"<<endl;
	else return Q->klienti[Q->front];
}
void EnQueueQ(klient x, que *Q){
	int n;
	if(Q->rear==9999) n=0;
	else n = Q->rear+1;
	Q->klienti[n] = x;
	Q->rear = n;
}
void DeQueueQ(que *Q){
	if(IsEmptyQ(Q)) cout << "prazan!"<<endl;
	else {
		if(Q->front==9999) Q->front=0;
		else Q->front++;
	}
}
