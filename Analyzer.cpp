#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;
std::ofstream out;

unsigned int idVar=0;

list<string> symbols;
list<int> index_symbols;
list<string>::iterator it;
vector<string> vecSymb;
vector<int> valVar;
vector<int> valOp;

//Writes each token on the text file "lexic.txt"
void writeFile(string token)
{
	out.open("lexic.txt", ios::app);
	if (token!="\n")
	{
		token.insert(0,"<");
		token.append(">");
	}
	out << token;
	out.close();
}

//Inserts each variable in symbol table
void insertTable(string token)
{
	string cadena;//String for storing variable's name
	bool exists=false;
	unsigned int id=0;//Int for assigning each variable an id
	for(it=symbols.begin();it!=symbols.end();it++)//Checks if variable exists in table symbol
	{
		id++;
		if(token.compare(*it)==0)
		{
			exists=true;
			break;
		}
	}
	cadena.assign("id_");
	if(!exists)//If the variable doesn't exists in table symbol, it adds it.
	{
		idVar++;
		index_symbols.push_back(idVar);
		symbols.push_back(token);
		out.open("SymbolTable.txt", ios::app);
		out << "id_" << idVar << "\t\t" << token << "\t\t" << 0 << endl;
		out.close();
		cadena.append(to_string(idVar));
		valVar.push_back(0);
	}
	else
	{
		cadena.append(to_string(id));//Assigns id number for symbol table
	}
	cadena.append(",");
	cadena.append(token);
	writeFile(cadena);//Adds token to "lexic.txt"
}

void itsType(string cadena)//Finds if it's a variable, number or neither
{
	unsigned int n;
	bool is_number=true;
	for (n=0; n<cadena.length();n++)//Checks if it's a number
	{
		if (!isdigit(cadena[n]))
		{
			is_number = false;
			break;
		}
	}
	if (is_number)//If it's a number, it writtes it on "lexic.txt"
	{
		cout << "Numeric";
		writeFile(cadena);
	}
	else
	{//If isn't a number, checks if it's a variable
		if (isalpha(cadena[0]))
		{
			cout << "Variable";
			insertTable(cadena);
		}
		else
		{
			cout << "Error; Input not recognized";
		}
	}
	cout << endl;
}

void cutLine(string cadena)//Separates each line of "archivo.txt" in tokens
{
	unsigned int n;//Int to run each line
	string token;//String to store each token
	for (n=0; n<cadena.length();n++)
	{
		if(isalnum(cadena[n]))//Finds if it's a variable, number or neither
		{
			token.append(cadena,n,1);
			if(!isalnum(cadena[n+1]))//Cuts string and verifies its type
			{
				cout << token << ": ";
				itsType(token);
				token.clear();//Empties string for next token
			}
		}
		else//Finds operator type
		{
			switch (cadena[n])
			{
				case '+':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=' || cadena[n+1]=='+')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '-':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=' || cadena[n+1]=='-')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '*':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=' || cadena[n+1]=='*')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '/':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '=':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '!':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '<':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				case '>':
					token.append(cadena,n,1);
					if (cadena[n+1]=='=')
					{
						n++;
						token.append(cadena,n,1);
					}
					cout << token << ": Operador" << endl;
					writeFile(token);
					token.clear();
					break;
				default:
					break;
			}
		}
	}
}

void openFile()//Abre el archivo del codigo en "archivo.txt"
{
	string line;
	ifstream myfile("archivo.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )//Checks each line
		{
			cutLine(line);//Cuts line to get each token
			line="\n";
			writeFile(line);//Writes lexic
			cout << endl;
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file" << endl; 
	}
}

void makeSymbol()//Creates file for table symbols
{
	ofstream new_file("SymbolTable.txt");
	if(new_file.is_open())
	{
		//new_file << "NULL\n";
	}
	else
	{
		cout << "Unable to open file";
	}
	cout << endl;
}

void makeFile()//Creates file "lexic.txt"
{
	ofstream new_file("lexic.txt");
	if(new_file.is_open())
	{
		openFile();
	}
	else
	{
		cout << "Unable to open file";
	}
	cout << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////
void makeTreeFile()//Creates one file to store tree in "Tree.txt"
{
	ofstream new_file("Tree.txt");
	if(new_file.is_open())
	{
		
	}
	else
	{
		cout << "Unable to open file";
	}
}

void inserTreeFile(string token)//Inserts operation order
{
	out.open("Tree.txt", ios::app);
	out << token;
	out.close();
}

void checkSyntax(string line)//Funcion para verificar la sintaxis
{
	bool error=false;//In case there's an error, ends operation.
	vector<string> listoken;//Token vector
	vector<string> operVect;//String vector for "syntax tree"
	string expresion;//String storing an individual operation
	unsigned int n=0, term=1, exp=1, op=1;
	while(!error && n<line.length())//Until end of file
	{
		//cout << line[n];
		if (line[n]=='<')//Separates in individual tokens y stores in token vector
		{
			n++;
			string tok;
			if (line[n]=='>')//If it's a '>'
			{
				cout << line[n];
				tok.append(line,n,1);
				n++;
			}
			if (line[n]=='i' && line[n+1]=='d' && line[n+2]=='_')//If it's a variable
			{
				while(line[n]!=',')
				{
					n++;
				}
				n++;
			}
			while(line[n]!='>')
			{
				tok.append(line,n,1);
				//cout << line[n];
				n++;
			}
			listoken.push_back(tok);
			//cout << "\ntoken: " << tok;
			//cout << endl;
		}
		n++;
	}
	if(!isalpha(listoken.at(0)[0]) || isalnum(listoken.at(1)[0]))//Verifies if the line follows the correct rule 'variable followed by asignation symbol'
	{
		error=true;
	}
	else
	{
		operVect.push_back(listoken.at(0));
		operVect.push_back(listoken.at(1));
		if (listoken.size()==3)
		{
			cout << "\n#Op_1= " << listoken.at(0) << " = " << listoken.at(2);
			expresion="\n#Op_1= "+listoken.at(0)+" = "+listoken.at(2);
			inserTreeFile(expresion);
		}
		else
		{
			n=2;
			while (n<listoken.size() && !error)//Starts the order '*' & '/'
			{
				if(listoken.at(n)[0]=='=')//Verifies there isn't a "=" in the line
				{
					error=true;
					break;
				}
				else
				{
					if(n>2)
					{
						if(!isalnum(listoken.at(n-1)[0]) && !isalnum(listoken.at(n)[0]))//Verifica que no existan dos operadores seguidos
						{
							error=true;
							break;
						}
						else
						{
							if(listoken.at(n)[0]=='*' || listoken.at(n)[0]=='/')//Si encuentra uno de los dos operadores, saca el valor anterior y se recorre uno adelante
							{
								operVect.pop_back();
								if(listoken.at(n-2)[0]=='*' || listoken.at(n-2)[0]=='/')//Verifica si existió un operador del mismo orden antes
								{
									expresion="\n#Op_"+to_string(op)+"= "+"#Op_"+to_string(op-1)+" "+listoken.at(n)+" "+listoken.at(n+1);
									operVect.push_back("#Op_"+to_string(op));
									inserTreeFile(expresion);
								}
								else
								{
									expresion="\n#Op_"+to_string(op)+"= "+listoken.at(n-1)+" "+listoken.at(n)+" "+listoken.at(n+1);
									operVect.push_back("#Op_"+to_string(op));
									inserTreeFile(expresion);
								}
								cout << expresion;
								op++;
								n++;
							}
							else
							{
								operVect.push_back(listoken.at(n));
							}
						}
					}
					else
					{
						operVect.push_back(listoken.at(n));
					}
				}
				n++;
			}
			//cout << "\nFirst scan: ";
			//for (n=0; n<operVect.size(); n++) cout << operVect.at(n) << " ";
			//Follows order: '+' & '-'
			n=2;
			while (n<operVect.size() && !error)
			{
				if(operVect.at(n)[0]=='+' || operVect.at(n)[0]=='-')
				{
					if(operVect.at(n-2)[0]=='+' || operVect.at(n-2)[0]=='-')
					{
						expresion="\n#Op_"+to_string(op)+"= "+"#Op_"+to_string(op-1)+" "+operVect.at(n)+" "+operVect.at(n+1);
						inserTreeFile(expresion);
					}
					else
					{
						expresion="\n#Op_"+to_string(op)+"= "+operVect.at(n-1)+" "+operVect.at(n)+" "+operVect.at(n+1);
						inserTreeFile(expresion);
					}
					cout << expresion;
					op++;
				}
				n++;
			}
			expresion="\n#Op_"+to_string(op)+"= "+operVect.at(0)+" "+operVect.at(1)+" "+"#Op_"+to_string(op-1);
			cout << expresion;
			inserTreeFile(expresion);
		}
	}
	cout << "\n";
	if (error)
	{
		cout  << "SYNTAX ERROR";
	}
	else
	{
		for (n=0; n<listoken.size(); n++) cout << listoken.at(n) << " ";
		cout << "CORRECT" << endl;
		/*int i=1;
		while (i<=op)//Inserts in "symbols" string each "Op"
		{
			symbols.push_back("#Op_"+to_string(i));
			i++;
		}*/
	}
}

void openLexic()//Opens "lexic.txt" and verifies syntax
{
	string line;
	ifstream myfile("lexic.txt");
	if (myfile.is_open())
	{
		makeTreeFile();
		while ( getline (myfile, line) )//Checks each line
		{
			checkSyntax(line);
			inserTreeFile("\n");
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file" << endl; 
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void cFileRes()
{
	ofstream new_file("Results.txt");
	if(new_file.is_open())
	{
		
	}
	else
	{
		cout << "Unable to open file";
	}
}

void meteVectorSymb()
{
	for(it=symbols.begin();it!=symbols.end();it++)//Inserts symbol table inside a vector
	{
		vecSymb.push_back(*it);
	}
}

//Realizes operations
void doOperation(string operation)
{
	cFileRes();
	int n=0;
	meteVectorSymb();
	if(operation!="")//Verifies the chain isn't empty
	{
		unsigned int n=0, id=0, i=0;
		int operand1=0, operand2=0, result=0;
		char oper;
		bool isNum=false;
		string ass,var1,var2,idOp;
		while (operation[n]!='=')//Gets asignation variable
		{
			ass.append(operation,n,1);
			n++;
		}
		cout << "Variable asignacion:" << ass << " ";
		n=n+2;//Pasa al siguiente token
		while(operation[n]!=' ')//Gets first token
		{
			var1.append(operation,n,1);
			n++;
		}
		cout << "Variable 1:" << var1;
		if (isdigit(var1[0]))//If it's a number
		{
			operand1=stoi(var1);
		}
		else
		{
			if(var1[0]=='#')//If it's a middle term
			{
				idOp.assign(var1.begin()+4,var1.end());
				operand1=valOp.at(stoi(idOp)-1);
			}
			else
			{
				if(isalpha(var1[0]))//If it's a variable
				{
					int i=0;
					for(it=symbols.begin();it!=symbols.end();it++)//Searchs which one belongs
					{
						if(var1.compare(*it)==0)
						{
							id=i;
							break;
						}
						i++;
					}
					operand1=valVar.at(id);
				}
			}
		}
		cout << "=" << operand1;
		n++;
		if (operation[n]!=' ')
		{
			oper=operation[n];
			n=n+2;
			while(n<operation.length())
			{
				var2.append(operation,n,1);
				n++;
			}
			cout << " Variable 2:" << var2;
			string var3=var2;
			if(isdigit(var2[0]))
			{
				operand2=stoi(var2);
			}
			else
			{
				if(var2[0]=='#')
				{
					idOp.assign(var2.begin()+4,var2.end());
					if (idOp=="0")
					{
						operand2=0;
					}
					else
					{
						operand2=valOp.at(stoi(idOp)-1);
					}
				}
				else
				{
					if(isalpha(var2[0]))
					{
						int i=0;
						for(it=symbols.begin();it!=symbols.end();it++)//Searchs which one belongs
						{
							if(var2.compare(*it)==0)
							{
								id=i;
								break;
							}
							i++;
						}
						operand2=valVar.at(i);
					}
				}
			}
			cout << "=" << operand2 << endl;
			switch (oper)//Executes the operations according symbol
			{
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				result = operand1 / operand2;
				break;
			case '=':
				result = operand2;
				valVar.at(id)=result;
				break;
			default:
				break;
			}
			cout << "Result:" << result << endl;
			valOp.push_back(result);
		}
	}
	else
	{
		valOp.clear();
		int i=0;
		for(it=symbols.begin();it!=symbols.end();it++)
		{
			cout << *it << "=" << valVar.at(i) << endl;
			i++;
		}
	}
}

void openTree()
{
	string line;
	ifstream myfile("Tree.txt");
	if (myfile.is_open())
	{
		while ( getline (myfile, line) )//Checks line per line
		{
			doOperation(line);
		}
		int i=0;
		for(it=symbols.begin();it!=symbols.end();it++)
		{
			cout << *it << "=" << valVar.at(i) << endl;
			i++;
		}
		myfile.close();
	}
	else
	{
		cout << "Unable to open file" << endl; 
	}
}

///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	makeSymbol();//Creates file "SymbolTable.txt"
	makeFile();//Creates "lexic.txt" and reads file input "archivo.txt"
	openLexic();//Starts syntax verification
	openTree();//Executes operations
	cout << endl;
	system("PAUSE");
	return 0;
}
