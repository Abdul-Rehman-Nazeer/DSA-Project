#include <bits/stdc++.h>
#include<conio.h>
#define latter 26
#include<windows.h>
using namespace std;

class Node
{
	public:
		
	Node *next[latter];
	bool isWord;

	Node()
	{
		for (int i = 0; i < latter; i++)
		{
			next[i] = 0;
		}
		isWord = false;
	}
};

class Tree
{
	private:
		
	Node *root;
	unsigned long long size;
	int ind;
	int Sno;
	
	public:
		
	Tree() : root(0), size(0){};
	Tree(string str) : size(0)
	{
		size++;
		root = new Node();
		Node *temp = root;
		for (int i = 0; i < str.length(); i++)
		{
			int index = str[i] - 'a';
			if (temp->next[index] == 0)
			{
				temp->next[index] = new Node();
			}
			temp = temp->next[index];
		}
		temp->isWord = true;
	}
	
	void InsertInTree(string str)
	{
		size++;
		if (root == 0)
		{
			root = new Node();
		}
		
		Node *temp = root;
		for (int i = 0; i < str.length(); i++)
		{
			int index=0;
			if(str[i] >= 'a' && str[i] <= 'z')
			{
				index = str[i] - 'a';
			}
			else if(str[i] >= 'A' && str[i] <= 'Z')
			{
				index = str[i] - 'A';
			}
			if (temp->next[index] == 0)
			{
				temp->next[index] = new Node();
			}
			temp = temp->next[index];
		}
		temp->isWord = true;
	}

	unsigned long long getSize() const
	{
		return size;
	}
	
	bool case5(string str)
	{
		int j=0;
		int count=0;
		for(j=0; j<str.length()-1; j++)
		{
			if(str[j] == '*')
			{
				++count;
			}
			if(count == 1 && str[j] == '*')
			{
				ind = j;
			}
		}
		if(count == 2)
		{
			return true;
		}
		return false;
	}
	
	void search(string str, int cases)
	{
		if(root != 0)
		{
			int index, i=0, level=0;
			char arr[50] = { 0 };
			bool exist=true;
			Node *temp;
			temp = root;
			Sno = 0;
			while(1)
			{
				if(str[i] == '*')	//could be case 1, 3, 5
				{
					if(case5(str))	//for case 5
					{
						displayWords(temp,arr,str,level, 5);	//bonus case 5: abc*abc*abc
						if(Sno == 0)
						{
							cout<<"\nError: Word(s) not found!\n";
						}
						return;
					}
					break;
				}
				
				else if(str[i] == '.') // Case 4
				{
					displayWords(temp,arr,str,level, 4);
					if(Sno == 0)
					{
						cout<<"\nError: Word(s) not found!\n";
					}
					return;
				}
				
				else if(str[i] == '\0')
				{
					system("cls");
					cout<<"Invalid Formate\n";
					return;
				}
				
				if(str[i] >= 'a' && str[i] <= 'z')// || str[i] >= 'A' && str[i] <= 'Z')
				{
					arr[i] = str[i];
					
					if(str[i] >= 'a' && str[i] <= 'z')
					{
						index = str[i] - 'a';
					}			
					if(!temp->next[index])
					{
						exist = false;
						break;
					}
					temp = temp->next[index];
					level++;
					i++;
				}
				
				else
				{
					system("cls");
					cout<<"Invalid Formate\n";
					return;
				}
			}	// end while
			
			if(exist)
			{
				i++;
				if(str[i] == '\0') // case 1: abc*
				{
					displayWords(temp,arr,str,level, cases);
				}
				
				else if(str[i] >= 'a' && str[i] <= 'z')	// case 3: abc*abc
				{
					displayWords(temp,arr,str,level, 3);
				}
			}
			
			else
			{
				cout<<"\nError: Word(s) not found!";
			}
		}
	}
	
	void displayWords(Node *temp, char arr[], string str, int level, int cases)
	{
		if(temp->isWord != false)
		{
			arr[level] = '\0';
			++Sno;
			if(cases == 1)
			{
				cout << Sno << " " << arr;
				cout << "  " << level << endl;
			}
			
			else if(cases == 2)
			{
				reverseDisplay(arr, level);
			}
			
			else if(cases == 3)	//abc*abc
			{
				if(cmpCase3(arr, str))	
				{
					cout << Sno << " " << arr;
					cout << "  " << level << endl;
				}
				
				else
				{
					--Sno;
				}
			}
			
			else if(cases == 4)	//case 4: abc..f
			{
				if(cmpCase4(arr, str))
				{
					cout << Sno << " " << arr;
					cout << "  " << level << endl;
				}
				
				else
				{
					--Sno;
				}
			}
			
			else if(cases == 5)	// case 5: abc*abc*abc
			{
				if(cmpCase5(arr, str))
				{
					cout << Sno << " " << arr;
					cout << "  " << level << endl;
				}
				
				else
				{
					--Sno;
				}
			}
		}
		
		for (int i = 0; i < latter; i++)
		{
			if (temp->next[i])
			{
				arr[level] = i + 'a';
				displayWords(temp->next[i], arr, str, level + 1, cases);
			}
		}
	}
	
	bool cmpCase5(string arr, string str)	//Case 5: if input is abc*abc*abc
	{
		int i,j;
		for(i = str.length()-1, j = arr.length()-1; str[i] != '*'; i--, j--)
		{
			if(str[i] != arr[j])
			{
				return false;
			}
		}
		
		i--;
		for( ; j >= ind; j--)
		{
			if(str[i] == arr[j])
			{
				int k,l;
				for(k=i, l=j; str[k]!='*' && l >= ind; k--,l--)
				{
					if(str[k] != arr[l])
					{
						break;
					}
				}
				
				if(str[k] == '*')
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	bool cmpCase4(string arr, string str)	//Case 4: if string contain '.'
	{
		if(str.length() != arr.length())
		{
			return false;
		}
		
		else
		{
			for(int i = str.length()-1, j = arr.length()-1; str[i] != '.'; i--, j--)
			{
				if(str[i] != arr[j])
				{
					return false;
				}
			}
			return true;
		}
	}
	
	bool cmpCase3(string arr, string str)	//Case 3: if input is abc*abc
	{
		if(arr.length() < str.length())
		{
			return false;
		}
		
		for(int i = str.length()-1, j = arr.length()-1; str[i] != '*'; i--, j--)
		{
			if(str[i] != arr[j])
			{
				return false;
			}
		}
		
		return true;
	}
	
	void reverseDisplay(char arr[], int size)	//for Case 2 if input is *abc
	{
		cout << Sno << " ";
		for (int i=size-1; i>=0; i--) 
		{
			cout << arr[i];
		}
		cout << "  " << size << endl;
	}

	void print() //to print dictionary in O(n) times
	{
		char str[50] = { 0 };
		Node *temp = root;
		displayWords(temp, str, "", 0, 1);
	}
		
};

class EWords
{
	private:
		
	Tree t1,t2;	//t1 contain words in rigth order t2 contain word in reverse order
	string str;
	
	public:
		
	void input()
	{
		ifstream fin;
		fin.open("unsorted.txt");
		
		if(fin.is_open())
		{				
			while(!fin.eof())
			{
				fin>>str;			//reading word by word from file and storing in dynamic2D array
				t1.InsertInTree(str);
				reverse(str.begin(),str.end());
				t2.InsertInTree(str);
			}
			
			fin.close();
		}
		else
		{
			cout<<"\nError: File not found!";
		}
	}
	
	void searchWord()
	{
		while(1)
		{
			system("cls");
			cout<<"\t\t\t              INSTRUCTIONS\n\n";
			cout<<"\t\t\t****************************************\n";
			cout<<"\t\t\t* ENTER SMALL CASE ALPHABETS ONLY      *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* INPUT FORMATS:                       *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* 1) xyz*                              *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* 2) *Qrd                              *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* 3) xyz*Qrd                           *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* 4) xyz..Qrd                          *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* 5) xyz*Qrd*uvw                       *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* 0) HELP                              *"<<endl;
			cout<<"\t\t\t*                                      *"<<endl;
			cout<<"\t\t\t* PRESS \"-\" TO EXIT                    *"<<endl;
			cout<<"\t\t\t****************************************\n";
			cout<<"\nTOTAL NUMBER OF WORDS IN OUR DICTIONARY = "<<t1.getSize()<<endl<<endl;
			cout<<"Enter here : ";
			cin>>str;
			
			if(str[0] == '-')
			{
				break;
			}
			
			else if(str[0] == '*')	//case 2: *abc
			{
				reverse(str.begin(),str.end());
				t2.search(str, 2);
			}
			
			else if(str[0] == '0')	//help
			{
				system("cls");
				cout<<"NOTE\n";
				cout<<"there are total five input formats a user can enter, read discription below\n\n";
				cout<<"1:- ENTER SOME STARTING LETTERS OF YOUR WORD WITH (*) AT END\n";
				cout<<"2:- ENTER SOME ENDING LETTERS OF YOUR WORD WITH (*) AT FRONT\n";
				cout<<"3:- ENTER SOME STARTING AND ENDING LETTERS OF YOUR WORD WITH (*) IN BETWEEN\n";
				cout<<"4:- ENTER STARTING AND ENDING LETTERS OF YOUR WORD WITH (..) IN BETWEEN\n";
				cout<<"5:- ENTER SOME FIRST, LAST AND IN BETWEEN LETTERS OF YOUR WORD WITH (*)\n    IN BETWEEN\n";
			}
			
			else	//Case 1: abc* and Case 3: abc*abc and Case 4: ab..ef and Case 5: abc*abc*abc
			{
				t1.search(str, 1);
			}
			
			// press enter to search next
			cout<<"\nPRESS ENTER TO CONTINUE...\n";
			getch();
		}
	}
	
	void merge(string arr[], int l, int m, int r)
	{
	    int n1 = m - l + 1;
	    int n2 = r - m;
	    string L[n1], R[n2];
	    for (int i = 0; i < n1; i++)
	    {
	    	L[i] = arr[l + i];
		}
	        
	    for (int j = 0; j < n2; j++)
	    {
	    	R[j] = arr[m + 1 + j];
		}
	        
	    int i = 0;
	    int j = 0;
	    int k = l;
	 
	    while (i < n1 && j < n2)
		{
	        if (L[i] <= R[j]) 
			{
	            arr[k] = L[i];
	            i++;
	        }
	        
	        else 
			{
	            arr[k] = R[j];
	            j++;
	        }
	        k++;
	    }
	    
	    while (i < n1)
		{
	        arr[k] = L[i];
	        i++;
	        k++;
	    }
	    
	    while (j < n2) 
		{
	        arr[k] = R[j];
	        j++;
	        k++;
	    }
	}
	
	void mergeSort(string arr[],int l,int r)
	{
	    if(l>=r)
		{
	        return;
	    }
	    
	    int m = (l+r-1)/2;
	    mergeSort(arr,l,m);
	    mergeSort(arr,m+1,r);
	    merge(arr,l,m,r);
	}
	
	int fileWordCount(string hold)
	{
		start:
		ifstream fin;
		fin.open(hold.c_str());
		if (!fin)
		{
			cout<<"File Does Not Exist"<<endl;
			getch();
			goto start;
		}
		
		else
		{
			int x=0;
			string Input;
			while(!fin.eof())
			{
				fin>>Input;
				x++;
			}
			return x;
		}
	}
	
	void Sort()
	{
		int i=0;
	
		ifstream fin;
		string hold;
		
		string Input,temp;
		cin>>hold;
		int count=fileWordCount(hold);
		string data[count];
		fin.open(hold.c_str());
		
		while(!fin.eof())
		{
			fin>>Input;
			data[i]=Input;
			i++;
		}
		
		fin.close();
		cout<<"\nSORTING FILE ALPHABETICALLY .";
		int z=0;
		
		while(z<5)
		{
			Sleep(1000);
			cout<<".";
			z++;
		}
		
		mergeSort(data,0,count-1);
	
	    ofstream outfile;
	    outfile.open("Sorted.txt");
	    
		for(int i=0 ;i<count;i++)
		{
			outfile<<data[i]<<endl;
		}
		
		cout<<endl<<"\nFILE IS NOW SORTED"<<endl;
		cout<<"\nPRESS ANY KEY TO SEE MENU ";
		getch();
	}
};

int main()
{
	EWords e1;
	cout<<"\t\t\tWORD PUZZLE PROJECT\n\n\n";
	cout<<"ENTER NAME OF UNSORTED FILE : ";	//if wrong input of file name program doest work correctly
	e1.Sort();
	
	e1.input();
	e1.searchWord();

	return 0;
}



//jo b word search krna agar usky agy kuch remaining h to word k agy * laga dein gay like "god*"  output godly

//jo b word search krna agar usky peche kuch remaining h to word k peche * laga dein gay like "*odly"  output godly