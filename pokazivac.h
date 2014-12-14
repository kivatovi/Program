struct klient{
	string ime, prezime;
	char spol;
	int dan, mj, god;
	int ai, bi, ci, di;
};
struct qu{
	klient value;
	qu *sljedeci;
};
struct que{
	qu *front, *rear;
};
que *InitQ(que *Q){
	Q = new que;
	qu *novi = new qu;
	novi->sljedeci = NULL;
	Q->front = novi;
	Q->rear = novi;
	return Q;
}
bool IsEmptyQ(que *Q){
	return Q->front == Q->rear;
}
klient FrontQ(que *Q){
	if(IsEmptyQ(Q)) cout << "prazan!"<<endl;
	else return Q->front->sljedeci->value;
}
void EnQueueQ(klient x, que *Q){
	qu *novi = new qu;
	novi->value = x;
	novi->sljedeci = NULL;
	Q->rear->sljedeci = novi;
	Q->rear = novi;
}
void DeQueueQ(que *Q){
	if(IsEmptyQ(Q)) cout << "prazan!"<<endl;
	else{
		qu *brisi = Q->front;
		Q->front = Q->front->sljedeci;
		delete brisi;
	}
}
