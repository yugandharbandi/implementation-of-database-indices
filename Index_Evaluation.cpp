#include<iostream>
#include<bits/stdc++.h>
using namespace std;

/*
1.records diskfiles are named as Block_Number_for_records_"+to_string(i)+".txt";
2.Bitmap diskfiles are named as "Block_Number_for_BitMap_"+to_string(i)+"_"+to_string(j)+".txt";
3.Bitslice diskfiles are named as "Block_Number_for_Bitslice_"+to_string(i)+"_"+to_string(j)+".txt";
4.RowID diskfiles are named as "Block_Number_for_RowID_"+to_string(i)+"_"+to_string(j)+".txt";
*/
int Number_Of_Records = 1000000;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed); 
int Theta = 50;


void Evaluate_NOINDEX(bool BF[]){
	//bring each disk block and check each row in the diskblock
	//The starting diskblock address is Block_Number_for_records_0.txt
	unsigned int rowid,Transaction_ID,Sales_Amount,Category;
	string Customer_Name;
	string filename = "Block_Number_for_records_0.txt";
	int iterator = 0;
	fstream infile;
	int ReadDiskBlockCount = 0;
	int flag = 0;
	while(1){
		infile.open(filename);
		ReadDiskBlockCount++;
		string line;
		while (getline(infile,line))
		{
			istringstream iss(line);
			string value;
			vector<string>record;
  			while (iss >> value) {
  				record.push_back(value);
  			}
  			if(BF[iterator] == 1){
  				//read the value and add it to the sum
  			}

  			if(record[0] != "-1"){
  				iterator++;
  			}
  			else if(record[4] == "-1"){
  				//end of the all blocks bring newone
  				flag = 1;
  			}
  			else if(record[0] == "-1"){
  				//end of the all blocks bring newone
  				filename = record[4];
  			}		
		}
		infile.close();
		if(flag == 1){
			flag = 0;
			break;
		}
	}
	cout<<ReadDiskBlockCount<<endl;	
}



void Evaluate_BITMAP(bool BF[]){
	string filename = "Block_Number_for_BitMap_1_0.txt";
	int iterator = 0;
	fstream infile;
	int ReadDiskBlockCount = 0;
	int flag = 0;
	vector<string>hashmap;
	hashmap.push_back("NULL");
	for(int i=1;i<=Theta;i++){
		string value="";
		value = "Block_Number_for_BitMap_"+to_string(i)+"_0.txt";
		hashmap.push_back(value);
	}
	
	for(int i=1;i<=Theta;i++){
		filename = hashmap[i];
		//cout<<hashmap[i]<<endl;

		while(1){
			infile.open(filename);
			//cout<<filename<<endl;
			ReadDiskBlockCount++;
			string line;
			string value;
			while(infile>>value){
				if(value == "1" || value == "0"){
					if(value == "1"){
						if(BF[iterator]){
							//add to the sum
						}
					}
					iterator++;
				}
				if(value == "-1"){
					flag = 1;
				}
				else if((value != "0" && value != "1")){
					filename = value;
					//cout<<filename<<endl;
				}
			}
			infile.close();
			if(flag == 1){
				flag = 0;
				break;
			}
		}

	}

	cout<<ReadDiskBlockCount<<endl;
}






void Evaluate_ROWID(bool BF[]){
	string filename = "Block_Number_for_RowID_1_0.txt";
	int iterator = 0;
	fstream infile;
	int ReadDiskBlockCount = 0;
	int flag = 0;
	vector<string>hashmap;
	hashmap.push_back("NULL");
	for(int i=1;i<=Theta;i++){
		string value="";
		value = "Block_Number_for_RowID_"+to_string(i)+"_0.txt";
		hashmap.push_back(value);
	}

	for(unsigned int i=1;i<=Theta;i++){
		//for each theta bring the corresponding rowid blocks and check whether they are equal to 1 in BF or not
			iterator = 0;
			filename = hashmap[i];
			int count = 0;
			while(1){
				infile.open(filename);
				//cout<<filename<<endl;
				ReadDiskBlockCount++;
				string line;
				string value;
				
				while(infile>>value){
					if(value == "-1"){
						flag = 1;
					}
					else if(value[0] == 'B'){
						filename = value;
					}	
					else{
						stringstream geek(value);
						int x = 0;
						geek >> x;
						if(BF[x] == 1){
							//add to the sum
							count++;
						}
						else{

						}
						iterator++;
					}
				}
			
				infile.close();
				if(flag == 1){
					flag = 0;
					count = 0;
					break;
				}
			}
	}

	cout<<ReadDiskBlockCount<<endl;

}





void Evaluate_BITSLICE(){
	string filename = "Block_Number_for_Bitslice_1_0.txt";
	int iterator = 0;
	fstream infile;
	int ReadDiskBlockCount = 0;
	int flag = 0;
	vector<string>hashmap;
	hashmap.push_back("NULL");
	for(int i=1;i<=16;i++){
		string value="";
		value = "Block_Number_for_Bitslice_"+to_string(i)+"_0.txt";
		hashmap.push_back(value);
	}

	for(unsigned int i=1;i<=Theta;i++){
		bool BF[Number_Of_Records];
		memset(BF,true,sizeof(BF));
		
		for(int j=16;j>=1;j--){
			unsigned int power = (int)pow(2,j);
			int C = 1;
			if((power & i) == 0){
				C = 0;
			}
			iterator = 0;
			filename = hashmap[j];
			while(1){
				infile.open(filename);
				//cout<<filename<<endl;
				ReadDiskBlockCount++;
				string line;
				string value;
				
				while(infile>>value){
					if(value == "1" || value == "0"){
						if(value == "1"){
							if(C == 0){
								BF[iterator] = false;
							}
						}
						else{
							if(C == 1){
								BF[iterator] = false;
							}
						}
						iterator++;
					}
					if(value == "-1"){
						flag = 1;
					}
					else if((value != "0" && value != "1")){
						filename = value;
						//cout<<filename<<endl;
					}
				}
			
				infile.close();
				if(flag == 1){
					flag = 0;
					break;
				}
			}

		}

	}
cout<<ReadDiskBlockCount<<endl;
ofstream outfile;
string f_name="Experiment"+to_string(Theta)+".txt";
outfile.open(f_name);
outfile<<ReadDiskBlockCount<<endl;
outfile.close();
}







int main(){
	bool BF1[Number_Of_Records]; //Experiment 1b
	bool BF2[Number_Of_Records]; //Experiment 2b
	bool BF3[Number_Of_Records]; //Experiment 3b
	memset(BF1,false,sizeof(BF1));
	memset(BF2,false,sizeof(BF1));
	memset(BF3,false,sizeof(BF1));
	vector<int>T_ID;
	for(unsigned int i=0;i<Number_Of_Records;i++){
		T_ID.push_back(i);
	}

	//Experiment 1b; 
	shuffle(T_ID.begin(), T_ID.end(), default_random_engine(seed));
	for(int i=0;i<100000;i++){
		BF1[T_ID[i]] = 1;
	}
	Evaluate_NOINDEX(BF1);
	Evaluate_BITMAP(BF1);
	Evaluate_ROWID(BF1);
	Evaluate_BITSLICE();


	string f_name="Experiment"+to_string(Theta)+".txt";
	outfile.open(f_name);
	outfile<<endl<<endl;
	outfile.close();

	//Experiment 2b;
	shuffle(T_ID.begin(), T_ID.end(), default_random_engine(seed));
	for(int i=0;i<10000;i++){
		BF2[T_ID[i]] = 1;
	}
	Evaluate_NOINDEX(BF2);
	Evaluate_BITMAP(BF2);
	Evaluate_ROWID(BF2);
	Evaluate_BITSLICE(BF2);
	string f_name="Experiment"+to_string(Theta)+".txt";
	outfile.open(f_name);
	outfile<<endl<<endl;
	outfile.close();

	//Experiment 3b
	shuffle(T_ID.begin(), T_ID.end(), default_random_engine(seed));
	for(int i=0;i<100;i++){
		BF3[T_ID[i]] = 1;
	}
	Evaluate_NOINDEX(BF3);
	Evaluate_BITMAP(BF3);
	Evaluate_ROWID(BF3);
	Evaluate_BITSLICE(BF3);
	
}