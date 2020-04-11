class MyString
{
private:
	char *str; // Pointer to the char array that holds the string
	int strLength; // Variable to store the length of the string

public:
	// Default constructor to initialize the str to null.
	MyString();
	
	// Overloaded constructor (do deep copy)
	MyString(const char *);    
	
	// Copy constructor (do deep copy)
	MyString(const MyString&); 
	
	//deep copies the passed object (the str of passed object will be deep copied into the str of object that called this function)
	void assign(const MyString); 
	
	//overloaded assign function (it does the same job but the the argument passed is char const*)
	void assign(const char*);
	
	// Display the string on screen. If str is null display empty string.
	void display();

	
	// Returns the length (# of characters excluding the null terminator) of the str
	int getLength();
	
	//append the passed character string to the end of str. (If str of the object that called this function is null, then simply copy the passed character string to str)
	void append(char const*);
	
	//overloaded append method which takes the object of MyString instead of char*
	void append(const MyString&);
	
	//compareTo method simply compares the str with the character string passed as argument. 
	//if str and the passed character string are same, return 0.
	//If the character of str at the index, where the first mismatch occurred, is greater in ASCII value; then return 1 
	//else return -1.
	int compareTo(const char* );
	
	//overloaded compareTo function which does the same job but the argument passed is of type MyString
	int compareTo(const MyString);
	

	// Destructor
	~MyString();
	

};


