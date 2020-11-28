int partc(string S , int k){

	string low = "a";
	string high = "";
	int power=0;
	while( low.length() < S.length()) {

		high=low;

		for(int i=0;i<high.length();i++) {
			low.append(fundamental[(int)(high[i]-'a')]);
		}
		power+=1;
		// low = high;
		// high="";
	}

	string stringABA = high + low + high;
	string stringAA = high + high;

	int lps[S.length()];

	int first = KMPdo(S, stringABA, lps);

	if(first!=-1){
		int last = first + S.length();

		if(last < low.length()){
			return power;
		}

		else if(last < low.length() + high.length()) {
			return power+1;
		}
		else return power+2;
	}

	int second = KMPdo(S, stringAA, lps);

	if(second != -1){

		return power+3;

	}

	return -1;
}