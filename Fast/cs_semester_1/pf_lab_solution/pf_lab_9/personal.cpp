bool is_unimodel(int array[],int size){
	int counter=0,diff,switching=0;
	bool inc=1, dec=0;
	while(counter <size-1){
		diff=array[counter+1]-array[counter];
		if(diff > 0){
			if(inc==0 && dec==1) {switching++;
			inc=1; dec=0;
			
			//cout << "increasing " << endl;
	
			}}
		//endif diff >0
		
		else{
			if(inc==1 && dec==0){ switching++;
			inc=0; dec=1;
			//cout << "decreasing " << endl;
			}}


		counter++;
		cout << switching << endl;
	}//endwhile
	if(switching <3) return true;
	else{return false;}
}
