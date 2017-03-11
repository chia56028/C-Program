//#define DEBUG

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

void EstablishAnArray();
bool TheGameEndAtFirstPrint();
int  CanGameGoOn();
int  GameOver();
int  CheckInput(string);
void PrintArray();
bool CanTwoCoordinateBeRemoved(int, int, int, int);
bool CheckLine(int, int, int, int);
bool CheckCorner(int, int, int, int);

int e=4;					//e=edge
int arr2d[4][4];

int main(int argc, char** argv) {
	EstablishAnArray();	
	cout<<"Welcome to the game~"<<endl;
	PrintArray();
	
	int x1, x2, y1, y2;
	int r1, r2, c1, c2;
	int game=1;

	while(game==1){
		//��J�y�� 
		x1=CheckInput("�п�J�Ĥ@�ծy��x��:");
		y1=CheckInput("�п�J�Ĥ@�ծy��y��:");
		x2=CheckInput("�п�J�ĤG�ծy��x��:");
		y2=CheckInput("�п�J�ĤG�ծy��y��:");
		
		//�ഫ���}�C��� 
		r1=x1-1, r2=x2-1, c1=y1-1, c2=y2-1;
		
		if(CanTwoCoordinateBeRemoved(r1,r2,c1,c2)){
			if(CheckLine(r1,r2,c1,c2)){
				arr2d[c1][r1]=0;
				arr2d[c2][r2]=0;
				cout<<"Successful Remove"<<endl;
			}else if(CheckCorner(r1,r2,c1,c2)){
				arr2d[c1][r1]=0;
				arr2d[c2][r2]=0;
				cout<<"Successful Remove"<<endl;
			}else{
				cout<<"�L�k������"<<endl; 
			}
		}
		PrintArray();
		game=GameOver();
	}

	return 0;
}

void EstablishAnArray(){
	//�إߤ@�Ӱ}�C�å��� 
	int arr[e*e];
	for(int i=0; i<e*e; i++){
		arr[i]=i%(e*e/2)+1;
	}
	do{
		srand(3);
		int m, n;
		for(int i=0; i<e*e; i++){
			m=rand()%e*e;
			n=arr[i];
			arr[i]=arr[m];
			arr[m]=n;
		}
		//��J�G���}�C
		int k=0;
		for(int i=0; i<e; i++){
			for(int j=0; j<e; j++){
				arr2d[j][i]=arr[k];
				k+=1;
			}
		}
	}while(TheGameEndAtFirstPrint());
}

bool TheGameEndAtFirstPrint(){
	if(CanGameGoOn()==1){
		return false;
	}else{
		return true;
	}
}

int CanGameGoOn(){
	int A1[e*e], A2[e*e], B1[e*e], B2[e*e], endgame[e*e], wingame[e*e];
	int r1, r2, c1, c2;
	int k;
	for(int i=0; i<e*e; i++){
		A1[i]=99, A2[i]=99, B1[i]=99, B2[i]=99, endgame[i]=0, wingame[i]=0;
	}
	for(int i=0; i<e; i++){
	  	for(int j=0; j<e; j++){
		    k=arr2d[j][i];
		    if(A1[k]==99){
          		B1[k]=j, A1[k]=i;
    		}else{
	        	B2[k]=j, A2[k]=i;
	        }
	  	}
	}
	for(int l=1; l<=e*e/2; l++){
		r1=A1[l], r2=A2[l], c1=B1[l], c2=B2[l];
		if(r1!=99 && r2!=99 && c1!=99 && c2!=99){
			if(CheckLine(r1,r2,c1,c2)){
				k=arr2d[c1][r1];
				A1[k]=99, B1[k]=99;
				A2[k]=99, B2[k]=99;
				#ifdef DEBUG
				cout<<"l="<<l<<", CheckLine=1"<<endl;
				#endif
				return 1;
			}else if(CheckCorner(r1,r2,c1,c2)){
				k=arr2d[c1][r1];
			 	A1[k]=99, B1[k]=99;
				A2[k]=99, B2[k]=99;
				#ifdef DEBUG
				cout<<"l="<<l<<", CheckCorner=1"<<endl;
				#endif
				return 1;
			}else{
				endgame[l]=1;
			}
		}else{
			endgame[l]=1;
			wingame[l]=1;
		}
		#ifdef DEBUG
		cout<<l<<", eg="<<endgame[l]<<", wg="<<wingame[l]<<endl;
		#endif
	}
	//�P�_�C����Ĺ 
	int game;
	game=2;
	for(int l=1; l<=e*e/2; l++){
	  	if(wingame[l]!=1) game=0;
	}
	if(game==2){
		#ifdef DEBUG
		cout<<"game==2"<<endl;
		#endif
		return 2;
	}else{
		game=0;
	}
	if(game==0){
		#ifdef DEBUG
		cout<<"game==0"<<endl;
		#endif
		for(int l=1; l<=e*e/2; l++){
		  	if(endgame[l]!=1) return 1;
		}
	}
	return 0;
}

int GameOver(){
	int a=CanGameGoOn();
	if(a==1){
		return 1;
	}else if(a==0){
		cout<<"�w�g�S�������B�i�������Ʀr�F�A�C������QWQ"<<endl;
	}else if(a==2){
		cout<<"You win the game!!!"<<endl;
	}
	return 0;
}

void PrintArray(){
	cout<<endl;
	for(int i=0; i<e; i++){
		for(int j=0; j<e; j++){
			if(arr2d[i][j]<10){
				cout<<" "<<arr2d[i][j]<<" ";
			}else{
				cout<<arr2d[i][j]<<" ";	
			}
		}
		cout<<endl;
	}
}

int CheckInput(string requirement){
	int check=0;
	string InputString;
	float InputInt;
	while(check==0){
		cout<<requirement;
		getline(cin,InputString);
		InputInt=atof(InputString.c_str());
		if(InputInt>=1 && InputInt<=e && (int)InputInt==InputInt){
			check=1;
			return InputInt;
		}else{
			cout<<"�u���J����1-6������Ƴ�!!!"<<endl;
		}
	}
}

bool CanTwoCoordinateBeRemoved(int r1, int r2, int c1, int c2){
	if(arr2d[c1][r1]==0 || arr2d[c2][r2]==0){
		cout<<"�Фŭ��ƿ�J�Ʀr�w�Q�������y��~"<<endl;
		return false;
	}else if(r1==r2 && c1==c2){
		cout<<"�п�J�⤣�P�y��~"<<endl;
		return false;
	}else if(arr2d[c1][r1]!=arr2d[c2][r2]){
		cout<<"�u������ۦP���Ʀr��~"<<endl;
		return false;
	}else{
		return true;
	}
}

//��Ʀr���{ or �b�P�@���u�W 
bool CheckLine(int r1, int r2, int c1, int c2){
	int checkline=0;
	int m, n;
	if(r1==r2 || c1==c2){
		checkline=1;
		if(r1==r2){
			if(c1>c2){
				n=c1, c1=c2, c2=n;
			}
			if(c2>c1){
				for(int i=c1+1; i<c2 ; i++){
					if(arr2d[i][r1]!=0)	checkline=0;
				}
			}	
		}
		if(c1==c2){
			if(r1>r2){
				m=r1, r1=r2, r2=m;
			}
			if(r2>r1){
				for(int i=r1+1; i<r2 ; i++){
					if(arr2d[c1][i]!=0)	checkline=0;
				}
			}
		}
		#ifdef DEBUG
		//cout<<"checkline="<<checkline<<endl;
		#endif
		if(checkline==1){
			return true;
		}else{
			return false;
		}
	}
	return false;
}

//��@���s
bool CheckCorner(int r1, int r2, int c1, int c2){
	int crr=1, ccr=1, crl=1, ccl=1; 
	int m, n;
	if(r1!=r2 && c1!=c2){
		//(c1>c2 && r1>r2) || (c2>c1 && r2>r1)
		if(r2>r1 && c2>c1){
			n=c1, c1=c2, c2=n;
			m=r1, r1=r2, r2=m;
		}
		if(c1>c2 && r1>r2){
			for(int i=r2+1; i<=r1; i++){
				if(arr2d[c2][i]!=0) crr=0;
			}
			for(int j=c2; j<c1; j++){
				if(arr2d[j][r1]!=0)	ccr=0;
			}
			for(int i=r2; i<r1; i++){
				if(arr2d[c1][i]!=0) crl=0;
			}
			for(int j=c2+1; j<=c1; j++){
				if(arr2d[j][r2]!=0)	ccl=0;
			}
		}
		//(r1>r2 && c2>c1) || (r2>r1 && c1>c2)
		if(r2>r1 && c1>c2){
			n=c1, c1=c2, c2=n;
			m=r1, r1=r2, r2=m;
		}
		if(r1>r2 && c2>c1){
			for(int i=r2; i<r1; i++){
				if(arr2d[c1][i]!=0) crl=0;
			}
			for(int j=c1; j<c2; j++){
				if(arr2d[j][r2]!=0) ccl=0;
			}
			for(int i=r2+1; i<=r1; i++){
				if(arr2d[c2][i]!=0) crr=0;
			}
			for(int j=c1+1; j<=c2; j++){
				if(arr2d[j][r1]!=0) ccr=0;
			}
		}
		if((crr==1 && ccr==1) || (crl==1 && ccl==1)){
			return true;
		}else{
			return false;
		}
	}
	return false;
}