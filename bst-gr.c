#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
struct node{
	int data;
	struct node* left;
	struct node* right;
};
int height(struct node* p) {
	int lh,rh;
	if(p==NULL) return 0;
	lh=height(p->left);
	rh=height(p->right);
	if(lh>rh) return lh+1;
	else return rh+1;
}
void insert(struct node** p,int x){
	if(*p==NULL){
		*p=(struct node*)malloc(sizeof(struct node));
		(*p)->left=NULL;
		(*p)->right=NULL;
		(*p)->data=x;
	}
	else{
		if(x<(*p)->data) insert(&(*p)->left,x);
		else insert(&(*p)->right,x);
	}
}
void preorder(struct node* p){
	if(p!=NULL){
		printf("%d ",p->data);
		preorder(p->left);
		preorder(p->right);
	}
}
void inorder(struct node* p){
	if(p!=NULL){
		inorder(p->left);
		printf("%d ",p->data);
		inorder(p->right);
	}
}
void postorder(struct node* p){
	if(p!=NULL){
		postorder(p->left);
		postorder(p->right);
		printf("%d ",p->data);
	}
}
void display(struct node* p,int xpad,int y,int hw,int lh){
	if(p!=NULL){
		char s[10];
		if(y==60) setcolor(YELLOW);
		else if(p->left==NULL && p->right==NULL) setcolor(GREEN);
		else setcolor(CYAN);
		sprintf(s,"%d",p->data);
		y+=5;
		outtextxy(xpad+hw,y,s);
		y+=10;
		setcolor(RED);
		if(p->left!=NULL){
			line(xpad+hw,y,xpad+hw/2,y+lh);
			display(p->left,xpad,y+lh,hw/2,lh);
		}
		if(p->right!=NULL){
			line(xpad+hw,y,xpad+hw*3/2,y+lh);
			display(p->right,xpad+hw,y+lh,hw/2,lh);
		}
	}
}
int main(void){
	int gdriver = DETECT, gmode;
	int maxx,maxy,h,lh,k,c;
	struct node *root=NULL;
	clrscr();
	initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");
	maxx=getmaxx();
	maxy=getmaxy();
	closegraph();
	do{
		printf("*** Binary Search Tree with Graphical Representation ***\n");
		printf("Enter a choice:\n0.Exit\n1.Insert\n2.Preorder 3.Inorder 4.Postorder\n5.Graphical Representation\n");
		scanf("%d",&c);
		if(c==0) break;
		if(c==1){
			printf("Enter Node:\n");
			scanf("%d",&k);
			insert(&root,k);
			printf("\n");
		}
		else if(c>=2 && c<=4){
			if(root==NULL) printf("Tree is Empty!\n\n");
			else{
				if(c==2){
					printf("Preorder: ");
					preorder(root);
				}
				if(c==3){
					printf("Inorder: ");
					inorder(root);
				}
				if(c==4){
					printf("Postorder: ");
					postorder(root);
				}
				printf("\n\n");
			}
		}
		else if(c==5){
			if(root==NULL) {
				printf("Tree is Empty!\n\n");
				continue;
			}
			initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");
			h=height(root);
			lh=(maxy-100)/h;
			cleardevice();
			outtextxy(maxx/2-100, 15, "Graphical Representation");
			outtextxy(maxx/2-75, 25, "Binary Search Tree");
			outtextxy(maxx/2-220, 35, "Root-Yellow, Internal Node-Cyan, Leaf-Green, Branch-Red");
			display(root,50,60,(maxx-100)/2,lh);
			getch();
			closegraph();
		}
		else printf("Invalid choice!\n\n");
	}
	while(c);
	return 0;
}
