#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>

//set margin and line spacing here
#define MARGIN 10
#define LINE_SPACING 5

//set colors
#define ROOT_COLOR YELLOW
#define ROOT_COLOR_STRING "Yellow"
#define NODE_COLOR CYAN
#define NODE_COLOR_STRING "Cyan"
#define LEAF_COLOR GREEN
#define LEAF_COLOR_STRING "Green"
#define BRANCH_COLOR RED
#define BRANCH_COLOR_STRING "Red"

//global variables initialised after display_graph() is called
int LINE_HEIGHT,LEVEL_HEIGHT;

//node structure
struct node{
	int data;
	struct node* left;
	struct node* right;
};

//height of subtree of a node
int height(struct node* p) {
	int lh,rh;
	if(p==NULL) return 0;
	lh=height(p->left);
	rh=height(p->right);
	if(lh>rh) return lh+1;
	else return rh+1;
}

//insert node if does not exist already
void insert(struct node** p,int x){
	if(*p==NULL){
		*p=(struct node*)malloc(sizeof(struct node));
		(*p)->left=NULL;
		(*p)->right=NULL;
		(*p)->data=x;
	}
	else if(x!=(*p)->data){
		if(x<(*p)->data) insert(&(*p)->left,x);
		else insert(&(*p)->right,x);
	}
}

//preorder traversal
void preorder(struct node* p){
	if(p!=NULL){
		printf("%d ",p->data);
		preorder(p->left);
		preorder(p->right);
	}
}

//inorder traversal
void inorder(struct node* p){
	if(p!=NULL){
		inorder(p->left);
		printf("%d ",p->data);
		inorder(p->right);
	}
}

//postorder traversal
void postorder(struct node* p){
	if(p!=NULL){
		postorder(p->left);
		postorder(p->right);
		printf("%d ",p->data);
	}
}

//display node and its children
void display_node(struct node* p,int xpad,int y,int hw,int isroot){
	int ny,tw;
	char s[10]; //maximum value of node is 10 digits

	if(p!=NULL){

		//coloring node
		if(isroot) {
			isroot=0;
			setcolor(ROOT_COLOR);
		}
		else if(p->left==NULL && p->right==NULL) setcolor(LEAF_COLOR);
		else setcolor(NODE_COLOR);

		//print node
		sprintf(s,"%d",p->data);
		tw=textwidth(s)/2;
		outtextxy(xpad+hw-tw,y+LINE_SPACING,s);
		ny=y+LINE_HEIGHT+2*LINE_SPACING;
		
		//set branch color
		setcolor(BRANCH_COLOR);

		//display child nodes
		if(p->left!=NULL){
			line(xpad+hw,ny,xpad+hw/2,y+LEVEL_HEIGHT);
			display_node(p->left,xpad,y+LEVEL_HEIGHT,hw/2,isroot);
		}
		if(p->right!=NULL){
			line(xpad+hw,ny,xpad+hw*3/2,y+LEVEL_HEIGHT);
			display_node(p->right,xpad+hw,y+LEVEL_HEIGHT,hw/2,isroot);
		}
	}
}

void display_graph(struct node* root, int *gdriver, int *gmode, int maxx, int maxy){
	int h,l1w,l2w,l3w,y;
	char *path="C:\\turboc3\\bgi";
	char *l1="Graphical Representation";
	char *l2="Binary Search Tree";
	char l3[150];

	sprintf(l3,"Root-%s, Internal Node-%s, Leaf-%s, Branch-%s",ROOT_COLOR_STRING, NODE_COLOR_STRING, LEAF_COLOR_STRING, BRANCH_COLOR_STRING);
	
	//initialise graph and clear screen
	initgraph(gdriver, gmode, path);
	cleardevice();
	
	//get line height and widths
	l1w=textwidth(l1),l2w=textwidth(l2),l3w=textwidth(l3);
	LINE_HEIGHT=textheight(l1);
	
	//display lines
	y=MARGIN+LINE_SPACING;
	outtextxy((maxx-l1w)/2, y, l1);
	y+=LINE_HEIGHT+LINE_SPACING;
	
	outtextxy((maxx-l2w)/2, y, l2);
	y+=LINE_HEIGHT+LINE_SPACING;
	
	outtextxy((maxx-l3w)/2, y, l3);
	y+=LINE_HEIGHT+LINE_SPACING;
	
	//get height of tree
	h=height(root);

	//if no children, still height 2 to print root at top (note the division by h-1 on next lines)
	if(h==1) h=2;

	//calculate level height
	//subtracting margin, printed lines height and leaf nodes height
	//divide by h-1 since h-1 sections of screen
	LEVEL_HEIGHT=(maxy-MARGIN-y-(2*LINE_SPACING+LINE_HEIGHT))/(h-1);
	
	//display root and its children
	display_node(root,MARGIN,y,(maxx-2*MARGIN)/2,1);

	//wait for input before going back to menu
	getch();

	//close graph
	closegraph();
}

int main(void){
	int gdriver = DETECT, gmode;
	int maxx,maxy,k,c;
	struct node *root=NULL;

	clrscr();

	//get maximum width and height
	initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");
	maxx=getmaxx();
	maxy=getmaxy();
	closegraph();
	
	//main loop
	do{
		printf("*** Binary Search Tree with Graphical Representation ***\n");
		printf("0.Exit\n1.Insert\n2.Preorder 3.Inorder 4.Postorder\n5.Graphical Representation\nEnter a choice: ");
		scanf("%d",&c);
		if(c==0) break;
		if(c==1){
			//accept and insert node
			printf("Enter Node: ");
			scanf("%d",&k);
			insert(&root,k);
			printf("\n");
		}
		else if(c>=2 && c<=4){
			//display if tree is not empty
			if(root==NULL) printf("Tree is Empty!\n\n");
			else{
				if(c==2){
					//display preorder
					printf("Preorder: ");
					preorder(root);
				}
				if(c==3){
					//display inorder
					printf("Inorder: ");
					inorder(root);
				}
				if(c==4){
					//display postorder
					printf("Postorder: ");
					postorder(root);
				}
				printf("\n\n");
			}
		}
		else if(c==5){
			//display graphical representation if tree is not empty
			if(root==NULL) printf("Tree is Empty!\n\n");
			else display_graph(root,&gdriver,&gmode,maxx,maxy);
		}
		else printf("Invalid choice!\n\n");
	}
	while(1);

	return 0;
}
