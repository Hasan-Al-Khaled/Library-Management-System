#include <windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<time.h>
#define RETURNTIME 1

char catagories[][16]={"C programming ","Data Structure","Operating System","Math","Physics","English"};
void returnfunc(void);
void welcome(void);			//declaration for welcome function
void login(void);			//declaration for login function
void mainmenu(void);		//declaration for the menu function
void addbooks(void);		//declaration for the add function
void deleterecordofbooksissued(void);		//declaration for the delete function
void returnbooks(void);		//declaration for the edit function
void searchforbooks(void);		//declaration for search function
void issuebooks(void);		//declaration for issuing function
void viewrecordofbookissued(void);		//declaration for viewing bok list function
void visitorcanbuybook(void);		//declaration for visitorcanbuybook function
int  getdata();
int  checkid(int);
int t(void);

void issuerecord();			//declaration for issuing record

COORD coord = {0, 0}; 		//function to set coordinates to 0,0
COORD max_res,cursor_size;
void gotoxy (int x, int y)		//function that sets the cursor positiion for simply to move the cursor on your monitor screen wherever desired.
{
        coord.X = x; coord.Y = y;		//function to input X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();		//shows the processor clock time used since the beginning of an
											//implementation defined era (normally the beginning of the program).
    while (goal > clock());
}
FILE *fp,*ft,*fs;	//global files that can be accessed from anywhere in program

//list of global variable
int s;
char findbook;

struct meroDate
{
    int mm,dd,yy;
};
struct books
{
    int id;
    char stname[20];
    char name[20];
    char Writer[20];
    int quantity;
    float Amount;
    int bookno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books r;
int main()

{
	welcome();
      login();
      getch();
   return 0;

}

void welcome()	//function to display welcome screen
{
	gotoxy(4,6);
	printf("");		//printf is used to display the output by print the character, string, integer etc.
	gotoxy(1,10);
	 printf("\n\t\t                 ________________________________________\n");

     printf("\n\t\t\t                          WELCOME ");
     printf("\n\t\t\t                             To ");
     printf("\n\t\t\t                  LIBRARY MANAGEMENT SYSTEM ");
	gotoxy(32,15);


     printf("\n\t\t                 ________________________________________");
	sleep(3);
	system("cls");
	getch();		//it is used as a trick to hold the output screen live for a desired period of time by the user
	login();
	mainmenu();
}
char u[30],p[30];
void login()		//function that display login screen
{
	do{
	printf("\n\n\n\t\t\t ENTER THE USERNAME AND PASSWORD\n\n\n\n");
	printf("\n\t\t\tUSERNAME: ");
	scanf("%s",&u);						//scanf is used to read input such as character, string, numeric data from keyboard.
	printf("\n\t\t\tPASSWORD: ");
	scanf("%s",&p);
	if((strcmp(u,"hasan")==0) && (strcmp(p,"pass")==0))
	{
		printf("\n\n\t\t login successful");
		printf("\n\n\n\t\t\t\t Press any key for main menu.....");
		getch();
		mainmenu();
	}
	else
	{
		printf("\n\n\t\tInvalid username and password");
	}

	}while("number_of_try");

}

// function to display main menu
void mainmenu()
{

    system("cls");
	int i; //local variable for switch options
	gotoxy(20,3);
	printf(" MAIN MENU ");
	gotoxy(20,5);
	printf(" 1. Add Books   ");
	gotoxy(20,7);
	printf(" 2. Delete Record Of Books Issued");
	gotoxy(20,9);
	printf(" 3. Search For Books");
	gotoxy(20,11);
	printf(" 4. Issue Books");
	gotoxy(20,13);
	printf(" 5. View Record Of Book Issued");
	gotoxy(20,15);
	printf(" 6. Return Books");
	gotoxy(20,17);
	printf(" 7. Visitor Can Buy Books");
	gotoxy(20,18);
	t();
	gotoxy(20,19);
	printf("Enter your choice:");
	switch(getch())
	{
		case '1':
		addbooks();
		break;
	case '2':
		deleterecordofbooksissued();
		break;
		case '3':
		searchforbooks();
	    break;
	case '4':
		issuebooks();
	    break;
	    case '5':
		viewrecordofbookissued();
		break;
	    case '6':
		returnbooks();
		break;
	    case '7':
	    {
		system("cls");
		delay(3000);
		visitorcanbuybook();
	    }
	    default:
		{
		gotoxy(10,23);
		printf("\nWrong Entry!!");
		if(getch())
		mainmenu();
		}

    }
}
void addbooks(void)    //function to add books
{
	system("cls");
	int i;		//local variable for switch option
	gotoxy(20,5);
	printf("\tSELECT CATEGOIES");
	gotoxy(20,7);
	printf(" 1. C programming");
	gotoxy(20,9);
	printf(" 2. Data Structure ");
	gotoxy(20,11);
	printf(" 3. Operating System ");
	gotoxy(20,13);
	printf(" 4. Math ");
	gotoxy(20,15);
	printf(" 5. Physics ");
	gotoxy(20,17);
	printf(" 6. English");
	gotoxy(20,19);
	printf(" 7. Main menu");
	gotoxy(20,21);
	printf("Enter your choice:");
	scanf("%d",&s);
	if(s==7)

	mainmenu() ;
	system("cls");
	fp=fopen("Project.dat","ab+");
	if(getdata()==1)
	{
	r.cat=catagories[s-1];
	fseek(fp,0,SEEK_END);			//fseek sets the file position of the given offset
	fwrite(&r,sizeof(r),1,fp);		//size_r this is the unsigned integral type and is the result of the sizeof keyword.
	fclose(fp);
	gotoxy(21,14);
	printf("The record is sucessfully saved");
	gotoxy(21,15);
	printf("Save any more?(Y / N):");
	if(getch()=='n')
	    mainmenu();
	else
	    system("cls");
	    addbooks();
	}
}
void deleterecordofbooksissued()    //function that delete from file fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  	//cause infinite loop
    {
	system("cls");
	gotoxy(10,5);
	printf("Enter the Book ID to  delete:");
	scanf("%d",&d);
	fp=fopen("Project.dat","rb+");
	rewind(fp);
	while(fread(&r,sizeof(r),1,fp)==1)
	{
	    if(r.id==d)
	    {

		gotoxy(10,7);
		printf("The book record is available");
		gotoxy(10,8);
		printf("Book name is %s",r.name);
		gotoxy(10,9);
		printf("Book No. is %d",r.bookno);
		findbook='t';
	    }
	}
	if(findbook!='t')
	{
	    gotoxy(10,10);
	    printf("No record is found to delete the search");
	    if(getch())
	    mainmenu();
	}
	if(findbook=='t' )
	{
	    gotoxy(10,9);
	    printf("Do you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("temp.dat","wb+");   //for deleting temporary files
		rewind(fp);					//sets the file position to the beginning of the file of the given stream
		while(fread(&r,sizeof(r),1,fp)==1)
		{
		    if(r.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);			//sets current position of file
			fwrite(&r,sizeof(r),1,ft); 	  //write all items in temporary file except we want to delete
		    }
		}
		fclose(ft);
		fclose(fp);
		remove("Project.dat");
		rename("temp.dat","Project.dat"); 		//read all items from temporary file except we want to delete
		fp=fopen("Project.dat","rb+");
		if(findbook=='t')
		{
		    gotoxy(10,10);
		    printf("The record is sucessfully deleted");
		    gotoxy(10,11);
		    printf("Delete another record?(Y/N)");
		}
	    }
	else
	mainmenu();
	fflush(stdin);		//the fflush function causes any unwritten data for that stream to be delivered to the host environment to be written to the file,
	                	//so the behaviour is undefined
	another=getch();
	}
	}
    gotoxy(10,15);
    mainmenu();
}

void visitorcanbuybook()
{
    system("cls");
    int d;
    gotoxy(20,6);
    printf("Search Book What You Want To Buy ");
    gotoxy(20,10);
    printf(" 1. Search By ID");
    gotoxy(20,14);
    printf(" 2. Search By Name");
    gotoxy( 15,20);
    printf("Enter Your Choice");
    fp=fopen("Project.dat","rb+"); 		//open file in read mode
    rewind(fp);   		//sets the file position to the beginning of the file of the given stream
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    gotoxy(25,4);
	    printf("Search Books By Id ");
	    gotoxy(20,5);
	    printf("Enter the book id:");
	    scanf("%d",&d);
	    gotoxy(20,7);
	    printf("Searching........");
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(r.id==d)
		{
		    delay(2);
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf(" ID:%d",r.id);
		    gotoxy(20,10);
		    printf(" Name:%s",r.name);
		    gotoxy(20,11);
		    printf(" Writer:%s ",r.Writer);
		    gotoxy(20,12);
		    printf(" Quantity:%d ",r.quantity);
		    gotoxy(20,13);
		    printf(" Amount:Rs.%.2f",r.Amount);
		    gotoxy(20,14);
		    printf(" Book No:%d ",r.bookno);

		    findbook='t';
		}

	    }
	    if(findbook!='t')  		//it checks weather the condition is entered loop or not
	    {

	    gotoxy(22,9);
		printf("\rNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Confirm Your Order(Y/N)");
	    if(getch()=='y'){
            gotoxy(25,20);
	 printf("\r ** You Successfully purchase Book ** ");
	  }  else
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    gotoxy(25,4);
	    printf("Search Books By Name ");
	    gotoxy(20,5);
	    printf("Enter Book Name:");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(strcmp(r.name,(s))==0) 		//it checks weather r.name is equal to s or not
		{
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf(" ID:%d",r.id);
		    gotoxy(20,10);
		    printf(" Name:%s",r.name);
		    gotoxy(20,11);
		    printf(" Writer:%s",r.Writer);
		    gotoxy(20,12);
		    printf(" Quantity:%d",r.quantity);
		    gotoxy(20,13);
		    printf(" Amount:Rs.%.2f",r.Amount);
		    gotoxy(20,14);
		    printf(" Book No:%d ",r.bookno);

		    d++;
		}

	    }
	    if(d==0)
	    {

	    gotoxy(22,9);
		printf("\rNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchforbooks();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchforbooks();
    }
    fclose(fp);
}
void searchforbooks()	    //function that search items from file fp
{
    system("cls");
    int d;
    gotoxy(20,6);
    printf("Search Books ");
    gotoxy(20,10);
    printf(" 1. Search By ID");
    gotoxy(20,14);
    printf(" 2. Search By Name");
    gotoxy( 15,20);
    printf("Enter Your Choice");
    fp=fopen("Project.dat","rb+"); 		//open file in read mode
    rewind(fp);   		//sets the file position to the beginning of the file of the given stream
    switch(getch())
    {
	  case '1':
	{
	    system("cls");
	    gotoxy(25,4);
	    printf("Search Books By Id ");
	    gotoxy(20,5);
	    printf("Enter the book id:");
	    scanf("%d",&d);
	    gotoxy(20,7);
	    printf("Searching........");
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(r.id==d)
		{
		    delay(2);
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf(" ID:%d",r.id);
		    gotoxy(20,10);
		    printf(" Name:%s",r.name);
		    gotoxy(20,11);
		    printf(" Writer:%s ",r.Writer);
		    gotoxy(20,12);
		    printf(" Qantity:%d ",r.quantity);
		    gotoxy(20,13);
		    printf(" Amount:Rs.%.2f",r.Amount);
		    gotoxy(20,14);
		    printf(" Book No:%d ",r.bookno);

		    findbook='t';
		}

	    }
	    if(findbook!='t')  		//it checks weather the condition is entered loop or not
	    {

	    gotoxy(22,9);
		printf("\rNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchforbooks();
	    else
	    mainmenu();
	    break;
	}
	case '2':
	{
	    char s[15];
	    system("cls");
	    gotoxy(25,4);
	    printf("Search Books By Name ");
	    gotoxy(20,5);
	    printf("Enter Book Name:");
	    scanf("%s",s);
	    int d=0;
	    while(fread(&r,sizeof(r),1,fp)==1)
	    {
		if(strcmp(r.name,(s))==0) 		//it checks weather r.name is equal to s or not
		{
		    gotoxy(20,7);
		    printf("The Book is available");
		    gotoxy(20,9);
		    printf(" ID:%d",r.id);
		    gotoxy(20,10);
		    printf(" Name:%s",r.name);
		    gotoxy(20,11);
		    printf(" Writer:%s",r.Writer);
		    gotoxy(20,12);
		    printf(" Qantity:%d",r.quantity);
		    gotoxy(20,13);
		    printf(" Amount:Rs.%.2f",r.Amount);
		    gotoxy(20,14);
		    printf(" Book No:%d ",r.bookno);

		    d++;
		}

	    }
	    if(d==0)
	    {

	    gotoxy(22,9);
		printf("\rNo Record Found");
	    }
	    gotoxy(20,17);
	    printf("Try another search?(Y/N)");
	    if(getch()=='y')
	    searchforbooks();
	    else
	    mainmenu();
	    break;
	}
	default :
	getch();
	searchforbooks();
    }
    fclose(fp);
}
void issuebooks(void)  	//function for issuing books
{
    int t;		//local variable for switch option

    system("cls");
    gotoxy(10,3);
    printf("   ISSUE SECTION ");
    gotoxy(10,5);
    printf(" 1. Issue a Book");
    gotoxy(10,7);
    printf(" 2. View Issued Book");
    gotoxy(10,9);
    printf(" 3. Search Issued Book");
    gotoxy(10,11);
    printf(" 4. Remove Issued Book");
    gotoxy(10,14);
    printf("Enter a Choice:");
    switch(getch())
    {
	case '1':  //issue book
	{
		system("cls");
		int c=0;
		char another='y';
		while(another=='y')		//infinite loop
		{
			system("cls");
			gotoxy(15,4);
			printf(" Issue Book section ");
			gotoxy(10,6);
			printf("Enter the Book Id:");
			scanf("%d",&t);
			fp=fopen("Project.dat","rb");
			fs=fopen("Issue.dat","ab+");
			if(checkid(t)==0) 		//check weather the book is available in library or not
			{
			     gotoxy(10,8);
			     printf("The book record is available");
			     gotoxy(10,9);
			     printf("There are %d unissued books in library ",r.quantity);
			     gotoxy(10,10);
			     printf("The name of book is %s",r.name);
			     gotoxy(10,11);
			     printf("Enter student name:");
			     scanf("%s",r.stname);
			     gotoxy(10,12);
			     printf("Issued date=%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy);	//for current date
			     gotoxy(10,13);
			     printf("The BOOK of ID %d is issued",r.id);
			     r.duedate.dd=r.issued.dd+RETURNTIME;   		//for return date
			     r.duedate.mm=r.issued.mm;
			     r.duedate.yy=r.issued.yy;
			     if(r.duedate.dd>30)
			     {
				 r.duedate.mm+=r.duedate.dd/30;
				 r.duedate.dd-=30;

			     }
			     if(r.duedate.mm>12)
			     {
				r.duedate.yy+=r.duedate.mm/12;
				r.duedate.mm-=12;

			     }
			     gotoxy(10,14);
			     printf("To be return:%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
			     fseek(fs,sizeof(r),SEEK_END);		//end of the file
			     fwrite(&r,sizeof(r),1,fs);
			     fclose(fs);
			     c=1;
			}
			if(c==0)
			{
			gotoxy(10,11);
			printf("No record found");
			}
			gotoxy(10,15);
			printf("Issue any more(Y/N):");
			fflush(stdin);
			another=getche();
			fclose(fp);
		}

		break;
	}
	case '2':  	//case shows the issue books list
	{
		system("cls");
		int j=4;
		gotoxy(2,1);
		printf("                          Issued book list                               ");
		gotoxy(2,2);
		printf("STUDENT NAME    CATEGORY    ID    BOOK NAME    ISSUED DATE    RETURN DATE");
	       fs=fopen("Issue.dat","rb");
		while(fread(&r,sizeof(r),1,fs)==1)
		{

			gotoxy(2,j);
			printf("%s",r.stname);
			gotoxy(18,j);
			printf("%s",r.cat);
			gotoxy(30,j);
			printf("%d",r.id);
			gotoxy(36,j);
			printf("%s",r.name);
			gotoxy(51,j);
			printf("%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy );
			gotoxy(65,j);
			printf("%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
			gotoxy(50,25);
			//printf("Current date=%d-%d-%d",d.day,d.month,d.year);
			j++;

		}
		fclose(fs);
		gotoxy(1,25);
		returnfunc();
	}
	break;
	case '3':   //search issued books by id
	{
		system("cls");
		gotoxy(10,6);
		printf("Enter Book ID:");
		int p,c=0;
		char another='y';
		while(another=='y')
		{

			scanf("%d",&p);
			fs=fopen("Issue.dat","rb");
			while(fread(&r,sizeof(r),1,fs)==1)
			{
				if(r.id==p)
				{
					issuerecord();
					gotoxy(10,12);
					printf("Press any key.......");
					getch();
					issuerecord();
					c=1;
				}

			}
			fflush(stdin);
			fclose(fs);
			if(c==0)
			{
				gotoxy(10,8);
				printf("No Record Found");
			}
			gotoxy(10,13);
			printf("Try Another Search?(Y/N)");
			another=getch();
		}
	}
	break;
	case '4':  	//case remove issued books from list
	{
		system("cls");
		int b;
		FILE *fg;  	//delete for temporary file is declared
		char another='y';
		while(another=='y')
		{
			gotoxy(10,5);
			printf("Enter book id to remove:");
			scanf("%d",&b);
			fs=fopen("Issue.dat","rb+");
			while(fread(&r,sizeof(r),1,fs)==1)
			{
				if(r.id==b)
				{
					issuerecord();
					findbook='t';
				}
				if(findbook=='t')
				{
					gotoxy(10,12);
					printf("Do You Want to Remove it?(Y/N)");
					if(getch()=='y')
					{
						fg=fopen("record.dat","wb+");
						rewind(fs);
						while(fread(&r,sizeof(r),1,fs)==1)
						{
							if(r.id!=b)
							{
							fseek(fs,0,SEEK_CUR);
							fwrite(&r,sizeof(r),1,fg);
							}
						}
						fclose(fs);
						fclose(fg);
						remove("Issue.dat");
						rename("record.dat","Issue.dat");
						gotoxy(10,14);
						printf("The issued book is removed from list");

				       }

				}
				if(findbook!='t')
				{
					gotoxy(10,15);
					printf("No Record Found");
				}
			}
			gotoxy(10,16);
			printf("Delete any more?(Y/N)");
			another=getch();
		}
	}
	default:
	gotoxy(10,18);
	printf("\nWrong Entry!!");
    getch();
	issuebooks();
	break;
      }
      gotoxy(1,30);
      returnfunc();
}
void viewrecordofbookissued(void)  	//function for showing the list of books available in library
{
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("                              Book List                                   \n");
    gotoxy(2,2);
    printf(" CATEGORY     ID    BOOK NAME     WRITER       QTY     AMOUNT     BOOK NO ");
    j=4;
    fp=fopen("Project.dat","rb");
    while(fread(&r,sizeof(r),1,fp)==1)
    {
	gotoxy(3,j);
	printf("%s",r.cat);
	gotoxy(16,j);
	printf("%d",r.id);
	gotoxy(22,j);
	printf("%s",r.name);
	gotoxy(36,j);
	printf("%s",r.Writer);
	gotoxy(50,j);
	printf("%d",r.quantity);
	gotoxy(57,j);
	printf("%.2f",r.Amount);
	gotoxy(69,j);
	printf("%d",r.bookno);
	printf("\n\n");
	j++;
	i=i+r.quantity;
      }
      gotoxy(3,25);
      printf("Total Books =%d",i);
      fclose(fp);
      gotoxy(35,25);
      returnfunc();
}
void returnbooks(void)  //function edit information about book
{
	system("cls");
	int c=0;
	int d,e;
	gotoxy(20,4);
	printf(" Return Books Section");
	char another='y';
	while(another=='y')
	{
		system("cls");
		gotoxy(15,6);
		printf("Enter Book Id to be Returned:");
		scanf("%d",&d);
		fp=fopen("Project.dat","rb+");
		while(fread(&r,sizeof(r),1,fp)==1)
		{
			if(checkid(d)==0)
			{
				gotoxy(15,7);
				//printf("The book is available");
				gotoxy(15,8);
				printf("The Book ID:%d",r.id);
				gotoxy(15,9);
				printf("Enter return book name:");scanf("%s",r.name);
				gotoxy(15,10);
				printf("Enter Writer:");scanf("%s",r.Writer);
				gotoxy(15,11);
				printf("Enter quantity:");scanf("%d",&r.quantity);
				gotoxy(15,12);
				printf("Enter  amount:");scanf("%f",&r.Amount);
				gotoxy(15,13);
				printf("Enter  bookno:");scanf("%d",&r.bookno);
				gotoxy(15,14);
				printf("The record is returned");
				fseek(fp,ftell(fp)-sizeof(r),0);	//ftell returns the current file position of the given stream.
				fwrite(&r,sizeof(r),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,9);
				printf("No record found");
			}
		}
		gotoxy(15,16);
		printf("Edit another Record?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}
void returnfunc(void)
{
    {
	printf(" Press ENTER to return to main menu");
    }
    r:
    if(getch()==13) 	//allow only the use of enter
    mainmenu();
    else
    goto r;
}
int getdata()
{
	int t;
	gotoxy(20,3);
	printf("Enter the Information Below");
	gotoxy(21,5);
	printf("Category:");
	gotoxy(31,5);
	printf("%s",catagories[s-1]);
	gotoxy(21,6);
	printf("Book ID:\t");
	gotoxy(30,6);
	scanf("%d",&t);
	if(checkid(t) == 0)
	{
		gotoxy(21,13);
		printf("\nThe book id already exists\n");
		getch();
		mainmenu();
		return 0;
	}
	r.id=t;
	gotoxy(21,7);
	printf("Book Name:");
	scanf("%s",r.name);
	gotoxy(21,8);
	printf("Writer:");
	scanf("%s",r.Writer);
	gotoxy(21,9);
	printf("Quantity:");
	scanf("%d",&r.quantity);
	gotoxy(21,10);
	printf("Amount:");
	scanf("%f",&r.Amount);
	gotoxy(21,11);
	printf("Book No:");
	scanf("%d",&r.bookno);
	return 1;
}
int checkid(int t)  	//checks weather the book exist in library or not
{
	rewind(fp);
	while(fread(&r,sizeof(r),1,fp)==1)		//size_r this is the unsigned integral type and is the result of the sizeof keyword.
	if(r.id==t)
	return 0;  		//return 0 if book exist
      return 1; 	//return 1 if book not exist
}
int t(void) 	//for adding time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

void issuerecord()  	//function that displayed the book's information
{
		 system("cls");
		 gotoxy(10,8);
		 printf("The Book has taken by Mr. %s",r.stname);
		 gotoxy(10,9);
		 printf("Issued Date:%d-%d-%d",r.issued.dd,r.issued.mm,r.issued.yy);
		 gotoxy(10,10);
		 printf("Returning Date:%d-%d-%d",r.duedate.dd,r.duedate.mm,r.duedate.yy);
}
// End of program
