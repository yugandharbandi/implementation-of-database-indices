#include<bits/stdc++.h>
using namespace std;
unordered_map<int,string>h;
int calculate_sum_bitmap(){
	int sum=0;
	vector<int>v;
	v.push_back(200);v.push_back(400);v.push_back(204);v.push_back(878);v.push_back(548);v.push_back(45);
	fstream data_bitmap,final_bitmap;
	for(int i=0;i<v.size();i++){
		data_bitmap.open(h[v[i]]);
		int val1=0,count=0;
		string bv="";
		while(data_bitmap>>val1){
			if(val1>=0) bv+=to_string(val1);
			else{
			string name;
			data_bitmap>>name;
			data_bitmap.close();
			data_bitmap.open(name);
			}
		}
		data_bitmap.close();
		final_bitmap.open("bitmap_final_1.txt");
		int j=0;
		int val2;
		while(final_bitmap>>val2){
	
			if(val2<0){
				string name;
				final_bitmap>>name;
				final_bitmap.close();
				final_bitmap.open(name);
			}
			else{
			
				if(val2==bv[j++]-'0'&&val2==1) count++;
			}
		}
		final_bitmap.close();
		cout<<v[i]<<" "<<count<<endl;
	}
	return 0;
}
void calculate_sum_rowid(){
	int sum=0;
	vector<int>v;
	v.push_back(200);v.push_back(400);v.push_back(204);v.push_back(878);v.push_back(548);v.push_back(45);
	fstream data_bitmap,final_bitmap;
	final_bitmap.open("bitmap_final_1.txt");
	int j=0;
	int val2,rowid,val1,count=0;
	string final_bitvector="";
	while(final_bitmap>>val2){
		if(val2<0){
			string name;
			final_bitmap>>name;
			final_bitmap.close();
			final_bitmap.open(name);
		}
		else{
			final_bitvector+=to_string(val2);
		}
	}
	for(int i=0;i<v.size();i++){
		count=0;
		data_bitmap.open("rowid"+to_string(v[i])+"_"+to_string(1)+".txt");
		while(data_bitmap>>rowid>>val1){
			if(val1<0){
				string name;
				data_bitmap>>name;
				data_bitmap.close();
				data_bitmap.open(name);
			}
			else{
				if(final_bitvector[rowid-1]=='1')
					count++;
			}
		}
		data_bitmap.close();
		cout<<v[i]<<" "<<count<<endl;
	}	
}

void append_to_bitslice(vector<unsigned int>array_amount){
	ofstream outfile;
	for(int i=1;i<=16;i++){
		outfile.open("bitslice_"+to_string(i)+".txt",std::ios_base::app);
		for(int j=0;j<array_amount.size();j++){
			unsigned int val=array_amount[j];
			cout<<val<<" "<<i<<" ";
			if(val){
				val=val<<(32-i);
				val=val>>31;
			}
			cout<<val<<endl;
			outfile<<val<<endl;
		}
		outfile.close();	
	}
}

void create_bit_slice(){
	fstream infile;

	infile.open("data1.txt");
	unsigned int amount,rowid,id,type;
	string name;
	vector<unsigned int>array_amount;
	while(infile >>rowid>> id >> amount>>name>>type){
		if(type==-1){
			append_to_bitslice(array_amount);
			array_amount.clear();
			infile.close();
			//outfile.close();
			infile.open(name);
//			cout<<name<<endl;
//			if(!infile.is_open()) cout<<"Error"<<endl;
//			infile >>rowid>> id >> amount>>name>>type;
//			cout<<endl<<endl<<"opening2\n\n\n\n"<<id<<endl;
		}
		else{
			array_amount.push_back(amount);
		}
	}
	append_to_bitslice(array_amount);
}

int main()
{
	fstream infile;
	ofstream outfile,outfile2;
	

    int id, amount, type, rowid;
    string name;//200 400 204 878 548 45
    vector<int>v;
    int block_size=5,block_size2=5;
	v.push_back(200);v.push_back(400);v.push_back(204);v.push_back(878);v.push_back(548);v.push_back(45);
	for(int i=0;i<v.size();i++){
		infile.open("data1.txt");
		//cout<<v[i]<<endl;
		int itr=1,itr2=1;
		string f_name="bitmap"+to_string(v[i])+"_"+to_string(itr)+".txt";
		string f_name2="rowid"+to_string(v[i])+"_"+to_string(itr2)+".txt";
		outfile.open(f_name);
		outfile2.open(f_name2);
		int count=0,count2=0;
		while (infile >>rowid>> id >> amount>>name>>type)
		{
			if(type==-1){
				infile.close();
				infile.open(name);
			} 
			else{
				if(h[v[i]]==""){
					h[v[i]]=f_name;
					
				}
				int val=0;
				if(amount==v[i]){
					val=1;
					outfile2<<rowid<<" "<<id<<endl;
					count2++;
				}
				outfile<<val<<endl;
				count++;
				if(count>=block_size){
					f_name="bitmap"+to_string(v[i])+"_"+to_string(++itr)+".txt";
					outfile<<"-1"<<" "<<f_name<<endl;
					outfile.close();
					outfile.open(f_name);
					count=0;
				}
				if(count2>=block_size2){
					f_name2="rowid"+to_string(v[i])+"_"+to_string(++itr2)+".txt";
					outfile2<<"-1"<<" "<<f_name2<<endl;
					outfile2.close();
					outfile2.open(f_name2);
					count2=0;
				}
			}
		}
		infile.close();
		outfile.close();
		outfile2.close();
	}
	create_bit_slice();
    return 0;
}
