#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//for experiments 1a 2a 3a

int Block_Size_records = 300;
int Number_Of_Records = 1000000;
int rowid = 0;
int Theta = 1500;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed); 
uniform_int_distribution<int> dist(0,Theta);
/*int Block_Size_RowIDs = 1000;
int Block_Size_BitMap = 32000;
*/




string generate_customer_name(){
	char a = rand()%26 + 97;
	char b = rand()%26 + 97;
	char c = rand()%26 + 97;
	string s="";
	s = s + a + b + c;
	return s;
}



void Create_DiskBlocks(int Transaction_ID,vector<int>T_ID,int Sales_Amount,string Customer_Name,int Category,vector<int>Sales_Amount_Vector,int Number_Of_DiskBlocks_Records,int Number_Of_DiskBlocks_Records_at_last_block){

	ofstream outfile;

	for(int i = 0;i<=Number_Of_DiskBlocks_Records;i++){
		//Create the records and put them in to a block
		string f_name="Block_Number_for_records_"+to_string(i)+".txt";
		outfile.open(f_name);
		if(i!=Number_Of_DiskBlocks_Records){
			for(int j = 0;j<Block_Size_records;j++){
				Transaction_ID = T_ID[rowid];
				Sales_Amount = dist(gen);
				Sales_Amount_Vector.push_back(Sales_Amount);
				Customer_Name = generate_customer_name();
				Category = (rand()%1500) + 1;
				outfile<<rowid<<" "<<Transaction_ID<<" "<<Sales_Amount<<" "<<Customer_Name<<" "<<Category<<endl;
				rowid++;
			}
			string filename = "Block_Number_for_records_"+to_string(i+1)+".txt";
			outfile<<-1<<" "<<-1<<" "<<-1<<" "<<-1<<" "<<filename<<endl;
			outfile.close();
		}
		else{
			cout<<Number_Of_DiskBlocks_Records<<endl;
			for(int j = 0;j<Number_Of_DiskBlocks_Records_at_last_block;j++){
				Transaction_ID = T_ID[rowid];
				Sales_Amount = dist(gen);
				Sales_Amount_Vector.push_back(Sales_Amount);
				Customer_Name = generate_customer_name();
				Category = (rand()%1500) + 1;
				outfile<<rowid<<" "<<Transaction_ID<<" "<<Sales_Amount<<" "<<Customer_Name<<" "<<Category<<endl;
				rowid++;
			}
			outfile<<-1<<" "<<-1<<" "<<-1<<" "<<-1<<" "<<-1<<endl;
			outfile.close();
		}
	}

}









int main(){
	int Transaction_ID,Sales_Amount,Category;
	string Customer_Name;
	vector<int>T_ID;
	vector<int>Sales_Amount_Vector;
	int Number_Of_DiskBlocks_Records = (Number_Of_Records/Block_Size_records);
	int Number_Of_DiskBlocks_Records_at_last_block = (Number_Of_Records%Block_Size_records);
	int Block_Number = 0;


	srand(time(0)); 
	for(int i=0;i<Number_Of_Records;i++){
		T_ID.push_back(i);
	}
	shuffle(T_ID.begin(), T_ID.end(), default_random_engine(seed));
	Create_DiskBlocks(Transaction_ID,T_ID,Sales_Amount,Customer_Name,Category,Sales_Amount_Vector,Number_Of_DiskBlocks_Records,Number_Of_DiskBlocks_Records_at_last_block);


}
