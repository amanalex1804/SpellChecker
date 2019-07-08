#include<bits/stdc++.h>
using namespace std;

#define ll long long 

map<string,int>favourable;  // for priority in suggesting words
vector<string>words_suggested;    // store words that are suggested

// implementing concept of trie for spellchecking
struct trie{
	string word_ending;        // stores the word that'll end here
	trie *child[26];	
};


// new trie node 

trie *create(){
	trie *temp = new trie;
	temp->word_ending = "";
	for(int i=0;i<=25;++i) temp->child[i]=false;
	return temp;
}

// insertion of new word

void ins(trie *root,string s){
	
	for(int i=0;i<(int)s.size();++i){
		int x = (int)(s[i]-'a');
		if(!root->child[x]) root->child[x]=create();
		root = root->child[x];
	}
	root->word_ending = s;
	
}


// function to check whether the provided word exists or not

bool isExist(trie *root,string s){
	for(int i=0;i<(int)s.size();++i){
		int x = (int)(s[i]-'a');
		if(!root->child[x]) return false;   // not found
		root = root->child[x];
	}
	if(root->word_ending!=s) return false;  // checking
	return true;
}

// function to generate all strings from given root

void suggesting_word(trie *root){
	for(int i=0;i<=25;++i) 
	   if(root->child[i])
	   	suggesting_word(root->child[i]);
	
	if(root->word_ending!="") words_suggested.push_back(root->word_ending);   	
}

void suggestion(trie *root,string s,int idx =0){
	
	if(idx>=(int)s.size()) return suggesting_word(root);  // extra words apart from oriinal
	
	int x = (int)(s[idx]-'a');
	if(root->word_ending!="") words_suggested.push_back(root->word_ending);
	
	if(root->child[x]==NULL) return suggesting_word(root);  // mismatch
	else return suggestion(root->child[x],s,idx+1);
	
}
int main(){
	
	ifstream in("WordList.txt");  // text file of english words
	string word;
	
	trie *root = create(); 
	
	while(in){
		in>>word;
		ins(root,word);
		favourable[word]++;
	}
	in.close();
	
	cout<<"System Ready For Spell Check\n\n";
	
	while(1){
		
		cout<<"Enter The Word or EXIT : ";
		string s;cin>>s;
		if(s=="EXIT" or s=="exit") break;
		
		if(isExist(root,s)) {
			cout<<"You've Entered the Correct Word\n";
			favourable[s]++;
		}
		else{
			cout<<"Wrong Word\n";
			cout<<"Press 1 for Adding it to dictionary\n";
			cout<<"Press 2 for suggesting other words\n";
			int inp; cin>>inp;
			if(inp==1){
				ins(root,s);
				favourable[s]++;
				cout<<"Successfully Added\n";
			}else{
					
				words_suggested.clear();
				suggestion(root,s);
				int freq = 0;
				string most_favourable="";
				
				for(int i=0;i<(int)words_suggested.size();++i){
					if(freq<favourable[words_suggested[i]]){
						freq=favourable[words_suggested[i]];
						most_favourable = words_suggested[i];
						favourable[words_suggested[i]]++;
					}
				}
				cout<<"Suggested Word: "<<most_favourable<<"\n";
				
			}
			
			
			
		}
		
	}
	
	
	return 0;
}
